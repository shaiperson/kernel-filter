#ifndef KERNELFILTEREDGEWRAP_H
#define KERNELFILTEREDGEWRAP_H

#include "KernelFilter.h"

template <typename DataType, size_t Channels>
class KernelFilterEdgeWrap : public KernelFilter<DataType, Channels> {

    typedef KernelFilter<DataType, Channels> super;

    using super::KernelFilter;
    using super::image;
    using super::kernel;
    using super::kernelPin;

    Mat toConvolutionData() const;

};

#include "../src/KernelFilterEdgeWrap.cpp"

#endif
