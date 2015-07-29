#ifndef UTILS_H
#define UTILS_H

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <vector>

static void drawSquares(cv::Mat& image, const std::vector<std::vector<cv::Point> >& squares );
void scaledDisplayRect(cv::Mat& image, cv::Rect& xrect);

void displateContours(cv::Mat& gray,
                      cv::InputArrayOfArrays contours,
                      std::vector<cv::Vec4i>& hierarchy);

double angle( cv::Point pt1, cv::Point pt2, cv::Point pt0 );
#endif // UTILS
