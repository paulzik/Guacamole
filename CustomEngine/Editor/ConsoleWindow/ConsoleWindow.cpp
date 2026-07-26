#include "ConsoleWindow.h"
#include "EditorWindow.h"
#include "ECS/Entity.h"
#include "EditorMacro.h"
#include "imgui.h"
#include "Utilities/Debug/Debug.h"

ConsoleWindow::ConsoleWindow(): EditorWindow("Console")
{
}

void ConsoleWindow::Draw() {
    if (!BeginWindow()) return;

    auto toggleButton = [](const char* icon, bool& state)
    {
        const bool active = state;
        if (active)
        {
            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.17f, 0.36f, 0.53f, 1.00f));
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.22f, 0.45f, 0.66f, 1.00f));
        }
        if (ImGui::Button(icon))
            state = !state;
        if (active)
            ImGui::PopStyleColor(2);
    };

    toggleButton("\xE2\x84\xB9", showLogs);
    ImGui::SameLine();
    toggleButton("\xE2\x9A\xA0", showWarnings);
    ImGui::SameLine();
    toggleButton("\xE2\x9C\x96", showErrors);

    ImGui::Separator();

    ImGui::BeginChild("ConsoleScroll");
    for (const LogEntry& log : Debug::GetLogs())
    {
        if (log.level == LogLevel::Info    && !showLogs)     continue;
        if (log.level == LogLevel::Warning && !showWarnings) continue;
        if (log.level == LogLevel::Error   && !showErrors)   continue;

        const char* icon =
            log.level == LogLevel::Warning ? "\xE2\x9A\xA0" :
            log.level == LogLevel::Error   ? "\xE2\x9C\x96" : "\xE2\x84\xB9";

        ImGui::Text("[%s] %s %s", log.timestamp.c_str(), icon, log.message.c_str());
    }
    ImGui::EndChild();

    ImGui::End();
}

REGISTER_EDITOR_WINDOW(ConsoleWindow)