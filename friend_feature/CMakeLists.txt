cmake_minimum_required(VERSION 3.6 FATAL_ERROR)

project(friend_feature LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(wxWidgets REQUIRED)
include(${wxWidgets_USE_FILE})

# Define the source files for the friend feature
set(FRIEND_SRCS friend_main.cpp)  # Include other source files if needed

# Add the executable for friend_feature
add_executable(friend_app WIN32 ${FRIEND_SRCS})

# Link with wxWidgets
target_link_libraries(friend_app PRIVATE ${wxWidgets_LIBRARIES})
