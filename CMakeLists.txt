cmake_minimum_required(VERSION 3.10)


add_subdirectory("vendors/GLFW")
add_subdirectory("vendors/GLAD")
add_subdirectory("vendors/STB_IMAGE") 
add_subdirectory("vendors/GLM") 
 
project(Pixelate VERSION 1.0)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB SOURCES "src/*.cpp")
add_executable(Pixelate ${SOURCES})	

target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC RESOURCES_PATH="${CMAKE_CURRENT_SOURCE_DIR}/resources/")


target_include_directories(Pixelate PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include/")


target_link_libraries(Pixelate PRIVATE glfw glad opengl32 stb_image glm)