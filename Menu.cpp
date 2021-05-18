#include "menu.h"
#define 	GLFW_MOUSE_PASSTHROUGH   0x0002000D

GLFWwindow* window;
const char* glsl_version;
bool menuShow;

//Creates menu context
void Menu::Create()
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
}

void Menu::Initialize()
{
    menuShow = true;

    if (!glfwInit())
        std::cout << "failed to init!" << std::endl;

    glsl_version = "#version 130";

    glfwWindowHint(GLFW_FLOATING, true);
    glfwWindowHint(GLFW_RESIZABLE, false);
    glfwWindowHint(GLFW_MAXIMIZED, true);
    glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, true);
    glfwWindowHint(GLFW_MOUSE_PASSTHROUGH, true);

    GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    int width = glfwGetVideoMode(monitor)->width;
    int height = glfwGetVideoMode(monitor)->height;

    if (!monitor)
    {
        std::cout << "Failed to get monitor, defaults to 1080p" << std::endl;
    }
    window = glfwCreateWindow(width, height, "", NULL, NULL);

    if (!window)
    {
        glfwTerminate();
        std::cout << "failed to create window!" << std::endl;
    }
    glfwSetWindowAttrib(window, GLFW_DECORATED, false);
    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync

    if (gl3wInit() != 0)
    {
        fprintf(stderr, "Failed to initialize OpenGL loader!\n");
    }
    
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);
}

void Menu::Render()
{

    glfwPollEvents();

    // Start the Dear ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();


    if (menuShow)
    {



        ImGui::Button("test");


    }


    // Rendering
    ImGui::Render();
    int display_w, display_h;
    glfwGetFramebufferSize(window, &display_w, &display_h);
    glViewport(0, 0, display_w, display_h);
    glClear(GL_COLOR_BUFFER_BIT);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    glfwSwapBuffers(window);
}

void Menu::Shutdown()
{
    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();
}

void Menu::ToggleMenu()
{
    menuShow = !menuShow;
}