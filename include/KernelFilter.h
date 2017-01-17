#ifndef KERNELFILTER_H
#define KERNELFILTER_H

#include "header.h"

struct Cell {
    Cell(size_t row, size_t col) : row(row), col(col) {}
    Cell(const Cell& another) : row(another.row), col(another.col) {}
    size_t row, col;
};

template <typename DataType, size_t Channels>
class KernelFilter {

typedef Vec<DataType, Channels> PixelType;

public:

    KernelFilter(const Mat& image, const Mat& kernel, const Cell& kernelPin);
    Mat compute() const;

    class Convolver {
    public:
        Convolver(const Mat& data, const Mat& kernel, const Cell& kernelPin);
        Mat convolveCroppingEdges() const;
    private:
        Mat data;
        Mat kernel;
        Cell kernelPin;

        PixelType convolutionStep(const Cell& target) const;
        PixelType roundAndConvertToDataType(const Vec<double,Channels>&) const;
    };

protected:

    Mat image;
    Mat kernel;
    Cell kernelPin;

    virtual Mat toConvolutionData() const = 0;

};

template <typename DataType, size_t Channels>
class KernelFilterEdgeCrop : public KernelFilter<DataType, Channels> {

    using KernelFilter<DataType, Channels>::KernelFilter;
    using KernelFilter<DataType, Channels>::image;

    Mat toConvolutionData() const {
        return image;
    }
};

#include "../src/KernelFilter.cpp"
#include "../src/Convolver.cpp"

#endif
