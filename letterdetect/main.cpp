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
//                      "AA",
                      "AB", // 1a
                      "AE", // plate 1a
                      "AF", // 8
                      "AI",
//                      "BB",
                      "BH",
                      "BL",
                      "CB", // 8
//                      "CC",
                      "CH",
                      "DC", // 6
                      "DB",
                      "DK",
                      "DL", // 1a
                      "EB",
                      "FC",
//                      "FF",
                      "FI",
                      "FJ", // 6
//                      "GG",
                      "GI",
//                      "HH",
                      "ID", // 6
                      "IE",
                      "JI",
                      "KE",
                      "KF",
//                      "KK",
                      "KL",
                      "LA", // 4
//                      "LL",
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
                      "TF",
                      "TH",
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
