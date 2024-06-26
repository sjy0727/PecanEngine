project(imgui)

# 设置 ImGui 目录
set(IMGUI_DIR .)

# 源文件列表
set(SOURCES ${IMGUI_DIR}/imgui.cpp
        ${IMGUI_DIR}/imgui_demo.cpp
        ${IMGUI_DIR}/imgui_draw.cpp
        ${IMGUI_DIR}/imgui_tables.cpp
        ${IMGUI_DIR}/imgui_widgets.cpp
        ${IMGUI_DIR}/backends/imgui_impl_sdl2.cpp
        ${IMGUI_DIR}/backends/imgui_impl_sdlrenderer2.cpp)

# 头文件列表
set(HEADERS ${IMGUI_DIR}/imgui.h
        ${IMGUI_DIR}/imconfig.h
        ${IMGUI_DIR}/imgui_internal.h
        ${IMGUI_DIR}/imgui_rectpack.h
        ${IMGUI_DIR}/imgui_textedit.h
        ${IMGUI_DIR}/imgui_truetype.h
        ${IMGUI_DIR}/backends/imgui_impl_sdl2.h
        ${IMGUI_DIR}/backends/imgui_impl_sdlrenderer2.h)

# 设置编译标志
set(CXXFLAGS "-g -Wall -Wformat")
include_directories(${IMGUI_DIR} ${IMGUI_DIR}/backends)

# 根据操作系统设置特定的编译标志和链接库
if (UNIX AND NOT APPLE)
    message(STATUS "Linux")
    set(LIBS ${SDL2_LIBRARIES} -lGL -ldl)
elseif (APPLE)
    message(STATUS "Mac OS X")
    set(LIBS ${SDL2_LIBRARIES}
            "-framework OpenGL"
            "-framework Cocoa"
            "-framework IOKit"
            "-framework CoreVideo"
            "-L/usr/local/lib"
#            "-L/opt/local/lib"
    )
    include_directories(
            "/usr/local/include"
#            "/opt/local/include"
    )
elseif (WIN32)
    message(STATUS "Windows")
    set(LIBS ${SDL2_LIBRARIES} -lgdi32 -lopengl32 -limm32)
endif ()

# 查找 SDL2 库
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_library(${PROJECT_NAME} STATIC ${SOURCES})


# 链接库
target_link_libraries(${PROJECT_NAME} ${LIBS})