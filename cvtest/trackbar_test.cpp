#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>

using namespace std;
using namespace cv;

int threshold_value = 0;
int threshold_type = 3;
int const max_value = 255;
int const max_type = 4;
int const max_BINARY_value = 255;

Mat src, src_gray, dst;
const char* windows_name = "Threshold Demo";

const char* trackbar_type = "Type:\n 0: Binary\n 1: Binary Inverted\n 2: Truncate\n 3: To Zero\n 4: To Zero Inverted";
const char* trackbar_value = "Value";

void Threshold_Demo(int, void*);

int trackbar_test(const char* img_path)
{
    src = imread(img_path, 1);
    cvtColor(src, src_gray, COLOR_RGB2GRAY);

    namedWindow(windows_name, WINDOW_AUTOSIZE);

    createTrackbar(trackbar_type, windows_name,
                   &threshold_type, max_type, Threshold_Demo);
    createTrackbar(trackbar_value, windows_name,
                   &threshold_value, max_value, Threshold_Demo);

    Threshold_Demo(0, 0);

    /*
    for(;;)
    {
        int c;
        c = waitKey( 20 );
        if ( (char)c == 27 )
        {
            break;
        }
    }
    */

    return 0;
}

void Threshold_Demo(int, void *)
{
    /*
     * 0: Binary
     * 1: Binary Inverted
     * 2: Truncate
     * 3: To Zero
     * 4: To Zero Inverted
     * */
    // threshold(src, dst, threshold_value, max_BINARY_value, threshold_type);
    threshold(src_gray, dst, threshold_value, max_BINARY_value, threshold_type);
    imshow(windows_name, dst);
}
