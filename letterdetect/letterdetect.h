// The "Square Detector" program.
// It loads several images sequentially and tries to find squares in
// each image

/*
 *g++ -I/usr/local/include/opencv -I/usr/local/include/opencv2 -L/usr/local/lib/ -g -o binary  squares.cpp -lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_ml -lopencv_video -lopencv_features2d -lopencv_calib3d -lopencv_objdetect -lopencv_contrib -lopencv_legacy -lopencv_stitching -llept -ltesseract
 */

#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

#include <tesseract/baseapi.h>
#include <tesseract/resultiterator.h>

#include <string>
#include <iostream>
#include <algorithm> // find

#include <math.h>
#include <string.h>
#include <stdexcept>

// #include "alignment.h"

class Recognition;

using namespace cv;
using namespace std;


int writeSquares(const char* whitelist, Mat& image, const vector<vector<Point> >& squares );

int detectLetters(string file, string& lr);

