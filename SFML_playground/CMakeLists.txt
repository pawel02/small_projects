cmake_minimum_required(VERSION 3.1)

project(Playground VERSION 0.1)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED true)
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")
add_compile_definitions(SFML_STATIC)

add_executable(${PROJECT_NAME} src/Source.cpp)

target_include_directories(${PROJECT_NAME} 
    PRIVATE "${PROJECT_SOURCE_DIR}/SFML/include"
)
target_link_directories(${PROJECT_NAME}
    PRIVATE "${PROJECT_SOURCE_DIR}/SFML/build/lib/Debug"
    PRIVATE "${PROJECT_SOURCE_DIR}/SFML/build/lib/Release"
    PRIVATE "${PROJECT_SOURCE_DIR}/libs"
)

# debug linking
target_link_libraries(${PROJECT_NAME} opengl32 winmm gdi32 freetype openal32 flac vorbisenc vorbisfile vorbis ogg ws2_32)
target_link_libraries(${PROJECT_NAME} sfml-audio-s-d sfml-graphics-s-d sfml-main-d sfml-network-s-d sfml-system-s-d sfml-window-s-d)
# only needed in release builds
#target_link_libraries(${PROJECT_NAME} sfml-audio-s sfml-graphics-s sfml-main sfml-network-s sfml-system-s sfml-window-s)