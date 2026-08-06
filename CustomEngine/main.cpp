#include <SDL3/SDL.h>
#include <GL/glew.h>
#include <glm/glm.hpp>
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
#include "ECS/Camera/Camera.h"
#include "ECS/Camera/CameraController.h"
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
#include "Animations/Animator.h"
#include "Editor/ConsoleWindow/ConsoleWindow.h"
#include "Editor/MenuBar/MenuBar.h"
#include "Editor/EditorStyle.h"
#include "Project/ProjectSettings.h"
#include "ECS/ComponentFactory.h"
#include <filesystem>
#include "Audio/AudioSource.h"
#include "Audio/AudioListener.h"
#include "Physics/BoxCollider.h"
#include "Physics/SphereCollider.h"
#include "Physics/RigidBody.h"
#include "Physics/PhysicsSystem.h"
#include "Time/Time.h"
#include "Systems/SystemManager.h"
#include "ECS/TransformSystem.h"
#include "ECS/Camera/CameraSystem.h"
#include "ECS/RenderSystem.h"
#include "Gizmos/GizmoRendererSystem.h"
#include "Selection/SelectionSystem.h"
#include "Audio/AudioSystem.h"
#include "Animations/AnimationSystem.h"
#include "Input/Input.h"
#include "Input/Mouse.h"
#include "Input/Keyboard.h"

using namespace glm;
using namespace std;

int main(int argc, char** argv) {
    // ---------------- SDL + OpenGL ----------------
    SDL_Init(SDL_INIT_VIDEO);

    // ---------------- Engine / project roots ----------------
    if (const char* enginePath = SDL_GetBasePath())
        Resources::SetEnginePath(std::filesystem::path(enginePath) / "EngineAssets");

    // A project folder can be passed on the command line; otherwise fall back
    // to the sample project that ships with the repository.
    std::filesystem::path projectFolder = (argc > 1)
        ? std::filesystem::path(argv[1])
        : std::filesystem::path(GUACAMOLE_DEFAULT_PROJECT);

    if (!ProjectSettings::Get().Load(projectFolder / "project.yaml"))
        ProjectSettings::Get().UseFolder(projectFolder);

    Resources::SetBasePath(ProjectSettings::Get().GetRootPath());
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

    // ---------------- Asset Importers ----------------
    AssetImporterRegistry::RegisterImporter(".fbx", new ModelImporter());
    AssetImporterRegistry::RegisterImporter(".obj", new ModelImporter());
    AssetImporterRegistry::RegisterImporter(".vert", new ShaderImporter());
    AssetImporterRegistry::RegisterImporter(".frag", new ShaderImporter());
    AssetImporterRegistry::RegisterImporter(".png", new Texture2DImporter());
    AssetImporterRegistry::RegisterImporter(".mp3", new AudioClipImporter());

    //Systems
    //SystemManager::AddSystem<InputSystem>();
    SystemManager::AddSystem<TransformSystem>();
    SystemManager::AddSystem<AnimationSystem>();
    SystemManager::AddSystem<PhysicsSystem>();
    SystemManager::AddSystem<CameraSystem>();
    SystemManager::AddSystem<SelectionSystem>();
    //SystemManager::AddSystem<ScriptingSystem>();
    SystemManager::AddSystem<AudioSystem>();
    SystemManager::AddSystem<GizmoRendererSystem>();
    SystemManager::AddSystem<RenderSystem>();
    //SystemManager::AddSystem<UISystem>();
    SystemManager::InitAllSystems();

    Time::Init();

    Input::AddDevice<Mouse>();
    Input::AddDevice<Keyboard>();
    Input::Init();

    //Shaders
    auto standardShader = Shader::FromFiles("engine://Shaders/BasicVertex.vert", "engine://Shaders/BasicFragment.frag");
    auto standardMaterial = make_shared<Material>(standardShader);

    auto skinnedShader = Shader::FromFiles("engine://Shaders/SkinnedVertex.vert", "engine://Shaders/BasicFragment.frag");

    // ---------------- Camera ----------------
    Entity* camera = Scene::Get().CreateEntity("MainCamera", vec3(0, 0, 4));
    Camera& cameraComp = camera->AddComponent<Camera>();
    Scene::Get().AddCamera(&cameraComp);
    camera->AddComponent<AudioListener>();
    camera->AddComponent<CameraController>();

    // ---------------- Scene primitives ----------------
    Entity* cube1 = Scene::Get().CreateEntity("Cube1", vec3(-1.2f, 0, 0));
    MeshFilter& cubeMesh = cube1->AddComponent<MeshFilter>(PrimitiveFactory::CreateCubePrimitive());
    MeshRenderer& cubeRenderer = cube1->AddComponent<MeshRenderer>();
    cubeRenderer.material = standardMaterial;
    // Collider first: PhysicsSystem only registers a RigidBody once its
    // Collider is present.
    cube1->AddComponent<BoxCollider>(false, glm::vec3(0.5f));
    cube1->AddComponent<RigidBody>(1.0f);

    Entity* sphereStatic = Scene::Get().CreateEntity("SphereStatic", vec3(-1.2f, -3, 0));
    MeshFilter& sphereStaticMesh = sphereStatic->AddComponent<MeshFilter>(PrimitiveFactory::CreateSpherePrimitive(0.5f));
    MeshRenderer& sphereStaticRenderer = sphereStatic->AddComponent<MeshRenderer>();
    sphereStaticRenderer.material = standardMaterial;
    sphereStatic->AddComponent<SphereCollider>(false, 0.5f);
    sphereStatic->AddComponent<RigidBody>(0);

    Entity* sphere1 = Scene::Get().CreateEntity("Sphere1", vec3(1, 1, -1));
    MeshFilter& sphereMesh = sphere1->AddComponent<MeshFilter>(PrimitiveFactory::CreateSpherePrimitive(0.8f));
    MeshRenderer& sphereRenderer = sphere1->AddComponent<MeshRenderer>();
    sphereRenderer.material = standardMaterial;

    Entity* light1 = Scene::Get().CreateEntity("Light1", vec3(-5, 0, 0));
    light1->AddComponent<PointLight>(vec3(1, 1, 1), 1.0f);

    Entity* light2 = Scene::Get().CreateEntity("Light2", vec3(5, 0, 3));
    light2->AddComponent<PointLight>(vec3(1, 0, 0), 1.0f);

    // ---------------- Scenegraph Editor / Inspector ----------------
    std::vector<std::unique_ptr<EditorWindow>> editorWindows;
    editorWindows.push_back(std::make_unique<ScenegraphEditor>(&Scene::Get().GetScenegraph()));
    editorWindows.push_back(std::make_unique<InspectorWindow>());
    editorWindows.push_back(std::make_unique<ConsoleWindow>());

    MenuBar menuBar(&editorWindows, window);

    // ---------------- Load model ----------------
    auto modelAsset = Resources::Load("Assets/Models/Miner.fbx");
    Entity* soldier = ModelInstantiator::Instantiate(modelAsset, "Miner");
    MeshRenderer& soldierRenderer = soldier->AddComponent<MeshRenderer>();
    auto albedo = Resources::Load("Assets/Models/MinerTexture.png");
    auto texture2D = std::dynamic_pointer_cast<Texture2D>(albedo);
    auto soldierMaterial = make_shared<Material>(texture2D, nullptr, standardShader);
    soldier->GetComponent<MeshRenderer>().material = soldierMaterial;

    // ---------------- Animated character ----------------
    auto generalAsset = Resources::Load("Assets/Models/GeneralAnimated.fbx");
    auto generalModel = std::dynamic_pointer_cast<Model>(generalAsset);
    Entity* general = ModelInstantiator::Instantiate(generalAsset, "General", vec3(-2.5f, -1.0f, 0));
    general->GetComponent<Transform>().scale = vec3(0.01f, 0.01f, 0.01f);

    auto generalAlbedo = std::dynamic_pointer_cast<Texture2D>(Resources::Load("Assets/Models/GeneralRed.png"));
    auto generalMaterial = make_shared<Material>(generalAlbedo, nullptr, skinnedShader);

    general->AddComponent<SkinnedMeshRenderer>().material = generalMaterial;
    general->AddComponent<Animator>(generalModel);

    //Extra meshes of the model live on child entities
    for (Entity* child : general->GetChildren())
        child->AddComponent<SkinnedMeshRenderer>().material = generalMaterial;

    // ---------------- ImGui ----------------
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    LoadEditorFonts(19.0f);
    ImGui_ImplSDL3_InitForOpenGL(window, glContext);
    ImGui_ImplOpenGL3_Init("#version 330");
    ApplyEditorStyle();

    auto audioClip = Resources::Load<AudioClip>("Assets/Audio/youwin.mp3");
    AudioSource& audioSource = cube1->AddComponent<AudioSource>();
    audioSource.clip = audioClip;
    //audioSource.Play();

    Scene::Get().Start();

    bool running = true;
    while (running) {
        SDL_Event e;

        while (SDL_PollEvent(&e)) {
            ImGui_ImplSDL3_ProcessEvent(&e);
            if (e.type == SDL_EVENT_QUIT) running = false;
            menuBar.HandleEvent(e);
            Input::SDL3_ProcessEvent(&e);
        }

        Input::Update();
        Time::Update();
        
        glClearColor(0.1f, 0.15f, 0.25f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        SystemManager::UpdateAllSystems();
        Scene::Get().Update();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL3_NewFrame();
        ImGui::NewFrame();

        menuBar.Draw();
        for (auto& window : editorWindows)
            window->Draw();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        SDL_GL_SwapWindow(window);
    }

    SystemManager::ShutdownAllSystems();

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL3_Shutdown();
    ImGui::DestroyContext();
    SDL_DestroyWindow(window);
    SDL_Quit();
}
