#ifndef KERNELFILTEREDGEEXTENSION_CPP
#define KERNELFILTEREDGEEXTENSION_CPP

template <typename DT, size_t CH>
Mat KernelFilterEdgeExtension<DT,CH>::toConvolutionData() const {
    Mat result(image.rows+kernel.rows-1, image.cols+kernel.cols-1, image.type());
    copyMakeBorder(
        image,
        result,
        kernelPin.row,
        kernel.rows-kernelPin.row-1,
        kernelPin.col,
        kernel.cols-kernelPin.col-1,
        BORDER_REPLICATE
    );
    return result;
}

#endif
