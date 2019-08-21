/*
 *      Project: Overlayered Project
 *      Author: Omid Karimpour
 */

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main (int argc, const char * argv[])
{
    
    //Capture the image
    Mat mainImage = imread("/Users/omidkarimpour/Desktop/ComputerVision/secondClass/input/mainImage.jpg");
    Mat layeredImage = imread("/Users/omidkarimpour/Desktop/ComputerVision/secondClass/input/layeredImage.jpg", IMREAD_UNCHANGED);
    if (mainImage.data == 0 || layeredImage.data == 0) {
        cerr << "Image not found!" << endl;// Show image not found if there is no data
        return -1;
    }
    
    //get the sizes
    cout << "Main image size:" << endl;
    cout << "Width : " << mainImage.size().width << endl;
    cout << "Height: " << mainImage.size().height << endl;
    cout << "Layered image size:" << endl;
    cout << "Width : " << layeredImage.size().width << endl;
    cout << "Height: " << layeredImage.size().height << endl;
    
    //resize
    Mat new_layeredImage;
    resize(layeredImage, new_layeredImage, Size(mainImage.size().width, mainImage.size().height));
    imwrite("/Users/omidkarimpour/Desktop/ComputerVision/secondClass/output/new_layeredImage.jpg", new_layeredImage);
    namedWindow("new Layered", WINDOW_AUTOSIZE);
    imshow("new Layered", new_layeredImage);
    
    //overlayer
    Mat finalImage;
    double alpha = 0.8;
    double beta = 1 - alpha;
    addWeighted(mainImage, alpha, new_layeredImage, beta, 0.0,finalImage);
    imwrite("/Users/omidkarimpour/Desktop/ComputerVision/secondClass/output/finalImage.jpg", finalImage);
    namedWindow("final Image", WINDOW_AUTOSIZE);
    imshow("final Image", finalImage);
    
}
