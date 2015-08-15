#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <stdlib.h>
#include <stdio.h>

#include <iostream>
#include <memory>
#include <vector>
#include <stdexcept>

#include "threshold.h"
#include "alignment.h"

using namespace cv;
using namespace std;

bool operator==(const CornerSquareOutputInfo& lhs,
                const CornerSquareOutputInfo& rhs){ return lhs._points == rhs._points; }

/// Global variables

// int threshold_value = 0;
// int const max_value = 255;
// int const max_BINARY_value = 255;
RNG rng(12345);

// string window_name = "Stamp Image";

/// Function headers
vector<int> Threshold_Demo( int, void*, const Mat& src, Mat& src_gray, CornerSquareInput input );

static double angle( Point pt1, Point pt2, Point pt0 )
{
    double dx1 = pt1.x - pt0.x;
    double dy1 = pt1.y - pt0.y;
    double dx2 = pt2.x - pt0.x;
    double dy2 = pt2.y - pt0.y;
    return (dx1*dx2 + dy1*dy2)/sqrt((dx1*dx1 + dy1*dy1)*(dx2*dx2 + dy2*dy2) + 1e-10);
}

void displayCornerSquareOutput( const Mat& sq,
                                const CornerSquareOutputInfo& middle )
{
    const Rect_<double> bb = boundingRect( Mat(middle._points) );
    const Rect_<double> childBB = middle._childRect;
    cout << "Square bb (threshold " << middle._threshold << "):" << bb.tl() << ", " << bb.br();
    cout << "\t child:" << childBB.tl() << ", " << childBB.br();
    cout << " LEFT:" << childBB.x - bb.x;
    cout << " RIGHT:" << bb.br().x - childBB.br().x;
    cout << " TOP:" << childBB.y - bb.y;
    cout << " BOTTOM:" << bb.br().y - childBB.br().y << endl;
    imshow( middle._leftSquare ? "SE" : "SW", sq );
    waitKey(0);
}

vector<int> Threshold_Demo( int, void*, const Mat& src, Mat& src_gray, CornerSquareInput input )
{
    LitchfieldData litchfield;
    litchfield.Initialize();
    vector<CornerSquareOutputInfo> squares;
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
        findContours( detected_edges, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE );

        vector<Point> approx;
        // test each contour
        for( size_t j = 0; j < contours.size(); j++ )
        {
            // approximate contour with accuracy proportional
            // to the contour perimeter
            approxPolyDP(Mat(contours[j]), approx, 4, true);
            Rect bb = boundingRect( Mat(approx) );

            // square cannot contain both left & right
            if (bb.contains(input.leftPoint) && bb.contains(input.rightPoint))
            {
                continue;
            }
            if (!bb.contains(input.leftPoint) &&
                    !bb.contains(input.rightPoint))
            {
                continue;
            }
            double maxCosine = 0;

            for( int k = 2; k < approx.size() + 1; k++ )
            {
                // find the maximum cosine of the angle between joint edges
                double cosine = fabs(angle(approx[k%4], approx[k-2], approx[k-1]));
                maxCosine = MAX(maxCosine, cosine);
            }

            // if cosines of all angles are small
            // (all angles are ~90 degree) then write quandrange
            // vertices to resultant sequence
            if( maxCosine < 0.3 )
            {
                bool leftSquare {false};
                if (bb.contains(input.leftPoint))
                    leftSquare = true;

                // must have a child (ie. letter in the box)

                // TODO: this needs to be a loop as might be several children.
                // e.g. letter 'K' made up from a couple of children contours.
                // The alignment will be incorrect if only use the first child.
                Point tl(1000,1000), br(0, 0);
                int childContour = hierarchy[j][2];
                while (childContour != -1) {
                    vector<Point> childApprox;
                    approxPolyDP(Mat(contours[childContour]), childApprox, /* arcLength(Mat(contours[childContour]), true)*0.001 */ 0.001, true);
                    Rect childBB = boundingRect(Mat(childApprox));
                    // cout << "Contour[" << childContour << "] " << " Child BB: " << childBB.tl() << ", " << childBB.br() << endl;

                    // TODO: XXX TIM if child contour goes out of box, then ignore it - MX cancel?
                    if (childBB.tl().x < tl.x)
                        tl.x = childBB.tl().x;
                    if (childBB.tl().y < tl.y)
                        tl.y = childBB.tl().y;

                    if (childBB.br().x > br.x)
                        br.x = childBB.br().x;
                    if (childBB.br().y > br.y)
                        br.y = childBB.br().y;
                    childContour = hierarchy[childContour][0]; // next
                }
                if (tl == Point(1000,1000) || br == Point(0,0)) {
                    // No children
                    continue;
                }
                Rect totalChildrenRect(tl, br);
                //cout << "Total Child Rect BB: " << totalChildrenRect.tl() << ", " << totalChildrenRect.br() << endl;

                CornerSquareOutputInfo tmp(approx, totalChildrenRect, leftSquare, src_gray(bb).clone(), thres);
                if(std::find(squares.begin(), squares.end(), tmp) != squares.end()) {
                    // v contains x
                    continue;
                }

                // If the child bounding rect not completely within the square, then continue
                // Note: absolute value of an area is used because
                // area may be positive or negative - in accordance with the
                // contour orientation
                if (fabs(bb.area()) < fabs(totalChildrenRect.area())) {
                    continue;
                }

                //cout << "approx.size: " << approx.size() << endl;
                squares.emplace_back(approx, totalChildrenRect, leftSquare, src_gray(bb).clone(), thres);
            }
        }
    }
    if ( squares.size() > 1 ) {
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
            if ( ( processLeftSquare && middle->_leftSquare ) ||
                 ( processRightSquare && !middle->_leftSquare ) ) {
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
            Rect childBB = middle->_childRect;
            Scalar color1 = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
            Scalar color2 = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
            rectangle(tmp, bb, color1, 2);
            rectangle(tmp, childBB, color2, 1);

            Mat sq = middle->_roi.clone();
//            displayCornerSquareOutput(sq, *middle);
        }

        double fx = 1.0;
        // multiply factor based on width height
        double lvert = -1000;
        double lhoriz = -1000;
        double rvert = -1000;
        double rhoriz = -1000;

        if (processLeftSquare) {
            // multiply factor based on width height
            Rect_<double> lbb = boundingRect( Mat(left._points) );
            Rect_<double> lchildBB = left._childRect;
            fx = 1.0/(lbb.width/20.0);
            double lleft = lchildBB.x*fx - lbb.x*fx;
            double lright = lbb.br().x*fx - lchildBB.br().x*fx;
            double ltop = lchildBB.y*fx - lbb.y*fx;
            double lbottom =  lbb.br().y*fx - lchildBB.br().y*fx;
            lvert = ltop - lbottom;
            lhoriz = lleft - lright;
        }
        if (processRightSquare) {
            Rect_<double> rbb = boundingRect( Mat(right._points) );
            Rect_<double> rchildBB = right._childRect;
            fx = 1.0/(rbb.width/20.0);
            double rleft = rchildBB.x*fx - rbb.x*fx;
            double rright = rbb.br().x*fx - rchildBB.br().x*fx;
            double rtop = rchildBB.y*fx - rbb.y*fx;
            double rbottom =  rbb.br().y*fx - rchildBB.br().y*fx;
            rvert = rtop - rbottom;
            rhoriz = rleft - rright;
        }

        vector<int> plates = litchfield.calculatePlate( input.leftLetter + input.rightLetter,
                        lvert, lhoriz,
                        rvert,  rhoriz );

#if 0
        imshow( window_name, tmp );
        waitKey( 0 );
        vector<int> compression_params;
        compression_params.push_back(CV_IMWRITE_JPEG_QUALITY);
        compression_params.push_back(90);

        try {
            imwrite("qvplate" + input.leftLetter + input.rightLetter + ".jpg", tmp, compression_params);
        }
        catch (runtime_error& ex) {
            fprintf(stderr, "Exception converting image to PNG format: %s\n", ex.what());
        }
#endif // 0

        return plates;
    }
}
