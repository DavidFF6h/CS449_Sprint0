#include <stdio.h>
#include <string.h>

#include  <GL/glew.h>
#include <GLFW/glfw3.h>

#include "ImGUI/imgui.h"
#include "ImGUI/imgui_impl_glfw.h"
#include "ImGUI/imgui_impl_opengl3.h"

// Window Size
const GLint WIDTH = 800, HEIGHT = 600;

// Specifies GUI content and layout
void GUI() {
	// Create a fixed window without title bar, moving, resizing, or collapsing
	ImGui::Begin("SOS Game Panel", NULL, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar);

	// Add GUI elements with spacing and separators
	ImGui::Text("Settings");
	ImGui::Separator();  // Adds a line under the "Settings" label

	// Checkbox section
	ImGui::Text("Enable Features");
	ImGui::Spacing();
	static bool checkbox_state1 = false;
	ImGui::Checkbox("Feature 1", &checkbox_state1);
	ImGui::Spacing();
	static bool checkbox_state2 = false;
	ImGui::Checkbox("Feature 2", &checkbox_state2);

	ImGui::Separator();  // Adds a horizontal line for separation

	// Slider section
	ImGui::Text("Adjustable Parameter");
	ImGui::Spacing();

	// Adding a slider for integer values
	static int int_slider_value = 10;  // Default integer slider value
	ImGui::SliderInt("Int Slider", &int_slider_value, 0, 100); // Slider with range 0 to 100

	ImGui::Separator();

	// Radio buttons section
	ImGui::Text("Options");
	ImGui::Spacing();  // Adds a bit of space
	static int selected_radio = 0;
	ImGui::RadioButton("Option 1", &selected_radio, 0);
	ImGui::RadioButton("Option 2", &selected_radio, 1);
	ImGui::RadioButton("Option 3", &selected_radio, 2);

	ImGui::End();
}

int main()
{
	// Initialize GLFW
	if (!glfwInit()) {	// Check for GLFW initialization success
		printf("GLFW initialization failed.\n");
		glfwTerminate();
		return 1;
	}

	// Setup GLFW window properties
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);	// OpenGL version 3.x
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);	// OpenGL version x.3
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);	// Core profile
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);	// Forward compatibility

	// Create GLFW window
	GLFWwindow* mainWindow = glfwCreateWindow(WIDTH, HEIGHT, "SOS Game", NULL, NULL);
	if (!mainWindow) {
		printf("GLFW window creation failed.");
		glfwTerminate();
		return 1;
	}

	// Get Buffer size info
	int bufferWidth, bufferHeight;
	glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);

	// Set context for GLEW
	glfwMakeContextCurrent(mainWindow);

	// Allow modern extension features
	glewExperimental = GL_TRUE;

	// Initialize GLEW and check for success
	if (glewInit() != GLEW_OK) {
		printf("GLEW initialization failed.\n");
		glfwDestroyWindow(mainWindow);
		glfwTerminate();
		return 1;
	}

	//Setup Viewport Size
	glViewport(0, 0, bufferWidth, bufferHeight);

	// Setup ImGui context
	ImGui::CreateContext();
	ImGui_ImplGlfw_InitForOpenGL(mainWindow, true);
	ImGui_ImplOpenGL3_Init("#version 130");

	//Window loop
	while (!glfwWindowShouldClose(mainWindow)) {
		// Get and handle user input
		glfwPollEvents();

		// Start the ImGui frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		// Get the current window size to calculate the left third
		int window_width, window_height;
		glfwGetWindowSize(mainWindow, &window_width, &window_height);
		float left_third_width = window_width * 1.0f / 3.0f;

		// Set the position and size for the ImGui window to the left third
		ImGui::SetNextWindowPos(ImVec2(0, 0)); // Top-left corner
		ImGui::SetNextWindowSize(ImVec2(left_third_width, window_height)); // Fixed to 1/3rd width and full height

		// Specifies GUI content and layout
		GUI();

		// Rendering
		ImGui::Render();

		// Clear Window
		glClearColor(0.13f, 0.17f, 0.21f, 1.0f);	// Set clear color
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear the window
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		// Swap buffers
		glfwSwapBuffers(mainWindow);
	}

	// Clean up and close the window
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	glfwDestroyWindow(mainWindow);
	glfwTerminate();
	return 0;
}