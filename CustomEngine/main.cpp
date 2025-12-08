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
#include "ECS/Transform.h"
#include "ECS/Camera.h"
#include "ScenegraphEditor/ScenegraphEditor.h"
#include <InspectorWindow/InspectorWindow.h>
#include "Importers/Resources.h"
#include "Importers/AssetImporterRegistry.h"
#include "Importers/ModelImporter.h"
#include "Importers/ModelInstantiator.h"
#include "Importers/ShaderImporter.h"

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

    // ---------------- Asset Importers ----------------
    AssetImporterRegistry::RegisterImporter(".fbx", new ModelImporter());
    AssetImporterRegistry::RegisterImporter(".obj", new ModelImporter());

    AssetImporterRegistry::RegisterImporter(".vert", new ShaderImporter());
    AssetImporterRegistry::RegisterImporter(".frag", new ShaderImporter());

    //Shaders
    auto standardShader = Shader::FromFiles("Assets/Shaders/BasicVertex.vert", "Assets/Shaders/BasicFragment.frag");
    auto standardMaterial = make_shared<Material>(standardShader);

    // ---------------- Camera ----------------
    Entity camera("MainCamera", vec3(0, 0, 3));
    camera.AddComponent<Camera>(vec3(0, 0, 0));

    // ---------------- Scene primitives ----------------
    Entity cube1("Cube1", vec3(-1.2f, 0, 0));
    MeshFilter& cubeMesh = cube1.AddComponent<MeshFilter>(PrimitiveFactory::CreateCubePrimitive());
    MeshRenderer& cubeRenderer = cube1.AddComponent<MeshRenderer>();
    cubeRenderer.material = standardMaterial;
    cubeMesh.InitGPU();
    cubeRenderer.Start();

    Entity sphere1("Sphere1", vec3(1, 1, -1));
    MeshFilter& sphereMesh = sphere1.AddComponent<MeshFilter>(PrimitiveFactory::CreateSpherePrimitive(0.8f));
    MeshRenderer& sphereRenderer = sphere1.AddComponent<MeshRenderer>();
    sphereRenderer.material = standardMaterial;

    sphereMesh.InitGPU();
    sphereRenderer.Start();

    Entity light1("Light1", vec3(0, 1, 5));
    light1.AddComponent<Light>(vec3(1, 1, 1), 0.5f);

    // ---------------- Scenegraph Editor / Inspector ----------------
    ScenegraphEditor sceneEditor(&Scene::Get().GetScenegraph());
    InspectorWindow inspectorWindow;

    // ---------------- Load model ----------------
    shared_ptr<Entity> bomb =  ModelInstantiator::Instantiate(Resources::Load("Assets/Models/Bomb.fbx"), "Bomb");
    bomb->GetComponent<MeshRenderer>().material = standardMaterial;

    // ---------------- ImGui ----------------
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui_ImplSDL3_InitForOpenGL(window, glContext);
    ImGui_ImplOpenGL3_Init("#version 330");
    ImGui::StyleColorsDark();

    bool running = true;
    while (running) {
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            ImGui_ImplSDL3_ProcessEvent(&e);
            if (e.type == SDL_EVENT_QUIT) running = false;
        }

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL3_NewFrame();
        ImGui::NewFrame();

        sceneEditor.Draw();
        inspectorWindow.Draw();

        ImGui::Render();

        glClearColor(0.1f, 0.15f, 0.25f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        Scene::Get().Update();

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        SDL_GL_SwapWindow(window);
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL3_Shutdown();
    ImGui::DestroyContext();
    SDL_DestroyWindow(window);
    SDL_Quit();
}
