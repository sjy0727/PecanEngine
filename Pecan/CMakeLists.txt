cmake_minimum_required(VERSION 3.16)
project(Pecan)

set(CMAKE_C_STANDARD 17)
set(CMAKE_CXX_STANDARD 17)

if (MSVC)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif ()

# 设置各模块编译选项
set(BUILD_SHARED_LIBS OFF CACHE BOOL "Disable BUILD_SHARED_LIBS option in SDL2")
set(SDL2IMAGE_BUILD_SHARED_LIBS OFF CACHE BOOL "Disable SDL2IMAGE_BUILD_SHARED_LIBS option in SDL2_image")

# 添加依赖
add_subdirectory(${PROJECT_SOURCE_DIR}/vendor/SDL)
add_subdirectory(${PROJECT_SOURCE_DIR}/vendor/SDL_image)
add_subdirectory(${PROJECT_SOURCE_DIR}/vendor/imgui)
add_subdirectory(${PROJECT_SOURCE_DIR}/vendor/spdlog)


# 获取运行时头文件与源文件
file(GLOB_RECURSE RUNTIME_HEADER_FILES "Runtime/*.h")
file(GLOB_RECURSE RUNTIME_SOURCE_FILES "Runtime/*.cpp")
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${RUNTIME_HEADER_FILES} ${RUNTIME_SOURCE_FILES})

# 添加源文件
add_library(${PROJECT_NAME} STATIC
        # Runtime
        ${RUNTIME_HEADER_FILES}
        ${RUNTIME_SOURCE_FILES}
)

# 预编译头
target_precompile_headers(${PROJECT_NAME} PRIVATE
        $<$<COMPILE_LANGUAGE:CXX>:${CMAKE_CURRENT_SOURCE_DIR}/pcpch.h>
)

# 头文件搜索目录
target_include_directories(${PROJECT_NAME}
        PUBLIC ${PROJECT_SOURCE_DIR}
        PUBLIC ${PROJECT_SOURCE_DIR}/vendor/SDL2/include
        PUBLIC ${PROJECT_SOURCE_DIR}/vendor/SDL2_image/include
        PUBLIC ${PROJECT_SOURCE_DIR}/vendor/imgui
        PUBLIC ${PROJECT_SOURCE_DIR}/vendor/imgui/backends
        PUBLIC ${PROJECT_SOURCE_DIR}/vendor/spdlog/include

        # 让编译器发现EntryPoint.h
#        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)


# 链接库
target_link_libraries(${PROJECT_NAME}
        PUBLIC SDL2-static
        PUBLIC SDL2_image
        PUBLIC spdlog
        PUBLIC imgui
)
