#include "../include/KernelFilter.h"
#include <iostream>

using namespace std;

int main() {
    cout << "testing" << endl;
    Mat m(3, 3, CV_8UC1, 1);
    cout << m << endl;
    cout << (short)m.at<uchar>(0,0) << endl;
    return 0;
}
