/*
 //OpenCV images overlayed project by Omid Karimpour
*/
#include <iostream>
#include "functions.hpp"

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
