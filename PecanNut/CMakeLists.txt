cmake_minimum_required(VERSION 3.16)
project(PecanNut)

set(CMAKE_C_STANDARD 17)
set(CMAKE_CXX_STANDARD 17)

# 获取运行时头文件与源文件
file(GLOB_RECURSE HEADER_FILES "source/*.h")
file(GLOB_RECURSE SOURCE_FILES "source/*.cpp")
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${HEADER_FILES} ${SOURCE_FILES})

# 添加源文件
add_executable(${PROJECT_NAME}
        # source
        ${HEADER_FILES}
        ${SOURCE_FILES}
)

# 头文件
target_include_directories(${PROJECT_NAME}
        PRIVATE ${PROJECT_SOURCE_DIR}
        PRIVATE ${Pecan_SOURCE_DIR}
)

# 链接库
target_link_libraries(${PROJECT_NAME}
        PUBLIC Pecan
)
