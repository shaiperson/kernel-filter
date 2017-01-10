#include "../include/KernelFilter.h"

template <class T>
KernelFilter<T>::KernelFilter(const Mat& image, const Kernel& kernel)
    : image(image), kernel(kernel) {}

template <class T>
Mat KernelFilter<T>::compute() const {
    return convolve(imageToConvolutionData());
}

