#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

Mat& ScanImageAndReduceC(Mat& I, const uchar* const table)
{
    CV_Assert(I.depth() != sizeof(uchar));
    int channels = I.channels();
    int nRows = I.rows;
    int nCols = I.cols * channels;

    if (I.isContinuous())
    {
        nCols *= nRows;
        nRows = 1;
    }

    int i, j;
    uchar *p;
    for (i = 0; i < nRows; ++i)
    {
        p = I.ptr<uchar>(i);
        for (j = 0; j < nCols; ++j)
        {
            // p[j] = table[p[j]];
            p[j] = 255 - p[j];
        }
    }

    return I;
}

int main()
{
    Mat image = imread("/home/houzy/opencv/opencvpro/myFirstOpenCv/lena.jpg", CV_LOAD_IMAGE_COLOR);
    imshow("image", image);
    imwrite("/home/houzy/opencv/opencvpro/lena.jpg", image);

    Mat image2 = image.clone();
    cout << "depth() == " << image2.depth() << endl;
    cout << "rows == " << image2.rows << endl;
    cout << "cols == " << image2.cols << endl;
    imshow("image2", ScanImageAndReduceC(image2, NULL));

    Mat image3 = image.clone();
    medianBlur(image, image3, 7); // 第三个参数是核的大小，就是取平均区域的大小
    imshow("image3", image3);

    Mat image4 = image.clone();
    GaussianBlur(image, image4, Size(5, 5), 0);
    imshow("image4", image4);

    Mat image5 = image.clone();
    Mat kernel;
    erode(image, image5, kernel);
    imshow("image5", image5);

    Mat image6 = image.clone();
    dilate(image, image6, kernel);
    imshow("image6", image6);

    waitKey(0);

    // 2x2 矩阵
    // CV_[The number of bits per item][Signed or Unsigned][Type Prefix]C[The channel number]
    Mat M(2, 2, CV_8UC3, Scalar(0, 0, 255));
        cout << "M = " << endl << " " << M << endl << endl;

    M.create(4,4, CV_8UC(2));
        cout << "M = "<< endl << " "  << M << endl << endl;

    Mat C = (Mat_<double>(3,3) << 0, -1.1, 0, -1, 5.1, -1, 0, -1, 0);
        cout << "C = " << endl << " " << C << endl << endl;

    Mat RowClone = C.row(1).clone();
        cout << "RowClone = " << endl << " " << RowClone << endl << endl;


    cout << "Hello World!" << endl;
    return 0;
}

