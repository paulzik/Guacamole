#include "ContentBrowserWindow.h"
#include "EditorWindow.h"
#include "ECS/Entity.h"
#include "EditorMacro.h"
#include "imgui.h"
#include "Utilities/Debug/Debug.h"
#include <iostream>
#include "../../src/Project/ProjectSettings.h"


ContentBrowserWindow::ContentBrowserWindow(): EditorWindow("ContentBrowser")
{
}

void ContentBrowserWindow::Draw() {
    if (!BeginWindow()) return;

    
    std::cout << ProjectSettings::Get().GetRootPath() << std::endl;
    

    for (auto& directoryEntry : std::filesystem::directory_iterator(ProjectSettings::Get().GetRootPath()))
    {        
        

        
    }
    
    ImGui::Columns(5);
    ImGui::Button("test", {100,100});
    ImGui::Text("Folder Test");
    ImGui::NextColumn();

    ImGui::Button("test", { 100,100 });
    ImGui::Text("Folder Test");

    ImGui::Columns(1);


    ImGui::End();
}

REGISTER_EDITOR_WINDOW(ContentBrowserWindow)