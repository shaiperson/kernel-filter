#include "../include/KernelFilter.h"

KernelFilter::KernelFilter(const Mat& image, const Kernel& kernel)
    : image(image), kernel(kernel) {}

Mat KernelFilter::compute() const {
    return convolve(imageToConvolutionData());
}

Scalar KernelFilter::sumOnTarget(const Point& target, const Mat& data) const {
    Scalar sum(0,0,0);
    size_t blockFirstRow = target.y - (kernel.pin).y;
    size_t blockFirstCol = target.x - (kernel.pin).x;
    for (size_t i = 0; i < (kernel.weights).rows; ++i)
        for (size_t j = 0 ; j < (kernel.weights).cols; ++j)
            for (size_t c = 0; c < data.channels(); ++c)
                sum[c] +=
                    data.at<Vec3d>(blockFirstRow + i, blockFirstCol + j)[c] *
                    (kernel.weights).at<double>(i,j);
    return sum;
}

Mat KernelFilter::convolve(const Mat& data) const {
    size_t resultRows = data.rows - (kernel.weights).rows + 1;
    size_t resultCols = data.cols - (kernel.weights).cols + 1;

    Mat result(resultRows, resultCols, image.type());
    Ptr<Vec3d> resultPtr = result.ptr(0);

    for (size_t i = (kernel.pin).y; i < (kernel.pin).y + resultRows; ++i) {
        for (size_t j = (kernel.pin).x; j < (kernel.pin).x + resultCols; ++j) {
            Scalar channelMeans = sumOnTarget(Point(i,j), data);
            for (size_t c = 0; c < data.channels(); ++c) {
                *resultPtr++ = channelMeans[c] / (kernel.weights).total();
            }
        }
    }

    return result;
}
