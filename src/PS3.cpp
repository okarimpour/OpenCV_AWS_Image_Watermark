/*
 *      Project: Overlayered Project
 *      Author: Omid Karimpour
 */

#include <opencv2/opencv.hpp>
#include <iostream>

inline bool failedToLoad(cv::Mat image) {
    if(image.empty() || 0 == image.size().width || 0 == image.size().height){
        return true;
    }
    return false;
}

cv::Mat readImage(std::string fileName){
    cv::Mat image = cv::imread(fileName);
    if (failedToLoad(image))
        throw "Image not found";
    return image;
}

void writeImage(std::string fileName, cv::Mat newImage){
    cv::imwrite(fileName, newImage);
}

void showImage(cv::Mat newFrontImage, std::string label){
    cv::namedWindow(label, cv::WINDOW_AUTOSIZE);
    cv::imshow(label, newFrontImage);
    cv::waitKey();
    cv::destroyAllWindows();
}

int main (int argc, const char * argv[])
{
    cv::Mat mainImage;
    cv::Mat layeredImage;
    static_cast<void>(argc);
    static_cast<void>(argv);
    
    //Reading the image
    try{
        mainImage = readImage("/Users/omidkarimpour/Desktop/ComputerVision/secondClass/input/mainImage.jpg");
        layeredImage = readImage("/Users/omidkarimpour/Desktop/ComputerVision/secondClass/input/layeredImage.jpg");
    }
    catch(const cv::Exception & e){
        std::cerr << e.what() << std::endl;
        return -1;
    }
    catch (const char* error){
        std::cerr << error << std::endl;
        return -1;
    }

    //Resizing the front image.
    std::cout << "Main image size:\nWidth : " << mainImage.size().width << "\n" << "Height: " << mainImage.size().height << "\nLayered image size:" << "\nWidth : " << layeredImage.size().width << "\nHeight: " << layeredImage.size().height << std::endl;

    cv::Mat newLayeredImage;
    
    cv::resize(layeredImage, newLayeredImage, mainImage.size());
    
    //Writing the image
    try{
        writeImage("/Users/omidkarimpour/Desktop/ComputerVision/secondClass/output/new_layeredImage.jpg", newLayeredImage);
    }
    catch(const cv::Exception & e){
        std::cerr << e.what() << std::endl;
        return -1;
    }
    
    //Showing the image
    showImage(newLayeredImage, "newLayeredImage");

    //overlayer
    cv::Mat finalImage;
    double alpha = 0.8;
    double beta = 1 - alpha;
    cv::addWeighted(mainImage, alpha, newLayeredImage, beta, 0.0,finalImage);
    
    //Writing the result
    try{
        writeImage("/Users/omidkarimpour/Desktop/ComputerVision/secondClass/output/finalImage.jpg", finalImage);
    }
    catch(const cv::Exception & e){
        std::cerr << e.what() << std::endl;
        return -1;
    }
    
    //Writing the result
    showImage(finalImage, "finalImage");
    
    return 0;
}
