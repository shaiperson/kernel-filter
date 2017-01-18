#include "catch.hpp"
#include "test.h"
#include "../include/KernelFilterEdgeExtension.h"

SCENARIO("Filtering with edge extension", "[extension] [border values]") {
    GIVEN("A 3x3 single-channel image with all 1s") {
        Mat image = (Mat_<uchar>(3,3) << 1,1,1,1,1,1,1,1,1);

        WHEN("Filtered with a 3x3 sum kernel") {
            Mat kernel = (Mat_<double>(3,3) << 1,1,1,1,1,1,1,1,1);
            KernelFilterEdgeExtension<uchar,1> filter(image, kernel, Cell(1,1));
            Mat result = filter.compute();

            THEN("Result's borders has sum of image elements") {
                std::vector<uchar> borderValues = {
                    result.at<uchar>(0,0),
                    result.at<uchar>(0,1),
                    result.at<uchar>(0,2),
                    result.at<uchar>(1,0),
                    result.at<uchar>(1,2),
                    result.at<uchar>(2,0),
                    result.at<uchar>(2,1),
                    result.at<uchar>(2,2),
                };

                REQUIRE(std::all_of(borderValues.cbegin(), borderValues.cend(), [](uchar pixel){return pixel == 9;}));
            }
        }
    }
}
