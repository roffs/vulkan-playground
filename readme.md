



### How to run manually

Install the required dependencies specified in the `xmake.lua` script:

```bash
xmake require
```

Generate `CMakeLists.txt` file from the xmake configuration:
```bash
xmake project -k cmake
```

Generate make build configuration given the CMakeLists.txt in the build directory
```bash
cmake -S . -B build
```

Compile the code: 
```bash
cmake --build build
```

Finally run the application: 
```
.\bin\Debug\vulkan_app.exe
```






