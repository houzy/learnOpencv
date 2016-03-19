#ifndef INCLUDE_HARRIS_DETECTOR_H__
#define INCLUDE_HARRIS_DETECTOR_H__

#include <vector>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/features2d/features2d.hpp>

class HarrisDetector {

    private:

        // 32-bit float image of corner strength, 32位浮点型角点强度图像
        cv::Mat cornerStrength;
        // 32-bit float image of thresholded corners, 32位浮点型阈值化角点图像
        cv::Mat cornerTh;
        // image of local maxima (internal), 局部最大值图像（内部使用）
        cv::Mat localMax;
        // size of neighbourhood for derivatives smoothing, 微分平滑（平滑导数？）的领域尺寸
        int neighbourhood;
        // aperture for gradient computation, 
        int aperture;
        // Harris parameter
        double k;
        // maximum strength for threshold computation
        double maxStrength;
        // calculated threshold (internal)
        double threshold;
        // size of neighbourhood for non-max suppression
        int nonMaxSize;
        // kernel for non-max suppression
        cv::Mat kernel;

    public:

        HarrisDetector() : neighbourhood(3), aperture(3), k(0.1), maxStrength(0.0), threshold(0.01), nonMaxSize(3) {

            setLocalMaxWindowSize(nonMaxSize);
        }

        // Create kernel used in non-maxima suppression
        void setLocalMaxWindowSize(int size) {

            nonMaxSize= size;
            kernel.create(nonMaxSize,nonMaxSize,CV_8U);
        }

        // Compute Harris corners
        void detect(const cv::Mat& image) {

            // Harris computation
            cv::cornerHarris(image,cornerStrength,
                    neighbourhood,// neighborhood size
                    aperture,     // aperture size
                    k);           // Harris parameter

            // internal threshold computation
            cv::minMaxLoc(cornerStrength,0,&maxStrength);

            // local maxima detection
            cv::Mat dilated;  // temporary image
            cv::dilate(cornerStrength,dilated,cv::Mat());
            cv::compare(cornerStrength,dilated,localMax,cv::CMP_EQ);
        }

        // Get the corner map from the computed Harris values
        cv::Mat getCornerMap(double qualityLevel) {

            cv::Mat cornerMap;

            // thresholding the corner strength
            threshold= qualityLevel*maxStrength;
            cv::threshold(cornerStrength,cornerTh,threshold,255,cv::THRESH_BINARY);

            // convert to 8-bit image
            cornerTh.convertTo(cornerMap,CV_8U);

            // non-maxima suppression
            cv::bitwise_and(cornerMap,localMax,cornerMap);

            return cornerMap;
        }

        // Get the feature points vector from the computed Harris values
        void getCorners(std::vector<cv::Point> &points, double qualityLevel) {

            // Get the corner map
            cv::Mat cornerMap= getCornerMap(qualityLevel);
            // Get the corners
            getCorners(points, cornerMap);
        }

        // Get the feature points vector from the computed corner map
        void getCorners(std::vector<cv::Point> &points, const cv::Mat& cornerMap) {

            // Iterate over the pixels to obtain all feature points
            for( int y = 0; y < cornerMap.rows; y++ ) {

                const uchar* rowPtr = cornerMap.ptr<uchar>(y);

                for( int x = 0; x < cornerMap.cols; x++ ) {

                    // if it is a feature point
                    if (rowPtr[x]) {

                        points.push_back(cv::Point(x,y));
                    }
                }
            }
        }

        // Draw circles at feature point locations on an image
        void drawOnImage(cv::Mat &image, const std::vector<cv::Point> &points, cv::Scalar color= cv::Scalar(255,255,255), int radius=3, int thickness=1) {

            std::vector<cv::Point>::const_iterator it= points.begin();

            // for all corners
            while (it!=points.end()) {

                // draw a circle at each corner location
                cv::circle(image,*it,radius,color,thickness);
                ++it;
            }
        }
};



#endif