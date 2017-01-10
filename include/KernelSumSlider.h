#ifndef KERNELSLIDER_H
#define KERNELSLIDER_H

#include "header.h"
#include "Kernel.h"

template <class PixelType, class KernelType>
class KernelSumSlider {
public:
    KernelSumSlider(const Mat& image, const Kernel& kernel);
    Scalar sumOnTarget(const Point& target) const;
    // PixelType slideRight(const Point& target, PixelType prev) const;
    // PixelType slideDown(const Point&, PixelType prev) const;

private:
    Mat image;
    Kernel kernel;
};

#endif
