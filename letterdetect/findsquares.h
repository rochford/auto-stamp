#ifndef FIND_SQUARES_H
#define FIND_SQUARES_H

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <vector>

void findSquares(const cv::Mat& image, std::vector<std::vector<cv::Point>>& squares);


#endif // FIND_SQUARES_H
