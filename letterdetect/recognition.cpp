#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <tesseract/baseapi.h>
#include <tesseract/resultiterator.h>

#include <string>
#include <iostream>
// #include <algorithm> // find

// #include <math.h>
#include <string.h>
#include <stdexcept>

#include "recognition.h"

using namespace std;

void Recognition::setWhitelist(const char* whitelist)
{
    _tess->SetVariable("tessedit_char_whitelist", whitelist);
    _tess->SetVariable("tessedit_char_blacklist", "abcdefghijklmnopqrstuvwxyzUVWXYZ0123456789");
    _tess->SetPageSegMode(tesseract::PSM_SINGLE_CHAR);
}

struct tess_data_struct Recognition::recognize(Mat& textRoi)
{
    struct tess_data_struct td;
    td.x1 = -1;
    td.y1 = -1;
    td.x2 = -1;
    td.y2 = -1;

    _tess->Clear();

    _tess->SetImage((uchar*)textRoi.data, textRoi.cols, textRoi.rows, 1, textRoi.cols);
    //        tess->SetRectangle(xp1.x, xp1.y, xrect.width, xrect.height);
    int ret = _tess->Recognize(0);
    if (ret) {
        return td;
    }
    tesseract::ResultIterator* ri = _tess->GetIterator();
    tesseract::PageIteratorLevel level = tesseract::RIL_SYMBOL;
    if (ri != 0) {
        do {
            char* word = ri->GetUTF8Text(level);
            if (!word || !isalpha(*word))
            {
                return td;
            }
            float conf = ri->Confidence(level);
            int x1, y1, x2, y2;
            ri->BoundingBox(level, &x1, &y1, &x2, &y2);
            //                cout << "rect.w:" << xrect.width << ", rect.h:" << xrect.height << endl;
            td.x1 = x1;
            td.y1 = y1;
            td.x2 = x2;
            td.y2 = y2;
            td.conf = conf;
            td.word = word;
//            delete[] word;
        } while (ri->Next(level));
    }
    return td;
}


