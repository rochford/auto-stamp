#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

using namespace cv;
using namespace std;

class SquareInfo {
public:
    SquareInfo(vector<Point> ownPoints,
               vector<Point> childPoints)
        : _points(ownPoints),
          _childPoints(childPoints)
    {}
    vector<Point> _points;
    vector<Point> _childPoints;
};

/// Global variables

int threshold_value = 0;
//int threshold_type = 3;;
int const max_value = 255;
//int const max_type = 4;
int const max_BINARY_value = 255;
RNG rng(12345);

Mat src, src_gray, dst;
char* window_name = "Threshold Demo";


/// Function headers
void Threshold_Demo( int, void* );

int main( int argc, char** argv )
{
    /// Load an image
    src = imread( argv[1], 1 );

    /// Convert the image to Gray
    cvtColor( src, src_gray, CV_RGB2GRAY );

    resize(src_gray,src_gray,Size(77*6,88*6));

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

void Threshold_Demo( int, void* )
{
    vector<SquareInfo> squares;
    vector<vector<Point> > contours;
    for (int i = 30; i < 150; i++)
    {
  //      squares.clear();
        Mat detected_edges;
        threshold( src_gray, dst, i, 255, 1);
        /// Reduce noise with a kernel 3x3
        blur( dst, detected_edges, Size(3,3) );

        /// Canny detector
        Canny( detected_edges, detected_edges, i, i*3, 3 );

        /// Using Canny's output as a mask, we display our result
        dst = Scalar::all(0);

        src_gray.copyTo( dst, detected_edges);

        vector<Vec4i> hierarchy;

        // find contours and store them all as a tree
        findContours(detected_edges, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);

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
/*                    if(std::find(squares.begin(), squares.end(), approx) != squares.end()) {
                        // v contains x
                    } else */ {
                        Rect bb = boundingRect( Mat(approx) );

                        // child contour info
                        //                    cout << "contour[" << i << "]" << "children:" << hierarchy[i][2] << endl;
                        // must have a child (ie. letter in the box)
                        const int childContour = hierarchy[i][2];
                        if (childContour != -1) {
                            cout << "Contour bb: " << bb.tl() << ", " << bb.br() << endl;
                            vector<Point> childApprox;

//                            squares.push_back(approx);
                            // approximate contour with accuracy proportional
                            // to the contour perimeter
                            approxPolyDP(Mat(contours[childContour]), childApprox, arcLength(Mat(contours[childContour]), true)*0.001, true);
                            Rect possibleText = boundingRect(Mat(childApprox));
                            cout << "\tChild bb:"<<possibleText.tl() << ", " << possibleText.br() << endl;
                            // could even calculate the offset here...
                            squares.emplace_back(approx, childApprox);
                            const int grandChildContour = hierarchy[childContour][2];
                            if (grandChildContour != -1) {
                                // okay if A,B,C,D,E,...if letter has an inner contour like a 'O'
                                vector<Point> grandChildApprox;
                                approxPolyDP(Mat(contours[grandChildContour]), grandChildApprox, arcLength(Mat(contours[grandChildContour]), true)*0.001, true);
                                Rect possibleText = boundingRect(Mat(grandChildApprox));
                                cout << "\t\tGrandChild bb:"<<possibleText.tl() << ", " << possibleText.br() << endl;
                            }
                        }
                    }
                }
            }
        }
    }
    //        cout << "squares.size(): " << squares.size() << endl;
    if ( squares.size() > 1 ) {
#if 0
        Rect a = boundingRect( Mat(squares[0]) );
        Rect b = boundingRect( Mat(squares[1]) );
        Rect intersectionRect  = a & b;
        if (intersectionRect.area() > 0)
        {
            continue;
        }
#endif // 0
        cout << "text recognition..." << endl;
        Mat tmp = src_gray.clone();
        for (auto i : squares) {
            Rect bb = boundingRect( Mat(i._points) );
            cout << "Square bb:" << bb.tl() << ", " << bb.br() << endl;
            Rect childBB = boundingRect( Mat(i._childPoints) );
            cout << "\t child:" << childBB.tl() << ", " << childBB.br() << endl;
            cout << "\t\tLEFT x:" << childBB.x - bb.x<< endl;
            cout << "\t\tRIGHT x:" << bb.br().x - childBB.br().x << endl;
            cout << "\t\tTOP y:" << childBB.y - bb.y << endl;
            cout << "\t\tBOTTOM y:" << bb.br().y - childBB.br().y << endl;
            Scalar color1 = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
            Scalar color2 = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
            rectangle(tmp, bb, color1, 1);
            rectangle(tmp, childBB, color2, 1);
        }
        imshow( window_name, tmp );
        waitKey(0);
    }
}
