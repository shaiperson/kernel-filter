#include "../include/KernelFilter.h"

template <class PixelType, class KernelType>
KernelFilter<PixelType, KernelType>::KernelFilter(const Mat& image, const Kernel& kernel)
    : image(image), kernel(kernel) {}

template <class PixelType, class KernelType>
Mat KernelFilter<PixelType, KernelType>::compute() const {
    return convolve(imageToConvolutionData());
}

