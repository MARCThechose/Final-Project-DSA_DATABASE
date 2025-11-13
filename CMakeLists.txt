# Set a modern CMake version.
cmake_minimum_required(VERSION 3.10)

cmake_policy(SET CMP0072 NEW)
set(OpenGL_GL_PREFERENCE GLVND)


# Define the project name.
project(datasets)

# --- Submodule Integration ---

# GLFW has a CMakeLists.txt, so add_subdirectory works perfectly for it.
add_subdirectory(external/glfw)

# For Dear ImGui, we will create a library target ourselves.
# This is the standard way to handle libraries that don't have a root CMakeLists.txt.
add_library(imgui
    external/imgui/imgui.cpp
    external/imgui/imgui_demo.cpp
    external/imgui/imgui_draw.cpp
    external/imgui/imgui_tables.cpp
    external/imgui/imgui_widgets.cpp
)

# Tell any target that links against our new 'imgui' library where to find its header files.
# 'PUBLIC' means that 'imgui' needs this for itself, and any code that uses 'imgui'
# also needs access to these headers.

target_include_directories(imgui PUBLIC external/imgui)

# Find OpenGL (required for ImGui backends)
find_package(OpenGL REQUIRED)

# --- Source Files ---
# List all the source files for YOUR application.
set(SOURCES
    src/helloworld.cpp
    external/imgui/backends/imgui_impl_glfw.cpp
    external/imgui/backends/imgui_impl_opengl3.cpp
)

# --- Executable Definition ---
# Create your executable with all the necessary source files.
add_executable(datasets ${SOURCES})

# Revert MySQL to manual findi`ng (since find_package fails)
find_path(MySQL_INCLUDE_DIR NAMES cppconn/connection.h PATHS /usr/include/cppconn)
find_library(MySQL_LIBRARY NAMES mysqlcppconn PATHS /usr/lib/x86_64-linux-gnu)
target_include_directories(datasets PRIVATE ${MySQL_INCLUDE_DIR})

# Add the include directory for the ImGui backends, which your executable needs.
target_include_directories(datasets PRIVATE external/imgui/backends )

# --- Linking Libraries ---
# Link your executable against the GLFW, ImGui, MySQL, and OpenGL libraries.
# CMake will now automatically handle all the necessary flags and includes from them.
target_link_libraries(datasets PRIVATE glfw imgui ${MySQL_LIBRARY} OpenGL::GL)
