ADD_LIBRARY(learnopencv cornerHarris_demo.cpp houghlines.cpp trackbar_test.cpp)
ADD_EXECUTABLE(main main.cpp)
#link OpenCV
TARGET_LINK_LIBRARIES(main ${OpenCV_LIBS})
