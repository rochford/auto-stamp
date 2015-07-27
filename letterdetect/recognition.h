#ifndef RECOGNITION_H
#define RECOGNITION_H

#include <opencv2/core/core.hpp>

#include <tesseract/baseapi.h>

#include <memory>
#include <string>

struct tess_data_struct {
    int x1;
    int y1;
    int x2;
    int y2;

    float conf;
    char* word;

    int vOffset;
    int hOffset;
};

class Recognition{
public:
    Recognition()
        : _tess(std::shared_ptr<tesseract::TessBaseAPI>(new tesseract::TessBaseAPI()))
    {
        _tess->Init(NULL, "eng", tesseract::OEM_DEFAULT);
    }
    ~Recognition() = default;

    struct tess_data_struct recognize(cv::Mat& textRoi);
    void setWhitelist(const std::string& whitelist);
private:
    std::shared_ptr<tesseract::TessBaseAPI> _tess;
};

#endif // RECOGNITION_H
