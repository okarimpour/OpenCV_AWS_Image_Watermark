/*
 //OpenCV images overlayed project by Omid Karimpour
*/
#include <iostream>

#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>

bool failedToLoad(const cv::Mat image){
    return image.empty() || 0 == image.size().width || 0 == image.size().height;
}

bool isEmpty(const cv::Mat image){
    return failedToLoad(image);
}

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

void printSize(const std::string name, const cv::Mat image){
    std::cout << name << " image size:\nWidth : " << image.size().width << "\nHeight: " << image.size().height << std::endl;
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

int main (int argc, const char * argv[])
{
    // to suppress -Wunsued-variable
    static_cast<void>(argc);
    static_cast<void>(argv);
    
    const auto mainImageFileName = "/Users/omidkarimpour/Desktop/openCV_Project/input/mainImage.jpg";
    const auto layeredImageFileName = "/Users/omidkarimpour/Desktop/openCV_Project/input/layeredImage.png";
    
    const auto newLayeredImageFileName = "/Users/omidkarimpour/Desktop/openCV_Project/output/newLayeredImage.png";
    const auto finalImagefileName = "/Users/omidkarimpour/Desktop/openCV_Project/output/finalImage.png";

    
    try {
        auto mainImage = readImage(mainImageFileName);
        auto layeredImage = readImage(layeredImageFileName);
        
        printSize("main", mainImage);
        printSize("layered", layeredImage);

        auto newLayeredImage = resizingImage(layeredImage, mainImage, 0.2);
        auto finalImage = overlayImage(mainImage, newLayeredImage, cv::Point(0, 0));
        
        printSize("new layered", newLayeredImage);
        
        writeImage(newLayeredImageFileName, newLayeredImage);
        writeImage(finalImagefileName, finalImage);
        
        
        showImage(newLayeredImage, "newLayeredImage");
        showImage(finalImage, "finalImage");
        
        
    } catch(const std::exception& ex){
        // show what you caught
        std::cerr << "Exception Raised: " << ex.what() << std::endl;
        return EXIT_FAILURE;
    } catch(const char* message){
        std::cerr << "Exception Thrown: " << message << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
    
}
