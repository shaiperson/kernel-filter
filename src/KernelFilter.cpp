#include "../include/KernelFilter.h"

KernelFilter::KernelFilter(const Mat& data, const Mat& kernel, const Point& kernelPin)
    : data(data), kernel(kernel), kernelPin(kernelPin) {}

Mat KernelFilter::compute() const {
    return convolve(toConvolutionData());
}

Vec3d KernelFilter::convolutionStep(const Mat& data, const Point& target) const {
    Vec3d sum = {0,0,0};
    size_t blockFirstRow = target.y - kernelPin.y;
    size_t blockFirstCol = target.x - kernelPin.x;
    for (size_t i = 0; i < kernel.rows; ++i)
        for (size_t j = 0; j < kernel.cols; ++j)
            for (size_t c = 0; c < data.channels(); ++c)
                sum[c] +=
                    data.at<Vec3d>(blockFirstRow + i, blockFirstCol + j)[c] *
                    kernel.at<double>(i,j);

    return sum;
}

Mat KernelFilter::convolve(const Mat& data) const {
    size_t resultRows = data.rows - kernel.rows + 1;
    size_t resultCols = data.cols - kernel.cols + 1;
    Mat result(resultRows, resultCols, CV_64FC3);

    int pinY = kernelPin.y;
    int pinX = kernelPin.y;

    for (size_t i = 0; i < resultRows; ++i)
        for (size_t j = 0; j < resultCols; ++j)
            result.at<Vec3d>(i,j) = convolutionStep(data, Point(pinY+i, pinX+j));

    return result;
}
