project(cmakegen)

set(CMAKE_CXX_STANDARD 17)

add_executable(${PROJECT_NAME}
    src/main.cpp
)

target_link_libraries(${PROJECT_NAME}
PRIVATE
    stdc++fs
)
