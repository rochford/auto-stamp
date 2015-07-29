
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

#include "findsquares.h"
#include "utils.h"

using namespace cv;
using namespace std;

int thresh = 50, N = 200;

// returns sequence of squares detected on the image.
// the sequence is stored in the specified memory storage
void findSquares(const Mat& image, vector<vector<Point>>& squares)
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
}

