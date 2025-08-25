# C++ Template — Project Structure and CMake Review (for VS Code / Codespaces)

This document reviews the current repository structure and CMake usage, and proposes a modern, target‑based layout and configuration that supports:
- A main program composed of multiple files (`src/`)
- Multiple libraries (`lib/`)
- A suite of tests (`test/`)

It also highlights specific issues to fix and provides concrete, modern CMake and devcontainer recommendations for smooth use in VS Code and GitHub Codespaces.


## TL;DR — Key Findings and Recommended Changes

- CMake version and style
  - Use a higher minimum CMake (≥ 3.21) and target‑based, modern CMake practices.
  - Prefer `target_compile_features(... cxx_std_17)` (or 20/23) over global `CMAKE_CXX_STANDARD` where possible; if you keep the global, add `CMAKE_CXX_STANDARD_REQUIRED` and `CMAKE_CXX_EXTENSIONS`.
- Library naming and includes
  - Rename target `libtreasure` to `treasure` (avoid baking the `lib` prefix into the logical target name; the platform adds it as needed).
  - Export include paths from the library via `target_include_directories(treasure PUBLIC ...)`; consumers should not use relative includes like `"../lib/treasure.h"`.
  - Consider a public `include/` folder for headers consumed by executables and tests.
- Tests and Catch2
  - Don’t mix `Catch2::Catch2WithMain` with a `test_main.cpp` that defines `CATCH_CONFIG_MAIN` (this causes multiple `main` definitions). Choose one.
  - `include(Catch)` is wrong for Catch2 v3; use `include(Catch2)` with the v3 package and `catch_discover_tests`.
  - Prefer pulling Catch2 with `FetchContent` or CPM.cmake so tests work out‑of‑the‑box in Codespaces.
- File name typo (build‑breaking): `lib/CmakeLists.txt` should be `lib/CMakeLists.txt` (case matters on Linux).
- Custom run target
  - Fix the typo `DEPENDS ${EXEC_NAME}iha`; use `$<TARGET_FILE:...>` instead of hardcoding runtime paths.
- Warnings and Werror
  - Centralize warnings in a reusable function/INTERFACE target and make `-Werror` opt‑in (use a CMake option). Avoid hard‑coding GCC/Clang flags without compiler guards.
- Devcontainer / Codespaces
  - Ensure compilers (gcc/clang), CMake, Ninja, and debuggers are available. Add VS Code extension recommendations. Consider CMakePresets.json to streamline configure/build/test.


## Target Structure (Proposed)

```
/                   # repo root
├─ CMakeLists.txt   # top-level, minimal, target-based
├─ CMakePresets.json# configure/build/test presets (VS Code friendly)
├─ cmake/           # cmake modules (e.g., FetchContent helpers)
├─ include/
│  └─ treasure/
│     └─ treasure.h # public headers consumed by apps/tests
├─ lib/
│  └─ treasure/
│     ├─ CMakeLists.txt
│     └─ treasure.cpp
├─ src/
│  ├─ CMakeLists.txt
│  ├─ main.cpp      # or multiple executables (p2, p5, etc.)
│  └─ ...           # additional translation units
├─ test/
│  ├─ CMakeLists.txt
│  ├─ test_main.cpp # only if NOT using Catch2WithMain
│  └─ treasure_tests.cpp
└─ .devcontainer/
   ├─ devcontainer.json
   └─ Dockerfile     # optional if using a base image/features
```

Notes:
- Public headers live in `include/` and are exported by the library as PUBLIC include directories.
- Each library gets its own subfolder under `lib/` with its own `CMakeLists.txt`.
- Executables in `src/` consume libraries via `target_link_libraries()` and do not include headers via relative paths.


## Modern CMake Blueprint (What “Good” Looks Like)

Top-level `CMakeLists.txt` (essentials):

- Require a recent CMake, define project and languages.
- Enable compile_commands.json for tooling (`clangd`, etc.).
- Add subdirectories for libraries, apps, and tests.

Example (conceptual):

```
cmake_minimum_required(VERSION 3.21)
project(<project_name> VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Optionally enforce standard globally
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_subdirectory(lib)
add_subdirectory(src)
add_subdirectory(test)
```

Library `lib/treasure/CMakeLists.txt`:

- Target name should be logical (without `lib` prefix).
- Export include directories as PUBLIC so consumers inherit them.
- Put warnings behind compiler checks and/or an option.

```
add_library(treasure STATIC
  treasure.cpp
)

# Public headers for consumers
target_include_directories(treasure
  PUBLIC
    ${PROJECT_SOURCE_DIR}/include
)

# Prefer features for standard selection
target_compile_features(treasure PUBLIC cxx_std_17)

# Example warnings (guarded)
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
  target_compile_options(treasure PRIVATE -Wall -Wextra -pedantic)
endif()
```

Executables in `src/CMakeLists.txt`:

- Add one or more executables, link to libraries, and avoid hardcoding output paths.
- If you want handy run targets, use generator expressions for the binary path.

```
add_executable(p5
  problem5.cpp
  # more .cpp files as needed
)

# Consumers just link the library and get its includes transitively
target_link_libraries(p5 PRIVATE treasure)

# Optional "run" target
add_custom_target(run_p5
  COMMAND $<TARGET_FILE:p5>
  DEPENDS p5
  COMMENT "Running p5"
)
```

Tests in `test/CMakeLists.txt` (Catch2 v3):

- Don’t define your own `main` if you link `Catch2::Catch2WithMain`.
- Use `FetchContent` (or CPM.cmake) to pull Catch2 in Codespaces; otherwise `find_package(Catch2 3 REQUIRED)` requires it to be preinstalled in the image.

```
include(FetchContent)
FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG v3.6.0
)
FetchContent_MakeAvailable(Catch2)

add_executable(${PROJECT_NAME}_tests
  treasure_tests.cpp
  # omit test_main.cpp if linking WithMain
)

target_link_libraries(${PROJECT_NAME}_tests PRIVATE
  treasure
  Catch2::Catch2WithMain
)

include(Catch2)
catch_discover_tests(${PROJECT_NAME}_tests)
```


## Specific Issues in the Current Repo (What to Change)

1) File names and paths
- `lib/CmakeLists.txt` → must be `lib/CMakeLists.txt` (case sensitive on Linux).

2) Top-level CMake
- `cmake_minimum_required(VERSION 3.9)` → raise to ≥ 3.21 for modern features and smoother VS Code/Codespaces integration.
- `project(hw5 CXX)` → name should match the actual project; consider `project(<your_name> VERSION 0.1.0 LANGUAGES CXX)`.
- If you keep `CMAKE_CXX_STANDARD`, also set `CMAKE_CXX_STANDARD_REQUIRED ON` and `CMAKE_CXX_EXTENSIONS OFF`.
- Remove unused `INCLUDE_DIR` (there’s no `include/` yet) or add an `include/` directory and use it.
- Consider separate output dirs (`bin/` for executables, `lib/` for archives) or let defaults stand; avoid forcing all outputs to a single `bin/` folder unless you have a reason.

3) Libraries (`lib/`)
- Target name `libtreasure` → rename to `treasure` (avoid double `liblibtreasure.a`).
- Export include directories with `PUBLIC` so `src/` and `test/` stop using relative includes. If headers are meant for consumers, move them under `include/`.
- Constrain warnings to compilers that support them (GNU/Clang) and make `-Werror` opt‑in with a CMake option (e.g., `-DENABLE_WERROR=ON`).

4) Executables (`src/`)
- `add_custom_target(run_${EXEC_NAME})` has a typo: `DEPENDS ${EXEC_NAME}iha`. Remove the stray `iha` and use `$<TARGET_FILE:${EXEC_NAME}>` instead of hardcoding the runtime dir.
- For multi‑file programs, list all `.cpp` sources in the `add_executable(...)` call (or use `target_sources`).

5) Tests (`test/`)
- Do not set `cmake_minimum_required()` in a subdirectory at a lower version than the root (root is 3.9, test sets 3.5). Remove the subdir call and rely on the top‑level.
- `include(Catch)` is wrong for Catch2 v3 — use `include(Catch2)`.
- Don’t combine `test_main.cpp` (with `CATCH_CONFIG_MAIN`) with `Catch2::Catch2WithMain`. Choose one approach:
  - EITHER: keep `test_main.cpp` and link `Catch2::Catch2` (no main in the lib),
  - OR: delete `test_main.cpp` and link `Catch2::Catch2WithMain`.
- Prefer vendoring Catch2 via `FetchContent` so Codespaces builds “just work” without extra package installs.
- Replace relative include `"../lib/treasure.h"` with `#include "treasure.h"` and rely on the library’s PUBLIC include dirs.

6) Tooling and hygiene
- Consider adding `CMakePresets.json` (configure/build/test presets) — VS Code’s CMake Tools integrates with these and makes Codespaces frictionless.
- Optionally integrate `clang-tidy`, `clang-format`, sanitizers (ASan/UBSan), and coverage as opt‑in CMake options.
- `tasks.py` rename helper currently tries to edit `f"{proj_name}/CMakeLists.txt"` which won’t exist; if you keep this script, fix it to target the repo root and update all subordinate `CMakeLists.txt`.


## VS Code / Codespaces Recommendations

- Devcontainer (`.devcontainer/devcontainer.json`)
  - Ensure compilers and tools: gcc, clang, CMake, Ninja, gdb/lldb. The current file adds a CMake feature but not compilers/debuggers explicitly.
  - Add VS Code extension recommendations under `customizations.vscode.extensions`:
    - `ms-vscode.cpptools-extension-pack`
    - `ms-vscode.cmake-tools`
    - Optionally: `llvm-vs-code-extensions.vscode-clangd`, `ms-vscode.cpptools-themes`
  - Optional `postCreateCommand` to configure once using presets (e.g., `cmake --preset default`).
- CMake presets
  - Add a simple `CMakePresets.json` with `configurePresets` (generator: Ninja), `buildPresets`, and `testPresets`. VS Code will pick this up automatically.
- Don’t rely on a VS Code task that directly calls `clang` on “active file” for a CMake project; let CMake Tools manage builds.


## Example: Minimal Presets (Conceptual)

```
{
  "version": 5,
  "configurePresets": [
    {
      "name": "default",
      "generator": "Ninja",
      "binaryDir": "${sourceDir}/build",
      "cacheVariables": {
        "CMAKE_BUILD_TYPE": "Debug"
      }
    }
  ],
  "buildPresets": [
    { "name": "default", "configurePreset": "default" }
  ],
  "testPresets": [
    { "name": "default", "configurePreset": "default" }
  ]
}
```


## How This Meets the Goals

- Main program with multiple files: `src/` contains one or more executables that link to libraries; additional `.cpp` files are simply added to the `add_executable` call or via `target_sources`.
- Multiple libraries: each sublibrary lives under `lib/<name>/` with its own `CMakeLists.txt`, exported headers in `include/` if public.
- Test suite: `test/` uses Catch2 v3 pulled via `FetchContent`, linking to the libraries under test, with auto discovery via `catch_discover_tests`.
- Codespaces friendly: Devcontainer has the right tools, VS Code picks up `CMakePresets.json`, and you can configure/build/test immediately.


## Suggested Next Steps (after review)

1) Adopt the proposed structure (create `include/`, move public headers, rename the library target, fix the lib/test CMake files).
2) Add `CMakePresets.json` and switch to Ninja generator in Codespaces.
3) Vendor Catch2 with `FetchContent` and correct the test configuration.
4) Centralize warnings and make `-Werror` opt‑in.
5) Update the devcontainer to include extensions and compilers/debuggers explicitly.

Once approved, we can implement these changes via a focused PR.


## Alternative structure: single program, no `lib/` folder

If your project is just one application (no reusable libraries), keep the layout minimal while still testable and scalable later.

Suggested layout:

```
/                   # repo root
├─ CMakeLists.txt   # top-level
├─ CMakePresets.json
├─ include/         # headers consumed by both app and tests
│  └─ project/      # optional namespace folder
│     └─ *.h
├─ src/             # implementation files (no main here)
│  └─ *.cpp
├─ app/             # the program’s entry point(s)
│  └─ main.cpp
└─ test/            # tests
   ├─ CMakeLists.txt
   └─ *.cpp
```

Key points:
- Put the program logic in `src/` and headers in `include/`; keep `main.cpp` in `app/`.
- This keeps tests linking to the same code as the executable without a separate `lib/` tree.
- In CMake, create an OBJECT library for `src/` and reuse its objects in both the app and the tests.

Top-level `CMakeLists.txt` (single program):

```
cmake_minimum_required(VERSION 3.21)
project(<project_name> VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_subdirectory(app)
add_subdirectory(test)
```

`app/CMakeLists.txt` (OBJECT library pattern):

```
# Build the core objects from src/ once
add_library(core_objs OBJECT
  ${PROJECT_SOURCE_DIR}/src/foo.cpp
  ${PROJECT_SOURCE_DIR}/src/bar.cpp
)

target_include_directories(core_objs PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_compile_features(core_objs PUBLIC cxx_std_17)
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
  target_compile_options(core_objs PRIVATE -Wall -Wextra -pedantic)
endif()

# Build the executable by linking the object files and main
add_executable(${PROJECT_NAME}
  main.cpp
  $<TARGET_OBJECTS:core_objs>
)
target_link_libraries(${PROJECT_NAME} PRIVATE core_objs)

add_custom_target(run
  COMMAND $<TARGET_FILE:${PROJECT_NAME}>
  DEPENDS ${PROJECT_NAME}
  COMMENT "Running ${PROJECT_NAME}"
)
```

Notes:
- You can add more apps by creating additional directories under `app/` with their own `main.cpp` and linking `$<TARGET_OBJECTS:core_objs>`.
- If you later outgrow this, you can promote `core_objs` to a proper `STATIC` library with almost no code change.


## Opinionated test stack and setup (Catch2 v3)

Recommendation: Use Catch2 v3, brought in via CMake `FetchContent`. It’s lightweight, integrates with CTest via `catch_discover_tests`, and works smoothly in Codespaces.

Why Catch2 v3 here:
- Simple assertion and BDD styles; one-header main via `Catch2::Catch2WithMain` (so you don’t maintain your own `main`).
- Excellent CMake integration; easy to vendor via `FetchContent` (no external package installs in Codespaces).

`test/CMakeLists.txt` (single program variant):

```
include(FetchContent)
FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG v3.6.0
)
FetchContent_MakeAvailable(Catch2)

add_executable(${PROJECT_NAME}_tests
  example_tests.cpp
  # add more test sources here
  $<TARGET_OBJECTS:core_objs>  # reuse production objects
)

target_include_directories(${PROJECT_NAME}_tests PRIVATE ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(${PROJECT_NAME}_tests PRIVATE Catch2::Catch2WithMain)

include(Catch2)
catch_discover_tests(${PROJECT_NAME}_tests)
```

Guidelines:
- Do not combine `Catch2::Catch2WithMain` with your own `test_main.cpp` that defines `CATCH_CONFIG_MAIN`. Pick one; we recommend using `Catch2WithMain` and omitting `test_main.cpp` entirely.
- Keep tests small and fast; colocate fixtures/helpers under `test/`.
- Use CMake presets so `ctest` runs easily in Codespaces.

Optional `CMakePresets.json` entries (single program):

```
{
  "version": 5,
  "configurePresets": [
    {
      "name": "default",
      "generator": "Ninja",
      "binaryDir": "${sourceDir}/build",
      "cacheVariables": {
        "CMAKE_BUILD_TYPE": "Debug"
      }
    }
  ],
  "buildPresets": [
    { "name": "default", "configurePreset": "default" }
  ],
  "testPresets": [
    { "name": "default", "configurePreset": "default" }
  ]
}
```

If you prefer GoogleTest:
- Replace the Catch2 `FetchContent` block with GTest’s, link `GTest::gtest_main`, and use `gtest_discover_tests`. The rest of the structure stays the same.

