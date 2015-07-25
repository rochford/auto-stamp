#ifndef RECOGNITION_H
#define RECOGNITION_H

#include "opencv2/core/core.hpp"

using namespace cv;

struct tess_data_struct {
    int x1;
    int y1;
    int x2;
    int y2;
    float conf;
    char* word;
};

struct tess_data_struct recognize(Mat& textRoi, const char* whitelist);

#endif // RECOGNITION_H
