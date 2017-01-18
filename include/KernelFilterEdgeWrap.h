#ifndef KERNELFILTEREDGEWRAP_H
#define KERNELFILTEREDGEWRAP_H

#include "header.h"
#include "KernelFilter.h"

template <typename DataType, size_t Channels>
class KernelFilterEdgeWrap : public KernelFilter<DataType, Channels> {

    typedef KernelFilter<DataType, Channels> super;

    using super::KernelFilter;
    using super::image;
    using super::kernel;
    using super::kernelPin;

    Mat toConvolutionData() const {
        Mat result(image.rows+kernel.rows-1, image.cols+kernel.cols-1, image.type());
        copyMakeBorder(
            image,
            result,
            kernelPin.row,
            kernel.rows-kernelPin.row-1,
            kernelPin.col,
            kernel.cols-kernelPin.col-1,
            BORDER_WRAP
        );
        std::cout << result << std::endl;
        return result;
    }

};

#endif
