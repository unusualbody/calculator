cmake_minimum_required(VERSION 3.16)

project(calculator LANGUAGES CXX)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

FetchContent_Declare(
    mathlib
#    GIT_REPOSITORY https://github.com/unusualbody/mathlib.git
#    GIT_TAG        v0.3
    URL https://github.com/unusualbody/mathlib/archive/refs/tags/v0.3.tar.gz
)

FetchContent_Declare(
    nlohmann_json
    URL https://github.com/nlohmann/json/archive/refs/tags/v3.12.0.tar.gz
)

FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.17.0.tar.gz
)

FetchContent_Declare(
    spdlog
    URL https://github.com/gabime/spdlog/archive/refs/tags/v1.17.0.tar.gz
)

FetchContent_MakeAvailable(
    mathlib
    nlohmann_json
    googletest
    spdlog
)

add_executable(calculator
    src/main.cpp

    src/expression.h

    src/runner.h
    src/runner.cpp

    src/parser.h
    src/parser.cpp

    src/checker.h
    src/checker.cpp

    src/calculator.h
    src/calculator.cpp

    src/printer.h
    src/printer.cpp
)
target_link_libraries(calculator
    PRIVATE
        mathlib
        nlohmann_json::nlohmann_json            
)

install(TARGETS calculator DESTINATION bin)

# clang-format
find_program(CLANG_FORMAT_EXE
    NAMES
        clang-format
        clang-format-15
)

if (CLANG_FORMAT_EXE)
    set(CLANG_FORMAT_FILES
        ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/expression.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/runner.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/runner.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/parser.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/parser.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/checker.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/checker.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/calculator.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/calculator.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/printer.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/printer.cpp
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
