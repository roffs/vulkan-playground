add_rules("mode.debug", "mode.release")
set_languages("c++latest")
set_targetdir("bin")

add_requires("glfw", "glm")

target("vulkan_app")
    set_kind("binary")
    add_files("src/main.cpp")

    add_packages("glfw", "glm")

   local vulkan_sdk = os.getenv("VULKAN_SDK")

   if vulkan_sdk then
       add_includedirs(path.join(vulkan_sdk, "Include"))
       print("Using Vulkan Include path: " .. path.join(vulkan_sdk, "Include"))

       add_linkdirs(path.join(vulkan_sdk, "Lib"))
       print("Using Vulkan Library path: " .. path.join(vulkan_sdk, "Lib"))

       add_links("vulkan-1")
   else
       print("Error: VULKAN_SDK environment variable is not set. Please install the Vulkan SDK.")
   end
   add_links("gdi32")