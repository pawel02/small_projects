cmake_minimum_required(VERSION 3.1)

project(Playground VERSION 0.1)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED true)

add_executable(${PROJECT_NAME} src/Source.cpp)

target_include_directories(${PROJECT_NAME} 
    PRIVATE "${PROJECT_SOURCE_DIR}/SFML/include"
)
target_link_directories(${PROJECT_NAME}
    PRIVATE "${PROJECT_SOURCE_DIR}/SFML/build/lib/Debug"
    PRIVATE "${PROJECT_SOURCE_DIR}/SFML/build/lib/Release"
)

# debug linking
target_link_libraries(${PROJECT_NAME} debug sfml-audio-s-d.lib sfml-graphics-s-d.lib sfml-main-d.lib sfml-network-s-d.lib sfml-system-s-d.lib sfml-window-s-d.lib)
# release linking
target_link_libraries(${PROJECT_NAME} optimized sfml-audio-s.lib sfml-graphics-s.lib sfml-main.lib sfml-network-s.lib sfml-system-s.lib sfml-window-s.lib)