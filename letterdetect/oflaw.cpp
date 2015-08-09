#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

#include <stdlib.h>
#include <stdio.h>

#include <iostream>
#include <memory>
#include <stdexcept>

using namespace cv;
using namespace std;

/// Global variables

int threshold_value = 0;
int const max_value = 255;
int const max_BINARY_value = 255;
RNG rng(12345);

Point middleO;

string window_name = "Stamp Image";

/// Function headers
void Threshold_Demo( int, void*, const Mat& src, Mat& src_gray);

void CallBackFunc( int event, int x, int y, int flags, void* userdata )
{
    if  ( event == EVENT_LBUTTONDOWN )
    {
        cout << "Left button of the mouse is clicked - position (" << x << ", " << y << ")" << endl;
        middleO = Point( x, y );
        destroyWindow( window_name );
    }
}

int main( int argc, char** argv )
{
    /// Load an image
    Mat src = imread( argv[1], 1 );
    if( src.empty() )
    {
        cout << "Couldn't load " << argv[1] << endl;
        return -1;
    }

    Mat src_gray;
    /// Convert the image to Gray
    cvtColor( src, src_gray, CV_RGB2GRAY );

    resize( src_gray, src_gray, Size(77*6,88*6) );

    /// Create a window to display results
    namedWindow( window_name, CV_WINDOW_AUTOSIZE );

    //set the callback function for any mouse event
    setMouseCallback( window_name, CallBackFunc);

    imshow( window_name, src_gray );
    waitKey( 0 );
    /// Call the function to initialize
    Threshold_Demo( 0, 0, src, src_gray);
}

void Threshold_Demo( int, void*, const Mat& src, Mat& src_gray)
{
    vector<vector<Point> > contours;
    for ( int thres = 20; thres < 170; thres++ )
    {
        Mat detected_edges, dst;
        threshold( src_gray, dst, thres, 255, CV_THRESH_BINARY_INV );
        /// Reduce noise with a kernel 3x3
        blur( dst, detected_edges, Size( 3,3 ) );

        /// Canny detector
        Canny( detected_edges, detected_edges, thres, thres*3, 3 );

        /// Using Canny's output as a mask, we display our result
        dst = Scalar::all( 0 );

        src_gray.copyTo( dst, detected_edges );

        vector<Vec4i> hierarchy;
        // find contours and store them all as a tree
        findContours( detected_edges, contours, hierarchy, RETR_TREE, CHAIN_APPROX_NONE );

        vector<Point> approx;
        // test each contour
        for( size_t j = 0; j < contours.size(); j++ )
        {
            // approximate contour with accuracy proportional
            // to the contour perimeter
//            approxPolyDP(Mat(contours[j]), approx, 4, true);
            Rect bb = boundingRect( Mat(contours[j]) );

//            cout << "Contour[" << j << "] " << " Child BB: " << bb.tl() << ", " << bb.br() << endl;
            if (!bb.contains(middleO))
            {
                continue;
            }
            cout << "Contour[" << j << "] " << " Child BB: " << bb.tl() << ", " << bb.br() << endl;
//            if(isContourConvex(Mat(approx)) )
            {
                {
                    // no children allowed
//                    if (hierarchy[j][2] != -1)
//                        continue;

                    int parentContour = hierarchy[j][3];
                    if (parentContour != -1) {
//                        vector<Point> parentApprox;
//                        approxPolyDP(Mat(contours[parentContour]), parentApprox, /* arcLength(Mat(contours[childContour]), true)*0.001 */ 0.001, true);
                        parentContour = hierarchy[parentContour][3];
                        if (parentContour != -1) {
    //                        vector<Point> parentApprox;
    //                        approxPolyDP(Mat(contours[parentContour]), parentApprox, /* arcLength(Mat(contours[childContour]), true)*0.001 */ 0.001, true);
                            Rect parentBB = boundingRect(Mat(contours[parentContour]));
                            cout << "Contour[" << parentContour << "] " << " P BB: " << parentBB.tl() << ", " << parentBB.br() << endl;
                            imshow( "data", src_gray(parentBB).clone() );
                            waitKey(0);
                        }
                    }
                }
            }
        }
    }
}
