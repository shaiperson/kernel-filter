#ifndef KERNELFILTER_H
#define KERNELFILTER_H

#include "header.h"
#include <cmath>

template <typename DataType, size_t Channels>
class KernelFilter {

typedef Vec<DataType, Channels> PixelType;

public:

    KernelFilter(const Mat& image, const Mat& kernel, const Point& kernelPin);
    Mat compute() const;

    class Convolver {
    public:
        Convolver(const Mat& data, const Mat& kernel, const Point& kernelPin);
        Mat convolveCroppingEdges() const;
    private:
        Mat data;
        Mat kernel;
        Point kernelPin;

        PixelType convolutionStep(const Point& target) const;
        PixelType roundAndConvertToDataType(const Vec<double,Channels>&) const;
    };

protected:

    Mat image;
    Mat kernel;
    Point kernelPin;

    virtual Mat toConvolutionData() const = 0;

};

template <typename DataType, size_t Channels>
class KernelFilterEdgeCrop : public KernelFilter<DataType, Channels> {

    using KernelFilter<DataType, Channels>::KernelFilter;
    using KernelFilter<DataType, Channels>::image;

    Mat toConvolutionData() const {
        return image;
    }
};

#include "../src/KernelFilter.cpp"
#include "../src/Convolver.cpp"

#endif
