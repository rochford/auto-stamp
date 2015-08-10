cmake_minimum_required (VERSION 2.8)
project (letterdetect)

find_package( OpenCV REQUIRED )

include_directories("/usr/local/include/UnitTest++/")
link_directories("/usr/local/lib/")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")

add_executable(letterdetect utils.cpp findsquares.cpp letterdetect.cpp alignment.cpp recognition.cpp main.cpp)
target_link_libraries(letterdetect ${OpenCV_LIBS} lept tesseract)

add_executable(erosion erosion.cpp)
target_link_libraries(erosion ${OpenCV_LIBS})

add_executable(corner corner.cpp)
target_link_libraries(corner ${OpenCV_LIBS})

# add_executable(platebyusercoords recognition.cpp alignment.cpp platebyusercoords.cpp)
# target_link_libraries(platebyusercoords ${OpenCV_LIBS} lept tesseract)

add_executable(contours findContours_demo.cpp)
target_link_libraries(contours ${OpenCV_LIBS})

add_executable(threshold threshold.cpp alignment.cpp recognition.cpp main_threshold.cpp)
target_link_libraries(threshold ${OpenCV_LIBS} lept tesseract)

add_executable(oflaw oflaw.cpp)
target_link_libraries(oflaw ${OpenCV_LIBS})

add_executable(test_threshold test_threshold.cpp threshold.cpp alignment.cpp)
target_link_libraries(test_threshold UnitTest++ ${OpenCV_LIBS})
