#include <iostream>
#include <string>
#include <stdexcept>
#include <cstdlib>
#include <vector>

// Define GLFW_INCLUDE_VULKAN before including GLFW
// This tells GLFW to include Vulkan-specific headers
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

const int WIDTH = 800;
const int HEIGHT = 600;

class HelloTriangleApplication {
public:
    void run() {
        initWindow();
        initVulkan();
        mainLoop();
        cleanup();
    }

private:
    GLFWwindow* window = nullptr; // Initialize to nullptr
    VkInstance instance = VK_NULL_HANDLE; // Initialize to VK_NULL_HANDLE

    void initWindow() {
        std::cout << "Initializing GLFW window...\n";

        // 1. Initialize GLFW library
        if (!glfwInit()) {
            throw std::runtime_error("Failed to initialize GLFW!");
        }

        // 2. Configure window hints for Vulkan
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API); // Crucial: Tell GLFW not to create an OpenGL context
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);   // Disable resizing for simplicity

        // 3. Create the window
        window = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan Tutorial", nullptr, nullptr);

        // --- Error Check for Window Creation ---
        if (!window) {
            glfwTerminate();
            throw std::runtime_error("Error: Failed to create GLFW window!");
        }
        std::cout << "GLFW window created successfully.\n";
    }

    void initVulkan() {
        createInstance();
    }

    void createInstance() {
        std::cout << "Attempting to create Vulkan instance...\n";

        // Application Info
        VkApplicationInfo appInfo{};
        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        appInfo.pApplicationName = "Hello Triangle";
        appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.pEngineName = "No Engine";
        appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.apiVersion = VK_API_VERSION_1_0;

        // Instance Creation Info
        VkInstanceCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        createInfo.pApplicationInfo = &appInfo;

        // Get required extensions from GLFW (needed for windowing integration)
        uint32_t glfwExtensionCount = 0;
        const char** glfwExtensions;
        glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

        std::cout << "Required GLFW Extensions (" << glfwExtensionCount << "):\n";
        for (uint32_t i = 0; i < glfwExtensionCount; i++) {
            std::cout << "\t- " << glfwExtensions[i] << "\n";
        }

        createInfo.enabledExtensionCount = glfwExtensionCount;
        createInfo.ppEnabledExtensionNames = glfwExtensions;

        // No validation layers enabled for this minimal setup
        createInfo.enabledLayerCount = 0;

        // Attempt to create the Vulkan Instance
        VkResult result = vkCreateInstance(&createInfo, nullptr, &instance);

        if (result != VK_SUCCESS) {
            // Include the result code in the error message for better debugging
            std::string error_msg = "failed to create Vulkan instance! VkResult: " + std::to_string(result);
            throw std::runtime_error(error_msg);
        }

        std::cout << "Successfully created Vulkan Instance.\n";
    }

    void mainLoop() {
        std::cout << "Entering main loop (close the window to exit)...\n";
        while (!glfwWindowShouldClose(window)) {
            // Process all pending GLFW events (input, window closing, etc.)
            glfwPollEvents();
        }
    }

    void cleanup() {
        std::cout << "Cleaning up resources...\n";
        // Destroy the Vulkan instance if it was created
        if (instance != VK_NULL_HANDLE) {
            vkDestroyInstance(instance, nullptr);
        }

        // Destroy the GLFW window and terminate GLFW
        if (window != nullptr) {
            glfwDestroyWindow(window);
        }
        glfwTerminate();
        std::cout << "Cleanup complete. Application terminated.\n";
    }
};

int main() {
    HelloTriangleApplication app;

    try {
        app.run();
    } catch (const std::exception& e) {
        std::cerr << "\n--- FATAL ERROR ---\n";
        std::cerr << "Exception caught: " << e.what() << std::endl;
        std::cerr << "-------------------\n";
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}