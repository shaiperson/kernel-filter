#ifndef KERNELFILTER_H
#define KERNELFILTER_H

#include "header.h"
#include "Kernel.h"
#include "KernelSumSlider.h"

template <class PixelType, class KernelType>
class KernelFilter {

public:
    KernelFilter(const Mat& image, const Kernel& kernel);
    Mat compute() const;

private:
    Mat image;
    Kernel kernel;

    Mat convolve(const Mat& data) const;
    Scalar sumOnTarget(const Point& target) const;
    virtual Mat imageToConvolutionData() const = 0;

};

#endif
