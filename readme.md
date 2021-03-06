<h1 align=center>
    <img src="./design/logo/hive_logo_alpha.svg" type="text/svg" rel="svg" height=481>
</h1>

# Current Dev Environment
- Visual Studio Code
    - Plugins:
        | name | version
        |--|--|
        | C/C++ | 0.28.1|
        | C/C++ Clang Command Adapter | 0.2.3|
        | CMake | 0.0.17|
        | CodeLLDB | 1.5.2|
        | Native Debug | 0.25.0|
        | Visual Studio IntelliCode | 1.2.7|
        | WebAssembly | 1.3.1|

- Chrome + Chrome Debug Tools - For WASM

# Dependencies

| name | version
|:--|--|
| Cmake | 3.17.0 | 
| Emscripten / Emsdk |  1.39.9 |
| LLVM and Clang | 9 |
| Python | 3.6 |
| deno | 1.01 |
| CandleFW | 0.1 |

# Python
Python script needs access to the libclang.so or libclang.dll file. Update LD_LIBRARY_PATH to include the path to this library.

# Cmake

Current project command for wasm dev build:
```bash
shell:./build$ emcmake cmake -G Ninja -DCMAKE_BUILD_TYPE=Debug ../
```

Linux build with testing:
```bash
shell:./desktop_build$ cmake -G Ninja -DCMAKE_BUILD_TYPE=Debug ../
shell:./desktop_build$ ninja && ninja test
```
