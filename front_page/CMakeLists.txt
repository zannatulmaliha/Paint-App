cmake_minimum_required(VERSION 3.6 FATAL_ERROR)

project(front_page LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find wxWidgets
find_package(wxWidgets REQUIRED)
include(${wxWidgets_USE_FILE})

# List the source files for the front page
set(FRONT_PAGE_SRCS front_page.cpp)

# Create the executable for the front page
add_executable(front_page_app WIN32 ${FRONT_PAGE_SRCS})

# Link the front page with wxWidgets
target_link_libraries(front_page_app PRIVATE ${wxWidgets_LIBRARIES})
