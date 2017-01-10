#include "../include/KernelFilter.h"

template <class PixelType, class KernelType>
KernelFilter<PixelType, KernelType>::KernelFilter(const Mat& image, const Kernel& kernel)
    : image(image), kernel(kernel) {}

template <class PixelType, class KernelType>
Mat KernelFilter<PixelType, KernelType>::compute() const {
    return convolve(imageToConvolutionData());
}

template <class PixelType, class KernelType>
Mat KernelFilter<PixelType, KernelType>::convolve(const Mat& data) const {
    KernelSumSlider<PixelType, KernelType> slider(data, kernel);
    Mat result(resultRows, resultCols, image.type());
    Ptr<PixelType> resultPtr = result.ptr(0);

    size_t resultRows = data.rows - (kernel.weights).rows + 1;
    size_t resultCols = data.cols - (kernel.weights).cols + 1;

    for (size_t i = (kernel.pin).y; i < (kernel.pin).y + resultRows; ++i) {
        for (size_t j = (kernel.pin).x; j < (kernel.pin).x + resultCols; ++j) {
            Scalar channelMeans = slider.sumOnTarget(Point(i,j));
            for (size_t c = 0; c < data.channels(); ++c) {
                *resultPtr++ = channelMeans[c] / (kernel.weights).total();
            }
        }
    }
    
    return result;
}
