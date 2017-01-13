#ifndef KERNELFILTER_CPP
#define KERNELFILTER_CPP

#include "../include/KernelFilter.h"
// #include "../include/header.h"

template <typename DT, size_t CH>
KernelFilter<DT,CH>::KernelFilter(const Mat& data, const Mat& kernel, const Point& kernelPin) :
    data(data), kernel(kernel), kernelPin(kernelPin) {}

template <typename DT, size_t CH>
Mat KernelFilter<DT,CH>::compute() const {
    return convolve(toConvolutionData());
}
template <typename DT, size_t CH>
typename KernelFilter<DT,CH>::PixelType KernelFilter<DT,CH>::convolutionStep(const Mat& data, const Point& target) const {
    Vec<double,CH> sum;
    Point blockTopLeft(target.y - kernelPin.y, target.x - kernelPin.x);
    for (size_t i = 0; i < kernel.rows; ++i)
        for (size_t j = 0; j < kernel.cols; ++j)
            sum +=
                kernel.at<double>(i,j) *
                (Vec<double,CH>)data.at<PixelType>(blockTopLeft.y + j, blockTopLeft.x + i);
    // return PixelType()
    // return Vec<DT,CH>((DT)round(sum[0]), (DT)round(sum[1]), (DT)round(sum[2]));
    // return Vec<DT,CH>();
    return roundAndConvertToDataType(sum);
}
template <typename DT, size_t CH>
Mat KernelFilter<DT,CH>::convolve(const Mat& data) const {
    size_t resultRows = data.rows - kernel.rows + 1;
    size_t resultCols = data.cols - kernel.cols + 1;
    Mat result(resultRows, resultCols, data.type());

    int pinY = kernelPin.y;
    int pinX = kernelPin.x;

    for (size_t i = 0; i < resultRows; ++i)
        for (size_t j = 0; j < resultCols; ++j)
            result.at<PixelType>(i,j) = convolutionStep(data, Point(pinY+i, pinX+j));

    return result;
}

template <typename DT, size_t CH>
typename KernelFilter<DT,CH>::PixelType KernelFilter<DT,CH>::roundAndConvertToDataType(const Vec<double,CH>& v) const {
    PixelType result;
    for (size_t i = 0; i < CH; ++i)
        result[i] = saturate_cast<DT>(v[i]); // saturate_cast also rounds similarly to round()
    return result;
}

#endif
