#include <SDL3/SDL.h>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "imgui.h"
#include "imgui_impl_sdl3.h"
#include "imgui_impl_opengl3.h"
#include <iostream>
#include <memory>
#include <vector>
#include "ECS/Entity.h"
#include "ECS/Scene.h"
#include "ECS/MeshFilter.h"
#include "ECS/PrimitiveFactory.h"
#include "ECS/MeshRenderer.h"
#include "ECS/SkinnedMeshRenderer.h"
#include "ECS/Transform.h"
#include "ECS/Camera.h"
#include "ScenegraphEditor/ScenegraphEditor.h"
#include <InspectorWindow/InspectorWindow.h>
#include "Importers/Resources.h"
#include "Importers/AssetImporterRegistry.h"
#include "Importers/ModelImporter.h"
#include "Importers/ModelInstantiator.h"
#include "Importers/ShaderImporter.h"
#include "Importers/Texture2DImporter.h"
#include "Importers/AudioClipImporter.h"
#include "Lighting/PointLight.h"
#include "Lighting/DirectionalLight.h"
#include "Animations/Animator.h"
#include "Animations/Animation.h"
#include "Utilities/Debug/Debug.h"
#include "Editor/ConsoleWindow/ConsoleWindow.h"
#include "Audio/AudioSource.h"
#include "Audio/GuacAudio.h"
#include "Audio/AudioListener.h"
#include "Physics/BoxCollider.h"
#include "Physics/SphereCollider.h"
#include "Physics/RigidBody.h"
#include "Physics/PhysicsSystem.h"
#include "Time/Time.h"
#include "Systems/SystemManager.h"

using namespace glm;
using namespace std;

int main() {
    // ---------------- SDL + OpenGL ----------------
    SDL_Init(SDL_INIT_VIDEO);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    SDL_Window* window = SDL_CreateWindow("ImGui + Phong Cube", 1280, 720,
        SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
    SDL_GLContext glContext = SDL_GL_CreateContext(window);
    glewInit();

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CCW);

    //Physics
    SystemManager::AddSystem(std::make_unique<PhysicsSystem>());

    Time::Init();

    // ---------------- Asset Importers ----------------
    AssetImporterRegistry::RegisterImporter(".fbx", new ModelImporter());
    AssetImporterRegistry::RegisterImporter(".obj", new ModelImporter());
    AssetImporterRegistry::RegisterImporter(".vert", new ShaderImporter());
    AssetImporterRegistry::RegisterImporter(".frag", new ShaderImporter());
    AssetImporterRegistry::RegisterImporter(".png", new Texture2DImporter());
    AssetImporterRegistry::RegisterImporter(".mp3", new AudioClipImporter());

    //Shaders
    auto standardShader = Shader::FromFiles("Assets/Shaders/BasicVertex.vert", "Assets/Shaders/BasicFragment.frag");
    auto standardMaterial = make_shared<Material>(standardShader);

    auto skinnedShader = Shader::FromFiles("Assets/Shaders/SkinnedVertex.vert", "Assets/Shaders/BasicFragment.frag");

    // ---------------- Camera ----------------
    Entity camera("MainCamera", vec3(0, 0, 3));
    camera.AddComponent<Camera>(vec3(0, 0, 0));
    camera.AddComponent<AudioListener>();

    // ---------------- Scene primitives ----------------
    Entity cube1("Cube1", vec3(-1.2f, 0, 0));
    MeshFilter& cubeMesh = cube1.AddComponent<MeshFilter>(PrimitiveFactory::CreateCubePrimitive());
    MeshRenderer& cubeRenderer = cube1.AddComponent<MeshRenderer>();
    cubeRenderer.material = standardMaterial;
    cube1.AddComponent<RigidBody>(1.0f);
    cube1.AddComponent<BoxCollider>(false, 1.0f);

    Entity cube2("Cube2Static", vec3(-1.2f, -3, 0));
    MeshFilter& cubeMesh2 = cube2.AddComponent<MeshFilter>(PrimitiveFactory::CreateCubePrimitive());
    MeshRenderer& cubeRenderer2 = cube2.AddComponent<MeshRenderer>();
    cubeRenderer2.material = standardMaterial;
    cube2.AddComponent<RigidBody>(0);
    cube2.AddComponent<SphereCollider>(false, 1.0f);


    Entity sphere1("Sphere1", vec3(1, 1, -1));
    MeshFilter& sphereMesh = sphere1.AddComponent<MeshFilter>(PrimitiveFactory::CreateSpherePrimitive(0.8f));
    MeshRenderer& sphereRenderer = sphere1.AddComponent<MeshRenderer>();
    sphereRenderer.material = standardMaterial;

    Entity light1("Light1", vec3(-5, 0, 0));
    light1.AddComponent<PointLight>(vec3(1, 1, 1), 1.0f);

    Entity light2("Light2", vec3(5, 0, 3));
    light2.AddComponent<PointLight>(vec3(1, 0, 0), 1.0f);

    // ---------------- Scenegraph Editor / Inspector ----------------
    ScenegraphEditor sceneEditor(&Scene::Get().GetScenegraph());
    InspectorWindow inspectorWindow;
    ConsoleWindow consoleWindow;

    // ---------------- Load model ----------------
    auto modelAsset = Resources::Load("Assets/Models/GeneralAnimated.fbx");
    shared_ptr<Entity> soldier = ModelInstantiator::Instantiate(modelAsset, "GeneralAnimated");    
    SkinnedMeshRenderer& soldierRenderer = soldier->AddComponent<SkinnedMeshRenderer>();
    auto albedo = Resources::Load("Assets/Models/GeneralRed.png");
    auto texture2D = std::dynamic_pointer_cast<Texture2D>(albedo);
    auto soldierMaterial = make_shared<Material>(texture2D, nullptr, skinnedShader);
    soldier->GetComponent<SkinnedMeshRenderer>().material = soldierMaterial;

    auto modelPtr = std::dynamic_pointer_cast<Model>(modelAsset);
    Animator& animator = soldier->AddComponent<Animator>(modelPtr);

    // ---------------- ImGui ----------------
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui_ImplSDL3_InitForOpenGL(window, glContext);
    ImGui_ImplOpenGL3_Init("#version 330");
    ImGui::StyleColorsDark();

    //Init AudioEngine
    if (!GuacAudio::Init()) return -1;

    auto audioClip = Resources::Load<AudioClip>("Assets/Audio/youwin.mp3");
    AudioSource& audioSource = cube1.AddComponent<AudioSource>();
    audioSource.SetClip(audioClip);
    //audioSource.Play();

    Scene::Get().Start();

    bool running = true;
    while (running) {
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            ImGui_ImplSDL3_ProcessEvent(&e);
            if (e.type == SDL_EVENT_QUIT) running = false;
        }

        Time::Update();
        SystemManager::UpdateAllSystems();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL3_NewFrame();
        ImGui::NewFrame();

        sceneEditor.Draw();
        inspectorWindow.Draw();
        consoleWindow.Draw();

        ImGui::Render();

        glClearColor(0.1f, 0.15f, 0.25f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        Scene::Get().Update();

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        SDL_GL_SwapWindow(window);
    }

    SystemManager::ShutdownAllSystems();
    GuacAudio::Shutdown();

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL3_Shutdown();
    ImGui::DestroyContext();
    SDL_DestroyWindow(window);
    SDL_Quit();
}
