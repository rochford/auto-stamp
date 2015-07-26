// The "Square Detector" program.
// It loads several images sequentially and tries to find squares in
// each image

#include <string>
#include <iostream>
#include <stdexcept>
#include <string.h>

#include <map>
#include "letterdetect.h"

using namespace cv;
using namespace std;

static void help()
{
    cout <<
            "Using OpenCV version %s\n" << CV_VERSION << "\n" << endl;
}

typedef int PlateNo;
class LitchfieldItem {
public:
    LitchfieldItem(int pl, int alv, int alh, int arv, int arl)
        : plate(pl), lv(alv), lh(alh), rv(arv), rh(arl)
    {}
    PlateNo plate;
    int lv; // lower left vertical
    int lh; // lower left horiz
    int rv; // lower right vertical
    int rh; // lower right horiz
};


map<string, vector<LitchfieldItem>> litchfieldLetterPosMap;

int main(int argc, char** argv)
{

    vector<LitchfieldItem> v;

    // AA
    v.emplace_back(0, 0, 1, 1, 1);
    v.emplace_back(1, 0, 1, 1, 1);
    v.emplace_back(2, 0, 0, 0, 0);
    v.emplace_back(3, -1, 2, 0, 0);
    v.emplace_back(4, -2, 2, -3, 0);
    v.emplace_back(5, 0, 0, 2, -2);
    v.emplace_back(6, 3, 0, 0, 0);
    v.emplace_back(8, 0,0, 0, 0);
    v.emplace_back(9, -4, 2, 3, -2);
    v.emplace_back(11, 0, 0, 2, 2);
    v.emplace_back(7, 4, -2, 0, 0);
    v.emplace_back(10, 0,0, 4, 0);
    litchfieldLetterPosMap["AA"] = v;
    v.clear();

    v.emplace_back(0, 0,0, 0, 2);
    v.emplace_back(1, 0,0,0,2);
    v.emplace_back(2, 1, 1, -2, 2);
    v.emplace_back(4, 4, 2, 0, -1);
    v.emplace_back(5, 0, 0, -1, -1);
    v.emplace_back(7, 0, 0, 0, 0);
    v.emplace_back(8, -1, -1, 0, 2);
    v.emplace_back(9, -2, 0, 0, -2);
    v.emplace_back(11, 0, 0, 2, -2);
    v.emplace_back(3, 0, 2, -2, 2);
    v.emplace_back(6, 0, 2, -2, 0);
    v.emplace_back(10, -2, 0, -2, 0);
    litchfieldLetterPosMap["AB"] = v;
    v.clear();

    v.emplace_back(0, 0, 2, 0, 0);
    v.emplace_back(1, 0, 2, 0, 0);
    v.emplace_back(2, 0, 1, 4, -3);
    v.emplace_back(5, 0, 1, 1, -2);
    v.emplace_back(6, 2, 0, 0, -2);
    v.emplace_back(8, 0, 2, 0, 0);
    v.emplace_back(9, 0, 2, 2, -1);
    v.emplace_back(11, 2, 0, 2, 1);
    v.emplace_back(3, 3, 2, 0, -2);
    v.emplace_back(4, 0, 2, 0, -2);
    v.emplace_back(7, 0, 0, 0, -2);
    v.emplace_back(10, 2, 0, 4, -2);
    litchfieldLetterPosMap["AC"] = v;
    v.clear();

    v.emplace_back(0, 0, 2, -2, 0);
    v.emplace_back(1, 0, 2, -2, 0);
    v.emplace_back(2, 2, 2, -1, 0);
    v.emplace_back(4, 0, 2, 0, -2);
    v.emplace_back(5, 1, 2, 0, -2);
    v.emplace_back(6, 3, 1, -2, 0);
    v.emplace_back(8, 0, -1, -2, 2);
    v.emplace_back(9, 0, 0, -1, 4);
    v.emplace_back(10, -2, 0, -2, 0);
    v.emplace_back(11, 2, 2, -1, 3);
    v.emplace_back(3, 0, 2, 0, 0);
    v.emplace_back(7, 0, 2, -2, 0);
    litchfieldLetterPosMap["AD"] = v;
    v.clear();

    v.emplace_back(0, 0, 2, 0, -2);
    v.emplace_back(1, 0, 2, 0, -2);
    v.emplace_back(3, 2, 0, 0, 3);
    v.emplace_back(4, 0, 0, 0, 3);
    v.emplace_back(5, 2, 0, -2, 0);
    v.emplace_back(6, 2, 2, -2, -2);
    v.emplace_back(8, -3, 0, -2, -1);
    v.emplace_back(9, -2, 0, -1, -2);
    v.emplace_back(11, 0,0, 0, 2);
    v.emplace_back(2, 2, 0, 0, -2);
    v.emplace_back(7, 4, 2, -2, -2);
    v.emplace_back(10, 0,0, 2, 0);
    litchfieldLetterPosMap["AE"] = v;
    v.clear();

    v.emplace_back(0, 2, 2, 0, 0);
    v.emplace_back(1, 2, 2, 0, 0);
    v.emplace_back(5, 1, -1, 2, -2);
    v.emplace_back(6, 0, 2, 2, -2);
    v.emplace_back(7, -2, 0, 0, -2);
    v.emplace_back(8, -2, 2, 2, 0);
    v.emplace_back(9, 0, 2, -1, -2);
    v.emplace_back(11, 3, -2, 2, 0);
    v.emplace_back(2, 2, -2, 0, 0);
    v.emplace_back(3, -2, 0, 2, 0);
    v.emplace_back(4, 4, -2, 4, 0);
    v.emplace_back(10, -3, 0, 2, 0);
    litchfieldLetterPosMap["AF"] = v;
    v.clear();

    v.emplace_back(0, -2, 2, -2, -2);
    v.emplace_back(1, -2, 2, -2, -2);
    v.emplace_back(2, 0, 2, -2, -2);
    v.emplace_back(3, 0, 0, -2, -2);
    v.emplace_back(5, 0, 0, -2, 0);
    v.emplace_back(6, 0, 2, -2, -2);
    v.emplace_back(7, 0, 2, -2, -2);
    v.emplace_back(8, -1, -1, -2, -2);
    v.emplace_back(9, 0, -2, 2, -2);
    v.emplace_back(10, 0, 2, 1, 0);
    v.emplace_back(11, -2, 0, -2, 0);
    v.emplace_back(4, 0, 2, -2, -2);
    litchfieldLetterPosMap["AG"] = v;
    v.clear();

    v.emplace_back(0, -2, 2, 0, -2);
    v.emplace_back(1, -2, 2, 0, -2);
    v.emplace_back(4, 0, 0, -3, -3);
    v.emplace_back(5, 0, 0, -2, -2);
    v.emplace_back(6, 0, 0, 0, -1);
    v.emplace_back(8, -2, 0, -4, 2);
    v.emplace_back(9, -2, 2, 0, -2);
    v.emplace_back(11, 4, 0, 0, 1);
    v.emplace_back(2, 4, -2, -2, 0);
    v.emplace_back(3, 0, 0, 2, 2);
    v.emplace_back(7, 0, 2, -2, -2);
    v.emplace_back(10, -2, 2, 1, -2);
    litchfieldLetterPosMap["AH"] = v;
    v.clear();

    v.emplace_back(0, 0, 2, 2, 0);
    v.emplace_back(1, 0, 2, 2, 0);
    v.emplace_back(3, 2, 2, 2, 0);
    v.emplace_back(4, 0, 1, 0, -1);
    v.emplace_back(5, 2, -2, 0, -2);
    v.emplace_back(6, 0, 1, -2, -2);
    v.emplace_back(7, 0, 0, 0, 0);
    v.emplace_back(8, 0, -2, 0, 2);
    v.emplace_back(9, 2, 0, 0, 0);
    v.emplace_back(10, -3, 2, 0, 2);
    v.emplace_back(11, 0, 2, -2, 0);
    v.emplace_back(2, 2, 2, -2, 2);
    litchfieldLetterPosMap["AI"] = v;
    v.clear();

    v.emplace_back(0, -2, 2, -2, 0);
    v.emplace_back(1, -2, 2, -2, 0);
    v.emplace_back(6, 0, 1, -2, -1);
    v.emplace_back(7, 0, -1, 0, 0);
    v.emplace_back(8, 0, 2, -2, -1);
    v.emplace_back(9, -2, 0, -2, 0);
    v.emplace_back(11, 2, 2, -3, 2);
    v.emplace_back(2, 2, 0, 2, 0);
    v.emplace_back(3, 2, -2, -2, -2);
    v.emplace_back(4, 2, 0, -3, 0);
    v.emplace_back(5, 0, 2, -2, -1);
    v.emplace_back(10, 2, 2, -2, 2);
    litchfieldLetterPosMap["AJ"] = v;
    v.clear();

    v.emplace_back(0, -2, 2, -2, 0);
    v.emplace_back(1, -2, 2, -2, 0);
    v.emplace_back(3, 0, 1, 0, -2);
    v.emplace_back(4, 2, 0, 0, 0);
    v.emplace_back(5, 0, -2, 0, -2);
    v.emplace_back(6, -2, 2, 0, 0);
    v.emplace_back(7, 0, 0, -2, 0);
    v.emplace_back(8, -2, 0, -2, -1);
    v.emplace_back(9, -2, 0, 4, -2);
    v.emplace_back(11, 0, 0, 0, 0);
    v.emplace_back(2, 0, 1, 0, 0);
    v.emplace_back(10, -2, 0, 0, 2);
    litchfieldLetterPosMap["AK"] = v;
    v.clear();


    v.emplace_back(0, 0, 2, -2, -2);
    v.emplace_back(1, 0, 2, -2, -2);
    v.emplace_back(2, 0, 0, -2, 0);
    v.emplace_back(3, 0, -2, 0, -2);
    v.emplace_back(5, 0, 2, 0, 0);
    v.emplace_back(6, -2, 2, -2, -2);
    v.emplace_back(7, 0, 2, 2, -2);
    v.emplace_back(8, 0, 0, -2, -2);
    v.emplace_back(10, 3, 0, 2, 2);
    v.emplace_back(11, -2, 2, 0, 2);
    v.emplace_back(4, 2, 1, -2, 1);
    v.emplace_back(9, 0, 0, 0, -2);
    litchfieldLetterPosMap["AL"] = v;
    v.clear();

    v.emplace_back(0, 0, 2, 0, 1);
    v.emplace_back(1, 0, 2, 0, 1);
    v.emplace_back(2, -1, 2, 2, -2);
    v.emplace_back(3, -1, 2, 0, 0);
    v.emplace_back(4, -2, 2, 0, 0);
    v.emplace_back(5, -1, 2, 0, 0);
    v.emplace_back(7, -1, 0, -2, 0);
    v.emplace_back(8, 0, 2, -1, 0);
    v.emplace_back(9, -2, 0, 0, 0);
    v.emplace_back(10, -2, 2, 0, 0);
    v.emplace_back(11, 3, 0, -2, 0);
    v.emplace_back(6, 2, 2, 2, 2);
    litchfieldLetterPosMap["BA"] = v;
    v.clear();

    v.emplace_back(0, 0, 0, 0, 0);
    v.emplace_back(1, 0, 0, 0, 0);
    v.emplace_back(2, 3, 2, -2, 2);
    v.emplace_back(7, 0, 2, 0, -2);
    v.emplace_back(8, 0, 2, -2, 2);
    v.emplace_back(9, -1, 2, -2, 0);
    v.emplace_back(11, 0, -2, 2, -1);
    v.emplace_back(3, -2, 2, -2, 2);
    v.emplace_back(4, -2, 2, -2, 2);
    v.emplace_back(5, 2, 0, -2, -2);
    v.emplace_back(6, 2, 2, 0, 0);
    v.emplace_back(10, -2, 1, -2, -1);
    litchfieldLetterPosMap["BB"] = v;
    v.clear();




    // TE
    v.emplace_back(0, 1, 1, 2, 3); // plate 1a
    v.emplace_back(1, 2, 1, 2, 3);
    v.emplace_back(2, 1, -2, -2, -1);
    v.emplace_back(3, -1, 2, 2, 0);
    v.emplace_back(4, 0, 0, -2, 4);
    v.emplace_back(5, 0, 3, 2, -2);
    v.emplace_back(6, 0, 3, -1, -2);
    v.emplace_back(7, 0, 1, -1, -1);
    v.emplace_back(8, 0, 1, 0, 0);
    v.emplace_back(9, 0, -1, 0, 0);
    v.emplace_back(10, 0, 2, -2, 1);
    v.emplace_back(11, -2, 2, 2, 0);
    litchfieldLetterPosMap["TE"] = v;
    v.clear();

    // TF
    v.emplace_back(2, 0, -2, 0, 0);
    v.emplace_back(3, -2, 2, -1, 0);
    v.emplace_back(5, 0, 0, 0, -2);
    v.emplace_back(6, 0, 4, 1, -3);
    v.emplace_back(8, -2, -2, 0, 0);
    v.emplace_back(10, 4, 0, -4, -2);
    v.emplace_back(11, 0, 2, -2, 0);
    v.emplace_back(0, 0, 2, -2, -2);
    v.emplace_back(1, 0, 2, -2, -2);
    v.emplace_back(4, -1, 1, -1, 0);
    v.emplace_back(7, 0, 2, -2, -2);
    v.emplace_back(9, 2, 0, 0, -2);
    litchfieldLetterPosMap["TF"] = v;
    v.clear();

    cout << litchfieldLetterPosMap["TF"][0].plate << endl;
    string data[] = { "AL", // 7
                      "AA",
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
