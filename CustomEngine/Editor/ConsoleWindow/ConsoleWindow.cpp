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

    const std::vector<LogEntry> logs = Debug::GetLogs();
    for(LogEntry log : logs)
    {
        ImVec4 logColor;
        if (log.level == LogLevel::Info) {
            logColor = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
            ImGui::TextColored(logColor, "Log:");
        }
        else if (log.level == LogLevel::Warning) {
            logColor = ImVec4(1.0f, 0.5f, 0.0f, 1.0f);

            ImGui::TextColored(ImVec4(logColor), "Warning:");
        }
        else if (log.level == LogLevel::Error) {
            logColor = ImVec4(1.0f, 0.0f, 0.0f, 1.0f);

            ImGui::TextColored(logColor, "Error:");
        }
        ImGui::SameLine(); ImGui::TextColored(logColor, log.message.c_str());
    }
    ImGui::End();
}

REGISTER_EDITOR_WINDOW(ConsoleWindow)