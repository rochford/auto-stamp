#ifndef THRESHOLD_H
#define THRESHOLD_H

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <stdlib.h>
#include <stdio.h>

#include <iostream>
#include <memory>
#include <stdexcept>

#include "alignment.h"

using namespace cv;
using namespace std;


class CornerSquareInput {
public:
    CornerSquareInput(const string& l, const string& r)
        : leftLetter(l), rightLetter(r), leftPoint(Point(-1, -1)), rightPoint(Point(-1, -1))
    {}
    CornerSquareInput(const string& l, const string& r, Point lp, Point rp, string file)
        : leftLetter(l), rightLetter(r), leftPoint(lp), rightPoint(rp), file(file)
    {}

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
                           Rect childRect,
                           bool leftSquare,
                           Mat roi,
                           int thresh)
        : _points(ownPoints),
          _childRect(childRect),
          _leftSquare(leftSquare),
          _roi(roi),
          _threshold(thresh)
    {}
    vector<Point> _points;
    Rect _childRect;
    bool _leftSquare;
    Mat _roi;
    int _threshold;
};


/// Function headers
void Threshold_Demo( int, void*, const Mat& src, Mat& src_gray, CornerSquareInput input );

static double angle( Point pt1, Point pt2, Point pt0 );

void displayCornerSquareOutput( const Mat& sq,
                                const CornerSquareOutputInfo& middle );

#endif THRESHOLD_H
