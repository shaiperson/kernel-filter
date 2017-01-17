#include "catch.hpp"
#include "test.h"

SCENARIO("Filtering with edge crop policy crops image correctly", "[edgecrop] [id]") {
    GIVEN("A square single-channel image") {
        Mat increasing(5,5,CV_8UC1);
        [&increasing] {
            for(size_t i = 0; i < 5; ++i)
                for(size_t j = 0; j < 5; ++j) increasing.at<uchar>(i,j) = i*5+j+1;
        } ();

        Mat kernel, result;

        WHEN("Filtered with a smaller square center-pinned identity kernel") {
            kernel = (Mat_<double>(3,3) << 0,0,0,0,1,0,0,0,0);
            KernelFilterEdgeCrop<uchar,1> filter(increasing, kernel, Cell(1,1));
            result = filter.compute();

            THEN("Result is a center section of original image of appropriate dimensions") {
                vector<uchar> expectedValues = {7,8,9,12,13,14,17,18,19};
                REQUIRE(result.rows == 3);
                REQUIRE(result.cols == 3);
                REQUIRE(std::equal(expectedValues.begin(), expectedValues.end(), result.begin<uchar>()));
            }
        }
    }
}
