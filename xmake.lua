set_project("VulkanApp")
set_version("0.1.0")

add_rules("mode.debug", "mode.release")

set_languages("cxx20")
add_defines("ENABLE_CPP20_MODULE=1")

set_targetdir("bin")

add_requires("glfw", "glm")

target("vulkan_app")
    set_kind("binary")
    add_files("src/main.cpp")
    
    add_packages("glfw", "glm")
    
    local vulkan_sdk = os.getenv("VULKAN_SDK")

    if vulkan_sdk then
        add_includedirs(path.join(vulkan_sdk, "Include"))
        add_linkdirs(path.join(vulkan_sdk, "Lib"))
        add_links("vulkan-1")

        print("Vulkan: Using SDK paths")
    else
        print("Vulkan: VULKAN_SDK not set, relying on system paths/package manager.")
    end

    -- Windows-specific links (use conditional linkage)
    if is_plat("windows") then
        add_links("gdi32")
    end