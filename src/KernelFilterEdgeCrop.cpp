#ifndef KERNELFILTEREDGECROP_CPP
#define KERNELFILTEREDGECROP_CPP

template <typename DT, size_t CH>
Mat KernelFilterEdgeCrop<DT,CH>::toConvolutionData() const {
    return super::image;
}

#endif
