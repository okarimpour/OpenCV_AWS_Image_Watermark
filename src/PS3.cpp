/*
 //OpenCV images overlayed project by Omid Karimpour
*/

#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
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

void resizingImage(cv::Mat originalImage, cv::Mat &resizedImage, cv::Mat backgroundImage, double xFactor, double yFactor){
    cv::resize(originalImage, resizedImage, cv::Size(backgroundImage.cols*xFactor, backgroundImage.rows*yFactor), 0, 0, cv::INTER_AREA);
    if (failedToLoad(resizedImage))
        throw "Could not resize";
}

void writeImage(std::string fileName, cv::Mat newImage){
    cv::imwrite(fileName, newImage);
    if (failedToLoad(newImage))
        throw "Could not write the image";
}

void showImage(cv::Mat newFrontImage, std::string label){
    cv::namedWindow(label, cv::WINDOW_AUTOSIZE);
    cv::imshow(label, newFrontImage);
    cv::waitKey();
    cv::destroyAllWindows();
}

int tryCatch(std::string name, cv::Mat image, void (*func)(std::string, cv::Mat)){
    try{
        (*func)(name, image);
    }
    catch(const cv::Exception & e){
        std::cerr << e.what() << std::endl;
        return -1;
    }
    catch (const char* error){
        std::cerr << error << std::endl;
        return -1;
    }
    return 0;
}

bool readTryCatch(std::string name, cv::Mat& image, cv::Mat (*func)(std::string)){
    try{
         image = (*func)(name);
    }
    catch(const cv::Exception & e){
        std::cerr << e.what() << std::endl;
        return false;
    }
    catch (const char* error){
        std::cerr << error << std::endl;
        return false;
    }
    return true;
}

void printSize(std::string name, cv::Mat image){
    std::cout << name << " image size:\nWidth : " << image.size().width << "\nHeight: " << image.size().height << std::endl;
}

int main (int argc, const char * argv[])
{
    cv::Mat mainImage, layeredImage, newLayeredImage, newMainImage;
    static_cast<void>(argc);
    static_cast<void>(argv);
    
    if (readTryCatch("/Users/omidkarimpour/Desktop/openCV_Project/input/mainImage.jpg", mainImage, readImage) == false){return -1;}
    if(readTryCatch("/Users/omidkarimpour/Desktop/openCV_Project/input/layeredImage.png", layeredImage, readImage) == false){return -1;}

    printSize("main", mainImage);
    printSize("layered", layeredImage);
    
//    cv::split(layeredImage, bgra);
//    std::vector<cv::Mat> channels = {bgra[0], bgra[1], bgra[2]};
//    cv::merge(channels, rgbImage);
//    showImage(rgbImage, "layeredImage");
    
//    //overlayer
//    cv::Mat finalImage;
//    double alpha = 0.5;
//    double beta = 1 - alpha;
//    cv::addWeighted(newMainImage, alpha, newLayeredImage, beta, 0.0,finalImage);
    
    cv::cvtColor(mainImage, newMainImage, cv::COLOR_RGB2RGBA, 4);
    
    if(layeredImage.size >= newMainImage.size){
        
        resizingImage(layeredImage, newLayeredImage, newMainImage, 0.1, 0.1);
        newLayeredImage.copyTo(newMainImage(cv::Rect(0, 0, newLayeredImage.cols, newLayeredImage.rows)));
        
    } else{
        //upsample
    }
    
        printSize("new layered", newLayeredImage);
        tryCatch("/Users/omidkarimpour/Desktop/openCV_Project/output/newMainImage.png", newMainImage, writeImage);
        tryCatch("/Users/omidkarimpour/Desktop/openCV_Project/output/newLayeredImage.png", newLayeredImage, writeImage);
        showImage(newMainImage, "newMainImage");
        showImage(newLayeredImage, "newLayeredImage");
        
    return 0;
}
