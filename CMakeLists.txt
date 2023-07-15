# CMakeList.txt: проект CMake для 22_PC_GDPS_MAIN; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#
cmake_minimum_required(VERSION 3.10.0)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
cmake_policy(SET CMP0057 NEW)

project ("22_PC_GDPS_MAIN")

#curly-eureka
file(GLOB_RECURSE curly-eureka-src ../curly-eureka/*.cpp)
set(curly-eureka-incl ../curly-eureka/minhook/include ../curly-eureka/gd.h/include ../curly-eureka/gd.h ../curly-eureka)
add_subdirectory(../curly-eureka/cocos-headers cocos-headers-build)
add_subdirectory(../curly-eureka/minhook minhook-build)

# Добавьте источник в исполняемый файл этого проекта.
file(GLOB_RECURSE src src/*)
add_library(${PROJECT_NAME} SHARED ${src} "verInf.rc" ${curly-eureka-src})
target_include_directories(${PROJECT_NAME} PRIVATE ${curly-eureka-incl})
target_link_libraries(${PROJECT_NAME} minhook cocos2d)

#add_library(LoadLibrary SHARED "LoadLibrary.cpp")

# Patches
add_library(DefaultSongBypass SHARED "Patches/DefaultSongBypass.cpp" "verInf.rc" ${curly-eureka-src})
target_include_directories(DefaultSongBypass PRIVATE ${curly-eureka-incl})
target_link_libraries(DefaultSongBypass minhook cocos2d)
add_library(EditorScrollOut SHARED "Patches/EditorScrollOut.cpp" "verInf.rc" ${curly-eureka-src})
target_include_directories(EditorScrollOut PRIVATE ${curly-eureka-incl})
target_link_libraries(EditorScrollOut minhook cocos2d)
add_library(MusicSyncCorrection SHARED "Patches/MusicSyncCorrection.cpp" "verInf.rc" ${curly-eureka-src})
target_include_directories(MusicSyncCorrection PRIVATE ${curly-eureka-incl})
target_link_libraries(MusicSyncCorrection minhook cocos2d)
add_library(ObjRotationHack SHARED "Patches/ObjRotationHack.cpp" "verInf.rc" ${curly-eureka-src})
target_include_directories(ObjRotationHack PRIVATE ${curly-eureka-incl})
target_link_libraries(ObjRotationHack minhook cocos2d)
add_library(PlaytestZoomBypass SHARED "Patches/PlaytestZoomBypass.cpp" "verInf.rc" ${curly-eureka-src})
target_include_directories(PlaytestZoomBypass PRIVATE ${curly-eureka-incl})
target_link_libraries(PlaytestZoomBypass minhook cocos2d)
add_library(SmoothEditorTrail SHARED "Patches/SmoothEditorTrail.cpp" "verInf.rc" ${curly-eureka-src})
target_include_directories(SmoothEditorTrail PRIVATE ${curly-eureka-incl})
target_link_libraries(SmoothEditorTrail minhook cocos2d)
add_library(ZoomInBypass SHARED "Patches/ZoomInBypass.cpp" "verInf.rc" ${curly-eureka-src})
target_include_directories(ZoomInBypass PRIVATE ${curly-eureka-incl})
target_link_libraries(ZoomInBypass minhook cocos2d)

add_library(FutureAnims SHARED "FutureAnims.cpp" "verInf.rc" ${curly-eureka-src})
target_include_directories(FutureAnims PRIVATE ${curly-eureka-incl})
target_link_libraries(FutureAnims minhook cocos2d)
add_library(LoadLibrary SHARED "LoadLibrary.cpp" "verInf.rc" ${curly-eureka-src})
target_include_directories(LoadLibrary PRIVATE ${curly-eureka-incl})
target_link_libraries(LoadLibrary minhook cocos2d)

set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/)
