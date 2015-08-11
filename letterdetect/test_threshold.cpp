#include <UnitTest++/UnitTest++.h>

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <vector>
#include <string>
#include <iostream>
#include <memory>
#include <algorithm>

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
        vector<int> expectedResult;
    };

    CornerSquareInput aa { "A", "A", Point(104,431), Point(363,435), "../data/AA.jpg", {6,7}};
    CornerSquareInput al { "A", "L", Point(29,487), Point(422,471), "../data/7AL.jpg", {5,7}};

    CornerSquareInput be { "B", "E", Point(51,449), Point(382,459), "../data/9BE.JPG", {9}};
    CornerSquareInput cd { "C", "D", Point(77,497), Point(396,487), "../data/6CD.jpg", {6,7}};

    CornerSquareInput df { "D", "F", Point(75,485), Point(418,492), "../data/5DF.jpg", {0,1,5,9,10}};
    CornerSquareInput ea { "E", "A", Point(82,416), Point(337,414), "../data/3EA.jpg", {2, 4, 11, 3, 7, 10}};
    CornerSquareInput ec { "E", "C", Point(44,466), Point(376,489), "../data/1EC.jpg", {1}};
    CornerSquareInput ed { "E", "D", Point(79,475), Point(387,465), "../data/10ED.jpg", {}};
    CornerSquareInput ee { "E", "E", Point(34,497), Point(389,504), "../data/1EE.jpg", {4,5,6}};
    CornerSquareInput fh { "F", "H", Point(56,497), Point(402,489), "../data/FH.jpg", {2}};
    CornerSquareInput fj { "F", "J", Point(95,442), Point(393,459), "../data/1FJ.jpg", {0,1,5}};
    CornerSquareInput hh { "H", "H", Point(40,475), Point(390,460), "../data/11HH.JPG", {10}};
    CornerSquareInput hi { "H", "I", Point(82,459), Point(400,441), "../data/6HI.jpg", {6}};
    CornerSquareInput ic { "I", "C", Point(68,458), Point(409,483), "../data/0IC.jpg", {0,1}};
    CornerSquareInput id { "I", "D", Point(58,474), Point(397,497), "../data/ID.jpg", {}};
    CornerSquareInput kl { "K", "L", Point(37,484), Point(425,456), "../data/KL.jpg", {3, 4, 6, 10, 7}};
    CornerSquareInput ja { "J", "A", Point(91,483), Point(385,451), "../data/JA.jpg", {9}};
    CornerSquareInput nl { "N", "L", Point(61,491), Point(419,476), "../data/5NL.jpg", {5}};
    CornerSquareInput ob { "O", "B", Point(74,481), Point(392,445), "../data/7OB.jpg", {7}};
    vector<CornerSquareInput> data {
                aa,
                al,
                be,
                cd,
                df,
                ea,
//                ec,
                ed,
                ee,
                fh,
                fj,
                hh,
                        hi,
                kl,
//                id,
                ic,
                        nl,
                        ob
    };

    TEST(Sanity)
    {
        CHECK_EQUAL(1, 1);
    }

    TEST(smoke_stamps)
    {
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

            bool found { false };
            vector<int> actualPlates = Threshold_Demo( 0, 0, src, src_gray, item );
            sort(actualPlates.begin(),actualPlates.end());
            sort(item.expectedResults.begin(), item.expectedResults.end());
            for (int i = 0; i < min(item.expectedResults.size(),actualPlates.size()); i++)
            {
                CHECK_EQUAL(item.expectedResults[i], actualPlates[i]);
            }
        }
    }
}

int main(int, const char *[])
{
    return UnitTest::RunAllTests();
}
