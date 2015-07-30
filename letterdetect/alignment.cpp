#include <map>
#include <vector>
#include <iostream>

using namespace std;

typedef int PlateNo;
class LitchfieldItem {
public:
    LitchfieldItem(const std::string letterPair,
                   int pl, int alv, int alh, int arv, int arl)
        : pair(letterPair), plate(pl), lv(alv), lh(alh), rv(arv), rh(arl)
    {}
    std::string pair;
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
//    cout << "calculatePlate: " << letterPair << endl;
//    cout << leftVert << ", "<< leftHoriz << endl;
//    cout << rightVert << ", "<< rightHoriz << endl;
    bool leftIsValid = false;
    bool rightIsValid = false;

    if (leftVert != -1000)
        leftIsValid = true;
    if (rightVert != -1000)
        rightIsValid = true;
//    cout << leftIsValid << ", " << rightIsValid << endl;
    int minLV = leftVert - 2;
    int maxLV = leftVert + 2;
    int minLH = leftHoriz - 2;
    int maxLH = leftHoriz + 2;

    int minRV = rightVert - 2;
    int maxRV = rightVert + 2;
    int minRH = rightHoriz - 2;
    int maxRH = rightHoriz + 2;

    vector<LitchfieldItem> candidates;
    vector<LitchfieldItem> all = litchfieldLetterPosMap[letterPair];
    for (LitchfieldItem i : all) {
//        cout << "checking: " << (int)i.plate << endl;

//        cout << i.lv << ", "<< i.lh << endl;
//        cout << i.rv << ", "<< i.rh << endl;

        if (leftIsValid && rightIsValid) {
            if (( i.lv >= minLV &&
                  i.lv <= maxLV &&
                  i.lh >= minLH &&
                  i.lh <= maxLH ) && (
                        i.rv >= minRV &&
                        i.rv <= maxRV &&
                        i.rh >= minRH &&
                        i.rh <= maxRH) ) {
                candidates.push_back(i);
            }
        } else if (leftIsValid) {
            if ( i.lv >= minLV &&
                 i.lv <= maxLV &&
                 i.lh >= minLH &&
                 i.lh <= maxLH ) {
                candidates.push_back(i);
            }
        } else if (rightIsValid) {
            if ( i.rv >= minRV &&
                 i.rv <= maxRV &&
                 i.rh >= minRH &&
                 i.rh <= maxRH ) {
                candidates.push_back(i);
            }
        }
    }

    cout << "Candidates: ";
    if (candidates.size())
    {
        for (auto i : candidates) {
            cout << i.plate << ", ";
        }
        cout << endl;
    }
    else
    {
        cout << "[]" << endl;
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

void printAlignment(int offsetVertical,
                    int offsetHorizontal)
{
    verticalAlignment(offsetVertical);
    horizontalAlignment(offsetHorizontal);
}

void setup() {
    vector<LitchfieldItem> v;

    // AA
    v.emplace_back("AA", 0, 0, 1, 1, 1);
    v.emplace_back("AA", 1, 0, 1, 1, 1);
    v.emplace_back("AA", 2, 0, 0, 0, 0);
    v.emplace_back("AA", 3, -1, 2, 0, 0);
    v.emplace_back("AA", 4, -2, 2, -3, 0);
    v.emplace_back("AA", 5, 0, 0, 2, -2);
    v.emplace_back("AA", 6, 3, 0, 0, 0);
    v.emplace_back("AA", 8, 0,0, 0, 0);
    v.emplace_back("AA", 9, -4, 2, 3, -2);
    v.emplace_back("AA", 11, 0, 0, 2, 2);
    v.emplace_back("AA", 7, 4, -2, 0, 0);
    v.emplace_back("AA", 10, 0,0, 4, 0);
    litchfieldLetterPosMap["AA"] = v;
    v.clear();

    v.emplace_back("AB", 0, 0,0, 0, 2);
    v.emplace_back("AB", 1, 0,0,0,2);
    v.emplace_back("AB", 2, 1, 1, -2, 2);
    v.emplace_back("AB", 4, 4, 2, 0, -1);
    v.emplace_back("AB", 5, 0, 0, -1, -1);
    v.emplace_back("AB", 7, 0, 0, 0, 0);
    v.emplace_back("AB", 8, -1, -1, 0, 2);
    v.emplace_back("AB", 9, -2, 0, 0, -2);
    v.emplace_back("AB", 11, 0, 0, 2, -2);
    v.emplace_back("AB", 3, 0, 2, -2, 2);
    v.emplace_back("AB", 6, 0, 2, -2, 0);
    v.emplace_back("AB", 10, -2, 0, -2, 0);
    litchfieldLetterPosMap["AB"] = v;
    v.clear();

    v.emplace_back("AC", 0, 0, 2, 0, 0);
    v.emplace_back("AC", 1, 0, 2, 0, 0);
    v.emplace_back("AC", 2, 0, 1, 4, -3);
    v.emplace_back("AC", 5, 0, 1, 1, -2);
    v.emplace_back("AC", 6, 2, 0, 0, -2);
    v.emplace_back("AC", 8, 0, 2, 0, 0);
    v.emplace_back("AC", 9, 0, 2, 2, -1);
    v.emplace_back("AC", 11, 2, 0, 2, 1);
    v.emplace_back("AC", 3, 3, 2, 0, -2);
    v.emplace_back("AC", 4, 0, 2, 0, -2);
    v.emplace_back("AC", 7, 0, 0, 0, -2);
    v.emplace_back("AC", 10, 2, 0, 4, -2);
    litchfieldLetterPosMap["AC"] = v;
    v.clear();

    v.emplace_back("AD", 0, 0, 2, -2, 0);
    v.emplace_back("AD", 1, 0, 2, -2, 0);
    v.emplace_back("AD", 2, 2, 2, -1, 0);
    v.emplace_back("AD", 4, 0, 2, 0, -2);
    v.emplace_back("AD", 5, 1, 2, 0, -2);
    v.emplace_back("AD", 6, 3, 1, -2, 0);
    v.emplace_back("AD", 8, 0, -1, -2, 2);
    v.emplace_back("AD", 9, 0, 0, -1, 4);
    v.emplace_back("AD", 10, -2, 0, -2, 0);
    v.emplace_back("AD", 11, 2, 2, -1, 3);
    v.emplace_back("AD", 3, 0, 2, 0, 0);
    v.emplace_back("AD", 7, 0, 2, -2, 0);
    litchfieldLetterPosMap["AD"] = v;
    v.clear();

    v.emplace_back("AE", 0, 0, 2, 0, -2);
    v.emplace_back("AE", 1, 0, 2, 0, -2);
    v.emplace_back("AE", 3, 2, 0, 0, 3);
    v.emplace_back("AE", 4, 0, 0, 0, 3);
    v.emplace_back("AE", 5, 2, 0, -2, 0);
    v.emplace_back("AE", 6, 2, 2, -2, -2);
    v.emplace_back("AE", 8, -3, 0, -2, -1);
    v.emplace_back("AE", 9, -2, 0, -1, -2);
    v.emplace_back("AE", 11, 0,0, 0, 2);
    v.emplace_back("AE", 2, 2, 0, 0, -2);
    v.emplace_back("AE", 7, 4, 2, -2, -2);
    v.emplace_back("AE", 10, 0,0, 2, 0);
    litchfieldLetterPosMap["AE"] = v;
    v.clear();

    v.emplace_back("AF", 0, 2, 2, 0, 0);
    v.emplace_back("AF", 1, 2, 2, 0, 0);
    v.emplace_back("AF", 5, 1, -1, 2, -2);
    v.emplace_back("AF", 6, 0, 2, 2, -2);
    v.emplace_back("AF", 7, -2, 0, 0, -2);
    v.emplace_back("AF", 8, -2, 2, 2, 0);
    v.emplace_back("AF", 9, 0, 2, -1, -2);
    v.emplace_back("AF", 11, 3, -2, 2, 0);
    v.emplace_back("AF", 2, 2, -2, 0, 0);
    v.emplace_back("AF", 3, -2, 0, 2, 0);
    v.emplace_back("AF", 4, 4, -2, 4, 0);
    v.emplace_back("AF", 10, -3, 0, 2, 0);
    litchfieldLetterPosMap["AF"] = v;
    v.clear();

    v.emplace_back("AG", 0, -2, 2, -2, -2);
    v.emplace_back("AG", 1, -2, 2, -2, -2);
    v.emplace_back("AG", 2, 0, 2, -2, -2);
    v.emplace_back("AG", 3, 0, 0, -2, -2);
    v.emplace_back("AG", 5, 0, 0, -2, 0);
    v.emplace_back("AG", 6, 0, 2, -2, -2);
    v.emplace_back("AG", 7, 0, 2, -2, -2);
    v.emplace_back("AG", 8, -1, -1, -2, -2);
    v.emplace_back("AG", 9, 0, -2, 2, -2);
    v.emplace_back("AG", 10, 0, 2, 1, 0);
    v.emplace_back("AG", 11, -2, 0, -2, 0);
    v.emplace_back("AG", 4, 0, 2, -2, -2);
    litchfieldLetterPosMap["AG"] = v;
    v.clear();

    v.emplace_back("AH", 0, -2, 2, 0, -2);
    v.emplace_back("AH", 1, -2, 2, 0, -2);
    v.emplace_back("AH", 4, 0, 0, -3, -3);
    v.emplace_back("AH", 5, 0, 0, -2, -2);
    v.emplace_back("AH", 6, 0, 0, 0, -1);
    v.emplace_back("AH", 8, -2, 0, -4, 2);
    v.emplace_back("AH", 9, -2, 2, 0, -2);
    v.emplace_back("AH", 11, 4, 0, 0, 1);
    v.emplace_back("AH", 2, 4, -2, -2, 0);
    v.emplace_back("AH", 3, 0, 0, 2, 2);
    v.emplace_back("AH", 7, 0, 2, -2, -2);
    v.emplace_back("AH", 10, -2, 2, 1, -2);
    litchfieldLetterPosMap["AH"] = v;
    v.clear();

    v.emplace_back("AI", 0, 0, 2, 2, 0);
    v.emplace_back("AI", 1, 0, 2, 2, 0);
    v.emplace_back("AI", 3, 2, 2, 2, 0);
    v.emplace_back("AI", 4, 0, 1, 0, -1);
    v.emplace_back("AI", 5, 2, -2, 0, -2);
    v.emplace_back("AI", 6, 0, 1, -2, -2);
    v.emplace_back("AI", 7, 0, 0, 0, 0);
    v.emplace_back("AI", 8, 0, -2, 0, 2);
    v.emplace_back("AI", 9, 2, 0, 0, 0);
    v.emplace_back("AI", 10, -3, 2, 0, 2);
    v.emplace_back("AI", 11, 0, 2, -2, 0);
    v.emplace_back("AI", 2, 2, 2, -2, 2);
    litchfieldLetterPosMap["AI"] = v;
    v.clear();

    v.emplace_back("AJ", 0, -2, 2, -2, 0);
    v.emplace_back("AJ", 1, -2, 2, -2, 0);
    v.emplace_back("AJ", 6, 0, 1, -2, -1);
    v.emplace_back("AJ", 7, 0, -1, 0, 0);
    v.emplace_back("AJ", 8, 0, 2, -2, -1);
    v.emplace_back("AJ", 9, -2, 0, -2, 0);
    v.emplace_back("AJ", 11, 2, 2, -3, 2);
    v.emplace_back("AJ", 2, 2, 0, 2, 0);
    v.emplace_back("AJ", 3, 2, -2, -2, -2);
    v.emplace_back("AJ", 4, 2, 0, -3, 0);
    v.emplace_back("AJ", 5, 0, 2, -2, -1);
    v.emplace_back("AJ", 10, 2, 2, -2, 2);
    litchfieldLetterPosMap["AJ"] = v;
    v.clear();

    v.emplace_back("AK", 0, -2, 2, -2, 0);
    v.emplace_back("AK", 1, -2, 2, -2, 0);
    v.emplace_back("AK", 3, 0, 1, 0, -2);
    v.emplace_back("AK", 4, 2, 0, 0, 0);
    v.emplace_back("AK", 5, 0, -2, 0, -2);
    v.emplace_back("AK", 6, -2, 2, 0, 0);
    v.emplace_back("AK", 7, 0, 0, -2, 0);
    v.emplace_back("AK", 8, -2, 0, -2, -1);
    v.emplace_back("AK", 9, -2, 0, 4, -2);
    v.emplace_back("AK", 11, 0, 0, 0, 0);
    v.emplace_back("AK", 2, 0, 1, 0, 0);
    v.emplace_back("AK", 10, -2, 0, 0, 2);
    litchfieldLetterPosMap["AK"] = v;
    v.clear();

    v.emplace_back("AL", 0, 0, 2, -2, -2);
    v.emplace_back("AL", 1, 0, 2, -2, -2);
    v.emplace_back("AL", 2, 0, 0, -2, 0);
    v.emplace_back("AL", 3, 0, -2, 0, -2);
    v.emplace_back("AL", 5, 0, 2, 0, 0);
    v.emplace_back("AL", 6, -2, 2, -2, -2);
    v.emplace_back("AL", 7, 0, 2, 2, -2);
    v.emplace_back("AL", 8, 0, 0, -2, -2);
    v.emplace_back("AL", 10, 3, 0, 2, 2);
    v.emplace_back("AL", 11, -2, 2, 0, 2);
    v.emplace_back("AL", 4, 2, 1, -2, 1);
    v.emplace_back("AL", 9, 0, 0, 0, -2);
    litchfieldLetterPosMap["AL"] = v;
    v.clear();

    v.emplace_back("BA", 0, 0, 2, 0, 1);
    v.emplace_back("BA", 1, 0, 2, 0, 1);
    v.emplace_back("BA", 2, -1, 2, 2, -2);
    v.emplace_back("BA", 3, -1, 2, 0, 0);
    v.emplace_back("BA", 4, -2, 2, 0, 0);
    v.emplace_back("BA", 5, -1, 2, 0, 0);
    v.emplace_back("BA", 7, -1, 0, -2, 0);
    v.emplace_back("BA", 8, 0, 2, -1, 0);
    v.emplace_back("BA", 9, -2, 0, 0, 0);
    v.emplace_back("BA", 10, -2, 2, 0, 0);
    v.emplace_back("BA", 11, 3, 0, -2, 0);
    v.emplace_back("BA", 6, 2, 2, 2, 2);
    litchfieldLetterPosMap["BA"] = v;
    v.clear();

    v.emplace_back("BB", 0, 0, 0, 0, 0);
    v.emplace_back("BB", 1, 0, 0, 0, 0);
    v.emplace_back("BB", 2, 3, 2, -2, 2);
    v.emplace_back("BB", 7, 0, 2, 0, -2);
    v.emplace_back("BB", 8, 0, 2, -2, 2);
    v.emplace_back("BB", 9, -1, 2, -2, 0);
    v.emplace_back("BB", 11, 0, -2, 2, -1);
    v.emplace_back("BB", 3, -2, 2, -2, 2);
    v.emplace_back("BB", 4, -2, 2, -2, 2);
    v.emplace_back("BB", 5, 2, 0, -2, -2);
    v.emplace_back("BB", 6, 2, 2, 0, 0);
    v.emplace_back("BB", 10, -2, 1, -2, -1);
    litchfieldLetterPosMap["BB"] = v;
    v.clear();

    // BC
    v.emplace_back("BC", 0, 2, 2, -1, -2);
    v.emplace_back("BC", 1 , 2, 2, -1, -2);
    v.emplace_back("BC", 2, 2, 2, 4, -4);
    v.emplace_back("BC", 6, 0, 2, 3, -2);
    v.emplace_back("BC", 8, 0, 0, 0, -2);
    v.emplace_back("BC", 9, -3, 0, 2, -2);
    v.emplace_back("BC", 11, 0, 0, 1, 2);
    v.emplace_back("BC", 3, 0, 2, -2, -2);
    v.emplace_back("BC", 4, 2, 0, 3, 0);
    v.emplace_back("BC", 5, 2, 0, 2, -2);
    v.emplace_back("BC", 7, -3, 2, 0, 0);
    v.emplace_back("BC", 10, -3, 2, -2, 0);
    litchfieldLetterPosMap["BB"] = v;
    v.clear();

    // BD
    v.emplace_back("BD", 0, 3, 2, 0, -2);
    v.emplace_back("BD", 1, 3, 2, 0, -2);
    v.emplace_back("BD", 2, 0, 0, 0, -2);
    v.emplace_back("BD", 4, -2, 2, 0, 0);
    v.emplace_back("BD", 5, 0, 2, 0, 0);
    v.emplace_back("BD", 9, -2, -2, 2, 2);
    v.emplace_back("BD", 11, 2, -1, 2, 3);
    v.emplace_back("BD", 3, 2, 2, 0, 0);
    v.emplace_back("BD", 6, 2, 2, 0, 0);
    v.emplace_back("BD", 7, 0, -1, 0, 0);
    v.emplace_back("BD", 8, 0, 0, 0, 2);
    v.emplace_back("BD", 10, -2, 2, -2, 0);
    litchfieldLetterPosMap["BD"] = v;
    v.clear();

    // BE
    v.emplace_back("BE", 0, 2, 2, 0, 3);
    v.emplace_back("BE", 1, 2, 2, 0, 3);
    v.emplace_back("BE", 2, 0, -2, 0, 0);
    v.emplace_back("BE", 3, 2, -2, 0, 2);
    v.emplace_back("BE", 4, 2, 2, 0, 3);
    v.emplace_back("BE", 5, 0, 2, -2, 0);
    v.emplace_back("BE", 6, 0, 2, 0, -2);
    v.emplace_back("BE", 7, 0, 2, -2, 0);
    v.emplace_back("BE", 9, 2, 2, 2, 0);
    v.emplace_back("BE", 11, 0, 2, 0, -2);
    v.emplace_back("BE", 8, 0, 2, 0, 0);
    v.emplace_back("BE", 10, -3, 2, 3, 0);
    litchfieldLetterPosMap["BE"] = v;
    v.clear();

    // BF
    v.emplace_back("BF", 0, 2, 2, -2, 0);
    v.emplace_back("BF", 1, 2, 2, -2, 0);
    v.emplace_back("BF", 2, 0, 0, 0, 0);
    v.emplace_back("BF", 3, -2, 2, 2, -2);
    v.emplace_back("BF", 4, 0, 0, 0, 0);
    v.emplace_back("BF", 5, -2, 0, 0, 0);
    v.emplace_back("BF", 6, 0, 3, 1, -2);
    v.emplace_back("BF", 7, 0, 0, 0, -2);
    v.emplace_back("BF", 8, 0, 2, 0, 0);
    v.emplace_back("BF", 9, -2, 2, -2, -1);
    v.emplace_back("BF", 11, 2, 2, 0, 0);
    v.emplace_back("BF", 10, 0, 2, 2, 0);
    litchfieldLetterPosMap["BF"] = v;
    v.clear();

    // BG
    v.emplace_back("BG", 4, 0, 2, -2, -2);
    v.emplace_back("BG", 5, 0, 0, -2, 0);
    v.emplace_back("BG", 6, 2, 2, -2, -2);
    v.emplace_back("BG", 8, -1, 0, -3, 0);
    v.emplace_back("BG", 9, -2, -2, 3, -2);
    v.emplace_back("BG", 11, 3, -2, -3, 0);
    v.emplace_back("BG", 0, 0, 0, 0, 0);
    v.emplace_back("BG", 1, 0, 0, 0, 0);
    v.emplace_back("BG", 2, 0, -1, 1, 0);
    v.emplace_back("BG", 3, 2, -2, -2, -2);
    v.emplace_back("BG", 7, 0, 2, -2, -2);
    v.emplace_back("BG", 10, 0, 2, -2, -2);
    litchfieldLetterPosMap["BG"] = v;
    v.clear();

    // BH
    v.emplace_back("BH", 0, 2, 2, 0, -1);
    v.emplace_back("BH", 1, 2, 2, 0, -1);
    v.emplace_back("BH", 2, 0, -2, -2, 2);
    v.emplace_back("BH", 4, 0, 2, -2, -2);
    v.emplace_back("BH", 5, -2, -2, 0, 0);
    v.emplace_back("BH", 6, 0, 2, -1, 0);
    v.emplace_back("BH", 7, 0, 0, -2, -2);
    v.emplace_back("BH", 9, -2, 0, 3, -2);
    v.emplace_back("BH", 10, 2, 2, 4, -2);
    v.emplace_back("BH", 11, 2, 0, 0, 2);
    v.emplace_back("BH", 3, 0, 2, -2, 0);
    v.emplace_back("BH", 8, -1, 1, -2, 2);
    litchfieldLetterPosMap["BH"] = v;
    v.clear();

    // BI
    v.emplace_back("BI", 0, 1, 2, 1, 2);
    v.emplace_back("BI", 1, 1, 2, 1, 2);
    v.emplace_back("BI", 4, 0, -2, 2, 0);
    v.emplace_back("BI", 6, 0, 2, 0, 0);
    v.emplace_back("BI", 7, 0, 2, 0, -2);
    v.emplace_back("BI", 8, 0, 2, -1, 0);
    v.emplace_back("BI", 9, -3, 2, 2, 0);
    v.emplace_back("BI", 11, 0, 0, -2, 2);
    v.emplace_back("BI", 2, -2, -2, 3, 0);
    v.emplace_back("BI", 3, 2, 0, -2, -1);
    v.emplace_back("BI", 5, 0, -1, 0, -2);
    v.emplace_back("BI", 10, 2, 2, 0, 1);
    litchfieldLetterPosMap["BI"] = v;
    v.clear();

    // BJ
    v.emplace_back("BJ", 0, 0, 2, -2, -2);
    v.emplace_back("BJ", 1, 0, 2, -2, -2);
    v.emplace_back("BJ", 5, -1, -2, -1, 0);
    v.emplace_back("BJ", 6, 0, 2, -3, -2);
    v.emplace_back("BJ", 7, 1, 0, 0, 0);
    v.emplace_back("BJ", 8, 0, 2, -2, 0);
    v.emplace_back("BJ", 9, 0, 2, -4, -2);
    v.emplace_back("BJ", 10, 2, 2, 4, -2);
    v.emplace_back("BJ", 11, 2, -2, -4, 2);
    v.emplace_back("BJ", 2, 0, -2, 0, 0);
    v.emplace_back("BJ", 3, -3, 2, -2, -2);
    v.emplace_back("BJ", 4, 2, 0, 0, 0);
    litchfieldLetterPosMap["BJ"] = v;
    v.clear();

    v.emplace_back("BK", 0, 0, 2, -2, -2);
    v.emplace_back("BK", 1, 0, 2, -2, -2);
    v.emplace_back("BK", 2, 0, -1, 0, 0);
    v.emplace_back("BK", 4, 0, 0, 0, 0);
    v.emplace_back("BK", 6, 0, 3, -2, -2);
    v.emplace_back("BK", 8, 0, 0, 0, 0);
    v.emplace_back("BK", 9, -2, -2, 2, -2);
    v.emplace_back("BK", 11, -2, 2, 0, 0);
    v.emplace_back("BK", 3, 0, 2, 0, -2);
    v.emplace_back("BK", 5, -2, 2, 0, 0);
    v.emplace_back("BK", 7, 0, 0, -1, -2);
    v.emplace_back("BK", 10, -4, 2, 0, 2);
    litchfieldLetterPosMap["BK"] = v;
    v.clear();

    // BL
    v.emplace_back("BL", 4, 0, -2, 0, 1);
    v.emplace_back("BL", 6, 0, 2, 0, 0);
    v.emplace_back("BL", 7, 2, -2, -2, -2);
    v.emplace_back("BL", 8, 0, 0, -2, 0);
    v.emplace_back("BL", 9, -2, -2, 2, -2);
    v.emplace_back("BL", 11, 0, -1, -2, 2);
    v.emplace_back("BL", 0, 0, 2, -2, -2);
    v.emplace_back("BL", 1, 0, 2, -2, -2);
    v.emplace_back("BL", 2, -2, 2, -3, -2);
    v.emplace_back("BL", 3, 0, 2, 0, -2);
    v.emplace_back("BL", 5, -2, 0, 0, -2);
    v.emplace_back("BL", 10, -1, 2, 0, 2);
    litchfieldLetterPosMap["BL"] = v;
    v.clear();

    // CA
    v.emplace_back("CA", 0, 0, -2, 2, 2);
    v.emplace_back("CA", 1, 0, -2, 2, 2);
    v.emplace_back("CA", 3, 1, 0, 0, 0);
    v.emplace_back("CA", 4, -2, 1, 0, 0);
    v.emplace_back("CA", 5, 2, -2, 2, 0);
    v.emplace_back("CA", 6, -2, 0, 2, 0);
    v.emplace_back("CA", 7, 1, -3, -2, 0);
    v.emplace_back("CA", 8, 0, -2, 0, 0);
    v.emplace_back("CA", 9, 2, -2, 1, 1);
    v.emplace_back("CA", 10, 2, -2, -2, 2);
    v.emplace_back("CA", 11, 3, 0, -4, 2);
    v.emplace_back("CA", 2, 4, 0, 0, 0);
    litchfieldLetterPosMap["CA"] = v;
    v.clear();

    // CB
    v.emplace_back("CB", 0, 0, 0, 0, 0);
    v.emplace_back("CB", 1, 0, 0, 0, 0);
    v.emplace_back("CB", 4, 2, -2, 0, 2);
    v.emplace_back("CB", 5, 2, -2, 0, 2);
    v.emplace_back("CB", 7, 0, -4, 0, -2);
    v.emplace_back("CB", 9, 4, -2, 2, 2);
    v.emplace_back("CB", 11, 2, -2, -2, 2);
    v.emplace_back("CB", 2, -2, 0, 2, 2);
    v.emplace_back("CB", 3, 0, 0, -3, 2);
    v.emplace_back("CB", 6, 3, 0, 3, 0);
    v.emplace_back("CB", 8, 0,0, 0, 2);
    v.emplace_back("CB", 10, 2, 0, 2, 2);
    litchfieldLetterPosMap["CB"] = v;
    v.clear();

    // CG
    v.emplace_back("CG", 0, 0, 0, -2, 0);
    v.emplace_back("CG", 1, 0, 0, -2, 0);
    v.emplace_back("CG", 2, 0, 0, -2, 0);
    v.emplace_back("CG", 3, 0, 0, -2, 0);
    v.emplace_back("CG", 7, -1, -2, -2, -2);
    v.emplace_back("CG", 9, -2, -1, 2, -2);
    v.emplace_back("CG", 10, -1, -2, 0, 0);
    v.emplace_back("CG", 11, 3, -2, -3, 2);
    v.emplace_back("CG", 4, 0, -2, -2, -2);
    v.emplace_back("CG", 5, 2, -1, -2, 0);
    v.emplace_back("CG", 6, -1, -2, -2, -2);
    v.emplace_back("CG", 8, 3, 0, -3, 0);

    // CH
    v.emplace_back("CH", 0, -2, 0, 0, 0);
    v.emplace_back("CH", 1, -2, 0, 0, 0);
    v.emplace_back("CH", 2, 0, 0, 2, 0);
    v.emplace_back("CH", 3, 1, 0, 0, 0);
    v.emplace_back("CH", 4, 2, 0, -4, -4);
    v.emplace_back("CH", 5, 1, -4, 2, 2);
    v.emplace_back("CH", 6, 2, -3, 0, 0);
    v.emplace_back("CH", 9, -2, 0, -2, -2);
    v.emplace_back("CH", 10, 0, -2, 3, 2);
    v.emplace_back("CH", 11, -2, -1, 0, 2);
    v.emplace_back("CH", 7, -1, 0, -3, 0);
    v.emplace_back("CH", 8, 2, -2, -2, 2);
    litchfieldLetterPosMap["CH"] = v;
    v.clear();

    // DA
    v.emplace_back("DA", 0, -1, 2, 1, -2);
    v.emplace_back("DA", 1, -1, 2, 1, -2);
    v.emplace_back("DA", 2, -2, 2, 3, -2);
    v.emplace_back("DA", 4, 0, 2, 0, 0);
    v.emplace_back("DA", 6, 0, 2, 2, -2);
    v.emplace_back("DA", 7, 0, 0, -2, -1);
    v.emplace_back("DA", 8, 0, 2, 0, 0);
    v.emplace_back("DA", 9, 2, 4, -2, 1);
    v.emplace_back("DA", 10, 3, -2, -3, 0);
    v.emplace_back("DA", 11, 1, 1, 0, 0);
    v.emplace_back("DA", 3, -2, 2, 0, 0);
    v.emplace_back("DA", 5, -3, 2, 3, 0);
    litchfieldLetterPosMap["CH"] = v;
    v.clear();

    // DB
    v.emplace_back("DB", 0, 0, 0, 0, 0);
    v.emplace_back("DB", 1, 0, 0, 0, 0);
    v.emplace_back("DB", 2, 0, 2, -1, 1);
    v.emplace_back("DB", 3, 1, 2, -2, 2);
    v.emplace_back("DB", 4, 0, 2, 0, 2);
    v.emplace_back("DB", 5, 2, 0, -1, 0);
    v.emplace_back("DB", 6, 0, 2, 2, 2);
    v.emplace_back("DB", 8, 0, -2, -2, 0);
    v.emplace_back("DB", 9, 0, 0, -2, 0);
    v.emplace_back("DB", 10, 0, 0, 2, 2);
    v.emplace_back("DB", 11, 2, 0, 0, 0);
    v.emplace_back("DB", 7, 2, -2, 0, 2);
    litchfieldLetterPosMap["DB"] = v;
    v.clear();

    // DK
    v.emplace_back("DK", 0, -2, 2, -2, 0);
    v.emplace_back("DK", 1, -2, 2, -2, 0);
    v.emplace_back("DK", 5, 0, 2, 1, -1);
    v.emplace_back("DK", 6, -2, 2, 2, -2);
    v.emplace_back("DK", 7, -2, 2, 0, -2);
    v.emplace_back("DK", 8, 0, 2, 0, -2);
    v.emplace_back("DK", 9, -2, -3, 0, -3);
    v.emplace_back("DK", 10, 3, 0, 2, 2);
    v.emplace_back("DK", 11, 3, 2, 2, 0);
    v.emplace_back("DK", 2, -3, 0, 3, -2);
    v.emplace_back("DK", 3, 0, 3, 0, 0);
    v.emplace_back("DK", 4, 0, 1, 0, 0);
    litchfieldLetterPosMap["DK"] = v;
    v.clear();

    // DL
    v.emplace_back("DL", 0, -2, 2, -2, -2);
    v.emplace_back("DL", 1, -2, 2, -2, -2);
    v.emplace_back("DL", 2, -2, -2, -2, -1);
    v.emplace_back("DL", 4, -2, 0, -3, 1);
    v.emplace_back("DL", 5, 1, 2, 0, 0);
    v.emplace_back("DL", 6, 0, 2, 0, 0);
    v.emplace_back("DL", 7, -1, 0, 0, 0);
    v.emplace_back("DL", 8, 0, 2, -1, -2);
    v.emplace_back("DL", 9, 0, 2, -2, -2);
    v.emplace_back("DL", 10, 0, 0, 4, 0);
    v.emplace_back("DL", 11, 0, 4, 0, 2);
    v.emplace_back("DL", 3, 0, 2, 0, 0);
    litchfieldLetterPosMap["DL"] = v;
    v.clear();

    // EB
    v.emplace_back("EB", 0, 0, 1, 0, 2);
    v.emplace_back("EB", 1, 0, 1, 0, 2);
    v.emplace_back("EB", 2, 1, -2, 0, 2);
    v.emplace_back("EB", 4, -1, 0, 0, 2);
    v.emplace_back("EB", 5, -2, -2, 0, 0);
    v.emplace_back("EB", 6, -1, 0, 2, 0);
    v.emplace_back("EB", 8, 0, -2, 0, -2);
    v.emplace_back("EB", 9, 0, 2, 0, 1);
    v.emplace_back("EB", 10, 3, 0, 0, 2);
    v.emplace_back("EB", 11, 0, 0, 3, 0);
    v.emplace_back("EB", 3, -3, 2, -3, 2);
    v.emplace_back("EB", 7, 0, 0, 0, 0);
    litchfieldLetterPosMap["EB"] = v;
    v.clear();

    // FC
    v.emplace_back("FC", 0, -1, 0, -2, 0);
    v.emplace_back("FC", 1, -1, 0, -2, 0);
    v.emplace_back("FC", 4, 0, 2, 2, -2);
    v.emplace_back("FC", 5, 0, 2, -3, -2);
    v.emplace_back("FC", 8, 0, 0, -3, 0);
    v.emplace_back("FC", 9, 1, -2, 1, -2);
    v.emplace_back("FC", 10, 4, -2, -3, -2);
    v.emplace_back("FC", 11, -3, 2, 0, -2);
    v.emplace_back("FC", 2, 3, -2, 2, -2);
    v.emplace_back("FC", 3, 4, 0, 0, -2);
    v.emplace_back("FC", 6, 1, 0, 2, 2);
    v.emplace_back("FC", 7, 1, 0, 2, -2);
    litchfieldLetterPosMap["FC"] = v;
    v.clear();

    // FI
    v.emplace_back("FI", 0, -2, 1, 2, -2);
    v.emplace_back("FI", 1, -2, 1, 2, -2);
    v.emplace_back("FI", 2, 0, 1, 0, -2);
    v.emplace_back("FI", 4, 0, 0, 0, 0);
    v.emplace_back("FI", 5, 0, 0, 2, -2);
    v.emplace_back("FI", 6, 0, -2, 2, -2);
    v.emplace_back("FI", 7, 0, 1, 0, 0);
    v.emplace_back("FI", 8, 0, 0, 0, 0);
    v.emplace_back("FI", 11, -3, 2, 3, 2);
    v.emplace_back("FI", 3, -2, 2, 0, -2);
    v.emplace_back("FI", 9, -2, -2, -2, 0);
    v.emplace_back("FI", 10, 2, 0, -2, 2);
    litchfieldLetterPosMap["FI"] = v;
    v.clear();

    // FJ
    v.emplace_back("FJ", 0, 2, 1, 0, -2);
    v.emplace_back("FJ", 1, 2, 1, 0, -2);
    v.emplace_back("FJ", 3, -3, 2, -3, 0);
    v.emplace_back("FJ", 5, 0, 2, 0, -2);
    v.emplace_back("FJ", 6, 0, -2, -2, -2);
    v.emplace_back("FJ", 9, -2, 2, -4, -2);
    v.emplace_back("FJ", 10, 3, -2, -2, 2);
    v.emplace_back("FJ", 11, -2, 2, -4, 2);
    v.emplace_back("FJ", 2, -2, 1, -2, 0);
    v.emplace_back("FJ", 4, 0, 2, -3, 0);
    v.emplace_back("FJ", 7, 0, -2, -2, -1);
    v.emplace_back("FJ", 8, 0, 2, 2, -2);
    litchfieldLetterPosMap["FJ"] = v;
    v.clear();

    // GI
    v.emplace_back("GI", 0, 3, 0, 2, 0);
    v.emplace_back("GI", 1, 3, 0, 2, 0);
    v.emplace_back("GI", 2, -2, -2, 0, -1);
    v.emplace_back("GI", 3, 0, 0, 0, -2);
    v.emplace_back("GI", 5, -2, 2, 2, -2);
    v.emplace_back("GI", 6, -2, -2, 3, -1);
    v.emplace_back("GI", 8, -2, -2, 0, -1);
    v.emplace_back("GI", 10, -2, 0, 0, 2);
    v.emplace_back("GI", 11, -2, 1, 0, 2);
    v.emplace_back("GI", 4, 0, 2, 1, -2);
    v.emplace_back("GI", 7, -4, -1, 1, 2);
    v.emplace_back("GI", 9, 0, 2, 2, 0);
    litchfieldLetterPosMap["GI"] = v;
    v.clear();

    // GJ
    v.emplace_back("GJ", 0, -1, 0, -2, -1);
    v.emplace_back("GJ", 1, -1, 0, -2, -1);
    v.emplace_back("GJ", 4, 2, 2, -2, -1);
    v.emplace_back("GJ", 5, 2, -2, 0, -2);
    v.emplace_back("GJ", 6, -3, -2, 1, -1);
    v.emplace_back("GJ", 9, -2, -2, 4, -2);
    v.emplace_back("GJ", 10, 0, -2, -2, 0);
    v.emplace_back("GJ", 2, -2, -2, -2, -1);
    v.emplace_back("GJ", 3, -2, -2, 0, 0);
    v.emplace_back("GJ", 7, -2, -2, -2, -1);
    v.emplace_back("GJ", 8, -2, -2, -4, 0);
    v.emplace_back("GJ", 11, -2, -2, -4, 2);
    litchfieldLetterPosMap["GJ"] = v;
    v.clear();

    // IE
    v.emplace_back("IE", 0, 2, 0, 2, 2);
    v.emplace_back("IE", 1, 2, 0, 2, 2);
    v.emplace_back("IE", 2, 2, -2, 2, -2);
    v.emplace_back("IE", 4, 2, 0, -3, 2);
    v.emplace_back("IE", 5, 3, 1, -1, 1);
    v.emplace_back("IE", 7, 0, 0, -2, -2);
    v.emplace_back("IE", 11, 0, 2, -2, 2);
    v.emplace_back("IE", 3, 3, -2, -3, -1);
    v.emplace_back("IE", 6, 0, -1, 4, 0);
    v.emplace_back("IE", 8, -2, 0, 0, -1);
    v.emplace_back("IE", 9, 2, 0, -1, 0);
    v.emplace_back("IE", 10, -2, 2, 2, 0);
    litchfieldLetterPosMap["IE"] = v;
    v.clear();

    // ID
    v.emplace_back("ID", 0, 3, 2, -3, -1);
    v.emplace_back("ID", 1, 3, 2, -3, -1);
    v.emplace_back("ID", 2, 0, 0, 0, 2);
    v.emplace_back("ID", 4, 1, -2, 0, 2);
    v.emplace_back("ID", 5, 2, 0, -2, 2);
    v.emplace_back("ID", 10, 4, 0, -3, 2);
    v.emplace_back("ID", 11, 0, 2, -3, 2);
    v.emplace_back("ID", 3, 0, -2, -2, 2);
    v.emplace_back("ID", 6, 4, -2, 1, 2);
    v.emplace_back("ID", 7, 0, -2, 1, 0);
    v.emplace_back("ID", 8, 2, 1, 0, 1);
    v.emplace_back("ID", 9, -2, 2, -2, 0);
    litchfieldLetterPosMap["IE"] = v;
    v.clear();


    // IF
    v.emplace_back("IF", 0, 2, 0, -2, -2);
    v.emplace_back("IF", 1, 2, 0, -2, -2);
    v.emplace_back("IF", 4, 1, 0, 0, 0);
    v.emplace_back("IF", 5, 0, 2, 1, 0);
    v.emplace_back("IF", 6, -1, -2, 2, -2);
    v.emplace_back("IF", 7, 0, -2, -1, -1);
    v.emplace_back("IF", 10, 2, -2, 0, 0);
    v.emplace_back("IF", 11, -2, 2, -2, 1);
    v.emplace_back("IF", 2, 0, 2, -1, -1);
    v.emplace_back("IF", 3, -2, -2, 2, -2);
    v.emplace_back("IF", 8, 0, 0, -1, 0);
    v.emplace_back("IF", 9, 3, 0, -3, -1);
    litchfieldLetterPosMap["IF"] = v;
    v.clear();

    // IG
    v.emplace_back("IG", 0, 2, 2, -2, -2);
    v.emplace_back("IG", 1, 2, 2, -2, -2);
    v.emplace_back("IG", 4, 0, 0, -2, 0);
    v.emplace_back("IG", 5, 2, 0, -2, -1);
    v.emplace_back("IG", 6, 0, 0, -2, -2);
    v.emplace_back("IG", 8, 2, 2, -3, -2);
   v.emplace_back("IG", 10, 2, -1, -2, 0);
    v.emplace_back("IG", 11, 2, 0, -1, 0);
    v.emplace_back("IG", 2, 2, 0, -2, -2);
    v.emplace_back("IG", 3, -4, -2, 0, -1);
    v.emplace_back("IG", 7, 0, 0, -2, -2);
    v.emplace_back("IG", 9, 2, 2, 0, -2);
    litchfieldLetterPosMap["IG"] = v;
    v.clear();

    // JI
    v.emplace_back("JI", 0, -2, 2, 2, 0);
    v.emplace_back("JI", 1, -2, 2, 2, 0);
    v.emplace_back("JI", 5, 0, 0, 0, -2);
    v.emplace_back("JI", 6, -1, 0, 2, -2);
    v.emplace_back("JI", 10, 0, 0, 0, 2);
    v.emplace_back("JI", 11, -3, 2, 0, 2);
    v.emplace_back("JI", 2, -2, 2, 2, 0);
    v.emplace_back("JI", 3, -3, 0, -1, -2);
    v.emplace_back("JI", 4, 0, 0, 1, -2);
    v.emplace_back("JI", 7, -2, 0, 2, -1);
    v.emplace_back("JI", 8, -2, -2, 0, -2);
    v.emplace_back("JI", 9, 0, 2, 2, -2);
    litchfieldLetterPosMap["JI"] = v;
    v.clear();

    // JJ
    v.emplace_back("JJ", 0, -2, 0, -2, 0);
    v.emplace_back("JJ", 1, -2, 0, -2, 0);
    v.emplace_back("JJ", 6, -2, 2, -2, -2);
    v.emplace_back("JJ", 10, -2, 0, -2, -2);
    v.emplace_back("JJ", 11, -4, 2, -4, 2);
    v.emplace_back("JJ", 2, 0, 0, 1, 0);
    v.emplace_back("JJ", 3, 0, 0, 0, 0);
    v.emplace_back("JJ", 4, 0, -2, 0, -2);
    v.emplace_back("JJ", 5, -2, 2, -2, 0);
    v.emplace_back("JJ", 7, -2, 1, -2, 0);
    v.emplace_back("JJ", 8, -2, 0, -3, 2);
    v.emplace_back("JJ", 9, 2, 0, -2, 0);
    litchfieldLetterPosMap["JJ"] = v;
    v.clear();

    // KE
    v.emplace_back("KE", 0, -2, 0, 0, 2);
    v.emplace_back("KE", 1, -2, 0, 0, 2);
    v.emplace_back("KE", 2, 0, 1, 0, 1);
    v.emplace_back("KE", 4, 0, 0, 0, 4);
    v.emplace_back("KE", 5, 0, 0, 0, -1);
    v.emplace_back("KE", 6, 0, 2, 3, -2);
    v.emplace_back("KE", 7, 0, -1, -2, -2);
    v.emplace_back("KE", 9, 3, -3, 3, 0 );
    v.emplace_back("KE", 11, 0, 2, 1, 2);
    v.emplace_back("KE", 3, 2, 0, -2, -1);
    v.emplace_back("KE", 8, 0, 0, 0, -1);
    v.emplace_back("KE", 10, 1, -2, -1, 0);
    litchfieldLetterPosMap["KE"] = v;
    v.clear();

    // KF
    v.emplace_back("KF", 0, -1, 0, -2, -1);
    v.emplace_back("KF", 1, -1, 0, -2, -1);
    v.emplace_back("KF", 3, 0, 0, 3, -2);
    v.emplace_back("KF", 4, 0, 0, 0, -2);
    v.emplace_back("KF", 9, 0, -2, -3, 2);
    v.emplace_back("KF", 10, 4, 0, 3, 1);
    v.emplace_back("KF", 11, 1, 0, -3, 1);
    v.emplace_back("KF", 2, 0, 2, 0, 2);
    v.emplace_back("KF", 5, 0, 0, 3, 0);
    v.emplace_back("KF", 6, 0, 0, 0, -3);
    v.emplace_back("KF", 7, 0, 0, 0, -2);
    v.emplace_back("KF", 8, -2, 1, 0, 0);
    litchfieldLetterPosMap["KF"] = v;
    v.clear();

    // KL
    v.emplace_back("KL", 0, -2, 2, -2, -2);
    v.emplace_back("KL", 1, -2, 2, -2, -2);
    v.emplace_back("KL", 2, -2, 1, -2, -1);
    v.emplace_back("KL", 3, 0, -2, 0, 0);
    v.emplace_back("KL", 4, 0, -2, -1, 0);
    v.emplace_back("KL", 5, 2, 2, -2, 0);
    v.emplace_back("KL", 6, 4, 0, -1, 0);
    v.emplace_back("KL", 9, 2, 1, -2, -2);
    v.emplace_back("KL", 10, 0, 2, 0, -2);
    v.emplace_back("KL", 11, 0, 2, -2, 2);
    v.emplace_back("KL", 7, 0, 2, 0, -2);
    v.emplace_back("KL", 8, -1, 2, -2, -2);
    litchfieldLetterPosMap["KL"] = v;
    v.clear();

    // MG
    v.emplace_back("MG", 0, -2, 1, 0, -2);
    v.emplace_back("MG", 1, -2, 1, 0, -2);
    v.emplace_back("MG", 2, 0, 0, -2, 0);
    v.emplace_back("MG", 3, -2, 0, -2, -1);
    v.emplace_back("MG", 6, -2, 0, 0, 0);
    v.emplace_back("MG", 9, 0, -2, 2, 2);
    v.emplace_back("MG", 11, 2, 2, -2, 0);
    v.emplace_back("MG", 4, 0, 0, -1, -3);
    v.emplace_back("MG", 5, 0, 0, 2, -3);
    v.emplace_back("MG", 7, -2, 1, -3, -2);
    v.emplace_back("MG", 8, -2, -2, -3, -1);
    v.emplace_back("MG", 10, -2, 2, 0, -2);
    litchfieldLetterPosMap["MG"] = v;
    v.clear();

    // MK
    v.emplace_back("MK", 0, 0, 0, -1, 1);
    v.emplace_back("MK", 1, 0, 0, -1, 1);
    v.emplace_back("MK", 4, -2, 2, 0, 0);
    v.emplace_back("MK", 6, 0, 0, 2, -2);
    v.emplace_back("MK", 7, 0, 2, 1, 0);
    v.emplace_back("MK", 9, 2, 2, -2, 2);
    v.emplace_back("MK", 10, 0, 0, -4, 2);
    v.emplace_back("MK", 11, 0, 2, 0, 0);
    v.emplace_back("MK", 2, 2, 0, -2, 0);
    v.emplace_back("MK", 3, -2, -2, -1, 0);
    v.emplace_back("MK", 5, 0, 0, 1, -2);
    v.emplace_back("MK", 8, -2, 0, 0, -2);
    litchfieldLetterPosMap["MK"] = v;
    v.clear();

    // NB
    v.emplace_back("NB", 0, 0, -2, -2, 0);
    v.emplace_back("NB", 1, 0, -2, -2, 0);
    v.emplace_back("NB", 2, -2, 2, -2, 1);
    v.emplace_back("NB", 5, -2, 2, 2, -2);
    v.emplace_back("NB", 7, 0, 0, -2, 1);
    v.emplace_back("NB", 8, -2, 0, 0, 0);
    v.emplace_back("NB", 9, -3, 2, 0, 0);
    v.emplace_back("NB", 10, 0, -2, -2, 2);
    v.emplace_back("NB", 11, -2, -2, -2, 0);
    v.emplace_back("NB", 3, -1, 2, -2, 2);
    v.emplace_back("NB", 4, 0, 0, 1, 2);
    v.emplace_back("NB", 6, 4, 2, 1, 0);
    litchfieldLetterPosMap["NB"] = v;
    v.clear();

    // NG
    v.emplace_back("NG", 0, 0, 0, -2, -1);
    v.emplace_back("NG", 1, 0, 0, -2, -1);
    v.emplace_back("NG", 2, 1, -3, 1, -3);
    v.emplace_back("NG", 4, 2, 0, -1, -3);
    v.emplace_back("NG", 5, -4, 2, -3, -2);
    v.emplace_back("NG", 9, 0, 2, 2, 2);
    v.emplace_back("NG", 10, 0, -2, -2, 0);
    v.emplace_back("NG", 11, -2, 0, -2, 0);
    v.emplace_back("NG", 3, 0, 2, -2, 0);
    v.emplace_back("NG", 6, 2, -4, -2, -1);
    v.emplace_back("NG", 7, 4, -2, -2, -2);
    v.emplace_back("NG", 8, -2, 0, 2, -2);
    litchfieldLetterPosMap["NG"] = v;
    v.clear();

    // OL
    v.emplace_back("OL", 0, -2, 0, 0, -2);
    v.emplace_back("OL", 1, -2, 0, 0, -2);
    v.emplace_back("OL", 2, -1, 0, -2, 0);
    v.emplace_back("OL", 3, 0, 0, -2, 0);
    v.emplace_back("OL", 4, 2, 2, 0, -2);
    v.emplace_back("OL", 5, -3, 1, 0, -2);
    v.emplace_back("OL", 6, 1, 2, 0, -1);
    v.emplace_back("OL", 7, 2, -2, 0, -2);
    v.emplace_back("OL", 8, 0, -2, -2, 0);
    v.emplace_back("OL", 9, 2, -2, 0, 0);
    v.emplace_back("OL", 10, -3, 2, 2, 2);
    v.emplace_back("OL", 11, -2, 2, -2, 2);
    litchfieldLetterPosMap["OL"] = v;
    v.clear();

    // PB
    v.emplace_back("PB", 0, 0, 0, 2, 1);
    v.emplace_back("PB", 1, 0, 0, 2, 1);
    v.emplace_back("PB", 2, 0, 2, -2, 2);
    v.emplace_back("PB", 5, 3, -2, 1, -2);
    v.emplace_back("PB", 6, -2, 0, -2, 2);
    v.emplace_back("PB", 7, 2, 2, -2, 2);
    v.emplace_back("PB", 8, -2, 4, 0, 0);
    v.emplace_back("PB", 10, 4, 0, -3, 0);
    v.emplace_back("PB", 11, 4, 0, 3, 0);
    v.emplace_back("PB", 3, 0, -2, -2, 2);
    v.emplace_back("PB", 4, 0, 2, -2, 0);
    v.emplace_back("PB", 9, 0, 0, -2, 0);
    litchfieldLetterPosMap["PB"] = v;
    v.clear();

    // PC
    v.emplace_back("PC", 0, 1, 0, -2, 0);
    v.emplace_back("PC", 1, 1, 0, -2, 0);
    v.emplace_back("PC", 2, 1, 0, -2, -1);
    v.emplace_back("PC", 3, -2, 0, -2, -2);
    v.emplace_back("PC", 4, 0, 2, 2, -2);
    v.emplace_back("PC", 5, 0, 0, 0, -1);
    v.emplace_back("PC", 6, 2, 0, 1, 0);
    v.emplace_back("PC", 7, -2, 2, -2, -2);
    v.emplace_back("PC", 8, -3, -2, 0, -2);
    v.emplace_back("PC", 9, 0, -2, -1, 0);
    v.emplace_back("PC", 10, 0, 0, -2, -1);
    v.emplace_back("PC", 11, -2, 0, 4, 0);
    litchfieldLetterPosMap["PC"] = v;
    v.clear();

    // QA
    v.emplace_back("QA", 0, -2, 2, 2, 0);
    v.emplace_back("QA", 1, -2, 2, 2, 0);
    v.emplace_back("QA", 2, 0, 0, 0, 2);
    v.emplace_back("QA", 3, -1, 2, 0, 2);
    v.emplace_back("QA", 4, 0, 2, 0, 0);
    v.emplace_back("QA", 5, -2, 0, 0, 1);
    v.emplace_back("QA", 6, -3, 0, -2, 2);
    v.emplace_back("QA", 7, -2, 0, 0, 0);
    v.emplace_back("QA", 8, 0, 1, 0, -1);
    v.emplace_back("QA", 9, 0, -2, -1, -1);
    v.emplace_back("QA", 10, -2, 0, -2, 0);
    v.emplace_back("QA", 11, 0, 0, -4, 2);
    litchfieldLetterPosMap["QA"] = v;
    v.clear();

    // QD
    v.emplace_back("QD", 0, -2, -2, -2, 0);
    v.emplace_back("QD", 1, -2, -2, -2, 0);
    v.emplace_back("QD", 2, 0, 0, -2, 2);
    v.emplace_back("QD", 5, 0, -1, -2, 0);
    v.emplace_back("QD", 8, 2, 0, 1, -1);
    v.emplace_back("QD", 9, -4, -4, -3, 3);
    v.emplace_back("QD", 11, -2, 0, -2, 3);
    v.emplace_back("QD", 3, 0, 0, 0, 2);
    v.emplace_back("QD", 4, 0, 2, 0, 3);
    v.emplace_back("QD", 6, 0, 2, 0, 3);
    v.emplace_back("QD", 7, 0, 0, -3, 1);
    v.emplace_back("QD", 10, -3, 0, 2, 0);
    litchfieldLetterPosMap["QD"] = v;
    v.clear();

    // QE
    v.emplace_back("QE", 3, -2, 0, -2, -2);
    v.emplace_back("QE", 4, 0, 1, -2, -4);
    v.emplace_back("QE", 5, 0, -2, 2, 0);
    v.emplace_back("QE", 6, -2, 2, 0, -2);
    v.emplace_back("QE", 8, 2, -2, 0, 0);
    v.emplace_back("QE", 9, 0, 2, 3, 0);
    v.emplace_back("QE", 11, 0, 2, 2, 0);
    v.emplace_back("QE", 0, 3, 0, 2, 2);
    v.emplace_back("QE", 1, 3, 0, 2, 2);
    v.emplace_back("QE", 2, 0, 1, -2, 2);
    v.emplace_back("QE", 7, 0, 0, -2, 0);
    v.emplace_back("QE", 10, -4, 2, 3, -2);
    litchfieldLetterPosMap["QE"] = v;
    v.clear();

    // RA
    v.emplace_back("RA", 0, -2, 2, 0, 0);
    v.emplace_back("RA", 1, -2, 2, 0, 0);
    v.emplace_back("RA", 2, 2, 2, 0, 0);
    v.emplace_back("RA", 3, 2, -2, 0, 0);
    v.emplace_back("RA", 5, 2, 2, 0, 0);
    v.emplace_back("RA", 6, 2, 2, -1, 0);
    v.emplace_back("RA", 7, 0, 0, 0, 0);
    v.emplace_back("RA", 8, 0, 0, 0, 0);
    v.emplace_back("RA", 9, 0, 0, 0, 0);
    v.emplace_back("RA", 10, -3, 2, 0, 0);
    v.emplace_back("RA", 11, 0, 2, -2, 0);
    v.emplace_back("RA", 4, 0, 2, 0, 2);
    litchfieldLetterPosMap["RA"] = v;
    v.clear();

    // SJ
    v.emplace_back("SJ", 0, 0, 0, -2, 0);
    v.emplace_back("SJ", 1, 0, 0, -2, 0);
    v.emplace_back("SJ", 2, -2, 1, -3, 0);
    v.emplace_back("SJ", 5, 4, 0, 0, -2);
    v.emplace_back("SJ", 8, -2, -2, -1, 0);
    v.emplace_back("SJ", 10, 3, 0, 2, 0);
    v.emplace_back("SJ", 11, 2, 0, 2, -2);
    v.emplace_back("SJ", 3, -2, 1, -2, 0);
    v.emplace_back("SJ", 4, -2, -2, -2, 0);
    v.emplace_back("SJ", 6, -2, 0, 0, -3);
    v.emplace_back("SJ", 7, -2, -2, 0, -1);
    v.emplace_back("SJ", 9, 1, 1, 2, -2);
    litchfieldLetterPosMap["SJ"] = v;
    v.clear();

    // SL
    v.emplace_back("SL", 0, 1, 0, -2, -2);
    v.emplace_back("SL", 1, 1, 0, -2, -2);
    v.emplace_back("SL", 2, -2, 2, -2, -2);
    v.emplace_back("SL", 3, 0, 0, -1, 0);
    v.emplace_back("SL", 7, -2, -1, 0, -2);
    v.emplace_back("SL", 8, 0, 1, 0, 0);
    v.emplace_back("SL", 9, 3, -3, 0, -2);
    v.emplace_back("SL", 10, -3, 0, 2, 0);
    v.emplace_back("SL", 11, -2, 2, 0, 2);
    v.emplace_back("SL", 4, -4, 0, 0, -2);
    v.emplace_back("SL", 5, -2, 0, 3, -3);
    v.emplace_back("SL", 6, -2, 1, 0, 0);
    litchfieldLetterPosMap["SL"] = v;
    v.clear();

    // TC
    v.emplace_back("TC", 0, 2, -2, -2, -2);
    v.emplace_back("TC", 1, 2, -2, -2, -2);
    v.emplace_back("TC", 2, 1, 2, 1, -2);
    v.emplace_back("TC", 3, -2, 0, 0, 0);
    v.emplace_back("TC", 4, -2, 0, -1, 0);
    v.emplace_back("TC", 5, 0, 2, -3, 0);
    v.emplace_back("TC", 6, 2, 1, 1, -2);
    v.emplace_back("TC", 7, 2, 1, 0, -2);
    v.emplace_back("TC", 8, 0, -2, -1, -1);
    v.emplace_back("TC", 9, -2, 0, -2, -1);
    v.emplace_back("TC", 10, 3, 2, -2, -1);
    v.emplace_back("TC", 11, -2, 2, 2, 0);
    litchfieldLetterPosMap["TC"] = v;
    v.clear();

    // TE
    v.emplace_back("TE", 0, 1, 1, 2, 3); // plate 1a
    v.emplace_back("TE", 1, 2, 1, 2, 3);
    v.emplace_back("TE", 2, 1, -2, -2, -1);
    v.emplace_back("TE", 3, -1, 2, 2, 0);
    v.emplace_back("TE", 4, 0, 0, -2, 4);
    v.emplace_back("TE", 5, 0, 3, 2, -2);
    v.emplace_back("TE", 6, 0, 3, -1, -2);
    v.emplace_back("TE", 7, 0, 1, -1, -1);
    v.emplace_back("TE", 8, 0, 1, 0, 0);
    v.emplace_back("TE", 9, 0, -1, 0, 0);
    v.emplace_back("TE", 10, 0, 2, -2, 1);
    v.emplace_back("TE", 11, -2, 2, 2, 0);
    litchfieldLetterPosMap["TE"] = v;
    v.clear();

    // TF
    v.emplace_back("TF", 2, 0, -2, 0, 0);
    v.emplace_back("TF", 3, -2, 2, -1, 0);
    v.emplace_back("TF", 5, 0, 0, 0, -2);
    v.emplace_back("TF", 6, 0, 4, 1, -3);
    v.emplace_back("TF", 8, -2, -2, 0, 0);
    v.emplace_back("TF", 10, 4, 0, -4, -2);
    v.emplace_back("TF", 11, 0, 2, -2, 0);
    v.emplace_back("TF", 0, 0, 2, -2, -2);
    v.emplace_back("TF", 1, 0, 2, -2, -2);
    v.emplace_back("TF", 4, -1, 1, -1, 0);
    v.emplace_back("TF", 7, 0, 2, -2, -2);
    v.emplace_back("TF", 9, 2, 0, 0, -2);
    litchfieldLetterPosMap["TF"] = v;
    v.clear();

    // TH
    v.emplace_back("TH", 0, 0, -2, 2, 0);
    v.emplace_back("TH", 1, 0, -2, 2, 0);
    v.emplace_back("TH", 2, 0, -2, 2, 0);
    v.emplace_back("TH", 4, 0, 0, -4, -3);
    v.emplace_back("TH", 5, 0, 0, -2, 0);
    v.emplace_back("TH", 6, -2, 2, -2, 0);
    v.emplace_back("TH", 8, -2, -2, -2, 2);
    v.emplace_back("TH", 9, 3, -2, 1, 0);
    v.emplace_back("TH", 11, 0, 0, -2, 0);
    v.emplace_back("TH", 3, -2, 2, -2, 0);
    v.emplace_back("TH", 7, 2, 2, -2, -2);
    v.emplace_back("TH", 10, 0, 2, 0, 2);
    litchfieldLetterPosMap["TH"] = v;
    v.clear();
}
