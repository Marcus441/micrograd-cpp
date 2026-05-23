cmake_minimum_required(VERSION 3.31)
set(CMAKE_CXX_SCAN_FOR_MODULES OFF)

project(back-prop LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(SOURCES
    src/main.cpp
    src/value.cpp
    src/util/graphing.cpp
    src/neuron.cpp
    src/layer.cpp
    src/MLP.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_options(${PROJECT_NAME} PRIVATE
    -stdlib=libc++
    -pedantic -Wall -Wextra -Wshadow -Wnon-virtual-dtor -Wunused
    $<$<CONFIG:Release>:-O3>
    $<$<CONFIG:RelWithDebInfo>:-O2 -g>
    $<$<CONFIG:Debug>:-g -Og>
)

target_link_options(${PROJECT_NAME} PRIVATE)

option(USE_SANITIZERS "Enable ASan/UBSan" OFF)
if(USE_SANITIZERS)
    if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
        set(SAN_FLAGS -fsanitize=address,undefined -fno-omit-frame-pointer)
        target_compile_options(${PROJECT_NAME} PRIVATE ${SAN_FLAGS})
        target_link_options(${PROJECT_NAME} PRIVATE ${SAN_FLAGS})
    endif()
endif()

install(TARGETS ${PROJECT_NAME} DESTINATION bin)
