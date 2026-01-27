#include "Time.h"

void Time::Init() {
    previousTime = std::chrono::high_resolution_clock::now();
    deltaTime = 0.0f;
    totalTime = 0.0f;
}

void Time::Update() {
    auto currentTime = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> elapsed = currentTime - previousTime;
    deltaTime = elapsed.count();
    totalTime += deltaTime;
    previousTime = currentTime;

    fps = 1.0 / deltaTime;
}
