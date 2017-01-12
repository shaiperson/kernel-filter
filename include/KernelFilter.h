#ifndef KERNELFILTER_H
#define KERNELFILTER_H

#include "header.h"
#include <cmath>

class KernelFilter {

public:
    KernelFilter(const Mat& data, const Mat& kernel, const Point& kernelPin);
    Mat compute() const;

protected:
    Mat data;
    Mat kernel;
    Point kernelPin;

    virtual Mat toConvolutionData() const = 0;
    Mat convolve(const Mat& convolutionData) const;
    Vec3b convolutionStep(const Mat& data, const Point& target) const;

};

class KernelFilterEdgeCrop : public KernelFilter {

    using KernelFilter::KernelFilter;
    Mat toConvolutionData() const {
        return data;
    }

};

#endif
