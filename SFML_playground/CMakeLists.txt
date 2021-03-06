cmake_minimum_required(VERSION 3.1)

project(Playground VERSION 0.1)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED true)
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")
add_compile_definitions(SFML_STATIC)


file(GLOB SOURCES 
    PRIVATE "${PROJECT_SOURCE_DIR}/src/*.cpp"
)

file(GLOB_RECURSE CONTROLLER 
    PRIVATE "${PROJECT_SOURCE_DIR}/src/Controller/*.hpp"
    PRIVATE "${PROJECT_SOURCE_DIR}/src/Controller/*.cpp"
)


file(GLOB_RECURSE EVENTSYSTEM 
    PRIVATE "${PROJECT_SOURCE_DIR}/src/EventSystem/*.hpp"
    PRIVATE "${PROJECT_SOURCE_DIR}/src/EventSystem/*.cpp"
)

file(GLOB_RECURSE GAME 
    PRIVATE "${PROJECT_SOURCE_DIR}/src/Game/*.hpp"
    PRIVATE "${PROJECT_SOURCE_DIR}/src/Game/*.cpp"
)

file(GLOB_RECURSE COMMON 
    PRIVATE "${PROJECT_SOURCE_DIR}/src/Common/*.hpp"
    PRIVATE "${PROJECT_SOURCE_DIR}/src/Common/*.cpp"
)

add_executable(${PROJECT_NAME} 
    ${SOURCES}
    ${EVENTSYSTEM}
    ${CONTROLLER}
    ${GAME}
    ${COMMON}
)

source_group("EventSystem"                FILES ${EVENTSYSTEM})
source_group("Controller"                 FILES ${CONTROLLER})
source_group("Game"                       FILES ${GAME})
source_group("Common"                     FILES ${COMMON})

target_include_directories(${PROJECT_NAME} 
    PRIVATE "${PROJECT_SOURCE_DIR}/SFML/include"
    PRIVATE "${PROJECT_SOURCE_DIR}/glm"
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