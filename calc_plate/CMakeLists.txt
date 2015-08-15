cmake_minimum_required (VERSION 2.8)
project (calc_plate)

find_package( OpenCV REQUIRED )

include_directories("/usr/local/include/UnitTest++/")
link_directories("/usr/local/lib/")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")

add_executable(threshold threshold.cpp alignment.cpp main_threshold.cpp)
target_link_libraries(threshold ${OpenCV_LIBS})

add_executable(test_threshold test_threshold.cpp threshold.cpp alignment.cpp)
target_link_libraries(test_threshold UnitTest++ ${OpenCV_LIBS})
