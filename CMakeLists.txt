cmake_minimum_required(VERSION 3.16)

project(calculator LANGUAGES CXX)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

FetchContent_Declare(
    mathlib
#    GIT_REPOSITORY https://github.com/unusualbody/mathlib.git
#    GIT_TAB        v0.1
    URL https://github.com/unusualbody/mathlib/archive/refs/tags/v0.1.tar.gz
)

FetchContent_MakeAvailable(mathlib)

add_executable(calculator src/main.cpp)
target_link_libraries(calculator PRIVATE mathlib)

install(TARGETS calculator DESTINATION bin)

# clang-format
find_program(CLANG_FORMAT_EXE clang-format)

if (CLANG_FORMAT_EXE)
    set(CLANG_FORMAT_FILES
        ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
    )

    add_custom_target(
        clang-format
        COMMAND ${CLANG_FORMAT_EXE}
            -i
            ${CLANG_FORMAT_FILES}
        COMMENT "Running clang-format"
    )
endif()

# clang-tidy
option (ENABLE_CLANG_TIDY "Run clang-tidy during build (optional)" OFF)

find_program(CLANG_TIDY_EXE clang-tidy)

if (CLANG_TIDY_EXE)
    # Manual target: run clang-tidy on demand
    add_custom_target(
        clang-tidy
        COMMAND ${CLANG_TIDY_EXE}
                -p ${CMAKE_BINARY_DIR}
                ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
        COMMENT "Running clang-tidy"
    )

    # Optional: run clang-tidy during normal build if user enabled it
    if (ENABLE_CLANG_TIDY)
        set_target_properties(
            calculator
            PROPERTIES
            CXX_CLANG_TIDY "${CLANG_TIDY_EXE}"
        )
    endif()
endif()
