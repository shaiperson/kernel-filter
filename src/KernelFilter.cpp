#include "../include/KernelFilter.h"

template <class T>
KernelFilter<T>::KernelFilter(const Mat& image, const Kernel& kernel)
    : image(image), kernel(kernel) {}

