#ifndef KERNELFILTEREDGECROP_H
#define KERNELFILTEREDGECROP_H

#include "header.h"
#include "KernelFilter.h"

template <typename DataType, size_t Channels>
class KernelFilterEdgeCrop : public KernelFilter<DataType, Channels> {

    typedef KernelFilter<DataType, Channels> super;

    using super::KernelFilter;
    using super::image;

    Mat toConvolutionData() const {
        return super::image;
    }
};

#endif
