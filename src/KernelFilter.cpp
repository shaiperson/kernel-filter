#ifndef KERNELFILTER_CPP
#define KERNELFILTER_CPP

#include "../include/KernelFilter.h"
// #include "../include/header.h"

template <typename DT, size_t CH>
KernelFilter<DT,CH>::KernelFilter(const Mat& data, const Mat& kernel, const Point& kernelPin) :
    data(data), kernel(kernel), kernelPin(kernelPin) {}

template <typename DT, size_t CH>
Mat KernelFilter<DT,CH>::compute() const {
    Convolver convolver(this);
    return convolver.convolveCroppingEdges(toConvolutionData());
}

template <typename DT, size_t CH>
Mat KernelFilter<DT,CH>::Convolver::convolveCroppingEdges(const Mat& data) const {
    size_t resultRows = (filter->data).rows - (filter->kernel).rows + 1;
    size_t resultCols = (filter->data).cols - (filter->kernel).cols + 1;
    Mat result(resultRows, resultCols, (filter->data).type());

    int pinY = (filter->kernelPin).y;
    int pinX = (filter->kernelPin).x;

    for (size_t i = 0; i < resultRows; ++i)
        for (size_t j = 0; j < resultCols; ++j)
            result.at<PixelType>(i,j) = convolutionStep(data, Point(pinY+i, pinX+j));

    return result;
}

template <typename DT, size_t CH>
typename KernelFilter<DT,CH>::PixelType KernelFilter<DT,CH>::Convolver::convolutionStep(const Mat& data, const Point& target) const {
    Vec<double,CH> sum;
    Point blockTopLeft(target.y - (filter->kernelPin).y, target.x - (filter->kernelPin).x);
    for (size_t i = 0; i < (filter->kernel).rows; ++i)
        for (size_t j = 0; j < (filter->kernel).cols; ++j)
            sum +=
                (filter->kernel).template at<double>(i,j) *
                (Vec<double,CH>)(filter->data).template at<PixelType>(blockTopLeft.y + j, blockTopLeft.x + i);
    return roundAndConvertToDataType(sum);
}

template <typename DT, size_t CH>
typename KernelFilter<DT,CH>::PixelType KernelFilter<DT,CH>::Convolver::roundAndConvertToDataType(const Vec<double,CH>& v) const {
    PixelType result;
    for (size_t i = 0; i < CH; ++i)
        result[i] = saturate_cast<DT>(v[i]); // saturate_cast also rounds similarly to round()
    return result;
}

#endif
