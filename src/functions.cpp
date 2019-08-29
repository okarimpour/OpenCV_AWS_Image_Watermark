#include "functions.hpp"

cv::Mat readImage(const std::string fileName){
    cv::Mat image = cv::imread(fileName, cv::IMREAD_UNCHANGED);
    if (failedToLoad(image)){
        throw "Image not found";
    }
    return image;
}

cv::Mat resizingImage(const cv::Mat originalImage, const cv::Mat backgroundImage, const double Factor){
    cv::Mat resizedImage;
    
    const auto originalAspectRatio = static_cast<double>(originalImage.rows) / originalImage.cols;
    
    const auto widthFactor = Factor * originalAspectRatio;
    
    cv::resize(
               originalImage,
               resizedImage,
               cv::Size(), // do nothing on Size, take Scale
               Factor,
               widthFactor,
               cv::INTER_AREA
               );
    
    if (failedToLoad(resizedImage))
        throw "Could not resize";
    
    return resizedImage;
}

void writeImage(const std::string fileName, const cv::Mat newImage){
    cv::imwrite(fileName, newImage);
    if (failedToLoad(newImage))
        throw "Could not write the image";
}

void showImage(cv::Mat newFrontImage, const std::string label){
    cv::namedWindow(label, cv::WINDOW_AUTOSIZE);
    cv::imshow(label, newFrontImage);
    cv::waitKey();
    cv::destroyAllWindows();
}

// location is a point on background, that defines the top left pixel of foreground
cv::Mat overlayImage(const cv::Mat background, const cv::Mat foreground, const cv::Point2i location){
    
    cv::Mat finalImage(background);
    
    auto maxLocationX = location.x + foreground.cols;
    auto maxLocationY = location.y + foreground.rows;
    float maxAlpha = 255;
    
    if (maxLocationX > background.cols || maxLocationY > background.rows){
        throw "location is out of bound";
    }
    
    if (location.x > 0 || location.y > 0){
        throw "location has negative value";
    }
    
    for(int row = location.y; row <= maxLocationY; row++){
        int foregroundY = row - location.y;
        
        for(int col = location.x; col <= maxLocationX; col++){
            int foregroundX = col - location.x;
            
            auto rgba = foreground.at<cv::Vec4b>(foregroundY, foregroundX);
            auto alpha = rgba[3] / maxAlpha;
            auto beta = 1 - alpha;
            
            for( auto pixelChannel = 0; pixelChannel < 3; pixelChannel++){
                finalImage.at<cv::Vec3b>(row, col)[pixelChannel] *= beta;
                finalImage.at<cv::Vec3b>(row, col)[pixelChannel] += alpha * rgba[pixelChannel];
            }
        }
    }
    
    return finalImage;
}
