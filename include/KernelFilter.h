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

    class Convolver {
    public:
        Convolver(const KernelFilter* filter) : filter(filter) {}
        PixelType convolutionStep(const Mat& data, const Point& target) const;
        PixelType roundAndConvertToDataType(const Vec<double,Channels>&) const;
    private:
        const KernelFilter* filter;
    };

protected:
    Mat data;
    Mat kernel;
    Point kernelPin;

    virtual Mat toConvolutionData() const = 0;
    Mat convolve(const Mat& convolutionData) const;

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
