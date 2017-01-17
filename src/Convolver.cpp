#ifndef CONVOLVER_CPP
#define CONVOLVER_CPP

#include "../include/KernelFilter.h"

#include <iostream>

template <typename DT, size_t CH>
KernelFilter<DT,CH>::Convolver::Convolver(const Mat& data, const Mat& kernel, const Cell& kernelPin)
    : data(data), kernel(kernel), kernelPin(kernelPin) {}

template <typename DT, size_t CH>
Mat KernelFilter<DT,CH>::Convolver::convolveCroppingEdges() const {
    size_t resultRows = data.rows - kernel.rows + 1;
    size_t resultCols = data.cols - kernel.cols + 1;
    Mat result(resultRows, resultCols, data.type());

    int pinRow = kernelPin.row;
    int pinCol = kernelPin.col;

    for (size_t i = 0; i < resultRows; ++i)
        for (size_t j = 0; j < resultCols; ++j)
            result.at<PixelType>(i,j) = convolutionStep(Cell(pinRow+i, pinCol+j));

    return result;
}

template <typename DT, size_t CH>
typename KernelFilter<DT,CH>::PixelType KernelFilter<DT,CH>::Convolver::convolutionStep(const Cell& target) const {
    Vec<double,CH> sum;
    Cell blockTopLeft(target.row - kernelPin.row, target.col - kernelPin.col);
    for (size_t i = 0; i < kernel.rows; ++i)
        for (size_t j = 0; j < kernel.cols; ++j)
            sum +=
                kernel . template at<double>(i,j) *
                (Vec<double,CH>)data . template at<PixelType>(blockTopLeft.row + i, blockTopLeft.col + j);
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
