#ifndef RECOGNITION_H
#define RECOGNITION_H

#include <opencv2/core/core.hpp>

#include <tesseract/baseapi.h>

using namespace cv;

struct tess_data_struct {
    int x1;
    int y1;
    int x2;
    int y2;
    float conf;
    char* word;
};


class Recognition{
public:
    Recognition()
        : _tess(new tesseract::TessBaseAPI())
    {
        _tess->Init(NULL, "eng", tesseract::OEM_DEFAULT);
    }
    ~Recognition()
    {
        if (_tess)
        {
            _tess->End();
        }
    }

    struct tess_data_struct recognize(Mat& textRoi);
    void setWhitelist(const char* whitelist);
private:
    tesseract::TessBaseAPI *_tess;
};


#endif // RECOGNITION_H
