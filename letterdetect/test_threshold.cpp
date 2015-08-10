#include <UnitTest++/UnitTest++.h>

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <vector>
#include <string>
#include <iostream>
#include <memory>

#include "threshold.h"

using namespace cv;
using namespace std;

SUITE(CornerLettersSuite)
{
    struct InputArgs {
        string leftLetter; // e.g. AL
        string rightLetter; // e.g. AL
        Point left;
        Point right;
        int expectedResult;
    };

    CornerSquareInput aa { "A", "A", Point(104,431), Point(363,435), "../data/AA.jpg" };
    CornerSquareInput al { "A", "L", Point(25,481), Point(419,473), "../data/AL.jpg" };
    CornerSquareInput fh { "F", "H", Point(56,497), Point(402,489), "../data/FH.jpg" };
    CornerSquareInput kl { "K", "L", Point(37,484), Point(425,456), "../data/KL.jpg" };
    CornerSquareInput id { "I", "D", Point(58,474), Point(397,497), "../data/ID.jpg" };

    TEST(Sanity)
    {
       CHECK_EQUAL(1, 1);
    }

    TEST(smoke_stamps)
    {
        vector<CornerSquareInput> data { aa, al, fh, kl, id};
        for (CornerSquareInput item : data) {
            /// Load an image
            Mat src = imread( item.file, 1 );
            if( src.empty() )
            {
                cout << "Couldn't load " << item.file << endl;
                return;
            }

            Mat src_gray;
            /// Convert the image to Gray
            cvtColor( src, src_gray, CV_RGB2GRAY );
            resize( src_gray, src_gray, Size(77*6,88*6) );

            Threshold_Demo( 0, 0, src, src_gray, item );

            /*
            cout << "\tResult: " << actualPlate << ", Expected: " << item.expectedResult << endl;
            */
        }
    }
}

int main(int, const char *[])
{
   return UnitTest::RunAllTests();
}
