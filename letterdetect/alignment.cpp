#include <map>
#include <set>
#include <vector>
#include <iostream>

using namespace std;

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


void calculatePlate(const std::string& letterPair,
                    int leftVert,
                    int leftHoriz,
                    int rightVert,
                    int rightHoriz)
{
    int minLV = leftVert - 1;
    int maxLV = leftVert + 1;
    int minLH = leftHoriz - 1;
    int maxLH = leftHoriz + 1;

    int minRV = rightVert - 1;
    int maxRV = rightVert + 1;
    int minRH = rightHoriz - 1;
    int maxRH = rightHoriz + 1;

    vector<LitchfieldItem> candidates;
    vector<LitchfieldItem> all = litchfieldLetterPosMap[letterPair];
    for (LitchfieldItem i : all) {
        cout << "checking: " << (int)i.plate << endl;
        if (( i.lv >= minLV &&
            i.lv <= maxLV &&
            i.lh >= minLH &&
            i.lh <= maxLH )  || (
            i.rv >= minRV &&
            i.lv <= maxRV &&
            i.lh >= minRH &&
            i.lh <= maxRH) ) {
            candidates.push_back(i);
        }
    }

    for (auto i : candidates) {
        cout << i.plate << endl;
    }

}

void verticalAlignment(int a) {
    switch (a) {
    case -5:
    case -4:
        cout << "ext high" ;
        break;
    case -3:
        cout << "very high" ;
        break;
    case -2:
        cout << "high" ;
        break;
    case -1:
        cout << "sl high" ;
        break;
    case 0:
        cout << "central" ;
        break;
    case 1:
        cout << "sl low" ;
        break;
    case 2:
        cout << "low" ;
        break;
    case 3:
        cout << "very low" ;
        break;
    case 4:
    case 5:
        cout << "ext low" ;
        break;
    default:
        cout << "XXX: " << a ;
    }
}

void horizontalAlignment(int a)
{
    switch (a) {
    case -4:
        cout << ", ext left" << endl;
        break;
    case -3:
        cout << ", very left" << endl;
        break;
    case -2:
        cout << ", left" << endl;
        break;
    case -1:
        cout << ", sl left" << endl;
        break;
    case 0:
        cout << ", central" << endl;
        break;
    case 1:
        cout << ", sl right" << endl;
        break;
    case 2:
        cout << ", right" << endl;
        break;
    case 3:
        cout << ", very right" << endl;
        break;
    case 4:
        cout << ", ext right" << endl;
        break;
    default:
        cout << "XXX: " << a << endl;
    }
}

void setup() {
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

}
