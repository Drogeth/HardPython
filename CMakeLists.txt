cmake_minimum_required(VERSION 3.10)
project(hard_python)

set(CMAKE_CXX_STANDARD 11)
#set(CMAKE_CXX_FLAGS "-O2 -static-libgcc -static-libstdc++")
#set(CMAKE_CXX_FLAGS "-pg -gdwarf-3")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake")

file(GLOB SOURCE_FILES
        src/*.cpp src/*.h
        src/core/*.cpp src/core/*.h
        src/game/*.cpp src/game/*.h
        src/renderers/*.cpp src/renderers/*.h)

file(GLOB SHADER_FILES shaders/*.glsl)
file(GLOB FONT_FILES fonts/*.fnt fonts/*.png)
file(GLOB AUDIO_FILES audio/*.wav audio/*.mp3 audio/*.ogg)
file(GLOB BINARY_FILES content/*.bin)
file(GLOB TEXTURE_FILES content/*.png)
file(MAKE_DIRECTORY ${PROJECT_BINARY_DIR}/shaders)
file(MAKE_DIRECTORY ${PROJECT_BINARY_DIR}/fonts)
file(MAKE_DIRECTORY ${PROJECT_BINARY_DIR}/audio)
file(MAKE_DIRECTORY ${PROJECT_BINARY_DIR}/content)
file(COPY ${SHADER_FILES} DESTINATION ${PROJECT_BINARY_DIR}/shaders)
file(COPY ${FONT_FILES} DESTINATION ${PROJECT_BINARY_DIR}/fonts)
file(COPY ${AUDIO_FILES} DESTINATION ${PROJECT_BINARY_DIR}/audio)
file(COPY ${BINARY_FILES} DESTINATION ${PROJECT_BINARY_DIR}/content)
file(COPY ${TEXTURE_FILES} DESTINATION ${PROJECT_BINARY_DIR}/content)

find_package(MINGW32 REQUIRED)
find_package(SDL2 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(IrrKlang REQUIRED)

add_executable(hard_python ${SOURCE_FILES} C:/Libraries/OpenGL/GLAD/src/glad.c)
target_link_libraries(hard_python ${MINGW32_LIB} ${SDL2_MAIN_LIB} ${SDL2_LIB} ${OPENGL_LIB} ${IRRKLANG_LIB})

add_custom_command(
        TARGET hard_python POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "C:/Libraries/SDL2/x86/bin/SDL2.dll"
        $<TARGET_FILE_DIR:hard_python>
)
add_custom_command(
        TARGET hard_python POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "C:/Libraries/irrKlang/bin/winx86-gcc/irrKlang.dll"
        $<TARGET_FILE_DIR:hard_python>
)