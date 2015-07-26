/*
 *g++ -I/usr/local/include/opencv -I/usr/local/include/opencv2 -L/usr/local/lib/ -g -o binary  squares.cpp -lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_ml -lopencv_video -lopencv_features2d -lopencv_calib3d -lopencv_objdetect -lopencv_contrib -lopencv_legacy -lopencv_stitching -llept -ltesseract
 */

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <string>
#include <iostream>
#include <algorithm> // find

#include <stdio.h>
#include <stdlib.h>

#include <math.h>
#include <string.h>
#include <stdexcept>

#include "alignment.h"
#include "recognition.h"

using namespace cv;
using namespace std;

int writeSquares(Recognition* recog, const char* whitelist, Mat& image, const vector<vector<Point> >& squares );

static void help()
{
    cout <<
            "Using OpenCV version %s\n" << CV_VERSION << "\n" << endl;
}

int thresh = 50, N = 200;
const char* wndname = "Square Detection Demo";

// helper function:
// finds a cosine of angle between vectors
// from pt0->pt1 and from pt0->pt2
static double angle( Point pt1, Point pt2, Point pt0 )
{
    double dx1 = pt1.x - pt0.x;
    double dy1 = pt1.y - pt0.y;
    double dx2 = pt2.x - pt0.x;
    double dy2 = pt2.y - pt0.y;
    return (dx1*dx2 + dy1*dy2)/sqrt((dx1*dx1 + dy1*dy1)*(dx2*dx2 + dy2*dy2) + 1e-10);
}

// returns sequence of squares detected on the image.
// the sequence is stored in the specified memory storage
static void findSquares( const Mat& image, vector<vector<Point> >& squares )
{
    squares.clear();

    Mat timg, gray0(image.size(), CV_8U), gray;

    timg = image.clone();
    vector<vector<Point> > contours;

    // find squares in every color plane of the image
    int c =0;
    //    for( int c = 0; c < 3; c++ )
    {
        int ch[] = {c, 0};
        mixChannels(&timg, 1, &gray0, 1, ch, 1);

        // try several threshold levels
        for( int l = 0; l < N; l++ )
        {
            // hack: use Canny instead of zero threshold level.
            // Canny helps to catch squares with gradient shading
            if( l == 0 )
            {
                // apply Canny. Take the upper threshold from slider
                // and set the lower to 0 (which forces edges merging)
                Canny(gray0, gray, 0, thresh, 3);
                // dilate canny output to remove potential
                // holes between edge segments
                dilate(gray, gray, Mat(), Point(-1,-1));
                // imshow("grey", gray);
                // waitKey(0);
            }
            else
            {
                // apply threshold if l!=0:
                //     tgray(x,y) = gray(x,y) < (l+1)*255/N ? 255 : 0
                gray = gray0 >= (l+1)*255/N;
                //                imshow("grey #n", gray);
                //            waitKey(0);
            }

            // find contours and store them all as a list
            vector<Vec4i> hierarchy;
            findContours(gray, contours, hierarchy, CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE);


            vector<Point> approx;

            // test each contour
            for( size_t i = 0; i < contours.size(); i++ )
            {
//                cout << contours[i] << endl;
                // approximate contour with accuracy proportional
                // to the contour perimeter
                approxPolyDP(Mat(contours[i]), approx, arcLength(Mat(contours[i]), true)*0.1, true);

                // square contours should have 4 vertices after approximation
                // relatively large area (to filter out noisy contours)
                // and be convex.
                // Note: absolute value of an area is used because
                // area may be positive or negative - in accordance with the
                // contour orientation
                //                cout << "shortvec = " << Mat(approx) << endl;
                if( approx.size() == 4 &&
                        fabs(contourArea(Mat(approx))) > 100 &&
                        //                        fabs(contourArea(Mat(approx))) < 4000 &&
                        isContourConvex(Mat(approx)) )
                {
#if 0
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
#endif // 0
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
                            squares.push_back(approx);
                            //                        cout << "shortvec = " << Mat(approx) << endl;
                        }
                    }
                }
            }
        }
    }
}

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

int writeSquares(const char* whitelist, Mat& image, const vector<vector<Point> >& squares )
{
    // Pass it to Tesseract API
    Recognition* recog = new Recognition();
    recog->setWhitelist(whitelist);

    char ret[2];
    for( size_t i = 0; i < squares.size(); i++ )
    {
        Point p1 = squares[i][0];
        Point p2 = squares[i][2];
        if (squares[i][0].x < 2)
            continue;
        if (squares[i][2].x < 2)
            continue;
        Point xp1(p1.x - 1, p1.y -1);
        Point xp2(p2.x + 1, p2.y + 1);
        Rect rect(p1, p2);
        Rect xrect(xp1, xp2);
        Mat textRoi = image(rect).clone();
#if 0
        cout << xrect.tl() << xrect.br() << endl;
        Mat roi = image(xrect).clone();
        Size size(160,160);//the dst image size,e.g.100x100
        Mat dst;
        resize(roi,dst,size,4.0,4.0);//resize image
        imshow("roi", dst);
        waitKey(0);
#endif // 0

        struct tess_data_struct td = recog->recognize(textRoi);
        if (td.x1 == -1) {
            continue;
        }
        int offTop = td.y1;
        int offBottom = xrect.height - td.y2;
        int offLeft = td.x1;
        int offRight = xrect.width - td.x2;
        printf("word: '%s'(%.2f%); Align: (%d,%d); [%d,%d,%d,%d] area=%d \t",
               td.word, td.conf,
               offLeft - offRight,
               offTop - offBottom,
               td.x1,
               td.y1,
               td.x2,
               td.y2,
               Rect(Point(td.x1, td.y1), Point(td.x2, td.y2)).area());
        verticalAlignment(offTop - offBottom);
        horizontalAlignment(offLeft -offRight);
        delete[] td.word;
    }
    delete recog;
    return 0;
}

int detectLetters(string file, string& lr) {
    cout << "starting: " << lr << endl;
    vector<vector<Point> > squares;

    Mat image = imread(file, 0);
    if( image.empty() )
    {
        cout << "Couldn't load " << file << endl;
        return -1;
    }

    int erosion_size = 1;
    Mat element = getStructuringElement( MORPH_CROSS,
                                         Size( 2*erosion_size + 1, 2*erosion_size+1 ),
                                         Point( erosion_size, erosion_size ) );

    Mat timg;
    erode( image, timg, element );

    //    Mat t1 = image.clone(); //timg.clone();
    Mat t1 = timg.clone();
    Mat t2 = image.clone();
    findSquares(t1, squares);

    int ret = writeSquares(lr.c_str(), t2, squares);
    return ret;
    //    drawSquares(image, squares);
}

