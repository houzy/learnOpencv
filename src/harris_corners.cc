#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main(int argc, char *argv[])
{
    Mat cornerStrength;
    // Mat input_image = imread("../images/1486OS_02_01.jpg", cv::IMREAD_COLOR);
    Mat input_image = imread("../images/1486OS_02_01.jpg", cv::IMREAD_GRAYSCALE);
    cout<<"input_image size: "<<input_image.size()<<endl;
    cout<<"input_image dims: "<<input_image.dims<<endl;
    cout<<"input_image channels: "<<input_image.channels()<<endl;
    cout<<"input_image type: "<<input_image.type()<<endl;
    imshow("input_image", input_image);

    // 检测Harris角点
    cv::cornerHarris(
            input_image,    // 输入图像
            cornerStrength, // 角点强度图像
            3,              // 领域尺寸
            3,              // 口径尺寸
            0.01            // Harris参数
            );
    imshow("cornerStrength", cornerStrength);

    // 对角点强度阈值化
    Mat cornerTh;
    double thresholdval = 0.0001;
    cv::threshold(cornerStrength, cornerTh, thresholdval, 255, cv::THRESH_BINARY);
    imshow("harrisCorners", cornerTh);

    waitKey(0);

    return 0;
}
