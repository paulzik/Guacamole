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

using namespace glm;
using namespace std;

// ====================== SHADERS ========================
const char* vertexShaderSrc = R"(
#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aColor;
layout(location = 2) in vec3 aNormal;

out vec3 FragPos;
out vec3 Normal;
out vec3 vertexColor;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    FragPos = vec3(model * vec4(aPos, 1.0));
    Normal  = mat3(transpose(inverse(model))) * aNormal;
    vertexColor = aColor;

    gl_Position = projection * view * model * vec4(aPos, 1.0);
}
)";

const char* fragmentShaderSrc = R"(
#version 330 core
out vec4 FragColor;

in vec3 FragPos;
in vec3 Normal;
in vec3 vertexColor;

uniform vec3 lightPos;
uniform vec3 viewPos;

void main()
{
    // Ambient
    vec3 ambient = 0.1 * vertexColor;

    // Diffuse
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(normalize(Normal), lightDir), 0.0);
    vec3 diffuse = diff * vertexColor;

    // Specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, normalize(Normal));
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = vec3(0.3) * spec;

    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result, 1.0);
}
)";

// Shader compile helper
GLuint compileShader(GLenum type, const char* src) {
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &src, NULL);
    glCompileShader(shader);
    return shader;
}


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

    // Compile shaders
    GLuint vs = compileShader(GL_VERTEX_SHADER, vertexShaderSrc);
    GLuint fs = compileShader(GL_FRAGMENT_SHADER, fragmentShaderSrc);
    GLuint shader = glCreateProgram();
    glAttachShader(shader, vs);
    glAttachShader(shader, fs);
    glLinkProgram(shader);
    glUseProgram(shader);

    Entity cube1("Cube1", vec3(0, 0, 0));
    MeshFilter& mesh = cube1.AddComponent<MeshFilter>(PrimitiveFactory::CreateCubePrimitive());
    mesh.InitGPU();

    


    // Uniform locations
    GLuint modelLoc = glGetUniformLocation(shader, "model");
    GLuint viewLoc = glGetUniformLocation(shader, "view");
    GLuint projLoc = glGetUniformLocation(shader, "projection");
    GLuint lightPosLoc = glGetUniformLocation(shader, "lightPos");
    GLuint viewPosLoc = glGetUniformLocation(shader, "viewPos");

    glm::vec3 lightPos(2, 2, 2);
    glm::vec3 cameraPos(0, 0, 3);

    glUniform3fv(lightPosLoc, 1, glm::value_ptr(lightPos));
    glm::mat4 projection = glm::perspective(radians(45.0f), 1280.f / 720.f, 0.1f, 100.f);
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

    // ---------------- ImGui ----------------
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui_ImplSDL3_InitForOpenGL(window, glContext);
    ImGui_ImplOpenGL3_Init("#version 330");
    ImGui::StyleColorsDark();

    float scale = 1.0f;
    float posx = 0, posy = 0, posz = 0;
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
        ImGui::SliderFloat("Scale", &scale, 0.1f, 2.0f);
        ImGui::SliderFloat("PosX", &posx, -2.0f, 2.0f);
        ImGui::SliderFloat("PosY", &posy, -2.0f, 2.0f);
        ImGui::SliderFloat("PosZ", &posz, -2.0f, 2.0f);
        ImGui::End();

        ImGui::Begin("Light Position");
        ImGui::SliderFloat("Light X", &lightx, -5.0f, 5.0f);
        ImGui::SliderFloat("Light Y", &lighty, -5.0f, 5.0f);
        ImGui::SliderFloat("Light Z", &lightz, -5.0f, 5.0f);
        ImGui::End();

        ImGui::Render();

        glClearColor(0.1f, 0.15f, 0.25f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(shader);
        glm::mat4 view = glm::lookAt(cameraPos, vec3(0, 0, 0), vec3(0, 1, 0));
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, value_ptr(view));
        glUniform3fv(viewPosLoc, 1, value_ptr(cameraPos));

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, vec3(posx, posy, posz));
        model = glm::rotate(model, (float)SDL_GetTicks() * 0.001f, vec3(0, 1, 0));
        model = glm::scale(model, vec3(scale));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, value_ptr(model));

        lightPos = vec3(lightx, lighty, lightz);
        glUniform3fv(lightPosLoc, 1, value_ptr(lightPos));

        mesh.Draw();

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        SDL_GL_SwapWindow(window);
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL3_Shutdown();
    ImGui::DestroyContext();

    SDL_DestroyWindow(window);
    SDL_Quit();
}
