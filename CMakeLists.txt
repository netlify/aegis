cmake_minimum_required(VERSION 3.16)
project(aegis LANGUAGES CXX VERSION 0.1.0)

list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(CheckCXXCompilerFlag)
include(CheckIPOSupported)
include(GNUInstallDirs)
include(FetchContent)
include(CTest)

FetchContent_Declare(apex GIT_REPOSITORY git@github.com:netlify/apex.git)
FetchContent_MakeAvailable(apex)

find_package(OpenSSL REQUIRED)

check_cxx_compiler_flag(-Wunused-variable CAN_WARN_UNUSED_VARIABLE)
check_cxx_compiler_flag(-Wstrict-aliasing CAN_WARN_STRICT_ALIASING)
check_cxx_compiler_flag(-Wuninitialized CAN_WARN_UNINITIALIZED)
check_cxx_compiler_flag(-Wuseless-cast CAN_WARN_USELESS_CAST)
check_cxx_compiler_flag(-Wcast-align CAN_WARN_CAST_ALIGN)
check_cxx_compiler_flag(-Wformat=2 CAN_WARN_FORMAT_2)
check_cxx_compiler_flag(-Wpedantic CAN_WARN_PEDANTIC)
check_cxx_compiler_flag(-Wextra CAN_WARN_EXTRA)
check_cxx_compiler_flag(-Wall CAN_WARN_DEFAULT)

set(--warn-unused-variable $<$<BOOL:${CAN_ALLOW_UNUSED_VARIABLE}>:-Wunused-variable>)
set(--warn-strict-aliasing $<$<BOOL:${CAN_WARN_STRICT_ALIASING}>:-Wstrict-aliasing>)
set(--warn-uninitialized $<$<BOOL:${CAN_WARN_UNINITIALIZED}>:-Wuninitialized>)
set(--warn-useless-cast $<$<BOOL:${CAN_WARN_USELESS_CAST}>:-Wuseless-cast>)
set(--warn-cast-align $<$<BOOL:${CAN_WARN_CAST_ALIGN}>:-Wcast-align>)
set(--warn-format-2 $<$<BOOL:${CAN_WARN_FORMAT_2}>:-Wformat=2>)
set(--warn-pedantic $<$<BOOL:${CAN_WARN_PEDANTIC}>:-Wpedantic>)
set(--warn-default $<$<BOOL:${CAN_WARN_DEFAULT}>:-Wall>)
set(--warn-extra $<$<BOOL:${CAN_WARN_EXTRA}>:-Wextra>)

add_library(${PROJECT_NAME})
add_library(netlify::${PROJECT_NAME} ALIAS ${PROJECT_NAME})
file(GLOB_RECURSE sources CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/src/*.cxx")
target_sources(${PROJECT_NAME} PRIVATE ${sources})
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_20)
target_compile_options(${PROJECT_NAME}
  PRIVATE
    $<$<AND:$<CXX_COMPILER_ID:GNU>,$<VERSION_LESS:${CMAKE_CXX_COMPILER_VERSION},10>>:-fconcepts>
    $<$<CXX_COMPILER_ID:Clang>:-fcolor-diagnostics>
    $<$<CXX_COMPILER_ID:GNU>:-fdiagnostics-color=always>
    $<$<CONFIG:Debug>:-fno-omit-frame-pointer>
    $<$<CONFIG:Debug>:-ggdb3>
    ${--warn-unused-variable}
    ${--warn-strict-aliasing}
    ${--warn-uninitialized}
    ${--warn-useless-cast}
    ${--warn-cast-align}
    ${--warn-format-2}
    ${--warn-pedantic}
    ${--warn-default}
    ${--warn-extra})
target_include_directories(${PROJECT_NAME}
  PUBLIC
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
  PRIVATE
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src>
    $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/src>)
target_link_libraries(${PROJECT_NAME}
  PUBLIC
    OpenSSL::Crypto
    netlify::apex)
