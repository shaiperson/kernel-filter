#include "catch.hpp"
#include "test.h"
#include "../include/KernelFilterEdgeWrap.h"

SCENARIO("Filtering with edge wrapping", "[wrap][border values]") {
    GIVEN("A 3x3 single-channel image with all different values") {
        Mat image = (Mat_<uchar>(3,3) << 1,2,3,4,5,6,7,8,9);

        WHEN("Filtered with a 3x3 sum kernel") {
            Mat kernel = (Mat_<double>(3,3) << 1,1,1,1,1,1,1,1,1);
            KernelFilterEdgeWrap<uchar,1> filter(image, kernel, Cell(1,1));
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

                REQUIRE(std::all_of(borderValues.cbegin(), borderValues.cend(), [](uchar pixel){return pixel == 45;}));
            }
        }
    }
}
