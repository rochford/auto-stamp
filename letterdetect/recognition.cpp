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

#include "recognition.h"
struct tess_data_struct recognize(Mat& textRoi, const char* whitelist)
{
    struct tess_data_struct td;

    td.x1 = -1;
    td.y1 = -1;
    td.x2 = -1;
    td.y2 = -1;

    tesseract::TessBaseAPI *tess = new tesseract::TessBaseAPI();

    tess->Init(NULL, "eng", tesseract::OEM_DEFAULT);
    tess->SetVariable("tessedit_char_whitelist", whitelist);
    tess->SetVariable("tessedit_char_blacklist", "abcdefghijklmnopqrstuvwxyzUVWXYZ0123456789");
    tess->SetPageSegMode(tesseract::PSM_SINGLE_CHAR);
    tess->SetImage((uchar*)textRoi.data, textRoi.cols, textRoi.rows, 1, textRoi.cols);
    //        tess->SetRectangle(xp1.x, xp1.y, xrect.width, xrect.height);
    int ret = tess->Recognize(0);
    if (ret) {
        tess->End();
        return td;
    }
    tesseract::ResultIterator* ri = tess->GetIterator();
    tesseract::PageIteratorLevel level = tesseract::RIL_SYMBOL;
    if (ri != 0) {
        do {
            char* word = ri->GetUTF8Text(level);
            if (!word || !isalpha(*word))
            {
                tess->End();
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
            td.word = strcpy(td.word, word);
            delete[] word;
        } while (ri->Next(level));
    }
    tess->End();
    return td;
}


