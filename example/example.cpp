#include "../include/KernelFilter.h"
#include <opencv2/highgui.hpp>
#include <iostream>
#include <cstdlib>

using namespace std;

void lolimshow(const Mat& papas) {
    imshow("papas", papas);
    waitKey();
}

string type2str(int type) {
  string r;

  uchar depth = type & CV_MAT_DEPTH_MASK;
  uchar chans = 1 + (type >> CV_CN_SHIFT);

  switch ( depth ) {
    case CV_8U:  r = "8U"; break;
    case CV_8S:  r = "8S"; break;
    case CV_16U: r = "16U"; break;
    case CV_16S: r = "16S"; break;
    case CV_32S: r = "32S"; break;
    case CV_32F: r = "32F"; break;
    case CV_64F: r = "64F"; break;
    default:     r = "User"; break;
  }

  r += "C";
  r += (chans+'0');

  return r;
}

Vec3d v1 = {1,1,1};
Vec3d v2 = {2,2,2};
Vec3d v3 = {3,3,3};
Vec3d v4 = {4,4,4};
Vec3d v5 = {5,5,5};
Vec3d v6 = {6,6,6};
Vec3d v7 = {7,7,7};
Vec3d v8 = {8,8,8};
Vec3d v9 = {9,9,9};

Mat simple5 = (Mat_<Vec3d>(5,5) <<  v1, v2, v3, v4, v5,
                                    v2, v3, v4, v5, v6,
                                    v3, v4, v5, v6, v7,
                                    v4, v5, v6, v7, v8,
                                    v5, v6, v7, v8, v9);

void simple5check() {
    // cout << simple5.rows << endl;
    // cout << simple5.cols << endl;
    // cout << simple5.total() << endl;
    // cout << simple5.depth() << endl;
    // cout << simple5.channels() << endl;
    // cout << simple5 << endl;
}

void testecito() {
    // Mat idKernel = (Mat_<double>(3,3) << 0,0,0,0,1,0,0,0,0);
    // KernelFilterEdgeCrop filter(simple5, idKernel, Point(1,1));
    // Mat result = filter.compute();
    // cout << result << endl;
}

void messi(const Mat& image) {
    Mat smallBoxBlurKernel = (Mat_<double>(3,3) <<  1.0/9.0,1.0/9.0,1.0/9.0,
                                                    1.0/9.0,1.0/9.0,1.0/9.0,
                                                    1.0/9.0,1.0/9.0,1.0/9.0);

    Mat largeBoxBlurKernel = (Mat_<double>(10,10) <<    1.0/100, 1.0/100, 1.0/100, 1.0/100, 1.0/100, 1.0/100, 1.0/100, 1.0/100, 1.0/100, 1.0/100,
                                                        1.0/100, 1.0/100, 1.0/100, 1.0/100, 1.0/100, 1.0/100, 1.0/100, 1.0/100, 1.0/100, 1.0/100,
                                                        1.0/100, 1.0/100, 1.0/100, 1.0/100, 1.0/100, 1.0/100, 1.0/100, 1.0/100, 1.0/100, 1.0/100,
                                                        1.0/100, 1.0/100, 1.0/100, 1.0/100, 1.0/100, 1.0/100, 1.0/100, 1.0/100, 1.0/100, 1.0/100,
                                                        1.0/100, 1.0/100, 1.0/100, 1.0/100, 1.0/100, 1.0/100, 1.0/100, 1.0/100, 1.0/100, 1.0/100,
                                                        1.0/100, 1.0/100, 1.0/100, 1.0/100, 1.0/100, 1.0/100, 1.0/100, 1.0/100, 1.0/100, 1.0/100,
                                                        1.0/100, 1.0/100, 1.0/100, 1.0/100, 1.0/100, 1.0/100, 1.0/100, 1.0/100, 1.0/100, 1.0/100,
                                                        1.0/100, 1.0/100, 1.0/100, 1.0/100, 1.0/100, 1.0/100, 1.0/100, 1.0/100, 1.0/100, 1.0/100,
                                                        1.0/100, 1.0/100, 1.0/100, 1.0/100, 1.0/100, 1.0/100, 1.0/100, 1.0/100, 1.0/100, 1.0/100,
                                                        1.0/100, 1.0/100, 1.0/100, 1.0/100, 1.0/100, 1.0/100, 1.0/100, 1.0/100, 1.0/100, 1.0/100);

    Mat sharpenkernel = (Mat_<double>(3,3) <<  0, -1, 0,
                                                    -1, 5, -1,
                                                    0, -1, 0);

    Mat edgeDetectionKernel1 = (Mat_<double>(3,3) <<    1, 0, -1,
                                                        0, 0, 0,
                                                        -1, 0, 1);

    Mat edgeDetectionKernel2 = (Mat_<double>(3,3) <<    -1, -1, -1,
                                                        -1, 8, -1,
                                                        -1, -1, -1);

    KernelFilterEdgeCrop<unsigned char, 3> filter(image, largeBoxBlurKernel, Point(1,1));
    Mat result = filter.compute();
    lolimshow(result);
    // imwrite("test/examples/edgedetection2.jpg", result);
}

template <typename T, int N>
void juanchopapotas(T a) {
    // Vec3d v1 = {1,1,1};
    // Vec3b v2 = {2,2,2};
    double x = 2.7;
    double result = round((double)a + x);
    cout << result << endl;
    Vec<T, N> v;
    cout << v << endl;
}

void juanchopapinhas() {
    double d = 251.9;
    uchar x = saturate_cast<uchar>(d);
    cout << (int)x << endl;
}

int main(int argc, char* argv[]) {
    // simple5check();
    // testecito();

    Mat input = imread(argv[1], CV_LOAD_IMAGE_COLOR);
    messi(input);

    // juanchopapotas<int, 2>(2);

    // juanchopapinhas();

    return 0;
}
