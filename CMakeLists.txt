cmake_minimum_required(VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project("discordBot")
set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)

# Set Vcpkg toolchain file
set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CACHE STRING "Vcpkg toolchain file")
set(VCPKG_TARGET_TRIPLET "x64-windows")

# Add source to this project's executable first
add_executable(discordBot "./src/main.cpp" "./src/backend.cpp" "./include/backend.h"  "src/ActionManager.cpp" "include/ActionManager.h" "include/DirectMsg.h" "src/DirectMsg.cpp" "src/customCommands.cpp" "include/customCommands.h")

# Manually set dpp_DIR if necessary
set(dpp_DIR "C:/Users/Office/Desktop/myProject/c++/Utils/vcpkg/installed/x64-windows/share/dpp")
find_package(dpp CONFIG REQUIRED)

# Link DPP to your project
target_link_libraries(discordBot PRIVATE dpp::dpp)

# Set C++ standard if CMake version is greater than 3.12
if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET discordBot PROPERTY CXX_STANDARD 20)
endif()
