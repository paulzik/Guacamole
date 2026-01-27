#pragma once
#include <chrono>

class Time{
public:
    static float DeltaTime() { return deltaTime; };
    static float TotalTime() { return totalTime; };
    static float FPS() { return fps; };

    static void Init();
    static void Update();

private:
    static inline float deltaTime = 0.0f;
    static inline float totalTime = 0.0f;

    static inline std::chrono::high_resolution_clock::time_point previousTime;
    static inline int fps;
};