// The "Square Detector" program.
// It loads several images sequentially and tries to find squares in
// each image

#include <string>
#include <iostream>
#include <stdexcept>
#include <string.h>

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
                      "TH",
                      "TF", */
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
