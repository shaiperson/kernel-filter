#ifndef KERNELFILTEREDGECROP_H
#define KERNELFILTEREDGECROP_H

#include "KernelFilter.h"

template <typename DataType, size_t Channels>
class KernelFilterEdgeCrop : public KernelFilter<DataType, Channels> {

    typedef KernelFilter<DataType, Channels> super;

    using super::KernelFilter;
    using super::image;

    Mat toConvolutionData() const;
};

#include "../src/KernelFilterEdgeCrop.cpp"

#endif
