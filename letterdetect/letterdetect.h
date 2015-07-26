#ifndef LETTER_DETECT_H
#define LETTER_DETECT_H

/*
 *g++ -I/usr/local/include/opencv -I/usr/local/include/opencv2 -L/usr/local/lib/ -g -o binary  squares.cpp -lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_ml -lopencv_video -lopencv_features2d -lopencv_calib3d -lopencv_objdetect -lopencv_contrib -lopencv_legacy -lopencv_stitching -llept -ltesseract
 */

#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

#include <string>

int writeSquares(const std::string& whitelist, cv::Mat& image, const std::vector<std::vector<cv::Point> >& squares );

int detectLetters(std::string file, std::string& lr);

#endif // LETTER_DETECT_H
