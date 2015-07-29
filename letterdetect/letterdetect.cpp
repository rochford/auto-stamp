/*
 *g++ -I/usr/local/include/opencv -I/usr/local/include/opencv2 -L/usr/local/lib/ -g -o binary  squares.cpp -lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_ml -lopencv_video -lopencv_features2d -lopencv_calib3d -lopencv_objdetect -lopencv_contrib -lopencv_legacy -lopencv_stitching -llept -ltesseract
 */

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <string>
#include <iostream>
#include <memory>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "findsquares.h"
#include "alignment.h"
#include "recognition.h"
#include "utils.h"

using namespace cv;
using namespace std;

int findCornerLetters(const std::string& whitelist, Mat& image, const vector<vector<Point> >& squares,
                      vector<struct tess_data_struct>& foundLetters)
{
    const int EDGE_OFFSET = 3;
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
        //        scaledDisplayRect(image, xrect);

        struct tess_data_struct td = recog->recognize(textRoi);
        if (td.x1 == -1) {
            continue;
        }
        if (td.letter != whitelist.front()) {
            continue;
        }

        Rect bb = Rect(Point(td.x1, td.y1), Point(td.x2, td.y2));
        if (bb.area() < 60)
            continue;

        // calculate offset amount
        int offTop = td.y1 + EDGE_OFFSET;
        int offBottom = rect.height - td.y2 + EDGE_OFFSET;
        int offLeft = td.x1 + EDGE_OFFSET;
        int offRight = rect.width - td.x2 + EDGE_OFFSET;
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

    vector<struct tess_data_struct> leftLetters;
    vector<struct tess_data_struct> rightLetters;

    char leftLetter = lr[lr.length() - 2];
    char rightLetter = lr[lr.length() - 1];
    int ret = findLeftLetter(&leftLetter, t2, squares, leftLetters);

    ret = findRightLetter(&rightLetter, t2, squares, rightLetters);
    // TODO: XXX TIM problem with same letter combinations e.g. AA, BB

    // okay now identify the plate:
    auto compareConfidence = [](const tess_data_struct &a, const tess_data_struct &b) { return a.conf > b.conf;};
    auto compareArea = [](const tess_data_struct &a, const tess_data_struct &b)
    {
        if (a.area == b.area)
            return a.conf > b.conf;
        return a.area > b.area;
    };

    struct tess_data_struct tdLeft = { -1000, -1000, -1000, -1000, 0.0f, 'x', -1, -1};
    if (leftLetters.size()) {
        std::partial_sort(leftLetters.begin(), leftLetters.begin() + 1, leftLetters.end(), compareArea);
        tdLeft = leftLetters.front();
    }
    struct tess_data_struct tdRight = { -1000, -1000, -1000, -1000, 0.0f, 'x', -1, -1};
    if (rightLetters.size()) {
         std::partial_sort(rightLetters.begin(), rightLetters.begin() + 1, rightLetters.end(), compareArea);
         tdRight = rightLetters.front();
    }
    if (leftLetters.size() || rightLetters.size()) {
        calculatePlate(lr, tdLeft.vOffset, tdLeft.hOffset, tdRight.vOffset, tdRight.hOffset);
    }
    return ret;
}
