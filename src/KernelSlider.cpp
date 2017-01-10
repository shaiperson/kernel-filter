#include "../include/KernelSlider.h"

template <class PixelType>
KernelSlider<PixelType>::KernelSlider(const Mat& image, const Kernel& kernel)
    : image(image), kernel(kernel) {}

