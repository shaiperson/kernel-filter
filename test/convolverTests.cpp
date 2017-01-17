#include "catch.hpp"
#include "test.h"

SCENARIO("Convolving crops image appropriately", "[cropping]") {
    GIVEN("A square image of certain pixel type") {
        Mat image = Mat_<double>(5,5);
        Mat kernel, result;

        WHEN("Convolved with a kernel of the same size and any pin point") {

            kernel = Mat_<double>(5,5);
            KernelFilter<double,1>::Convolver convolver(image, kernel, Cell(2,4));
            result = convolver.convolveCroppingEdges();

            THEN("Result is 1x1 in size") {
                REQUIRE(result.total() == 1);
            }
        }

        WHEN("Convolved with a smaller not-1x1 kernel with any pin point") {

            kernel = Mat_<double>(3,3);
            KernelFilter<double,1>::Convolver convolver(image, kernel, Cell(2,1));
            result = convolver.convolveCroppingEdges();

            THEN("Result size is 3x3") {
                REQUIRE(result.rows == 3);
                REQUIRE(result.cols == 3);
            }
        }

        WHEN("Convolved with a 1x1 kernel") {

            kernel = Mat_<double>(1,1);
            KernelFilter<double,1>::Convolver convolver(image, kernel, Cell(0,0));
            result = convolver.convolveCroppingEdges();

            THEN("Result is same size as original") {
                REQUIRE(result.rows == 5);
                REQUIRE(result.cols == 5);
            }
        }
    }
}

SCENARIO("Convolving a non-square image with multiple channels and integer data type with different identity kernels", "[id]") {
    GIVEN("A non-square image of certain pixel type") {
        Mat allOneTwoThrees(4,5,CV_8UC3);
        [&allOneTwoThrees] {
            for(size_t i = 0; i < 4; ++i)
                for(size_t j = 0; j < 5; ++j)
                    allOneTwoThrees.ptr<Vec3b>(i)[j] = Vec3b(1,2,3);
        } ();

        Mat idKernel, result;

        WHEN("Convolving with identity kernel-pin config of the same size") {
            idKernel = (Mat_<double>(4,5) << 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0);
            KernelFilter<uchar,3>::Convolver convolver(allOneTwoThrees, idKernel, Cell(3,2));
            result = convolver.convolveCroppingEdges();

            THEN("All result values are correct") {
                REQUIRE(
                    std::all_of(
                        result.begin<Vec3b>(),
                        result.end<Vec3b>(),
                        [](Vec3b pixel) {return pixel[0] == 1 && pixel[1] == 2 && pixel[2] == 3;}
                    )
                );
            }
        }

        WHEN("Convolving with identity kernel-pin of smaller size") {
            idKernel = (Mat_<double>(3,4) << 0,0,0,0,0,0,1,0,0,0,0,0);
            KernelFilter<uchar,3>::Convolver convolver(allOneTwoThrees, idKernel, Cell(1,2));
            result = convolver.convolveCroppingEdges();

            THEN("All result values are correct") {
                REQUIRE(
                    std::all_of(
                        result.begin<Vec3b>(),
                        result.end<Vec3b>(),
                        [](Vec3b pixel){return pixel[0] == 1 && pixel[1] == 2 && pixel[2] == 3;}
                    )
                );
            }
        }

        WHEN("Convolving with identity kernel of size 1x1") {
            idKernel = (Mat_<double>(1,1) << 1);
            KernelFilter<uchar,3>::Convolver convolver(allOneTwoThrees, idKernel, Cell(0,0));
            result = convolver.convolveCroppingEdges();

            THEN("All result values are correct") {
                REQUIRE(
                    std::all_of(
                        result.begin<Vec3b>(),
                        result.end<Vec3b>(),
                        [](Vec3b pixel){return pixel[0] == 1 && pixel[1] == 2 && pixel[2] == 3;}
                    )
                );
            }
        }
    }
}

SCENARIO("Convolving a square single-channel image with sum kernel", "[sum]") {
    GIVEN("A square single-channel image") {
        Mat allOnes(5,5,CV_8UC1);
        [&allOnes] {
            for(size_t i = 0; i < 5; ++i)
                for(size_t j = 0; j < 5; ++j) allOnes.at<uchar>(i,j) = 1;
        } ();

        Mat sumKernel, result;

        WHEN("Convolved with a sum kernel of the same size") {
            sumKernel = (Mat_<double>(5,5) << 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1);
            KernelFilter<uchar,1>::Convolver convolver(allOnes, sumKernel, Cell(2,2));
            result = convolver.convolveCroppingEdges();

            THEN("Result is a one pixel image containing the sum of pixels in original image") {
                REQUIRE(result.total() == 1);
                REQUIRE(result.at<uchar>(0,0) == std::accumulate(allOnes.begin<uchar>(), allOnes.end<uchar>(), 0));
            }
        }
    }
}
