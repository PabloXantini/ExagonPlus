cmake_minimum_required(VERSION 3.10.0)
project(ExagonPlus VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(MSVC)
    set(CMAKE_MSVC_RUNTIME_LIBRARY "Multithreaded$<$<CONFIG:Debug>:Debug>")
    #add_compile_options(/fsanitize=address /Zi /Od)
    #add_link_options(/INCREMENTAL:NO /DEBUG /fsanitize=address)
endif()

include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/include/AL)
include_directories(${PROJECT_SOURCE_DIR}/include/GLFW)
include_directories(${PROJECT_SOURCE_DIR}/include/FreeImage)
link_directories(${CMAKE_SOURCE_DIR}/lib)
file(GLOB_RECURSE SOURCES
    src/MainFrame.cpp
    src/glad.c
    src/game/AEngine/Engine.cpp
    src/game/AEngine/AudioProcessor.cpp)

if(WIN32)
    list(APPEND SOURCES src/resource.rc)
endif()

add_executable(ExagonPlus ${SOURCES})

target_link_libraries(ExagonPlus PRIVATE glfw3dll.lib FreeImage.lib OpenAL32.lib)
#copiar cosas del ejecutable
add_custom_command(TARGET ExagonPlus POST_BUILD COMMAND ${CMAKE_COMMAND} 
-E copy_if_different 
"${PROJECT_SOURCE_DIR}/glfw3.dll"
"${PROJECT_SOURCE_DIR}/FreeImage.dll"
"${PROJECT_SOURCE_DIR}/OpenAL32.dll"
$<TARGET_FILE_DIR:ExagonPlus>
)
#copiar cosas del juego
add_custom_command(TARGET ExagonPlus POST_BUILD COMMAND ${CMAKE_COMMAND} 
-E copy_directory 
"${PROJECT_SOURCE_DIR}/src/levels"
"$<TARGET_FILE_DIR:ExagonPlus>/levels"
)