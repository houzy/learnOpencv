# ADD_LIBRARY(learnopencv houghlines.cpp trackbar_test.cpp)
ADD_EXECUTABLE(harris_corners harris_corners.cc)
#link OpenCV
TARGET_LINK_LIBRARIES(harris_corners ${OpenCV_LIBS})
