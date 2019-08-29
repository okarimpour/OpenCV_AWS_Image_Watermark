#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>

inline bool failedToLoad(const cv::Mat image){
    return image.empty() || 0 == image.size().width || 0 == image.size().height;
}

inline bool isEmpty(const cv::Mat image){
    return failedToLoad(image);
}

cv::Mat readImage(const std::string fileName);

cv::Mat resizingImage(const cv::Mat originalImage, const cv::Mat backgroundImage, const double Factor);

void writeImage(const std::string fileName, const cv::Mat newImage);

void showImage(cv::Mat newFrontImage, const std::string label);

inline void printSize(const std::string name, const cv::Mat image){
    std::cout << name << " image size:\nWidth : " << image.size().width << "\nHeight: " << image.size().height << std::endl;
}

// location is a point on background, that defines the top left pixel of foreground
cv::Mat overlayImage(const cv::Mat background, const cv::Mat foreground, const cv::Point2i location);

#endif
