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

#include "letterdetect.h"

using namespace cv;
using namespace std;

static void help()
{
    cout <<
            "Using OpenCV version %s\n" << CV_VERSION << "\n" << endl;
}

int main(int argc, char** argv)
{

    string data[] = { "AL", // 7
/*                      "AA",
                      "BB",
                      "BH",
                      "BL",
                      "CC",
                      "CH",
                      "DB",
                      "DK",
                      "EB",
                      "FC",
                      "FF",
                      "FI",
                      "GG",
                      "GI",
                      "HH",
                      "IE",
                      "JI",
                      "KE",
                      "KF",
                      "KK",
                      "KL",
                      "LL",
                      "MG",
                      "MK",
                      "NB",
                      "NG",
                      "OL",
                      "PB",
                      "PC",
                      "QA",
                      "QD",
                      "QE",
                      "RA",
                      "SJ",
                      "SF",
                      "SL",
                      "TC",
                      "TH",*/
                      "TF",
                      "LAST"
                    };
    //    namedWindow( wndname, 1 );

    string letters;
    int i = 0;
    while ((letters = data[i++]) != "LAST") {
        detectLetters("../data/" + letters + ".jpg", letters);
    }
    return 0;
#if 0
    string letters;
    string arg2(argv[1]);
    if (argc ==2) {
        size_t len = strlen(argv[1]);
        letters = arg2.substr(len - 6);
    } else {
        letters = argv[2];
    }
    detectLetters(argv[1], letters);
#endif // 0
    return 0;
}
