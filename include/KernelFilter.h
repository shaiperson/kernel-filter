#ifndef KERNELFILTER_H
#define KERNELFILTER_H

#include "header.h"
#include "Kernel.h"
#include "KernelSlider.h"

template <class PixelType>
class KernelFilter {

public:
    KernelFilter(const Mat& image, const Kernel& kernel);
    Mat compute() const;

private:
    Mat image;
    Kernel kernel;

    virtual Mat imageToConvolutionData() const = 0;
    Mat convolve(const Mat& data) const;

};

#endif
