cmake_minimum_required (VERSION 2.8)
project (letterdetect)
find_package( OpenCV REQUIRED )
add_executable(letterdetect letterdetect.cpp alignment.cpp recognition.cpp main.cpp)
target_link_libraries(letterdetect ${OpenCV_LIBS} lept tesseract)

find_package( OpenCV REQUIRED )
add_executable(erosion erosion.cpp)
target_link_libraries(erosion ${OpenCV_LIBS})

find_package( OpenCV REQUIRED )
add_executable(corner corner.cpp)
target_link_libraries(corner ${OpenCV_LIBS})
