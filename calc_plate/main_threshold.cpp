#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <stdlib.h>
#include <stdio.h>

#include <iostream>
#include <memory>
#include <stdexcept>

#include "threshold.h"
#include "alignment.h"

using namespace cv;
using namespace std;

/// Global variables

int threshold_value = 0;
int const max_value = 255;
int const max_BINARY_value = 255;

string window_name = "Stamp Image";

void CallBackFunc( int event, int x, int y, int flags, void* userdata )
{
    if  ( event == EVENT_LBUTTONDOWN )
    {
        cout << "Left button of the mouse is clicked - position (" << x << ", " << y << ")" << endl;
        CornerSquareInput* i =  static_cast<CornerSquareInput*>(userdata);
        bool ret = i->setPoint( Point( x, y ) );
        if ( ret )
            destroyWindow( window_name );
    }
}

int main( int argc, char** argv )
{
    string leftLetter, rightLetter;
    string arg2( argv[1] );
    if ( argc==2 ) {
        size_t len = strlen(argv[1]);
        leftLetter = arg2.at(len - 6);
        rightLetter = arg2.at(len - 5);
    }

    CornerSquareInput in { leftLetter, rightLetter };
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
    setMouseCallback( window_name, CallBackFunc, (void*)&in );

    imshow( window_name, src_gray );
    waitKey( 0 );
    /// Call the function to initialize
    Threshold_Demo( 0, 0, src, src_gray, in );
}

