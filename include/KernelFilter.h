#ifndef KERNELFILTER_H
#define KERNELFILTER_H

#include "header.h"
#include <cmath>

template <typename DataType, size_t Channels>
class KernelFilter {

typedef Vec<DataType, Channels> PixelType;

public:
    KernelFilter(const Mat& data, const Mat& kernel, const Point& kernelPin);
    Mat compute() const;

protected:
    Mat data;
    Mat kernel;
    Point kernelPin;

    virtual Mat toConvolutionData() const = 0;
    Mat convolve(const Mat& convolutionData) const;
    PixelType convolutionStep(const Mat& data, const Point& target) const;
    PixelType roundAndConvertToDataType(const Vec<double,Channels>&) const;

};

template <typename DataType, size_t Channels>
class KernelFilterEdgeCrop : public KernelFilter<DataType, Channels> {

    using KernelFilter<DataType, Channels>::KernelFilter;
    using KernelFilter<DataType, Channels>::data;

    Mat toConvolutionData() const {
        return data;
    }

};

#include "../src/KernelFilter.cpp"

#endif
