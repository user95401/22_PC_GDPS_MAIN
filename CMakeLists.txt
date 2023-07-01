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

add_library(LoadLibrary SHARED "LoadLibrary.cpp")

add_library(Patches SHARED "Patches.cpp" "verInf.rc" ${curly-eureka-src})
target_include_directories(Patches PRIVATE ${curly-eureka-incl})
target_link_libraries(Patches minhook cocos2d)

add_library(FutureAnims SHARED "FutureAnims.cpp" "verInf.rc" ${curly-eureka-src})
target_include_directories(FutureAnims PRIVATE ${curly-eureka-incl})
target_link_libraries(FutureAnims minhook cocos2d)

set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/)
