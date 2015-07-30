/**
 * @file Threshold.cpp
 * @brief Sample code that shows how to use the diverse threshold options offered by OpenCV
 * @author OpenCV team
 */

#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

using namespace cv;
using namespace std;

/// Global variables

int threshold_value = 0;
int threshold_type = 3;;
int const max_value = 255;
int const max_type = 4;
int const max_BINARY_value = 255;

Mat src, src_gray, dst;
char* window_name = "Threshold Demo";

char* trackbar_type = "Type: \n 0: Binary \n 1: Binary Inverted \n 2: Truncate \n 3: To Zero \n 4: To Zero Inverted";
char* trackbar_value = "Value";

/// Function headers
void Threshold_Demo( int, void* );

/**
 * @function main
 */
int main( int argc, char** argv )
{
    /// Load an image
    src = imread( argv[1], 1 );

    /// Convert the image to Gray
    cvtColor( src, src_gray, CV_RGB2GRAY );

    /// Create a window to display results
    namedWindow( window_name, CV_WINDOW_AUTOSIZE );

    /// Call the function to initialize
    Threshold_Demo(0, 0);
}

static double angle( Point pt1, Point pt2, Point pt0 )
{
    double dx1 = pt1.x - pt0.x;
    double dy1 = pt1.y - pt0.y;
    double dx2 = pt2.x - pt0.x;
    double dy2 = pt2.y - pt0.y;
    return (dx1*dx2 + dy1*dy2)/sqrt((dx1*dx1 + dy1*dy1)*(dx2*dx2 + dy2*dy2) + 1e-10);
}


/**
 * @function Threshold_Demo
 */
void Threshold_Demo( int, void* )
{
    vector<vector<Point> > squares;
    vector<vector<Point> > contours;
    for (int i = 40; i < 130; i++)
    {
        squares.clear();
        Mat detected_edges;
        threshold( src_gray, dst, i, 255, 1);
        /// Reduce noise with a kernel 3x3
        blur( dst, detected_edges, Size(3,3) );

        /// Canny detector
        Canny( detected_edges, detected_edges, i, i*3, 3 );

        /// Using Canny's output as a mask, we display our result
        dst = Scalar::all(0);

        src_gray.copyTo( dst, detected_edges);

        // find contours and store them all as a list
        findContours(detected_edges, contours, RETR_LIST, CHAIN_APPROX_SIMPLE);
//        cout << contours.size() << endl;

        vector<Point> approx;
        // test each contour
        for( size_t i = 0; i < contours.size(); i++ )
        {
            // approximate contour with accuracy proportional
            // to the contour perimeter
            approxPolyDP(Mat(contours[i]), approx, 4, true);

            // square contours should have 4 vertices after approximation
            // relatively large area (to filter out noisy contours)
            // and be convex.
            // Note: absolute value of an area is used because
            // area may be positive or negative - in accordance with the
            // contour orientation
            if( approx.size() == 4 &&
                    //                 fabs(contourArea(Mat(approx))) > 1000 &&
                    isContourConvex(Mat(approx)) )
            {
                double maxCosine = 0;

                for( int j = 2; j < 5; j++ )
                {
                    // find the maximum cosine of the angle between joint edges
                    double cosine = fabs(angle(approx[j%4], approx[j-2], approx[j-1]));
                    maxCosine = MAX(maxCosine, cosine);
                }

                // if cosines of all angles are small
                // (all angles are ~90 degree) then write quandrange
                // vertices to resultant sequence
                if( maxCosine < 0.3 ) {
                    if(std::find(squares.begin(), squares.end(), approx) != squares.end()) {
                        /* v contains x */
                    } else {
                        Rect bb = boundingRect( Mat(approx) );
//                        cout << bb.tl() << ", " << bb.br() << endl;
                        squares.push_back(approx);
                    }
                }
            }
        }
//        cout << "squares.size(): " << squares.size() << endl;
        if (squares.size() == 2) {
            cout << "text recognition..." << endl;
            for (vector<Point> i : squares) {
                Rect bb = boundingRect( Mat(i) );
                cout << bb.tl() << ", " << bb.br() << endl;
            }
        }
        imshow( window_name, dst );
        waitKey(0);
    }
}
