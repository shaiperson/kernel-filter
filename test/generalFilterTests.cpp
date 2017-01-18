#include "catch.hpp"
#include "test.h"
#include "../include/KernelFilterEdgeCrop.h"
#include "../include/KernelFilterEdgeExtension.h"
#include "../include/KernelFilterEdgeWrap.h"

SCENARIO(
    "Filtering with any non-cropping policy using any identity kernel-pin configuration results in identical image",
    "[general] [non-cropping] [id]"
) {
    GIVEN("A non-square image") {
        Mat increasing(4,5,CV_8UC1);
        [&increasing] {
            for(size_t i = 0; i < 4; ++i)
                for(size_t j = 0; j < 5; ++j) increasing.at<uchar>(i,j) = i*5+j+1;
        } ();

        WHEN("Filtered with a square center-pinned identity kernel") {
            Mat kernel = (Mat_<double>(3,3) << 0,0,0,0,1,0,0,0,0);
            KernelFilterEdgeExtension<uchar,1> filterExtension(increasing, kernel, Cell(1,1));
            KernelFilterEdgeWrap<uchar,1> filterWrap(increasing, kernel, Cell(1,1));

            Mat resultExtension = filterExtension.compute();
            Mat resultWrap = filterWrap.compute();

            THEN("Result is equal to original image") {
                REQUIRE(std::equal(resultExtension.begin<uchar>(), resultExtension.end<uchar>(), increasing.begin<uchar>()));
                REQUIRE(std::equal(resultWrap.begin<uchar>(), resultWrap.end<uchar>(), increasing.begin<uchar>()));
            }
        }

        WHEN("Filtered with a non-square non-center-pinned identity kernel") {
            Mat kernel = (Mat_<double>(2,3) << 0,0,0,0,0,1);
            KernelFilterEdgeExtension<uchar,1> filterExtension(increasing, kernel, Cell(1,2));
            KernelFilterEdgeWrap<uchar,1> filterWrap(increasing, kernel, Cell(1,2));

            Mat resultExtension = filterExtension.compute();
            Mat resultWrap = filterWrap.compute();

            THEN("Result is equal to original image") {
                REQUIRE(std::equal(resultExtension.begin<uchar>(), resultExtension.end<uchar>(), increasing.begin<uchar>()));
                REQUIRE(std::equal(resultWrap.begin<uchar>(), resultWrap.end<uchar>(), increasing.begin<uchar>()));
            }
        }
    }
}

SCENARIO("Filtering with any filter using null kernels results in null images", "[general] [null]") {
    GIVEN("A non-square image") {
        Mat increasing(4,5,CV_8UC1);
        [&increasing] {
            for(size_t i = 0; i < 4; ++i)
                for(size_t j = 0; j < 5; ++j) increasing.at<uchar>(i,j) = i*5+j+1;
        } ();

        WHEN("Filtered with different null kernels") {
            Mat nullKernel1 = (Mat_<double>(3,3) << 0,0,0,0,0,0,0,0,0);
            Mat nullKernel2 = (Mat_<double>(2,4) << 0,0,0,0,0,0,0,0);

            KernelFilterEdgeCrop<uchar,1> filterCrop1(increasing, nullKernel1, Cell(1,1));
            KernelFilterEdgeCrop<uchar,1> filterCrop2(increasing, nullKernel2, Cell(1,1));

            KernelFilterEdgeExtension<uchar,1> filterExtension1(increasing, nullKernel1, Cell(1,1));
            KernelFilterEdgeExtension<uchar,1> filterExtension2(increasing, nullKernel2, Cell(1,1));

            KernelFilterEdgeWrap<uchar,1> filterWrap1(increasing, nullKernel1, Cell(1,1));
            KernelFilterEdgeWrap<uchar,1> filterWrap2(increasing, nullKernel2, Cell(1,1));

            Mat resultCrop1 = filterCrop1.compute();
            Mat resultCrop2 = filterCrop2.compute();

            Mat resultExtension1 = filterExtension1.compute();
            Mat resultExtension2 = filterExtension2.compute();

            Mat resultWrap1 = filterWrap1.compute();
            Mat resultWrap2 = filterWrap2.compute();

            THEN("Result is equal to original image") {
                REQUIRE(std::all_of(resultCrop1.begin<uchar>(), resultCrop1.end<uchar>(), [](uchar pixel) {return pixel == 0;}));
                REQUIRE(std::all_of(resultCrop2.begin<uchar>(), resultCrop2.end<uchar>(), [](uchar pixel) {return pixel == 0;}));

                REQUIRE(std::all_of(resultExtension1.begin<uchar>(), resultExtension1.end<uchar>(), [](uchar pixel) {return pixel == 0;}));
                REQUIRE(std::all_of(resultExtension2.begin<uchar>(), resultExtension2.end<uchar>(), [](uchar pixel) {return pixel == 0;}));

                REQUIRE(std::all_of(resultWrap1.begin<uchar>(), resultWrap1.end<uchar>(), [](uchar pixel) {return pixel == 0;}));
                REQUIRE(std::all_of(resultWrap2.begin<uchar>(), resultWrap2.end<uchar>(), [](uchar pixel) {return pixel == 0;}));
            }
        }
    }
}
