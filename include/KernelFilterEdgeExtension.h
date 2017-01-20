#ifndef KERNELFILTEREDGEEXTENSION_H
#define KERNELFILTEREDGEEXTENSION_H

#include "KernelFilter.h"

template <typename DataType, size_t Channels>
class KernelFilterEdgeExtension : public KernelFilter<DataType, Channels> {

    typedef KernelFilter<DataType, Channels> super;

    using super::KernelFilter;
    using super::image;
    using super::kernel;
    using super::kernelPin;

    Mat toConvolutionData() const;

};

#include "../src/KernelFilterEdgeExtension.cpp"

#endif
