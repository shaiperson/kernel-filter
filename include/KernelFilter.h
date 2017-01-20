#ifndef KERNELFILTER_H
#define KERNELFILTER_H

#include <opencv2/core.hpp>

using namespace std;
using namespace cv;

struct Cell {
    Cell(int row, int col) : row(row), col(col) {}
    Cell(const Cell& another) : row(another.row), col(another.col) {}
    Cell() : row(-1), col(-1) {}
    int row, col;
};

template <typename DataType, size_t Channels>
class KernelFilter {

typedef Vec<DataType, Channels> PixelType;

public:

    KernelFilter(const Mat& image, const Mat& kernel, const Cell& kernelPin);
    KernelFilter(const Mat& image);
    void setKernel(Mat& kernel, Cell& kernelPin);

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

#include "../src/KernelFilter.cpp"
#include "../src/Convolver.cpp"

#endif
