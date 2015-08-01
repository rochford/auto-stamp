#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

#include <stdlib.h>
#include <stdio.h>

#include <iostream>
#include <memory>

#include "alignment.h"

using namespace cv;
using namespace std;

class CornerSquareInput {
public:
    CornerSquareInput(const string& l, const string& r)
        : leftLetter(l), rightLetter(r), leftPoint(Point(-1, -1)), rightPoint(Point(-1, -1))
    {}
    /*    CornerSquareInput(const string& l, const string& r, Point lp, Point rp)
        : leftLetter(l), rightLetter(r), leftPoint(lp), rightPoint(rp)
    {}
    */
    bool setPoint(Point pt)
    {
        if (leftPoint == Point(-1, -1))
            leftPoint = pt;
        else {

            rightPoint = pt;
            return true;
        }
        return false;
    }

    string leftLetter;
    string rightLetter;
    Point leftPoint;
    Point rightPoint;
    string file;
};

class CornerSquareOutputInfo {
public:
    CornerSquareOutputInfo() = default;
    CornerSquareOutputInfo(vector<Point> ownPoints,
                           vector<Point> childPoints,
                           bool leftSquare,
                           Mat roi,
                           int thresh)
        : _points(ownPoints),
          _childPoints(childPoints),
          _leftSquare(leftSquare),
          _roi(roi),
          _threshold(thresh)
    {}
    vector<Point> _points;
    vector<Point> _childPoints;
    bool _leftSquare;
    Mat _roi;
    int _threshold;
};

bool operator==(const CornerSquareOutputInfo& lhs,
                const CornerSquareOutputInfo& rhs){ return lhs._points == rhs._points; }

/// Global variables

int threshold_value = 0;
int const max_value = 255;
int const max_BINARY_value = 255;
RNG rng(12345);

string window_name = "Stamp Image";

/// Function headers
void Threshold_Demo( int, void*, const Mat& src, Mat& src_gray, CornerSquareInput input );

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
    setup();
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

static double angle( Point pt1, Point pt2, Point pt0 )
{
    double dx1 = pt1.x - pt0.x;
    double dy1 = pt1.y - pt0.y;
    double dx2 = pt2.x - pt0.x;
    double dy2 = pt2.y - pt0.y;
    return (dx1*dx2 + dy1*dy2)/sqrt((dx1*dx1 + dy1*dy1)*(dx2*dx2 + dy2*dy2) + 1e-10);
}

void displayCornerSquareOutput( const Mat& sq,
                                CornerSquareOutputInfo& middle )
{
    const Rect bb = boundingRect( Mat(middle._points) );
    const Rect childBB = boundingRect( Mat(middle._childPoints) );
    cout << "Square bb (threshold " << middle._threshold << "):" << bb.tl() << ", " << bb.br();
    cout << "\t child:" << childBB.tl() << ", " << childBB.br();
    cout << " LEFT:" << childBB.x - bb.x;
    cout << " RIGHT:" << bb.br().x - childBB.br().x;
    cout << " TOP:" << childBB.y - bb.y;
    cout << " BOTTOM:" << bb.br().y - childBB.br().y << endl;
    imshow( middle._leftSquare ? "SE" : "SW", sq );
    waitKey(0);

}

void Threshold_Demo( int, void*, const Mat& src, Mat& src_gray, CornerSquareInput input )
{
    vector<CornerSquareOutputInfo> squares;
    vector<vector<Point> > contours;
    for ( int thres = 30; thres < 150; thres++ )
    {
        Mat detected_edges, dst;
        threshold( src_gray, dst, thres, 255, 1);
        /// Reduce noise with a kernel 3x3
        blur( dst, detected_edges, Size(3,3) );

        /// Canny detector
        Canny( detected_edges, detected_edges, thres, thres*3, 3 );

        /// Using Canny's output as a mask, we display our result
        dst = Scalar::all( 0 );

        src_gray.copyTo( dst, detected_edges );

        vector<Vec4i> hierarchy;
        // find contours and store them all as a tree
        findContours(detected_edges, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);

        vector<Point> approx;
        // test each contour
        for( size_t j = 0; j < contours.size(); j++ )
        {
            // approximate contour with accuracy proportional
            // to the contour perimeter
            approxPolyDP(Mat(contours[j]), approx, 4, true);
            Rect bb = boundingRect( Mat(approx) );

            if (!bb.contains(input.leftPoint) &&
                    !bb.contains(input.rightPoint))
            {
                continue;
            }

            // square contours should have 4 vertices after approximation
            // and be convex.
            if( approx.size() == 4 && isContourConvex(Mat(approx)) )
            {
                double maxCosine = 0;

                for( int k = 2; k < 5; k++ )
                {
                    // find the maximum cosine of the angle between joint edges
                    double cosine = fabs(angle(approx[k%4], approx[k-2], approx[k-1]));
                    maxCosine = MAX(maxCosine, cosine);
                }

                // if cosines of all angles are small
                // (all angles are ~90 degree) then write quandrange
                // vertices to resultant sequence
                if( maxCosine < 0.3 ) {
                    // must have a child (ie. letter in the box)
                    const int childContour = hierarchy[j][2];
                    if (childContour != -1) {
                        vector<Point> childApprox;

                        // approximate contour with accuracy proportional
                        // to the contour perimeter
                        approxPolyDP(Mat(contours[childContour]), childApprox, /* arcLength(Mat(contours[childContour]), true)*0.001 */ 1, true);

                        bool leftSquare {false};
                        if (bb.contains(input.leftPoint))
                            leftSquare = true;

                        CornerSquareOutputInfo tmp(approx, childApprox, leftSquare, src_gray(bb).clone(), thres);
                        if(std::find(squares.begin(), squares.end(), tmp) != squares.end()) {
                            // v contains x
                            continue;
                        }

                        Rect childBB = boundingRect(Mat(childApprox));
                        // If the child bounding rect not completely within the square, then continue
                        // Note: absolute value of an area is used because
                        // area may be positive or negative - in accordance with the
                        // contour orientation
                        if (fabs(bb.area()) < fabs(childBB.area()) ||
                                !bb.contains(childBB.tl()) ||
                                !bb.contains(childBB.br())) {
                            continue;
                        }
#if 0
                        // For alignment checking to work, all the squares need to be similar sizes,
                        // so calculate new approx, childApprox,
                        Mat normalizedSquare;
                        resize(src_gray(bb).clone(),normalizedSquare,Size(40,40));
#endif // 0
                        squares.emplace_back(approx, childApprox, leftSquare, src_gray(bb).clone(), thres);

                        const int grandChildContour = hierarchy[childContour][2];
                        if (grandChildContour != -1) {
                            // okay if A,B,C,D,E,...if letter has an inner contour like a 'O'
                            vector<Point> grandChildApprox;
                            approxPolyDP(Mat(contours[grandChildContour]), grandChildApprox, /* arcLength(Mat(contours[grandChildContour]), true)*0.001 */ 1, true);
                        }
                    }
                }
            }
        }
    }
    if ( squares.size() > 1 ) {
        cout << "calculating..." << endl;
        Mat tmp = src.clone();
        resize(tmp,tmp,Size(77*6,88*6));

        // Starting from the middle threshold value seems to be the best approach.
        // vector should already be in threshold order.
        auto middle = squares.begin();
        std::advance( middle, squares.size()/2 );

        bool processLeftSquare {false};
        bool processRightSquare {false};
        CornerSquareOutputInfo left;
        CornerSquareOutputInfo right;

        while ( middle++ != squares.end()) {
            if ( processLeftSquare && middle->_leftSquare ||
                 processRightSquare && !middle->_leftSquare ) {
                continue;
            }

            if ( middle->_leftSquare ) {
                processLeftSquare = true;
                left = *middle;
            } else {
                processRightSquare = true;
                right = *middle;
            }
            Rect bb = boundingRect( Mat(middle->_points) );
            Rect childBB = boundingRect( Mat(middle->_childPoints) );
            Scalar color1 = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
            Scalar color2 = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
            rectangle(tmp, bb, color1, 2);
            rectangle(tmp, childBB, color2, 1);

            Mat sq = middle->_roi.clone();
            displayCornerSquareOutput(sq, *middle);
        }
        if ( processLeftSquare && processRightSquare ) {
            Rect lbb = boundingRect( Mat(left._points) );
            Rect lchildBB = boundingRect( Mat(left._childPoints) );
            int lleft = lchildBB.x - lbb.x;
            int lright = lbb.br().x - lchildBB.br().x;
            int ltop = lchildBB.y - lbb.y;
            int lbottom =  lbb.br().y - lchildBB.br().y;

            Rect rbb = boundingRect( Mat(right._points) );
            Rect rchildBB = boundingRect( Mat(right._childPoints) );
            int rleft = rchildBB.x - rbb.x;
            int rright = rbb.br().x - rchildBB.br().x;
            int rtop = rchildBB.y - rbb.y;
            int rbottom =  rbb.br().y - rchildBB.br().y;

            calculatePlate( input.leftLetter + input.rightLetter,
                            ltop - lbottom, lleft - lright,
                            rtop - rbottom,  rleft - rright );
        }
        imshow( window_name, tmp );
        waitKey( 0 );
    }
}
