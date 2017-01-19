#include <opencv2/highgui.hpp>
#include <iostream>
#include <cstdlib>
#include "../include/KernelFilterEdgeCrop.h"
#include "../include/KernelFilterEdgeExtension.h"
#include "../include/KernelFilterEdgeWrap.h"

using namespace cv;
using namespace std;

Mat smallBoxBlurKernel = (Mat_<double>(5,5) <<  1/25.0,1/25.0,1/25.0,1/25.0,1/25.0,
                                                1/25.0,1/25.0,1/25.0,1/25.0,1/25.0,
                                                1/25.0,1/25.0,1/25.0,1/25.0,1/25.0,
                                                1/25.0,1/25.0,1/25.0,1/25.0,1/25.0,
                                                1/25.0,1/25.0,1/25.0,1/25.0,1/25.0);

Mat sharpenKernel = (Mat_<double>(3,3) <<  0, -1, 0,
                                           -1, 5, -1,
                                           0, -1, 0);

Mat edgeDetectionKernel = (Mat_<double>(3,3) <<    -1, -1, -1,
                                                    -1, 8, -1,
                                                    -1, -1, -1);

int main(int argc, char* argv[]) {

    Mat img = imread(argv[1], CV_LOAD_IMAGE_COLOR);

    /*===================================*/

    // construct and run an edge extension policy filter with a non-centered box blur kernel
    KernelFilterEdgeExtension<uchar, 3> boxBlurEdgeExtension(img, smallBoxBlurKernel, Cell(0,1));

    cout << "running blur..." << endl;
    Mat blur = boxBlurEdgeExtension.compute();

    /*===================================*/

    // construct an edge wrap policy filter for input image and define kernels later */
    KernelFilterEdgeWrap<uchar, 3> filter1(img);

    Cell center3by3(1,1);

    // run sharpen kernel
    filter1.setKernel(sharpenKernel, center3by3);

    cout << "running sharpen..." << endl;
    Mat sharpen = filter1.compute();

    // run an edge detection kernel on defined filter
    filter1.setKernel(edgeDetectionKernel, center3by3);

    cout << "running edge detection..." << endl;
    Mat edgeDetectionResult1 = filter1.compute();

    /*===================================*/

    // construct and run an edge crop policy filter with an edge detection kernel on a gray-scale 32-bit int image
    Mat imgGrayScaleUchar = imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE);
    Mat imgGrayScaleInt;
    imgGrayScaleUchar.convertTo(imgGrayScaleInt, CV_32SC1);

    KernelFilterEdgeCrop<float, 1> filter2(imgGrayScaleInt, edgeDetectionKernel, center3by3);

    cout << "running edge detection..." << endl;
    Mat edgeDetectionResult2 = filter2.compute();

    /*===================================*/

    imwrite(string(argv[2])+"/blur.jpg", blur);
    imwrite(string(argv[2])+"/sharpen.jpg", sharpen);
    imwrite(string(argv[2])+"/edgeDetection1.jpg", edgeDetectionResult1);
    imwrite(string(argv[2])+"/edgeDetection2.jpg", edgeDetectionResult2);

    return 0;
}
