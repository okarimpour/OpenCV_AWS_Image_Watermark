#include <opencv2/opencv.hpp>
#include <iostream>

inline bool failedToLoad(cv::Mat image) {
    if(image.empty() || 0 == image.size().width || 0 == image.size().height){
        return true;
    }
    return false;
}

cv::Mat readImage(std::string fileName){
    cv::Mat image = cv::imread(fileName, cv::IMREAD_UNCHANGED);
    if (failedToLoad(image))
        throw "Image not found";
    return image;
}

cv::Mat writeImage(std::string fileName, cv::Mat newImage){
    imwrite(fileName, newImage);
    if (failedToLoad(newImage))
        throw "Could not write the image";
    return newImage;
}

void showImage(cv::Mat newFrontImage, std::string label){
    cv::namedWindow(label, cv::WINDOW_AUTOSIZE);
    cv::imshow(label, newFrontImage);
    cv::waitKey();
    cv::destroyAllWindows();
}

cv::Mat resizingImage(cv::Mat originalImage, cv::Mat resizedImage, cv::Mat backgroundImage){
    cv::resize(originalImage, resizedImage, backgroundImage.size());
    if (failedToLoad(resizedImage))
        throw "Could not resize";
    return resizedImage;
}

int main (int argc, const char * argv[])
{
    cv::Mat mainImage, layeredImage, newLayeredImage, newMainImage;
    static_cast<void>(argc);
    static_cast<void>(argv);
    
    //Reading the image
    try{
        mainImage = readImage("/Users/omidkarimpour/Desktop/ComputerVision/secondClass/input/mainImage.jpg");
        layeredImage = readImage("/Users/omidkarimpour/Desktop/ComputerVision/secondClass/input/layeredImage.png");
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
    std::cout << "Main image size:Width : " << mainImage.size().width << "\n" << "Height: " << mainImage.size().height << "\nLayered image size:" << "\nWidth : " << layeredImage.size().width << "\nHeight: " << layeredImage.size().height << std::endl;
    
//    cv::split(layeredImage, bgra);
//    std::vector<cv::Mat> channels = {bgra[0], bgra[1], bgra[2]};
//    cv::merge(channels, rgbImage);
//    showImage(rgbImage, "layeredImage");
    
    cv::cvtColor(mainImage, newMainImage, cv::COLOR_RGB2RGBA, 4);
    
    try{
        resizingImage(layeredImage, newLayeredImage, newMainImage);
    }
    catch(const cv::Exception & e){
        std::cerr << e.what() << std::endl;
        return -1;
    }
    catch (const char* error){
        std::cerr << error << std::endl;
        return -1;
    }
    cv::resize(layeredImage, newLayeredImage, mainImage.size());
    
    //Writing the image
    try{
        writeImage("/Users/omidkarimpour/Desktop/ComputerVision/secondClass/output/newLayeredImage.png", newLayeredImage);
    }
    catch(const cv::Exception & e){
        std::cerr << e.what() << std::endl;
        return -1;
    }
    catch (const char* error){
        std::cerr << error << std::endl;
        return -1;
    }

    //Showing the image
    showImage(newLayeredImage, "newLayeredImage");

    //overlayer
    cv::Mat finalImage;
    double alpha = 0.5;
    double beta = 1 - alpha;
    cv::addWeighted(newMainImage, alpha, newLayeredImage, beta, 0.0,finalImage);

    //Writing the result
    try{
        writeImage("/Users/omidkarimpour/Desktop/ComputerVision/secondClass/output/finalImage.png", finalImage);
    }
    catch(const cv::Exception & e){
        std::cerr << e.what() << std::endl;
        return -1;
    }

    //Writing the result
    showImage(finalImage, "finalImage");
    
    return 0;
}
