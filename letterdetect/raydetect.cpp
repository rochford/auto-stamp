/*
 *g++ -I/usr/local/include/opencv -I/usr/local/include/opencv2 -L/usr/local/lib/ -g -o binary  squares.cpp -lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_ml -lopencv_video -lopencv_features2d -lopencv_calib3d -lopencv_objdetect -lopencv_contrib -lopencv_legacy -lopencv_stitching -llept -ltesseract
 */

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <string>
#include <iostream>
#include <algorithm> // find
#include <memory>
#include <stdexcept>

#include <stdio.h>
#include <stdlib.h>

#include <math.h>
#include <string.h>

#include "alignment.h"
#include "recognition.h"
#include "debugutils.h"

using namespace cv;
using namespace std;

int thresh = 50, N = 200;

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
static void findSquares(const Mat& image, vector<vector<Point>>& squares)
{
    squares.clear();

    Mat gray(image.size(), CV_8U), cedge, edge;
    int edgeThresh = 1;

    cedge.create(image.size(), image.type());
    cvtColor(image, gray, CV_BGR2GRAY);

    blur(gray, edge, Size(3,3));

    // try several threshold levels
    for( int l = 20; l < 100; l +=5 )
    {
        vector<vector<Point> > contours;
        // Run the edge detector on grayscale
        Canny(edge, edge, l, l*3, 3);
//        dilate(edge, edge, Mat(), Point(-1,-1));
        cedge = Scalar::all(0);

        image.copyTo(cedge, edge);
        imshow("Edge map", cedge);
        waitKey(0);
        cvtColor(cedge, gray, CV_BGR2GRAY);
        // find contours and store them all as a list
        vector<Vec4i> hierarchy;
        findContours(gray, contours, hierarchy, CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE);

        vector<Point> approx;

        // test each contour
        for( size_t i = 0; i < contours.size(); i++ )
        {
            // approximate contour with accuracy proportional
            // to the contour perimeter
            approxPolyDP(Mat(contours[i]), approx, arcLength(Mat(contours[i]), true)*0.1, true);

            // square contours should have 4 vertices after approximation
            // relatively large area (to filter out noisy contours)
            // and be convex.
            // Note: absolute value of an area is used because
            // area may be positive or negative - in accordance with the
            // contour orientation
            // cout << "shortvec = " << Mat(approx) << endl;
            if( approx.size() == 4 &&
                    fabs(contourArea(Mat(approx))) > 100 &&
                    //                        fabs(contourArea(Mat(approx))) < 4000 &&
                    isContourConvex(Mat(approx)) )
            {
                //                    displateContours(gray, contours, hierarchy);
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
                                                cout << "shortvec = " << Mat(approx) << endl;
                    }
                }
            }
        }
    }

    return;
#if 0
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
                Canny(gray0, gray, 110, thresh, 3);
                // dilate canny output to remove potential
                // holes between edge segments
                dilate(gray, gray, Mat(), Point(-1,-1));
            }
            else
            {
                // apply threshold if l!=0:
                //     tgray(x,y) = gray(x,y) < (l+1)*255/N ? 255 : 0
                gray = gray0 >= (l+1)*255/N;
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
                    //                    displateContours(gray, contours, hierarchy);
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
#endif // 0
}

int findCornerLetters(const std::string& whitelist, Mat& image, const vector<vector<Point> >& squares,
                      vector<struct tess_data_struct>& foundLetters)
{
    // Pass it to Tesseract API
    std::shared_ptr<Recognition> recog(new Recognition());
    recog->setWhitelist(whitelist);

    char ret[2];
    for( size_t i = 0; i < squares.size(); i++ )
    {
        Point p1 = squares[i][0];
        Point p2 = squares[i][2];
        Rect rect(p1, p2);
        Mat textRoi = image(rect).clone();
        scaledDisplayRect(image, rect);

        struct tess_data_struct td = recog->recognize(textRoi);
        if (td.x1 == -1) {
            continue;
        }
        if (td.letter != whitelist.front()) {
            continue;
        }

        Rect bb = Rect(Point(td.x1, td.y1), Point(td.x2, td.y2));
        double centerX = bb.width /2;
        double centerY = bb.height /2;
        // calculate offset amount
        //        cout << xrect.width << ", " << xrect.height << endl;
        //        cout << centerX << ", " << centerY << endl;
        if (bb.area() < 60)
            continue;
        int offTop = td.y1 + centerY;
        int offBottom = rect.height - td.y2 + centerY;
        int offLeft = td.x1 + centerX;
        int offRight = rect.width - td.x2 + centerX;
        td.hOffset = offLeft - offRight;
        td.vOffset = offTop - offBottom;
        td.area = bb.area();

        printf("letter: '%c',%.2f, Align: %d,%d [%d,%d,%d,%d] area:%d\t",
               td.letter, td.conf,
               offLeft - offRight,
               offTop - offBottom,
               td.x1,
               td.y1,
               td.x2,
               td.y2,
               bb.area());
        foundLetters.push_back(td);
        printAlignment(offTop - offBottom, offLeft -offRight);
    }
    return 0;
}

int findLeftLetter(const std::string& letter, Mat& image, const vector<vector<Point> >& squares,
                   vector<struct tess_data_struct>& foundLetters)
{
    findCornerLetters(letter, image, squares, foundLetters);
    return 0;
}

int findRightLetter(const std::string& letter, Mat& image, const vector<vector<Point> >& squares,
                    vector<struct tess_data_struct>& foundLetters)
{
    findCornerLetters(letter, image, squares, foundLetters);
    return 0;
}

bool comp(const tess_data_struct &a, const tess_data_struct &b)
{
    Rect aRect(Point(a.x1, a.y1), Point(a.x2, a.y2));
    Rect bRect(Point(b.x1, b.y1), Point(b.x2, b.y2));
    return aRect.area() > bRect.area();
}

int detectLetters(const string& file, const string& lr) {
    setup();
    cout << "starting: " << lr << endl;
    vector<vector<Point> > squares;

    Mat image = imread(file, 1);
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

    vector<struct tess_data_struct> leftLetters;
    vector<struct tess_data_struct> rightLetters;

    char leftLetter = lr[0];
    char rightLetter = lr[1];
    int ret = findLeftLetter(&leftLetter, t2, squares, leftLetters);

    ret = findRightLetter(&rightLetter, t2, squares, rightLetters);
    // TODO: XXX TIM problem with same letter combinations e.g. AA, BB

    // okay now identify the plate:
    auto compareConfidence = [](const tess_data_struct &a, const tess_data_struct &b) { return a.conf > b.conf;};

    struct tess_data_struct tdLeft = { -1000, -1000, -1000, -1000, 0.0f, 'x', -1, -1};
    if (leftLetters.size()) {
        std::partial_sort(leftLetters.begin(), leftLetters.begin() + 1, leftLetters.end(), compareConfidence);
        tdLeft = leftLetters.front();
    }
    struct tess_data_struct tdRight = { -1000, -1000, -1000, -1000, 0.0f, 'x', -1, -1};
    if (rightLetters.size()) {
        std::partial_sort(rightLetters.begin(), rightLetters.begin() + 1, rightLetters.end(), compareConfidence);
        tdRight = rightLetters.front();
    }
    calculatePlate(lr, tdLeft.vOffset, tdLeft.hOffset, tdRight.vOffset, tdRight.hOffset);
    return ret;
}
