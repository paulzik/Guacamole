#include <SDL3/SDL.h>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "imgui.h"
#include "imgui_impl_sdl3.h"
#include "imgui_impl_opengl3.h"
#include <iostream>
#include "ECS/Entity.h"
#include "ECS/Scene.h"
#include "ECS/MeshFilter.h"
#include "ECS/PrimitiveFactory.h"
#include "ECS/MeshRenderer.h"
#include "ECS/Transform.h"
#include "ECS/Camera.h"

using namespace glm;
using namespace std;

// Shader compile helper
GLuint compileShader(GLenum type, const char* src) {
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &src, NULL);
    glCompileShader(shader);
    return shader;
}
float rotAngle = 0;

int main() {

    SDL_Init(SDL_INIT_VIDEO);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    SDL_Window* window = SDL_CreateWindow("ImGui + Phong Cube", 1280, 720, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
    SDL_GLContext glContext = SDL_GL_CreateContext(window);
    glewInit();

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CCW);

    Entity camera("MainCamera", vec3(0, 0, 3));
    camera.AddComponent<Camera>(vec3(0,0,0));

    Entity cube1("Cube1", vec3(0, 0, 0));
    MeshFilter& mesh = cube1.AddComponent<MeshFilter>(PrimitiveFactory::CreateCubePrimitive());
    MeshRenderer& meshrend = cube1.AddComponent<MeshRenderer>();
    mesh.InitGPU();
    meshrend.Start();

    // Uniform locations
    GLuint modelLoc = glGetUniformLocation(meshrend.shaderProgram, "model");
    GLuint viewLoc = glGetUniformLocation(meshrend.shaderProgram, "view");
    GLuint projLoc = glGetUniformLocation(meshrend.shaderProgram, "projection");
    GLuint lightPosLoc = glGetUniformLocation(meshrend.shaderProgram, "lightPos");

    // ---------------- ImGui ----------------
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui_ImplSDL3_InitForOpenGL(window, glContext);
    ImGui_ImplOpenGL3_Init("#version 330");
    ImGui::StyleColorsDark();

    float posx = 0, posy = 0, posz = 0;
    float lookX = 0, lookY = 0, lookZ = 0;
    float lightx = 2, lighty = 2, lightz = 2;

    bool running = true;

    
    cout << "------" << endl;
    cube1.PrintComponents();
       

    while (running) {
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            ImGui_ImplSDL3_ProcessEvent(&e);
            if (e.type == SDL_EVENT_QUIT) running = false;
        }

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL3_NewFrame();
        ImGui::NewFrame();

        // --- ImGui sliders ---
        ImGui::Begin("Cube Transform");
        ImGui::SliderFloat("PosX", &posx, -2.0f, 2.0f);
        ImGui::SliderFloat("PosY", &posy, -2.0f, 2.0f);
        ImGui::SliderFloat("PosZ", &posz, -2.0f, 2.0f);
        ImGui::End();

        ImGui::Begin("Light Position");
        ImGui::SliderFloat("Light X", &lightx, -5.0f, 5.0f);
        ImGui::SliderFloat("Light Y", &lighty, -5.0f, 5.0f);
        ImGui::SliderFloat("Light Z", &lightz, -5.0f, 5.0f);
        ImGui::End();

        ImGui::Begin("Camera");
        ImGui::SliderFloat("CameraPosX", &lookX, -5.0f, 5.0f);
        ImGui::SliderFloat("CameraPosY", &lookY, -5.0f, 5.0f);
        ImGui::SliderFloat("CameraPosZ", &lookZ, -5.0f, 5.0f);
        ImGui::End();

        ImGui::Render();

        glClearColor(0.1f, 0.15f, 0.25f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        cube1.GetComponent<Transform>().setPosition(vec3(posx, posy, posz));
        camera.GetComponent<Camera>().setLookAtVector(vec3(lookX, lookY, lookZ));

        meshrend.Update();

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        SDL_GL_SwapWindow(window);
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL3_Shutdown();
    ImGui::DestroyContext();

    SDL_DestroyWindow(window);
    SDL_Quit();
}
