﻿# CMakeList.txt: проект CMake для Task_2_GaussianElimination; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#
cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("Task_2_GaussianElimination")

# Добавьте источник в исполняемый файл этого проекта.
add_executable (Task_2_GaussianElimination "GaussianElimination.cpp" "GaussianElimination.h" "Matrix.h" "Matrix.cpp" "main.cpp" "RandomDouble.h" "RandomDouble.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Task_2_GaussianElimination PROPERTY CXX_STANDARD 20)
endif()

# TODO: Добавьте тесты и целевые объекты, если это необходимо.
