#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <stdio.h>
#include <stdlib.h>

#include <math.h>
#include <stdexcept>

#include "utils.h"

using namespace std;
using namespace cv;

const char* wndname = "Square Detection Demo";

// the function draws all the squares in the image
static void drawSquares( Mat& image, const vector<vector<Point> >& squares )
{
    for( size_t i = 0; i < squares.size(); i++ )
    {
        const Point* p = &squares[i][0];
        int n = (int)squares[i].size();
        polylines(image, &p, &n, 1, true, Scalar(0,255,0), 3, CV_AA);
    }
}

void scaledDisplayRect(Mat& image, Rect& xrect)
{
//    cout << xrect.tl() << xrect.br() << endl;
    Mat roi = image(xrect).clone();
    Size size(160,160);//the dst image size,e.g.100x100
    Mat dst;
    resize(roi,dst,size,4.0,4.0);//resize image
    imshow(wndname, dst);
    waitKey(0);
}

void displateContours(Mat& gray,
                      InputArrayOfArrays contours,
                      vector<Vec4i>& hierarchy)
{
    Mat dst = Mat::zeros(gray.rows, gray.cols, CV_8UC3);
    int idx = 0;
    for( ; idx >= 0; idx = hierarchy[idx][0] )
    {
        Scalar color( rand()&255, rand()&255, rand()&255 );
        drawContours( dst, contours, idx, color, 1, 8, hierarchy );
    }

    namedWindow( "Components", 1 );
    imshow( "Components", dst );
    waitKey(0);
}

// helper function:
// finds a cosine of angle between vectors
// from pt0->pt1 and from pt0->pt2
double angle( Point pt1, Point pt2, Point pt0 )
{
    double dx1 = pt1.x - pt0.x;
    double dy1 = pt1.y - pt0.y;
    double dx2 = pt2.x - pt0.x;
    double dy2 = pt2.y - pt0.y;
    return (dx1*dx2 + dy1*dy2)/sqrt((dx1*dx1 + dy1*dy1)*(dx2*dx2 + dy2*dy2) + 1e-10);
}
