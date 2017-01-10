#include "../include/KernelSumSlider.h"

template <class PixelType, class KernelType>
KernelSumSlider<PixelType, KernelType>::KernelSumSlider(const Mat& image, const Kernel& kernel)
    : image(image), kernel(kernel) {}

// PixelType could be, for instance, vec3b
template <class PixelType, class KernelType>
Scalar KernelSumSlider<PixelType, KernelType>::sumOnTarget(const Point& target) const {
    Scalar sum(0,0,0);
    size_t blockFirstRow = target.y - (kernel.pin).y;
    size_t blockFirstCol = target.x - (kernel.pin).x;
    for (size_t i = 0; i < (kernel.weights).rows; ++i)
        for (size_t j = 0 ; j < (kernel.weights).cols; ++j)
            for (size_t c = 0; c < image.channels(); ++c)
                sum[c] +=
                    image.at<PixelType>(blockFirstRow + i, blockFirstCol + j)[c] *
                    (kernel.weights).at<KernelType>(i,j);
    return sum;
}

// template <class PixelType, class KernelType>
// PixelType KernelSumSlider<PixelType, KernelType>::slideRight(const Point& target, PixelType prev) const {
// }
//
// template <class PixelType, class KernelType>
// PixelType KernelSumSlider<PixelType, KernelType>::slideDown(const Point& target, PixelType prev) const {
// }
