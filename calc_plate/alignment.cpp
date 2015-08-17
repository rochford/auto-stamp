#include <map>
#include <vector>
#include <iostream>

#include "alignment.h"

using namespace std;


vector<int> LitchfieldData::calculatePlate(const std::string& letterPair,
                    int leftVert,
                    int leftHoriz,
                    int rightVert,
                    int rightHoriz,
                                           int maxOffset)
{
    bool leftIsValid = false;
    bool rightIsValid = false;

    if (leftVert != -1000)
        leftIsValid = true;
    if (rightVert != -1000)
        rightIsValid = true;

    int minLV = leftVert - maxOffset;
    int maxLV = leftVert + maxOffset;
    int minLH = leftHoriz - maxOffset;
    int maxLH = leftHoriz + maxOffset;

    int minRV = rightVert - maxOffset;
    int maxRV = rightVert + maxOffset;
    int minRH = rightHoriz - maxOffset;
    int maxRH = rightHoriz + maxOffset;

    vector<LitchfieldItem> candidates;
    vector<LitchfieldItem> all =  litchfieldLetterPosMap[letterPair];
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

    vector<int> plates;
    if (candidates.size())
    {
        for (auto i : candidates) {
            plates.push_back(i.plate);
        }
    }
    return plates;
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
    case -5:
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
    case 5:
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

void LitchfieldData::Initialize()
{
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

    // CC
    v.emplace_back("CC", 0, 0, 0, 0, -2);
    v.emplace_back("CC", 1, 0, 0, 0, -2);
    v.emplace_back("CC", 2, 4, -2, 4, -2);
    v.emplace_back("CC", 4, 2, -2, -2, -2);
    v.emplace_back("CC", 5, 1, -2, 1, -2);
    v.emplace_back("CC", 6, 0, -2, 1, -2);
    v.emplace_back("CC", 7, -2, -2, -2, -2);
    v.emplace_back("CC", 8, 0, 2, -2, 0);
    v.emplace_back("CC", 10, 0, -1, 2, -2);
    v.emplace_back("CC", 11, -1, -2, -2, 2);
    v.emplace_back("CC", 3, -2, 0, -2, 0);
    v.emplace_back("CC", 9, 0, -2, 1, -1);
    litchfieldLetterPosMap["CC"] = v;
    v.clear();

    // CD
    v.emplace_back("CD", 0, 0, -2, -2, 0);
    v.emplace_back("CD", 1, 0, -2, -2, 0);
    v.emplace_back("CD", 4, 0, 0, 0, 0);
    v.emplace_back("CD", 5, 2, -2, 3, 3);
    v.emplace_back("CD", 6, 1, -2, 0, 1);
    v.emplace_back("CD", 7, 0, -2, -1, 0);
    v.emplace_back("CD", 8, -2, 0, 0, 2);
    v.emplace_back("CD", 9, 3, -3, 0, 3);
    v.emplace_back("CD", 10, -2, -1, 0, 0);
    v.emplace_back("CD", 11, 2, -2, -3, 4);
    v.emplace_back("CD", 2, 0, 0, 0, 0);
    v.emplace_back("CD", 3, -2, 0, 0, 2);
    litchfieldLetterPosMap["CD"] = v;
    v.clear();

    // CE
    v.emplace_back("CE", 0, -1, 0, -2, -1);
    v.emplace_back("CE", 1, -1, 0, -2, -1);
    v.emplace_back("CE", 4, 2, 0, 2, 3);
    v.emplace_back("CE", 5, 4, 4, 0, -2);
    v.emplace_back("CE", 6, 2, -1, 0, -2);
    v.emplace_back("CE", 7, 0, -3, 2, 0);
    v.emplace_back("CE", 9, 4, -2, 2, -1);
    v.emplace_back("CE", 10, 2, 0, 2, -1);
    v.emplace_back("CE", 11, 3, -2, -3, 4);
    v.emplace_back("CE", 2, 2, 0, 0, -2);
    v.emplace_back("CE", 3, 0, 0, -2, 1);
    v.emplace_back("CE", 8, -1, 2, -2, -1);
    litchfieldLetterPosMap["CE"] = v;
    v.clear();

    // CF
    v.emplace_back("CF", 0, 0, -2, -2, 0);
    v.emplace_back("CF", 1, 0, -2, -2, 0);
    v.emplace_back("CF", 3, 0, 0, 0, -2);
    v.emplace_back("CF", 4, 2, 0, 3, 0);
    v.emplace_back("CF", 5, 3, -4, 4, 0);
    v.emplace_back("CF", 6, 2, -4, 0, 0);
    v.emplace_back("CF", 7, 0, -2, -2, 0);
    v.emplace_back("CF", 8, -1, 0, -2, 0);
    v.emplace_back("CF", 9, -2, -1, 0, -2);
    v.emplace_back("CF", 11, 4, -3, 0, 0);
    v.emplace_back("CF", 2, 2, -1, 0, 0);
    v.emplace_back("CF", 10, -2, -2, 4, 0);
    litchfieldLetterPosMap["CF"] = v;
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

    // CI
    v.emplace_back("CI", 0, -2, 1, 2, 0);
    v.emplace_back("CI", 1, -2, 1, 2, 0);
    v.emplace_back("CI", 2, 0, -2, 2, 0);
    v.emplace_back("CI", 4, 2, -1, 3, 0);
    v.emplace_back("CI", 6, 4, -2, 1, -2);
    v.emplace_back("CI", 7, -2, -3, 0, 0);
    v.emplace_back("CI", 8, 0, 0, 0, 0);
    v.emplace_back("CI", 9, -2, -2, 2, 2);
    v.emplace_back("CI", 10, 2, -3, 0, 0);
    v.emplace_back("CI", 11, 0, -2, -2, 0);
    v.emplace_back("CI", 3, 0, 0, 0, 0);
    v.emplace_back("CI", 5, 0, -3, 0, 0);
    litchfieldLetterPosMap["CI"] = v;
    v.clear();

    // CJ
    v.emplace_back("CJ", 0, 2, 0, -3, 0);
    v.emplace_back("CJ", 1, -2, 0, -3, 0);
    v.emplace_back("CJ", 4, 0, -3, -2, -1);
    v.emplace_back("CJ", 5, -1, 0, -2, 0);
    v.emplace_back("CJ", 6, 0, 2, 2, -2);
    v.emplace_back("CJ", 7, -2, 0, 0, 0);
    v.emplace_back("CJ", 8, -3, 0, 0, 0);
    v.emplace_back("CJ", 9, -2, 0, 0, 0);
    v.emplace_back("CJ", 11, 4, -2, -3, 2);
    v.emplace_back("CJ", 2, 4, 0, 0, -2);
    v.emplace_back("CJ", 3, 0, 0, -2, 1);
    v.emplace_back("CJ", 10, -2, 0, -3, 2);
    litchfieldLetterPosMap["CJ"] = v;
    v.clear();

    // CK
    v.emplace_back("CK", 2, 0, 0, 0, 2);
    v.emplace_back("CK", 4, 1, -1, 0, -1);
    v.emplace_back("CK", 6, -2, 0, 0, -2);
    v.emplace_back("CK", 7, 0, -2, 0, 0);
    v.emplace_back("CK", 9, -2, 0, 0, 2);
    v.emplace_back("CK", 10, 0, 0, 0, 2);
    v.emplace_back("CK", 11, 4, 0, 3, -2);
    v.emplace_back("CK", 0, -1, 1, -1, 0);
    v.emplace_back("CK", 1, -1, 1, -1, 0);
    v.emplace_back("CK", 3, 0, 0, -1, 0);
    v.emplace_back("CK", 5, -2, -2, 1, -2);
    v.emplace_back("CK", 8, -2, 0, 0, 0);
    litchfieldLetterPosMap["CK"] = v;
    v.clear();

    // CL
    v.emplace_back("CL", 0, 0, 0, -2, -2);
    v.emplace_back("CL", 1, 0, 0, -2, -2);
    v.emplace_back("CL", 2, 0, 0, -2, -2);
    v.emplace_back("CL", 4, 2, 0, 0, -2);
    v.emplace_back("CL", 5, 2, -2, 0, 1);
    v.emplace_back("CL", 6, 0, -2, 0, 0);
    v.emplace_back("CL", 7, 0, -2, 0, -2);
    v.emplace_back("CL", 8, -2, -2, -2, -2);
    v.emplace_back("CL", 9, -2, -2, 2, 0);
    v.emplace_back("CL", 10, 0, 0, 2, 0);
    v.emplace_back("CL", 11, 2, -2, -2, 2);
    v.emplace_back("CL", 3, 1, -1, 0, 1);
    litchfieldLetterPosMap["CL"] = v;
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

    // DC
    v.emplace_back("DC", 0, 0, 2, 0, -2);
    v.emplace_back("DC", 1, 0, 2, 0, -2);
    v.emplace_back("DC", 2, -2, 0, -2, 0);
    v.emplace_back("DC", 4, 3, 2, 0, -2);
    v.emplace_back("DC", 5, 2, 3, 0, -3);
    v.emplace_back("DC", 6, 2, 2, 0, 0 );
    v.emplace_back("DC", 8, 0, 3, 0, -3);
    v.emplace_back("DC", 9, 0, 3, 2, -2);
    v.emplace_back("DC", 10, 1, 2, 1, -3);
    v.emplace_back("DC", 11, 1, 3, -1, 0);
    v.emplace_back("DC", 3, 0, 3, 2, -3);
    v.emplace_back("DC", 7, 3, 0, 0, -3);
    litchfieldLetterPosMap["DC"] = v;
    v.clear();

    // DD
    v.emplace_back("DD", 0, -2, 2, -2, -2);
    v.emplace_back("DD", 1, -2, 2, -2, -2);
    v.emplace_back("DD", 2, 0, 2, -2, -2);
    v.emplace_back("DD", 4, -2, 2, -2, 0);
    v.emplace_back("DD", 5, 1, 2, 2, 0);
    v.emplace_back("DD", 6, 0, 2, 0, 0);
    v.emplace_back("DD", 8, 0, 2, -2, 2);
    v.emplace_back("DD", 9, 2, 0, 0, 2);
    v.emplace_back("DD", 10, 4, 4, -3, 3);
    v.emplace_back("DD", 11, 0, 3, 0, 3);
    v.emplace_back("DD", 3, 3, 2, -1, 2);
    v.emplace_back("DD", 7, 0, 2, -1, 0);
    litchfieldLetterPosMap["DD"] = v;
    v.clear();

    // DE
    v.emplace_back("DE", 2, -2, 2, 0, 0);
    v.emplace_back("DE", 4, 2, 2, -2, -3);
    v.emplace_back("DE", 5, 3, 2, -2, -1);
    v.emplace_back("DE", 9, 0, 0, 0, 0);
    v.emplace_back("DE", 10, -2, 2, 0, -2);
    v.emplace_back("DE", 11, 2, 2, -2, -3);
    v.emplace_back("DE", 0, -2, 2, 2, -2);
    v.emplace_back("DE", 1, -2, 2, 2, -2);
    v.emplace_back("DE", 3, 0, 2, -2, 2);
    v.emplace_back("DE", 6, 2, 2, 0, -2);
    v.emplace_back("DE", 7, -1, 2, -1, 0);
    v.emplace_back("DE", 8, 0, 3, -2, 0);
    litchfieldLetterPosMap["DE"] = v;
    v.clear();

    // DF
    v.emplace_back("DF", 0, -2, 2, 0, 0);
    v.emplace_back("DF", 1, -2, 2, 0, 0);
    v.emplace_back("DF", 4, 2, 0, -1, -2);
    v.emplace_back("DF", 5, -2, 2, -1, 0);
    v.emplace_back("DF", 6, -3, 2, 0, -2);
    v.emplace_back("DF", 7, 0, 2, -3, 0);
    v.emplace_back("DF", 9, -2, 2, 0, 0);
    v.emplace_back("DF", 10, -2, 2, 0, 0);
    v.emplace_back("DF", 11, 4, 2, 2, 0);
    v.emplace_back("DF", 2, -1, 0, 0, 0);
    v.emplace_back("DF", 3, 2, 2, 3, 0);
    v.emplace_back("DF", 8, 2, 2, 3, 0);
    litchfieldLetterPosMap["DF"] = v;
    v.clear();

    // DG
    v.emplace_back("DG", 0, -2, 2, -2, -2);
    v.emplace_back("DG", 1, -2, 2, -2, -2);
    v.emplace_back("DG", 2, -2, 1, -2, -1);
    v.emplace_back("DG", 4, 2, 0, -2, 2);
    v.emplace_back("DG", 5, -3, 2, -2, -2);
    v.emplace_back("DG", 7, 0, 0, -2, 0);
    v.emplace_back("DG", 8, 2, 2, -2, 0);
    v.emplace_back("DG", 9, -2, 2, 0, -1);
    v.emplace_back("DG", 10, 3, 2, 0, -2);
    v.emplace_back("DG", 11, 2, 2, -3, 2);
    v.emplace_back("DG", 3, 2, 0, -2, 0);
    v.emplace_back("DG", 6, -2, 2, -2, -2);
    litchfieldLetterPosMap["DG"] = v;
    v.clear();

    // DH
    v.emplace_back("DH", 0, -2, -2, 2, -2);
    v.emplace_back("DH", 1, -2, -2, 2, -2);
    v.emplace_back("DH", 2, -3, 2, -3, 0);
    v.emplace_back("DH", 4, 1, 2, -3, 0);
    v.emplace_back("DH", 5, -2, 2, -2, 0);
    v.emplace_back("DH", 6, 1, 2, -3, 0);
    v.emplace_back("DH", 7, 0, 2, -3, 0);
    v.emplace_back("DH", 8, 0, 2, 0, 2);
    v.emplace_back("DH", 9, 2, -2, 0, 0);
    v.emplace_back("DH", 10, 0, 2, -3, 0);
    v.emplace_back("DH", 11, 0, 4, -4, 2);
    v.emplace_back("DH", 3, 0, 3, -2, -2);
    litchfieldLetterPosMap["DH"] = v;
    v.clear();

    // DI
    v.emplace_back("DI", 0, -2, 2, 1, 0);
    v.emplace_back("DI", 1, -2, 2, 1, 0);
    v.emplace_back("DI", 2, -3, 2, -1, 0);
    v.emplace_back("DI", 4, 2, 2, 0, -2);
    v.emplace_back("DI", 5, 0, 2, 2, 0);
    v.emplace_back("DI", 6, -2, 2, 2, -2);
    v.emplace_back("DI", 7, 0, -1, 0, 0);
    v.emplace_back("DI", 8, 0, 2, 0, 0);
    v.emplace_back("DI", 9, 0, 0, -2, 0);
    v.emplace_back("DI", 10, 0, 2, 0, 0);
    v.emplace_back("DI", 11, -2, 2, 0, 2);
    v.emplace_back("DI", 3, 0, 2, 0, 0);
    litchfieldLetterPosMap["DI"] = v;
    v.clear();

    // DJ
    v.emplace_back("DJ", 0, -2, 2, -2, 0);
    v.emplace_back("DJ", 1, -2, 2, -2, 0);
    v.emplace_back("DJ", 2, -2, 2, -2, 0);
    v.emplace_back("DJ", 4, 0, 2, -2, 0);
    v.emplace_back("DJ", 5, -2, 2, -2, 0);
    v.emplace_back("DJ", 6, -2, 2, 0, -2);
    v.emplace_back("DJ", 7, 1, 2, 0, -2);
    v.emplace_back("DJ", 9, 0, 2, 0, -1);
    v.emplace_back("DJ", 10, 2, 2, -2, 0);
    v.emplace_back("DJ", 11, 1, 2, -3, 2);
    v.emplace_back("DJ", 3, 0, 3, -3, -1);
    v.emplace_back("DJ", 8, 1, 2, 1, 0);
    litchfieldLetterPosMap["DJ"] = v;
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

    // EA
    v.emplace_back("EA", 0, -1, 2, -2, 2);
    v.emplace_back("EA", 1, -1, 2, -2, 2);
    v.emplace_back("EA", 2, 0, -2, 0, 2);
    v.emplace_back("EA", 4, 0, 0, 0, 0);
    v.emplace_back("EA", 5, -2, 2, 0, 0);
    v.emplace_back("EA", 6, -2, 0, 4, 2);
    v.emplace_back("EA", 8, -2, -2, 0, 1);
    v.emplace_back("EA", 9, -3, 2, 0, 0);
    v.emplace_back("EA", 11, 1, 0, 3, 0);
    v.emplace_back("EA", 3, 0, -2, 0, 0);
    v.emplace_back("EA", 7, 0, 0, 0, 2);
    v.emplace_back("EA", 10, 0, 0, -4, 0);
    litchfieldLetterPosMap["EA"] = v;
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

    // EC
    v.emplace_back("EC", 0, 1, 2, 0, -1);
    v.emplace_back("EC", 1, 1, 2, 0, -1);
    v.emplace_back("EC", 2, 2, 0, 0, -2);
    v.emplace_back("EC", 4, 0, 0, 2, 0);
    v.emplace_back("EC", 5, 0, 0, 2, -2);
    v.emplace_back("EC", 6, -2, 0, -2, 0);
    v.emplace_back("EC", 8, -2, -2, 2, 0);
    v.emplace_back("EC", 9, -4, 2, -2, -2);
    v.emplace_back("EC", 11, 0, 0, 0, 0);
    v.emplace_back("EC", 3, -2, 0, -2, -2);
    v.emplace_back("EC", 7, 0, -2, 0, -2);
    v.emplace_back("EC", 10, 2, 0, -2, -2);
    litchfieldLetterPosMap["EC"] = v;
    v.clear();

    // ED
    v.emplace_back("ED", 0, 0, 0, -3, 0);
    v.emplace_back("ED", 1, 0, 0, -3, 0);
    v.emplace_back("ED", 4, 0, 1, 0, 1);
    v.emplace_back("ED", 6, -1, 0, 0, 2);
    v.emplace_back("ED", 7, -2, -1, -2, 0);
    v.emplace_back("ED", 9, -4, 0, 2, 2);
    v.emplace_back("ED", 11, 4, 2, 4, 2);
    v.emplace_back("ED", 2, 0, 2, 0, 2);
    v.emplace_back("ED", 3, -2, 2, 0, 2);
    v.emplace_back("ED", 5, 0, 0, 0, 1);
    v.emplace_back("ED", 8, -2, 1, -2, 0);
    v.emplace_back("ED", 10, 2, 0, 0, 0);
    litchfieldLetterPosMap["ED"] = v;
    v.clear();

    // EE
    v.emplace_back("EE", 0, 2, 2, -2, 2);
    v.emplace_back("EE", 1, 2, 2, -2, 2);
    v.emplace_back("EE", 2, 0, -2, 0, 0);
    v.emplace_back("EE", 4, 0, 1, -2, 0);
    v.emplace_back("EE", 6, 0, 0, -2, 0);
    v.emplace_back("EE", 8, -2, 0, -2, 0);
    v.emplace_back("EE", 9, 0, 2, 0, 0);
    v.emplace_back("EE", 11, -4, 0, -3, 2);
    v.emplace_back("EE", 3, -3, 2, -3, 0);
    v.emplace_back("EE", 5, 0, 1, 0, 0);
    v.emplace_back("EE", 7, 2, -4, 4, 0);
    v.emplace_back("EE", 10, 2, 2, 2, 0);
    litchfieldLetterPosMap["EE"] = v;
    v.clear();

    // EF
    v.emplace_back("EF", 0, 2, -2, -2, 0);
    v.emplace_back("EF", 1, 2, -2, -2, 0);
    v.emplace_back("EF", 2, 0, -2, 1, 0);
    v.emplace_back("EF", 4, 0, 0, -2, -2);
    v.emplace_back("EF", 6, -2, -1, 0, 0);
    v.emplace_back("EF", 8, -1, 0, 0, 0);
    v.emplace_back("EF", 9, -3, 0, 0, -2);
    v.emplace_back("EF", 10, 1, 2, 3, 0);
    v.emplace_back("EF", 11, 0, 3, -3, 0);
    v.emplace_back("EF", 3, -2, 4, 4, -2);
    v.emplace_back("EF", 5, 0, 0, 0, 0);
    v.emplace_back("EF", 7, 0, 0, -2, -2);
    litchfieldLetterPosMap["EF"] = v;
    v.clear();

    // EG
    v.emplace_back("EG", 0, -2, 2, -2, -2);
    v.emplace_back("EG", 1, -2, 2, -2, -2);
    v.emplace_back("EG", 4, 0, -2, 0, -1);
    v.emplace_back("EG", 6, 0, -2, -3, -4);
    v.emplace_back("EG", 7, 0, 0, -2, 0);
    v.emplace_back("EG", 8, 0, 0, -2, 0);
    v.emplace_back("EG", 10, 1, 1, 1, 0);
    v.emplace_back("EG", 11, -2, 2, -2, 0);
    v.emplace_back("EG", 2, 0, -1, 1, -4);
    v.emplace_back("EG", 3, -2, 3, -1, -2);
    v.emplace_back("EG", 5, 0, 2, -3, -2);
    v.emplace_back("EG", 9, -2, 0, 0, -3);
    litchfieldLetterPosMap["EG"] = v;
    v.clear();

    // EH
    v.emplace_back("EH", 0, 2, 2, 2, -2);
    v.emplace_back("EH", 1, 2, 2, 2, -2);
    v.emplace_back("EH", 5, 0, 0, -3, 0);
    v.emplace_back("EH", 6, -2, -2, 0, 2);
    v.emplace_back("EH", 7, 0, -4, 0, 0);
    v.emplace_back("EH", 9, -2, 0, 0, -2);
    v.emplace_back("EH", 10, -1, 1, 3, 0);
    v.emplace_back("EH", 11, -2, -1, 0, 0);
    v.emplace_back("EH", 2, 0, 0, -4, 0);
    v.emplace_back("EH", 3, -3, 2, 0, 0);
    v.emplace_back("EH", 4, 0, -2, -3, 2);
    v.emplace_back("EH", 8, -1, -2, -2, 3);
    litchfieldLetterPosMap["EH"] = v;
    v.clear();

    // EI
    v.emplace_back("EI", 0, 2, 2, 2, 0);
    v.emplace_back("EI", 1, 2, 2, 2, 0);
    v.emplace_back("EI", 4, 0, 0, 0, 0);
    v.emplace_back("EI", 5, 2, 0, 1, 0);
    v.emplace_back("EI", 7, 0, 0, 3, 1);
    v.emplace_back("EI", 8, -1, 0, 0, 0);
    v.emplace_back("EI", 9, -2, 0, 2, 0);
    v.emplace_back("EI", 11, -2, 2, 0, 0);
    v.emplace_back("EI", 2, 0, 0, 4, 0);
    v.emplace_back("EI", 3, -3, 2, 0, -2);
    v.emplace_back("EI", 6, -2, -1, 1, -2);
    v.emplace_back("EI", 10, 2, 0, -2, 2);
    litchfieldLetterPosMap["EI"] = v;
    v.clear();

    // EJ
    v.emplace_back("EJ", 0, 0, 2, -2, 0);
    v.emplace_back("EJ", 1, 0, 2, -2, 0);
    v.emplace_back("EJ", 2, 0, -2, 0, 0);
    v.emplace_back("EJ", 3, 0, 0, -4, -1);
    v.emplace_back("EJ", 6, -2, -2, -1, 0);
    v.emplace_back("EJ", 7, -1, 1, -2, -2);
    v.emplace_back("EJ", 8, 0, 0, -2, 0);
    v.emplace_back("EJ", 9, 2, 0, -2, 0);
    v.emplace_back("EJ", 10, -2, 2, 3, 2);
    v.emplace_back("EJ", 11, 3, 2, -4, 0);
    v.emplace_back("EJ", 4, 2, 0, -2, 1);
    v.emplace_back("EJ", 5, -2, -2, -2, 0);
    litchfieldLetterPosMap["EJ"] = v;
    v.clear();

    // EK
    v.emplace_back("EK", 0, 0, 2, -2, 0);
    v.emplace_back("EK", 1, 2, 2, -2, 2);
    v.emplace_back("EK", 2, 0, 0, 0, 0);
    v.emplace_back("EK", 4, 2, -2, 0, 2);
    v.emplace_back("EK", 5, 0, 0, 2, 0);
    v.emplace_back("EK", 6, -1, 0, 2, -2);
    v.emplace_back("EK", 7, 0, 0, 1, 0);
    v.emplace_back("EK", 8, 0, 0, 0, 0);
    v.emplace_back("EK", 9, -3, 2, 0, -2);
    v.emplace_back("EK", 10, 0, 2, 0, 2);
    v.emplace_back("EK", 11, 0, 0, 1, 0);
    v.emplace_back("EK", 3, -4, 2, 0, 2);
    litchfieldLetterPosMap["EK"] = v;
    v.clear();

    // EL
    v.emplace_back("EL", 0, -1, 2, -2, -1);
    v.emplace_back("EL", 1, -1, 2, -2, -1);
    v.emplace_back("EL", 2, 0, -2, -3, -2);
    v.emplace_back("EL", 3, 0, 0, -2, -1);
    v.emplace_back("EL", 4, 0, 0, 0, 2);
    v.emplace_back("EL", 5, 0, 0, 3, 0);
    v.emplace_back("EL", 6, 0, -2, 0, 0);
    v.emplace_back("EL", 8, -2, -2, -2, -2);
    v.emplace_back("EL", 11, 2, 0, -2, 2);
    v.emplace_back("EL", 7, -2, 0, 2, 0);
    v.emplace_back("EL", 9, -2, 0, 0, 0);
    v.emplace_back("EL", 10, -3, 2, 0, 0);
    litchfieldLetterPosMap["EL"] = v;
    v.clear();

    // FA
    v.emplace_back("FA", 0, -2, 0, 2, 2);
    v.emplace_back("FA", 1, -2, 0, 2, 2);
    v.emplace_back("FA", 4, 1, 2, 0, 0);
    v.emplace_back("FA", 5, 0, 0, 2, 0);
    v.emplace_back("FA", 6, 0, -1, 4, 2);
    v.emplace_back("FA", 7, 2, 0, 0, 2);
    v.emplace_back("FA", 11, 2, 2, 0, 0);
    v.emplace_back("FA", 2, 2, 0, 0, 0);
    v.emplace_back("FA", 3, 3, -2, 2, 2);
    v.emplace_back("FA", 8, 0, -2, 0, 0);
    v.emplace_back("FA", 9, 0, 0, 0, 0);
    v.emplace_back("FA", 10, 2, 1, 0, 0);
    litchfieldLetterPosMap["FA"] = v;
    v.clear();

    // FB
    v.emplace_back("FB", 0, -2, 1, 2, 1);
    v.emplace_back("FB", 1, -2, 1, 2, 1);
    v.emplace_back("FB", 3, 2, -2, -2, 2);
    v.emplace_back("FB", 4, 0, 2, -4, 2);
    v.emplace_back("FB", 6, 2, -1, 0, 2);
    v.emplace_back("FB", 7, 2, 0, 0, 0);
    v.emplace_back("FB", 8, 0, -2, -2, 0);
    v.emplace_back("FB", 9, -3, 2, -2, 0);
    v.emplace_back("FB", 10, 0, 2, 2, 1);
    v.emplace_back("FB", 11, 2, 1, 0, 2);
    v.emplace_back("FB", 2, 2, 2, -2, 2);
    v.emplace_back("FB", 5, 2, -2, 3, 0);
    litchfieldLetterPosMap["FB"] = v;
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

    // FD
    v.emplace_back("FD", 0, -2, 0, -1, -2);
    v.emplace_back("FD", 1, -2, 0, -1, -2);
    v.emplace_back("FD", 2, -2, 1, -2, 0);
    v.emplace_back("FD", 3, 2, 0, 0, 2);
    v.emplace_back("FD", 5, 0, 2, -2, 2);
    v.emplace_back("FD", 6, 1, 0, -1, 0);
    v.emplace_back("FD", 8, 0, 0, -1, 0);
    v.emplace_back("FD", 9, 2, 0, -2, 3);
    v.emplace_back("FD", 10, 3, 0, -2, 2);
    v.emplace_back("FD", 11, -2, 2, 0, 2);
    v.emplace_back("FD", 4, 0, 0, -2, 0);
    v.emplace_back("FD", 7, 0, -2, 0, 2);
    litchfieldLetterPosMap["FD"] = v;
    v.clear();

    // FE
    v.emplace_back("FE", 0, 0, 0, 0, 2);
    v.emplace_back("FE", 1, 0, 0, 0, 2);
    v.emplace_back("FE", 3, 3, 2, -3, 2);
    v.emplace_back("FE", 4, 0, 2, 2, 0);
    v.emplace_back("FE", 5, 0, 0, 0, -1);
    v.emplace_back("FE", 6, 0, 0, 2, 2);
    v.emplace_back("FE", 9, 0, 0, -2, 1);
    v.emplace_back("FE", 11, -2, 2, -2, 2);
    v.emplace_back("FE", 2, 2, 1, 0, 0);
    v.emplace_back("FE", 7, 3, -3, 2, -1);
    v.emplace_back("FE", 8, -1, 1, 0, 0);
    v.emplace_back("FE", 10, 3, 2, 2, 0);
    litchfieldLetterPosMap["FE"] = v;
    v.clear();

    // FF
    v.emplace_back("FF", 0, 0, -2, 0, 0);
    v.emplace_back("FF", 1, 0, -2, 0, 0);
    v.emplace_back("FF", 4, 2, 1, 0, 0);
    v.emplace_back("FF", 5, 4, 0, 0, 2);
    v.emplace_back("FF", 6, 0, 0, 2, 0);
    v.emplace_back("FF", 7, 0, 2, -2, -2);
    v.emplace_back("FF", 8, 0, 0, -2, -1);
    v.emplace_back("FF", 9, -2, 0, 0, 0);
    v.emplace_back("FF", 11, -3, 2, -4, 0);
    v.emplace_back("FF", 2, -2, 2, -3, 0);
    v.emplace_back("FF", 3, 0, 2, 2, 2);
    v.emplace_back("FF", 10, 0, 2, -2, 0);
    litchfieldLetterPosMap["FF"] = v;
    v.clear();

    // FG
    v.emplace_back("FG", 0, 0, 0, -2, -2);
    v.emplace_back("FG", 1, 0, 0, -2, -2);
    v.emplace_back("FG", 2, -2, 0, -2, -2);
    v.emplace_back("FG", 5, 2, 0, 3, -3);
    v.emplace_back("FG", 8, -1, 0, -2, 0);
    v.emplace_back("FG", 10, 2, 0, 2, 0);
    v.emplace_back("FG", 11, 0, 2, 3, -3);
    v.emplace_back("FG", 3, 0, 2, 3, -2);
    v.emplace_back("FG", 4, 3, 0, -2, 0);
    v.emplace_back("FG", 6, 2, 0, -2, -2);
    v.emplace_back("FG", 7, 2, 1, -2, -2);
    v.emplace_back("FG", 9, 0, 0, -2, -4);
    litchfieldLetterPosMap["FG"] = v;
    v.clear();

    // FH
    v.emplace_back("FH", 0, 0, 0, 2, -2);
    v.emplace_back("FH", 1, 0, 0, 2, -2);
    v.emplace_back("FH", 4, 0, 0, 0, 1);
    v.emplace_back("FH", 5, 2, 0, -4, -2);
    v.emplace_back("FH", 6, 0, 0, -2, -2);
    v.emplace_back("FH", 7, 0, 0, -1, 1);
    v.emplace_back("FH", 8, 0, 0, -4, 2);
    v.emplace_back("FH", 11, -2, 0, 0, 0);
    v.emplace_back("FH", 2, 1, 0, 3, 0);
    v.emplace_back("FH", 3, -2, 2, -2, -1);
    v.emplace_back("FH", 9, -2, 0, -2, 2);
    v.emplace_back("FH", 10, 3, 1, 3, 4);
    litchfieldLetterPosMap["FH"] = v;
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

    // FK
    v.emplace_back("FK", 0, 0, 0, 0, -2);
    v.emplace_back("FK", 1, 0, 0, 0, -2);
    v.emplace_back("FK", 3, 2, 2, 0, -4);
    v.emplace_back("FK", 4, 0, 2, 0, 0);
    v.emplace_back("FK", 5, 0, 2, -2, 0);
    v.emplace_back("FK", 6, 0, -2, 2, 0);
    v.emplace_back("FK", 9, 0, 0, 2, -2);
    v.emplace_back("FK", 10, -1, 2, -2, 2);
    v.emplace_back("FK", 11, 0, 0, -2, 0);
    v.emplace_back("FK", 2, -2, 0, 2, 2);
    v.emplace_back("FK", 7, 4, 2, 0, 0);
    v.emplace_back("FK", 8, 0, 2, -1, 0);
    litchfieldLetterPosMap["FK"] = v;
    v.clear();

    // FL
    v.emplace_back("FL", 0, 0, 0, -2, 0);
    v.emplace_back("FL", 1, 0, 0, -2, 0);
    v.emplace_back("FL", 4, 0, 1, -2, 0);
    v.emplace_back("FL", 5, -2, 2, 3, -2);
    v.emplace_back("FL", 6, 0, -1, 0, -1);
    v.emplace_back("FL", 7, 0, 1, 1, -1);
    v.emplace_back("FL", 8, 0, 2, 0, -2);
    v.emplace_back("FL", 10, 2, 2, -1, 2);
    v.emplace_back("FL", 11, 2, 0, 0, 3);
    v.emplace_back("FL", 2, -2, 0, -2, -2);
    v.emplace_back("FL", 3, 0, 2, 0, -1);
    v.emplace_back("FL", 9, -4, 0, 3, -4);
    litchfieldLetterPosMap["FL"] = v;
    v.clear();

    // GA
    v.emplace_back("GA", 0, 0, 0, 0, 1);
    v.emplace_back("GA", 1, 0, 0, 0, 1);
    v.emplace_back("GA", 4, -2, 0, 4, -1);
    v.emplace_back("GA", 5, 2, -2, 2, 1);
    v.emplace_back("GA", 6, -2, -2, 0, 2);
    v.emplace_back("GA", 7, -2, -2, 0, -1);
    v.emplace_back("GA", 8, -2, -2, 0, -2);
    v.emplace_back("GA", 9, -2, 1, -2, -2);
    v.emplace_back("GA", 10, 0, 0, 0, 0);
    v.emplace_back("GA", 11, -2, 0, 2, 1);
    v.emplace_back("GA", 2, -2, 0, 0, -2);
    v.emplace_back("GA", 3, 0, 0, 0, 0 );
    litchfieldLetterPosMap["GA"] = v;
    v.clear();

    // GB
    v.emplace_back("GB", 0, -2, 0, 0, 2);
    v.emplace_back("GB", 1, -2, 0, 0, 2);
    v.emplace_back("GB", 4, -2, 0, 1, -1);
    v.emplace_back("GB", 6, -2, -2, 0, 2);
    v.emplace_back("GB", 7, -1, -2, 0, 0);
    v.emplace_back("GB", 10, 0, -2, -3, 0);
    v.emplace_back("GB", 2, 2, -2, -2, 2);
    v.emplace_back("GB", 3, 2, 0, -2, 2);
    v.emplace_back("GB", 5, 0, -2, 0, 0);
    v.emplace_back("GB", 8, -2, -2, 0, -2);
    v.emplace_back("GB", 9, 2, -2, 0, 0);
    v.emplace_back("GB", 11, 2, -2, -1, 2);
    litchfieldLetterPosMap["GB"] = v;
    v.clear();

    // GC
    v.emplace_back("GC", 0, -2, -2, -2, -2);
    v.emplace_back("GC", 1, -2, -2, 0, -2);
    v.emplace_back("GC", 4, -2, 2, 0, -2);
    v.emplace_back("GC", 5, -2, -2, 0, -2);
    v.emplace_back("GC", 6, -2, -2, 0, -2);
    v.emplace_back("GC", 9, 2, 2, -2, -2);
    v.emplace_back("GC", 11, 1, 0, -2, -1);
    v.emplace_back("GC", 2, 0, 0, 0, -2);
    v.emplace_back("GC", 3, 2, 0, -2, -2);
    v.emplace_back("GC", 7, -2, -2, -3, -2);
    v.emplace_back("GC", 8, -2, -2, 0, 0);
    v.emplace_back("GC", 10, 0, 0, -1, -2);
    litchfieldLetterPosMap["GC"] = v;
    v.clear();

    // GD
    v.emplace_back("GD", 0, 2, -2, -4, 0);
    v.emplace_back("GD", 1, 2, -2, -4, 0);
    v.emplace_back("GD", 4, -1, -2, 0, 3);
    v.emplace_back("GD", 5, 0, 0, -3, 2);
    v.emplace_back("GD", 7, 0, -3, 0, 0);
    v.emplace_back("GD", 8, -1, -2, 2, 0);
    v.emplace_back("GD", 9, 0, -3, -2, 2);
    v.emplace_back("GD", 10, 0, 0, -2, 2);
    v.emplace_back("GD", 11, 4, 0, 3, -1);
    v.emplace_back("GD", 2, -2, -2, 0, 0);
    v.emplace_back("GD", 3, 2, 0, 0, 2);
    v.emplace_back("GD", 6, -2, -2, 2, 2);
    litchfieldLetterPosMap["GD"] = v;
    v.clear();

    // GE
    v.emplace_back("GE", 0, -2, -3, 2, 3);
    v.emplace_back("GE", 1, -2, -3, 2, 3);
    v.emplace_back("GE", 3, 0, -2, -2, 0);
    v.emplace_back("GE", 4, -1, 1, -1, -1);
    v.emplace_back("GE", 5, 2, -2, 0, -2);
    v.emplace_back("GE", 6, -2, -2, -1, -2);
    v.emplace_back("GE", 9, 2, -2, 2, -2);
    v.emplace_back("GE", 11, 0, 2, -2, 2);
    v.emplace_back("GE", 2, 0, -3, -2, 0);
    v.emplace_back("GE", 7, -2, -2, 2, 0);
    v.emplace_back("GE", 8, -2, -2, -1, 0);
    v.emplace_back("GE", 10, 2, 0, 0, 2);
    litchfieldLetterPosMap["GE"] = v;
    v.clear();

    // GF
    v.emplace_back("GF", 0, 2, -3, 0, 0);
    v.emplace_back("GF", 1, 2, -3, 0, 0);
    v.emplace_back("GF", 2, -2, -3, 0, 0);
    v.emplace_back("GF", 4, -2, -2, 0, 0);
    v.emplace_back("GF", 5, 2, -2, 2, 1);
    v.emplace_back("GF", 6, -2, -2, 2, -1);
    v.emplace_back("GF", 7, -2, 1, -2, -1);
    v.emplace_back("GF", 9, -2, -1, 0, -2);
    v.emplace_back("GF", 10, 1, -1, 1, -2);
    v.emplace_back("GF", 11, 0, 2, -2, 2);
    v.emplace_back("GF", 3, 0, -3, 0, 2);
    v.emplace_back("GF", 8, -2, -3, 0, 0);
    litchfieldLetterPosMap["GF"] = v;
    v.clear();

    // GG
    v.emplace_back("GG", 0, 2, 2, -2, -2);
    v.emplace_back("GG", 1, 2, 2, -2, -2);
    v.emplace_back("GG", 4, -2, 2, -3, 0);
    v.emplace_back("GG", 6, -2, -2, 2, -2);
    v.emplace_back("GG", 9, 0, -2, 0, 2);
    v.emplace_back("GG", 11, -1, 0, 0, 0);
    v.emplace_back("GG", 2, 0, 0, -3, -2);
    v.emplace_back("GG", 3, 2, -2, 0, 2);
    v.emplace_back("GG", 5, 0, -3, 2, -2);
    v.emplace_back("GG", 7, 0, 0, -2, -2);
    v.emplace_back("GG", 8, -2, -2, -2, 0);
    v.emplace_back("GG", 10, 0, 0, 2, -2);
    litchfieldLetterPosMap["GG"] = v;
    v.clear();

    // GH
    v.emplace_back("GH", 0, 1, -3, 1, -1);
    v.emplace_back("GH", 1, 1, -3, 1, -1);
    v.emplace_back("GH", 2, -1, 0, 0, 2);
    v.emplace_back("GH", 4, -2, 2, 1, 0);
    v.emplace_back("GH", 9, 0, 2, -1, 1);
    v.emplace_back("GH", 10, 2, 0, -1, 2);
    v.emplace_back("GH", 11, 0, -2, 2, 0);
    v.emplace_back("GH", 3, 0, -2, -1, 0);
    v.emplace_back("GH", 5, 2, 0, 0, -2);
    v.emplace_back("GH", 6, -4, -2, -2, 2);
    v.emplace_back("GH", 7, -2, -2, -3, 0);
    v.emplace_back("GH", 8, -2, -2, -2, 2);
    litchfieldLetterPosMap["GH"] = v;
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

    // GK
    v.emplace_back("GK", 0, 0, -2, -2, -2);
    v.emplace_back("GK", 1, 2, 0, 0, 2);
    v.emplace_back("GK", 2, 2, -2, 2, 0);
    v.emplace_back("GK", 4, 0, 2, 0, 2);
    v.emplace_back("GK", 5, 0, 0, 2, -2);
    v.emplace_back("GK", 6, -2, -2, 0, -3);
    v.emplace_back("GK", 7, -2, 1, 0, 0);
    v.emplace_back("GK", 8, -2, -2, 0, -3);
    v.emplace_back("GK", 9, 3, 0, 0, 0);
    v.emplace_back("GK", 11, 0,0, 2, 0);
    v.emplace_back("GK", 3, -2, -2, 0, -2);
    v.emplace_back("GK", 10, -2, 0, 0, 2);
    litchfieldLetterPosMap["GK"] = v;
    v.clear();

    // GL
    v.emplace_back("GL", 0, -2, 0, -2, -2);
    v.emplace_back("GL", 1, -2, 0, -2, -2);
    v.emplace_back("GL", 2, 0, 0, -1, -2);
    v.emplace_back("GL", 4, -2, -2, -2, 0);
    v.emplace_back("GL", 6, -2, -2, 0, 0);
    v.emplace_back("GL", 7, -2, 0, 1, -1);
    v.emplace_back("GL", 8, -2, -2, -1, -2);
    v.emplace_back("GL", 10, 3, -2, 2, 0);
    v.emplace_back("GL", 11, 0, 4, -2, 2);
    v.emplace_back("GL", 3, -2, -2, 0, 0);
    v.emplace_back("GL", 5, -2, 0, 1, -1);
    v.emplace_back("GL", 9, 0, -4, 0, 0);
    litchfieldLetterPosMap["GL"] = v;
    v.clear();

    //HA
    v.emplace_back("HA", 0, 2, -2, 0, 2);
    v.emplace_back("HA", 1, 2, -2, 0, 2);
    v.emplace_back("HA", 2, 0, 2, 0, 0);
    v.emplace_back("HA", 3, -4, 2, 0, 0);
    v.emplace_back("HA", 4, -2, 2, -2, 0);
    v.emplace_back("HA", 5, -2, -2, 2, 0);
    v.emplace_back("HA", 6, -2, 2, -2, 2);
    v.emplace_back("HA", 7, -4, -2, 0, 0);
    v.emplace_back("HA", 8, -3, -2, 1, 0);
    v.emplace_back("HA", 9, 0, 0, -2, 0);
    v.emplace_back("HA", 10, -1, 2, 2, 2);
    v.emplace_back("HA", 11, 2, 0, -2, 2);
    litchfieldLetterPosMap["HA"] = v;
    v.clear();

    // HB
    v.emplace_back("HB", 0, 2, -2, 1, 1);
    v.emplace_back("HB", 1, 2, -2, 1, 1);
    v.emplace_back("HB", 4, -2, 4, 0, -2);
    v.emplace_back("HB", 5, -2, -4, 0, 2);
    v.emplace_back("HB", 7, -2, -2, 0, 0);
    v.emplace_back("HB", 9, 4, 0, -1, 2);
    v.emplace_back("HB", 10, -1, 2, 2, 0);
    v.emplace_back("HB", 11, 2, 0, -3, 3);
    v.emplace_back("HB", 2, 0, 2, 0, 1);
    v.emplace_back("HB", 3, 3, -2, -2, 2);
    v.emplace_back("HB", 6, -2, 1, 0, 0);
    v.emplace_back("HB", 8, -3, -2, 0, 2);
    litchfieldLetterPosMap["HB"] = v;
    v.clear();

    // HC
    v.emplace_back("HC", 0, 2, -2, 0, -2);
    v.emplace_back("HC", 1, 2, -2, 0, -2);
    v.emplace_back("HC", 2, 0, 2, 3, -2);
    v.emplace_back("HC", 3, 2, 2, -2, -2);
    v.emplace_back("HC", 4, 3, 2, 0, -1);
    v.emplace_back("HC", 5, -2, -4, 2, -2);
    v.emplace_back("HC", 6, 0, 3, 3, -2);
    v.emplace_back("HC", 8, -2, -1, 2, -2);
    v.emplace_back("HC", 9, 1, 0, -2, -2);
    v.emplace_back("HC", 10, -2, 2, -3, -1);
    v.emplace_back("HC", 11, 2, -2, 0, -2);
    v.emplace_back("HC", 7, -2, -2, -1, -3);
    litchfieldLetterPosMap["HC"] = v;
    v.clear();

    // HD
    v.emplace_back("HD", 0, 2, -2, -2, 0);
    v.emplace_back("HD", 1, 2, -2, -2, 0);
    v.emplace_back("HD", 2, 2, 2, 0, 2);
    v.emplace_back("HD", 3, 0, 2, 0, 2);
    v.emplace_back("HD", 4, 4, 2, 0, 0);
    v.emplace_back("HD", 5, -2, -3, -2, 1);
    v.emplace_back("HD", 7, 0, -2, 0, 0);
    v.emplace_back("HD", 10, -2, 1, -3, 2);
    v.emplace_back("HD", 11, 0, 2, 0, 2);
    v.emplace_back("HD", 6, -2, 2, -1, 1);
    v.emplace_back("HD", 8, -2, -1, 0, -2);
    v.emplace_back("HD", 9, 0, 0, 2, 4);
    litchfieldLetterPosMap["HD"] = v;
    v.clear();

    // HE
    v.emplace_back("HE", 0, 0, -2, 2, 1);
    v.emplace_back("HE", 1, 0, -2, 2, 1);
    v.emplace_back("HE", 2, 0, 2, -3, 2);
    v.emplace_back("HE", 4, -2, 2, 0, -2);
    v.emplace_back("HE", 5, -2, -4, -3, -1);
    v.emplace_back("HE", 6, 0, 0, 0, 0);
    v.emplace_back("HE", 8, -2, 0, 0, 0);
    v.emplace_back("HE", 9, 2, 0, 2, -2);
    v.emplace_back("HE", 11, 2, 1, -2, 0);
    v.emplace_back("HE", 3, 0, 2, -2, 2);
    v.emplace_back("HE", 7, -2, 0, 0, 0);
    v.emplace_back("HE", 10, 0, 0, 2, 0);
    litchfieldLetterPosMap["HE"] = v;
    v.clear();

    // HF
    v.emplace_back("HF", 0, 2, -2, 0, -2);
    v.emplace_back("HF", 1, 2, -2, 0, -2);
    v.emplace_back("HF", 4, 3, 2, 0, 0);
    v.emplace_back("HF", 5, -2, -4, -3, 2);
    v.emplace_back("HF", 8, -2, 1, 0, 0);
    v.emplace_back("HF", 9, -2, -2, 2, -2);
    v.emplace_back("HF", 11, 2, 2, -2, -2);
    v.emplace_back("HF", 2, -2, 2, 0, -1);
    v.emplace_back("HF", 3, 3, 2, 3, 0);
    v.emplace_back("HF", 6, 0, 2, 2, -2);
    v.emplace_back("HF", 7, -4, -2, 0, 0);
    v.emplace_back("HF", 10, 0, 2, -1, 0);
    litchfieldLetterPosMap["HF"] = v;
    v.clear();

    // HG
    v.emplace_back("HG", 0, 2, -2, -2, -2);
    v.emplace_back("HG", 1, 2, -2, -2, -2);
    v.emplace_back("HG", 3, 0, 2, 2, -2);
    v.emplace_back("HG", 5, 0, -1, -2, -3);
    v.emplace_back("HG", 8, -2, -2, -2, -3);
    v.emplace_back("HG", 11, 2, -2, -2, -2);
    v.emplace_back("HG", 2, 0, 0, 0, -1);
    v.emplace_back("HG", 4, 0, 2, 0, -3);
    v.emplace_back("HG", 6, -2, 2, -2, 0);
    v.emplace_back("HG", 7, -2, -2, -1, -2);
    v.emplace_back("HG", 9, -3, 2, 0, -2);
    v.emplace_back("HG", 10, 0, 2, 2, 0);
    litchfieldLetterPosMap["HG"] = v;
    v.clear();

    // HH
    v.emplace_back("HH", 0, 2, -2, 2, -2);
    v.emplace_back("HH", 1, 2, -2, 2, -2);
    v.emplace_back("HH", 3, -2, 2, -2, 1);
    v.emplace_back("HH", 4, 0, 2, -2, 0);
    v.emplace_back("HH", 5, 0, 0, -2, -2);
    v.emplace_back("HH", 6, 0, 2, 0, 2);
    v.emplace_back("HH", 8, -2, 0, -2, 0);
    v.emplace_back("HH", 9, 0, 0, -2, 0);
    v.emplace_back("HH", 11, -2, 0, -2, -2);
    v.emplace_back("HH", 2, 2, 2, -2, 2);
    v.emplace_back("HH", 7, -2, 0, -2, 1);
    v.emplace_back("HH", 10, 0, 2, 3, 0);
    litchfieldLetterPosMap["HH"] = v;
    v.clear();

    // HI
    v.emplace_back("HI", 0, 2, -2, 2, 0);
    v.emplace_back("HI", 1, 2, -2, 2, 0);
    v.emplace_back("HI", 5, -2, 0, 4, -3);
    v.emplace_back("HI", 6, -4, 2, 1, -2);
    v.emplace_back("HI", 8, -2, -2, -2, 1);
    v.emplace_back("HI", 11, 0, 0, 0, 2);
    v.emplace_back("HI", 2, 1, 0, 0, 0);
    v.emplace_back("HI", 3, 2, 2, 0, -2);
    v.emplace_back("HI", 4, -2, 2, 0, -2);
    v.emplace_back("HI", 7, -2, 0, 2, -1);
    v.emplace_back("HI", 9, 3, -2, 2, -1);
    v.emplace_back("HI", 10, 0, 2, 2, 2);
    litchfieldLetterPosMap["HI"] = v;
    v.clear();

    // HJ
    v.emplace_back("HJ", 0, 1, -2, 0, -1);
    v.emplace_back("HJ", 1, 1, -2, 0, -1);
    v.emplace_back("HJ", 4, 3, 2, -2, 0);
    v.emplace_back("HJ", 5, 0, -1, -2, 0);
    v.emplace_back("HJ", 6, -2, 0, -2, -2);
    v.emplace_back("HJ", 7, -3, 0, 0, 0);
    v.emplace_back("HJ", 11, 3, -2, -3, 0);
    v.emplace_back("HJ", 2, 1, -2, -2, 0);
    v.emplace_back("HJ", 3, 0, 2, -2, -2);
    v.emplace_back("HJ", 8, -2, 0, 0, -1);
    v.emplace_back("HJ", 9, 0, -2, -3, -2);
    v.emplace_back("HJ", 10, 3, 2, 0, -2);
    litchfieldLetterPosMap["HJ"] = v;
    v.clear();

    // HK
    v.emplace_back("HK", 0, 2, -2, 2, -3);
    v.emplace_back("HK", 1, 2, -2, 2, -3);
    v.emplace_back("HK", 3, -2, 0, -2, -2);
    v.emplace_back("HK", 4, 2, 0, 0, 1);
    v.emplace_back("HK", 5, -2, 0, 2, -2);
    v.emplace_back("HK", 7, -2, 2, 0, 0);
    v.emplace_back("HK", 8, -2, -1, 0, -2);
    v.emplace_back("HK", 9, 0, -2, 2, -2);
    v.emplace_back("HK", 11, -2, 2, 0, 2);
    v.emplace_back("HK", 2, 0, 0, 0, 0);
    v.emplace_back("HK", 6, -2, 2, 0, -3);
    v.emplace_back("HK", 10, 0, 1, -2, 1);
    litchfieldLetterPosMap["HK"] = v;
    v.clear();

    // HL
    v.emplace_back("HL", 0, 2, -2, -2, 0);
    v.emplace_back("HL", 1, 2, -2, -2, 0);
    v.emplace_back("HL", 2, 2, 0, -3, -2);
    v.emplace_back("HL", 4, 4, 2, 2, 0);
    v.emplace_back("HL", 6, 0, 0, 0, 0);
    v.emplace_back("HL", 7, -2, 2, 0, -2);
    v.emplace_back("HL", 8, 0, 0, -1, -2);
    v.emplace_back("HL", 10, -2, 2, 3, 3);
    v.emplace_back("HL", 11, 0, 0, -3, 2);
    v.emplace_back("HL", 3, -3, 3, 0, 0);
    v.emplace_back("HL", 5, -1, -1, 0, -2);
    v.emplace_back("HL", 9, 2, -4, -2, -1);
    litchfieldLetterPosMap["HL"] = v;
    v.clear();

    // IA
    v.emplace_back("IA", 0, 2, 2, 0, 1);
    v.emplace_back("IA", 1, 2, 2, 0, 1);
    v.emplace_back("IA", 2, 0, 0, 1, 2);
    v.emplace_back("IA", 4, 2, 0, -1, 0);
    v.emplace_back("IA", 5, 3, 0, 3, 0);
    v.emplace_back("IA", 6, 0, -2, 0, 0);
    v.emplace_back("IA", 8, 0, 0, -1, 0);
    v.emplace_back("IA", 9, 0, 0, 0, 1);
    v.emplace_back("IA", 10, -2, 2, -2, 2);
    v.emplace_back("IA", 3, 0, -2, 0, -1);
    v.emplace_back("IA", 7, 0, 0, 0, 0);
    v.emplace_back("IA", 11, 2, 0, -2, 2);
    litchfieldLetterPosMap["IA"] = v;
    v.clear();

    // IB
    v.emplace_back("IB", 0, 2, 0, 1, 2);
    v.emplace_back("IB", 1, 2, 0, 1, 2);
    v.emplace_back("IB", 2, 3, 0, 0, 2);
    v.emplace_back("IB", 4, 3, -2, -1, -1);
    v.emplace_back("IB", 5, 0, 0, 1, -2);
    v.emplace_back("IB", 6, 0, 0, 0, 1);
    v.emplace_back("IB", 7, 0, -1, 0, 2);
    v.emplace_back("IB", 8, 0, 0, 0, 0);
    v.emplace_back("IB", 11, -2, 2, -2, 2);
    v.emplace_back("IB", 3, 0, 0, -2, 2);
    v.emplace_back("IB", 9, -2, 1, 1, 1);
    v.emplace_back("IB", 10, 3, 0, 1, 1);
    litchfieldLetterPosMap["IB"] = v;
    v.clear();

    // IC
    v.emplace_back("IC", 0, 2, 1, 0, -1);
    v.emplace_back("IC", 1, 2, 1, 0, -1);
    v.emplace_back("IC", 2, -2, 1, -2, -2);
    v.emplace_back("IC", 3, 0, 2, 0, -2);
    v.emplace_back("IC", 4, 1, 2, 3, -2);
    v.emplace_back("IC", 7, 0, -1, 0, -3);
    v.emplace_back("IC", 11, 1, 2, 0, -2);
    v.emplace_back("IC", 5, 1, 0, 0, -3);
    v.emplace_back("IC", 6, 2, 0, 0, -2);
    v.emplace_back("IC", 8, -1, 0, 0, 0);
    v.emplace_back("IC", 9, 0, 0, -2, -2);
    v.emplace_back("IC", 10, 2, 2, -3, -1);
    litchfieldLetterPosMap["IC"] = v;
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
    litchfieldLetterPosMap["ID"] = v;
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

    // IH
    v.emplace_back("IH", 0, 3, 0, 1, -1);
    v.emplace_back("IH", 1, 3, 0, 1, -1);
    v.emplace_back("IH", 3, 0, 0, -2, -1);
    v.emplace_back("IH", 4, 2, 0, -2, -1);
    v.emplace_back("IH", 6, 0, 0, -2, -1);
    v.emplace_back("IH", 7, 0, 0, -2, -3);
    v.emplace_back("IH", 9, 2, -2, -2, -2);
    v.emplace_back("IH", 11, -2, -2, 2, 0);
    v.emplace_back("IH", 2, 2, -1, -4, 0);
    v.emplace_back("IH", 5, 2, 0, 0, -2);
    v.emplace_back("IH", 8, -2, 0, -2, 3);
    v.emplace_back("IH", 10, 2, 0, 3, 2);
    litchfieldLetterPosMap["IH"] = v;
    v.clear();

    // II
    v.emplace_back("II", 0, 2, 0, 2, 2);
    v.emplace_back("II", 1, 2, 0, 2, 2);
    v.emplace_back("II", 4, 4, -2, 0, -1);
    v.emplace_back("II", 5, 3, 2, -3, -2);
    v.emplace_back("II", 6, 1, 0, 1, 0);
    v.emplace_back("II", 8, -2, 2, 0, 0);
    v.emplace_back("II", 11, 4, 0, -4, 2);
    v.emplace_back("II", 2, -2, 0, 1, -1);
    v.emplace_back("II", 3, -2, 0, -2, 2);
    v.emplace_back("II", 7, 0, 0, 1, 0);
    v.emplace_back("II", 9, 1, -2, 1, -1);
    v.emplace_back("II", 10, -2, 2, 2, -2);
    litchfieldLetterPosMap["II"] = v;
    v.clear();

    // IJ
    v.emplace_back("IJ", 0, 2, 0, -2, 0);
    v.emplace_back("IJ", 1, 2, 0, -2, 0);
    v.emplace_back("IJ", 5, 2, 0, -3, 0);
    v.emplace_back("IJ", 6, 0, 0, -2, 0);
    v.emplace_back("IJ", 7, -1, -2, 4, -2);
    v.emplace_back("IJ", 10, 1, 2, 4, 0);
    v.emplace_back("IJ", 11, 1, 2, -2, 0);
    v.emplace_back("IJ", 2, 0, 0, 1, 0);
    v.emplace_back("IJ", 3, 2, 0, -2, -1);
    v.emplace_back("IJ", 4, 2, -2, -2, -2);
    v.emplace_back("IJ", 8, 0, 2, -3, -1);
    v.emplace_back("IJ", 9, 4, -2, 4, -2);
    litchfieldLetterPosMap["IJ"] = v;
    v.clear();

    // IK
    v.emplace_back("IK", 0, 2, 0, -2, 0);
    v.emplace_back("IK", 1, 2, 0, -2, 0);
    v.emplace_back("IK", 5, 2, -2, 0, 0);
    v.emplace_back("IK", 6, -1, -1, 2, -1);
    v.emplace_back("IK", 9, 2, 0, 2, 0);
    v.emplace_back("IK", 11, 0, 2, 0, 0);
    v.emplace_back("IK", 2, -1, -2, 0, 0);
    v.emplace_back("IK", 3, -2, 2, 0, -2);
    v.emplace_back("IK", 4, 1, 0, 0, 4);
    v.emplace_back("IK", 7, 0, -1, 0, 0);
    v.emplace_back("IK", 8, 0, 2, 0, -2);
    v.emplace_back("IK", 10, -2, 2, 3, 2);
    litchfieldLetterPosMap["IK"] = v;
    v.clear();

    // IL
    v.emplace_back("IL", 0, 2, 0, -2, 0);
    v.emplace_back("IL", 1, 2, -2, 0, 0);
    v.emplace_back("IL", 2, -1, 1, -2, 0);
    v.emplace_back("IL", 3, 2, 2, -2, -2);
    v.emplace_back("IL", 4, 2, 0, 0, 2);
    v.emplace_back("IL", 6, 0, 0, 0, 0);
    v.emplace_back("IL", 11, 0, 2, 0, 2);
    v.emplace_back("IL", 5, 2, -2, -1, -2);
    v.emplace_back("IL", 7, 0, 0, 0, -2);
    v.emplace_back("IL", 8, -2, 0, -2, -2);
    v.emplace_back("IL", 9, 4, 0, -2, 0);
    v.emplace_back("IL", 10, 0, 0, 2, 0);
    litchfieldLetterPosMap["IL"] = v;
    v.clear();

    // JA
    v.emplace_back("JA", 0, 2, -2, 2, 2);
    v.emplace_back("JA", 1, 2, -2, 2, 2);
    v.emplace_back("JA", 2, -2, 0, 4, 2);
    v.emplace_back("JA", 4, -2, 0, 3, 2);
    v.emplace_back("JA", 5, 0, -2, 2, 2);
    v.emplace_back("JA", 6, 1, -2, 0, 2);
    v.emplace_back("JA", 10, -2, 2, -3, 0);
    v.emplace_back("JA", 11, -4, 2, -2, 0);
    v.emplace_back("JA", 3, -4, 0, 0, 0);
    v.emplace_back("JA", 7, 0, 0, 0, 0);
    v.emplace_back("JA", 8, -2, 0, 0, -1);
    v.emplace_back("JA", 9, 0, -1, -2, 0);
    litchfieldLetterPosMap["JA"] = v;
    v.clear();

    // JB
    v.emplace_back("JB", 0, 0, 0, 0, 1);
    v.emplace_back("JB", 1, 0, 0, 0, 1);
    v.emplace_back("JB", 2, -2, 0, -3, 2);
    v.emplace_back("JB", 4, 0, -2, -1, 0);
    v.emplace_back("JB", 5, 4, 0, -1, 1);
    v.emplace_back("JB", 11, -4, 2, 0, 2);
    v.emplace_back("JB", 3, -2, 0, 0, 2);
    v.emplace_back("JB", 6, 0, 0, 2, 0);
    v.emplace_back("JB", 7, -2, -1, 0, 2);
    v.emplace_back("JB", 8, -2, 2, 0, 0);
    v.emplace_back("JB", 9, 2, -2, -2, 0);
    v.emplace_back("JB", 10, -3, 1, 4, 2);
    litchfieldLetterPosMap["JB"] = v;
    v.clear();

    // JC
    v.emplace_back("JC", 0, -2, 0, 2, -2);
    v.emplace_back("JC", 1, 0, 0, -2, 0);
    v.emplace_back("JC", 2, -4, 0, -4, -2);
    v.emplace_back("JC", 4, 0, 0, 4, -2);
    v.emplace_back("JC", 11, -3, 2, -1, 0);
    v.emplace_back("JC", 3, -2, -2, -4, -2);
    v.emplace_back("JC", 5, 3, -2, 3, -2);
    v.emplace_back("JC", 6, -2, -2, -2, 0);
    v.emplace_back("JC", 7, -2, -2, 0, -2);
    v.emplace_back("JC", 8, -2, 2, -2, 0);
    v.emplace_back("JC", 9, -4, 0, -3, -2);
    v.emplace_back("JC", 10, -2, 2, 0, 0);
    litchfieldLetterPosMap["JC"] = v;
    v.clear();

    // JD
    v.emplace_back("JD", 0, -3, 0, -2, 0);
    v.emplace_back("JD", 1, -3, 0, -2, 0);
    v.emplace_back("JD", 2, 0, 2, -2, -2);
    v.emplace_back("JD", 3, -3, 2, 0, 0);
    v.emplace_back("JD", 4, 0, -2, 0, 2);
    v.emplace_back("JD", 8, -2, -1, -2, 0);
    v.emplace_back("JD", 9, 0, 0, -2, 0);
    v.emplace_back("JD", 11, -3, 2, 2, 2);
    v.emplace_back("JD", 5, 4, -3, -2, 2);
    v.emplace_back("JD", 6, -2, -2, -2, 2);
    v.emplace_back("JD", 7, -2, 0, 4, 2);
    v.emplace_back("JD", 10, 2, 0, -2, -2);
    litchfieldLetterPosMap["JD"] = v;
    v.clear();

    // JE
    v.emplace_back("JE", 0, -3, 0, 2, 2);
    v.emplace_back("JE", 1, -3, 0, 2, 2);
    v.emplace_back("JE", 2, -2, 0, 0, -1);
    v.emplace_back("JE", 4, -3, 0, 1, -4);
    v.emplace_back("JE", 5, 4, -1, 2, -1);
    v.emplace_back("JE", 8, -2, 2, -2, -2);
    v.emplace_back("JE", 11, -3, 2, 0, 2);
    v.emplace_back("JE", 3, 2, -2, -3, 2);
    v.emplace_back("JE", 6, -2, 0, -2, -1);
    v.emplace_back("JE", 7, -2, 2, -1, -1);
    v.emplace_back("JE", 9, 0, 0, 0, 0);
    v.emplace_back("JE", 10, 1, 0, 1, -1);
    litchfieldLetterPosMap["JE"] = v;
    v.clear();

    // JF
    v.emplace_back("JF", 0, 0, -2, 0, 0);
    v.emplace_back("JF", 1, 0, -2, 0, 0);
    v.emplace_back("JF", 2, -2, 0, -2, 0);
    v.emplace_back("JF", 3, -2, -1, 2, 0);
    v.emplace_back("JF", 4, -2, -2, 1, -2);
    v.emplace_back("JF", 5, -3, 0, 0, 0);
    v.emplace_back("JF", 6, 0, -2, 0, -2);
    v.emplace_back("JF", 8, 0, -2, 0, 0);
    v.emplace_back("JF", 10, 0, 0, -2, -2);
    v.emplace_back("JF", 11, -4, 2, -4, 2);
    v.emplace_back("JF", 7, -2, 0, 1, -1);
    v.emplace_back("JF", 9, -2, 0, -2, 0);
    litchfieldLetterPosMap["JF"] = v;
    v.clear();

    // JG
    v.emplace_back("JG", 0, -2, -2, 0, -2);
    v.emplace_back("JG", 1, -2, -2, 0, -2);
    v.emplace_back("JG", 4, -2, -3, -4, -4);
    v.emplace_back("JG", 5, -2, 0, 0, -3);
    v.emplace_back("JG", 7, -2, -2, -2, 0);
    v.emplace_back("JG", 9, 2, 0, 1, 1);
    v.emplace_back("JG", 10, 3, -1, 3, -1);
    v.emplace_back("JG", 11, -4, 2, 2, -1);
    v.emplace_back("JG", 2, -3, 2, -3, -2);
    v.emplace_back("JG", 3, -3, -2, 1, -2);
    v.emplace_back("JG", 6, 0, -2, -2, -2);
    v.emplace_back("JG", 8, -2, 0, -2, -1);
    litchfieldLetterPosMap["JG"] = v;
    v.clear();

    // JH
    v.emplace_back("JH", 0, -2, -2, 2, -2);
    v.emplace_back("JH", 1, -2, -2, 2, -2);
    v.emplace_back("JH", 4, 0, 2, -2, -2);
    v.emplace_back("JH", 10, -3, 2, 4, 2);
    v.emplace_back("JH", 11, -3, 2, -1, 0);
    v.emplace_back("JH", 2, -1, 0, -2, -1);
    v.emplace_back("JH", 3, -3, 0, -2, 0);
    v.emplace_back("JH", 5, -2, 0, -2, 1);
    v.emplace_back("JH", 6, -2, 0, -2, 0);
    v.emplace_back("JH", 7, -2, 0, -4, -4);
    v.emplace_back("JH", 8, -2, 0, -2, 3);
    v.emplace_back("JH", 9, 0, 2, -2, 0);
    litchfieldLetterPosMap["JH"] = v;
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

    // JK
    v.emplace_back("JK", 0, 0, 0, -2, 0);
    v.emplace_back("JK", 1, 0, 0, -2, 0);
    v.emplace_back("JK", 2, -3, 0, -2, 0);
    v.emplace_back("JK", 5, -2, 0, 2, -2);
    v.emplace_back("JK", 6, 1, -2, 0, 0);
    v.emplace_back("JK", 10, -3, 2, 2, 1);
    v.emplace_back("JK", 11, -3, 2, 3, 2);
    v.emplace_back("JK", 3, -2, 0, -2, 2);
    v.emplace_back("JK", 4, -2, 0, 0, -3);
    v.emplace_back("JK", 7, -2, 0, 0, 2);
    v.emplace_back("JK", 8, -2, -2, 0, 0);
    v.emplace_back("JK", 9, 2, 0, 0, 0);
    litchfieldLetterPosMap["JK"] = v;
    v.clear();

    // JL
    v.emplace_back("JL", 0, -2, 0, -2, 0);
    v.emplace_back("JL", 1, -2, 0, -2, 0);
    v.emplace_back("JL", 2, -1, 0, 0, 0);
    v.emplace_back("JL", 3, -3, 0, 0, 0);
    v.emplace_back("JL", 4, 0, 0, 0, -2);
    v.emplace_back("JL", 5, 0, 0, 0, 0);
    v.emplace_back("JL", 6, 0, 0, 0, 2);
    v.emplace_back("JL", 9, -2, 0, 2, 0);
    v.emplace_back("JL", 10, 0, 0, -2, 2);
    v.emplace_back("JL", 11, -4, 2, -3, 2);
    v.emplace_back("JL", 7, -2, 0, 0, -3);
    v.emplace_back("JL", 8, -3, 0, 2, -2);
    litchfieldLetterPosMap["JL"] = v;
    v.clear();

    // KA
    v.emplace_back("KA", 0, -2, 1, 0, 0);
    v.emplace_back("KA", 1, -2, 1, 0, 0);
    v.emplace_back("KA", 2, 0, 1, -1, 1);
    v.emplace_back("KA", 4, -1, 0, 0, 0);
    v.emplace_back("KA", 5, -2, 0, 0, 0);
    v.emplace_back("KA", 6, 0, 0, -1, 0);
    v.emplace_back("KA", 9, 3, -2, -3, 0);
    v.emplace_back("KA", 10, -2, 0, 2, 0);
    v.emplace_back("KA", 11, 4, 2, 0, 2);
    v.emplace_back("KA", 3, 0, 1, 0, 1);
    v.emplace_back("KA", 7, 0, -1, 1, 0);
    v.emplace_back("KA", 8, 0, 2, 0, -1);
    litchfieldLetterPosMap["KA"] = v;
    v.clear();

    // KB
    v.emplace_back("KB", 0, 0, 0, 0, 0);
    v.emplace_back("KB", 1, 0, 0, 0, 0);
    v.emplace_back("KB", 4, 3, 0, -3, 2);
    v.emplace_back("KB", 5, 0, 0, 1, 0);
    v.emplace_back("KB", 6, 0, 0, 0, 0);
    v.emplace_back("KB", 7, 0, -2, 2, 0);
    v.emplace_back("KB", 9, 0, 0, 0, 0);
    v.emplace_back("KB", 10, 4, 2, -3, 0);
    v.emplace_back("KB", 11, 0, 0, -3, 2);
    v.emplace_back("KB", 2, 1, 1, 1, 0);
    v.emplace_back("KB", 3, 0, 0, -2, 2);
    v.emplace_back("KB", 8, 0, 0, 0, 2);
    litchfieldLetterPosMap["KB"] = v;
    v.clear();

    // KC
    v.emplace_back("KC", 0, 0, -2, 0, -2);
    v.emplace_back("KC", 1, 0, -2, 0, -2);
    v.emplace_back("KC", 2, 0, 0, 4, 0);
    v.emplace_back("KC", 3, 2, 2, 0, -2);
    v.emplace_back("KC", 4, 0, 0, 2, -2);
    v.emplace_back("KC", 5, 4, 0, 2, -1);
    v.emplace_back("KC", 6, -1, -2, 2, -2);
    v.emplace_back("KC", 7, 0, -2, -2, -1);
    v.emplace_back("KC", 9, 0, 0, 0, -1);
    v.emplace_back("KC", 10, 3, 2, -1, -2);
    v.emplace_back("KC", 11, 3, -2, -2, 0);
    v.emplace_back("KC", 8, 0, -1, 2, 0);
    litchfieldLetterPosMap["KC"] = v;
    v.clear();

    // KD
    v.emplace_back("KD", 0, -2, 0, -2, 0);
    v.emplace_back("KD", 1, -2, 0, -2, 0);
    v.emplace_back("KD", 2, 0, 0, 3, 0);
    v.emplace_back("KD", 4, 0, 2, -4, 2);
    v.emplace_back("KD", 5, 2, 0, -2, 2);
    v.emplace_back("KD", 6, 0, 0, -2, 1);
    v.emplace_back("KD", 9, 0, 0, -2, 0);
    v.emplace_back("KD", 11, 2, 2, -4, 3);
    v.emplace_back("KD", 3, 0, 1, 3, 2);
    v.emplace_back("KD", 7, 0, 1, 1, 0);
    v.emplace_back("KD", 8, 0, 1, 0, 0);
    v.emplace_back("KD", 10, 4, 0, -3, 0);
    litchfieldLetterPosMap["KD"] = v;
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

    // KG
    v.emplace_back("KG", 0, -1, 2, -2, -2);
    v.emplace_back("KG", 1, -1, 2, -2, -2);
    v.emplace_back("KG", 4, -2, 1, -2, 0);
    v.emplace_back("KG", 5, 3, 0, -2, -1);
    v.emplace_back("KG", 6, 0, 0, -2, -2);
    v.emplace_back("KG", 7, 0, 0, -2, -1);
    v.emplace_back("KG", 9, 2, -1, -2, -1);
    v.emplace_back("KG", 10, 1, -2, -2, -1);
    v.emplace_back("KG", 11, 0, 0, -4, 2);
    v.emplace_back("KG", 2, 3, 0, 1, -2);
    v.emplace_back("KG", 3, -1, 0, 2, -2);
    v.emplace_back("KG", 8, 1, 2, -2, 0);
    litchfieldLetterPosMap["KG"] = v;
    v.clear();

    // KH
    v.emplace_back("KH", 0, 0, 0, 2, 0);
    v.emplace_back("KH", 1, 0, 0, 2, 0);
    v.emplace_back("KH", 4, 0, 0, -3, -2);
    v.emplace_back("KH", 5, 2, 1, -2, -1);
    v.emplace_back("KH", 6, 0, 1, -2, -1);
    v.emplace_back("KH", 9, 3, -2, 0, 0);
    v.emplace_back("KH", 11, 2, -2, 0, -1);
    v.emplace_back("KH", 2, -2, 2, 0, 0);
    v.emplace_back("KH", 3, -2, -2, 3, 0);
    v.emplace_back("KH", 7, 0, 0, -3, -2);
    v.emplace_back("KH", 8, -2, 2, 0, 0);
    v.emplace_back("KH", 10, 3, -2, 2, 1);
    litchfieldLetterPosMap["KH"] = v;
    v.clear();


    // KI
    v.emplace_back("KI", 0, -1, 0, 2, 3);
    v.emplace_back("KI", 1, -1, 0, 2, 3);
    v.emplace_back("KI", 2, -2, 1, 0, 2);
    v.emplace_back("KI", 4, 0, -1, 3, 0);
    v.emplace_back("KI", 5, 0, -2, 3, -2);
    v.emplace_back("KI", 6, 0, 0, 0, -2);
    v.emplace_back("KI", 8, 0, 0, -3, -1);
    v.emplace_back("KI", 9, 4, -2, 3, -2);
    v.emplace_back("KI", 10, 0, -2, 2, 2);
    v.emplace_back("KI", 11, 0, 1, 3, 1);
    v.emplace_back("KI", 3, 1, 0, -2, -1);
    v.emplace_back("KI", 7, 0, -2, 2, -1);
    litchfieldLetterPosMap["KI"] = v;
    v.clear();

    // KJ
    v.emplace_back("KJ", 0, -1, 0, -3, 0);
    v.emplace_back("KJ", 1, -1, 0, -3, 0);
    v.emplace_back("KJ", 2, -2, 2, -3, -2);
    v.emplace_back("KJ", 4, -2, 1, 0, -1);
    v.emplace_back("KJ", 5, 0, -3, 0, 0);
    v.emplace_back("KJ", 6, 0, 2, 0, 0);
    v.emplace_back("KJ", 7, 0, 0, 0, -1);
    v.emplace_back("KJ", 9, 2, 1, 0, 0);
    v.emplace_back("KJ", 10, 4, -4, 0, -2);
    v.emplace_back("KJ", 3, 0, -2, -3, -2);
    v.emplace_back("KJ", 8, 0, 2, -2, 0);
    v.emplace_back("KJ", 11, 3, -2, -3, 1);
    litchfieldLetterPosMap["KJ"] = v;
    v.clear();

    // KK
    v.emplace_back("KK", 2, 0, 0, 0, 0);
    v.emplace_back("KK", 4, 0, 0, 3, 0);
    v.emplace_back("KK", 6, 2, -1, 0, -2);
    v.emplace_back("KK", 7, 0, 2, 0, -2);
    v.emplace_back("KK", 9, 0, 1, 0, 2);
    v.emplace_back("KK", 10, -2, 2, 3, 2);
    v.emplace_back("KK", 11, -1, 2, 0, 0);
    v.emplace_back("KK", 0, -2, 0, -2, 0);
    v.emplace_back("KK", 1, -2, 0, -2, 0);
    v.emplace_back("KK", 3, -2, -1, -3, 0);
    v.emplace_back("KK", 5, 2, -2, 2, -2);
    v.emplace_back("KK", 8, 2, 0, 1, 0);
    litchfieldLetterPosMap["KK"] = v;
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

    // LA
    v.emplace_back("LA", 0, 0, -1, 1, 1);
    v.emplace_back("LA", 1, 0, -1, 1, 1);
    v.emplace_back("LA", 2, 0, 0, 0, 0);
    v.emplace_back("LA", 3, 0, -1, 0, 2);
    v.emplace_back("LA", 4, 2, 2, 0, 0);
    v.emplace_back("LA", 5, 2, -2, 0, 0);
    v.emplace_back("LA", 6, 1, -2, 0, 0);
    v.emplace_back("LA", 7, 0, 1, 0, 0);
    v.emplace_back("LA", 11, -2, 2, -3, 1);
    v.emplace_back("LA", 8, 0, 0, 0, 0);
    v.emplace_back("LA", 9, -2, 0, -2, 0);
    v.emplace_back("LA", 10, -3, 2, -1, 0);
    litchfieldLetterPosMap["LA"] = v;
    v.clear();

    // LB
    v.emplace_back("LB", 0, -1, 0, -2, 2);
    v.emplace_back("LB", 1, -1, 0, -2, 2);
    v.emplace_back("LB", 2, -2, 0, -2, 2);
    v.emplace_back("LB", 3, 0, 0, -1, 2);
    v.emplace_back("LB", 4, 0, -2, 0, 1);
    v.emplace_back("LB", 6, 0, -1, 2, 0);
    v.emplace_back("LB", 7, 0, 0, 4, 0);
    v.emplace_back("LB", 8, -4, -2, 0, -1);
    v.emplace_back("LB", 9, 0, 0, -2, 2);
    v.emplace_back("LB", 11, 4, 4, -2, 0);
    v.emplace_back("LB", 5, 2, -1, 0, 0);
    v.emplace_back("LB", 10, 3, 2, -3, 2);
    litchfieldLetterPosMap["LB"] = v;
    v.clear();

    // LC
    v.emplace_back("LC", 0, -2, 1, 2, -2);
    v.emplace_back("LC", 1, -2, 1, 2, -2);
    v.emplace_back("LC", 3, 0, 0, -2, -2);
    v.emplace_back("LC", 4, 2, 0, 2, -2);
    v.emplace_back("LC", 5, 0, -2, 0, 0);
    v.emplace_back("LC", 6, 0, 0, -2, 1);
    v.emplace_back("LC", 7, 0, -1, 0, -2);
    v.emplace_back("LC", 11, 4, 0, 1, 0);
    v.emplace_back("LC", 2, -2, 0, 0, -4);
    v.emplace_back("LC", 8, 1, -1, -2, 0);
    v.emplace_back("LC", 9, -2, 0, 0, 0);
    v.emplace_back("LC", 10, 2, 2, -3, -2);
    litchfieldLetterPosMap["LC"] = v;
    v.clear();

    // LD
    v.emplace_back("LD", 0, 0, 0, -2, 0);
    v.emplace_back("LD", 1, 0, 0, -2, 0);
    v.emplace_back("LD", 3, 0, 2, -1, 2);
    v.emplace_back("LD", 4, 0, 0, 0, 0);
    v.emplace_back("LD", 5, 0, -2, -2, 2);
    v.emplace_back("LD", 7, 0, 0, 0, 1);
    v.emplace_back("LD", 8, -2, -2, 0, 1);
    v.emplace_back("LD", 11, 3, 2, 0, 3);
    v.emplace_back("LD", 2, -1, 0, 0, 2);
    v.emplace_back("LD", 6, 0, -1, 0, 0);
    v.emplace_back("LD", 9, -1, 0, 0, 2);
    v.emplace_back("LD", 10, 2, 2, -2, 1);
    litchfieldLetterPosMap["LD"] = v;
    v.clear();

    // LE
    v.emplace_back("LE", 0, 0, 0, 3, 2);
    v.emplace_back("LE", 1, 0, 0, 3, 2);
    v.emplace_back("LE", 2, 0, 0, 0, 2);
    v.emplace_back("LE", 3, 0, 0, -3, 3);
    v.emplace_back("LE", 4, 0, 0, 0, 0);
    v.emplace_back("LE", 5, 2, 0, 2, -2);
    v.emplace_back("LE", 7, 0, -2, -2, 0);
    v.emplace_back("LE", 9, -2, -2, 0, 0);
    v.emplace_back("LE", 11, 4, 0, -3, 2);
    v.emplace_back("LE", 6, -1, 0, -2, 0);
    v.emplace_back("LE", 8, 0, 1, -1, 0);
    v.emplace_back("LE", 10, 2, 2, 2, -2);
    litchfieldLetterPosMap["LE"] = v;
    v.clear();

    // LF
    v.emplace_back("LF", 0, -2, 0, -2, 0);
    v.emplace_back("LF", 1, -2, 0, -2, 0);
    v.emplace_back("LF", 2, -2, 0, 2, 0);
    v.emplace_back("LF", 3, 0, 2, 2, 0);
    v.emplace_back("LF", 5, -2, 0, 0, 2);
    v.emplace_back("LF", 8, 0, 2, -4, 0);
    v.emplace_back("LF", 9, -1, 1, -1, 0);
    v.emplace_back("LF", 11, 4, 0, -3, 1);
    v.emplace_back("LF", 4, 0, 0, 0, -1);
    v.emplace_back("LF", 6, 0, -2, 2, -2);
    v.emplace_back("LF", 7, 0, 0, 0, -2);
    v.emplace_back("LF", 10, 2, 2, 3, 0);
    litchfieldLetterPosMap["LF"] = v;
    v.clear();

    // LG
    v.emplace_back("LG", 0, -2, 0, -2, -2);
    v.emplace_back("LG", 1, -2, 0, -2, -2);
    v.emplace_back("LG", 2, 0, 0, -3, -2);
    v.emplace_back("LG", 3, 1, 0, -2, -1);
    v.emplace_back("LG", 4, 0, 0, -2, 0);
    v.emplace_back("LG", 5, -2, 2, 1, -1);
    v.emplace_back("LG", 11, 2, 3, -3, 0);
    v.emplace_back("LG", 6, 0, 0, -2, 0);
    v.emplace_back("LG", 7, -1, -1, 1, -2);
    v.emplace_back("LG", 8, -2, -2, -2, 0);
    v.emplace_back("LG", 9, 2, 0, 1, 1);
    v.emplace_back("LG", 10, 0, 4, 2, 1);
    litchfieldLetterPosMap["LG"] = v;
    v.clear();

    // LH
    v.emplace_back("LH", 0, 0, 0, 1, -1);
    v.emplace_back("LH", 1, 0, 0, 1, -1);
    v.emplace_back("LH", 3, 0, 0, 3, -3);
    v.emplace_back("LH", 4, 0, 0, -3, -2);
    v.emplace_back("LH", 5, -3, 0, -2, -2);
    v.emplace_back("LH", 6, 0, 0, 0, 0);
    v.emplace_back("LH", 7, 0, 0, -2, -2);
    v.emplace_back("LH", 11, 3, 3, -3, 0);
    v.emplace_back("LH", 2, -2, 0, 2, 2);
    v.emplace_back("LH", 8, 0, -2, 0, 0);
    v.emplace_back("LH", 9, -2, 0, -2, -2);
    v.emplace_back("LH", 10, 4, 2, 1, 0);
    litchfieldLetterPosMap["LH"] = v;
    v.clear();

    // LI
    v.emplace_back("LI", 0, 0, 0, 2, 2);
    v.emplace_back("LI", 1, 0, 0, 2, 2);
    v.emplace_back("LI", 2, -2, 0, -4, 0);
    v.emplace_back("LI", 3, 0, 0, -2, -2);
    v.emplace_back("LI", 4, 0, -2, 1, 0);
    v.emplace_back("LI", 5, -2, 0, 0, -2);
    v.emplace_back("LI", 6, 2, -2, 1, -2);
    v.emplace_back("LI", 7, 0, -2, 1, 0);
    v.emplace_back("LI", 8, -2, -2, 0, 0);
    v.emplace_back("LI", 10, -4, 2, 0, 2);
    v.emplace_back("LI", 11, 0, 2, -2, 2);
    v.emplace_back("LI", 9, -2, 1, 2, 2);
    litchfieldLetterPosMap["LI"] = v;
    v.clear();

    // LJ
    v.emplace_back("LJ", 3, 0, 0, -4, 0);
    v.emplace_back("LJ", 6, -3, 0, 1, -2);
    v.emplace_back("LJ", 7, 0, 0, 0, -2);
    v.emplace_back("LJ", 11, 0, 2, -4, 1);
    v.emplace_back("LJ", 0, -2, 0, -2, 0);
    v.emplace_back("LJ", 1, -2, 0, -2, 0);
    v.emplace_back("LJ", 2, -2, 2, 2, -2);
    v.emplace_back("LJ", 4, 0, 0, -2, 0);
    v.emplace_back("LJ", 5, -2, 0, 0, 0);
    v.emplace_back("LJ", 8, 0, 0, 0, 0);
    v.emplace_back("LJ", 9, -1, 1, -3, 0);
    v.emplace_back("LJ", 10, 0, 2, 4, -2);
    litchfieldLetterPosMap["LJ"] = v;
    v.clear();

    // LK
    v.emplace_back("LK", 0, 0, -2, 2, 0);
    v.emplace_back("LK", 1, 0, -2, 2, 0);
    v.emplace_back("LK", 2, -2, 0, 1, 0);
    v.emplace_back("LK", 6, 2, 0, 3, 2);
    v.emplace_back("LK", 7, 0, 2, 0, 0);
    v.emplace_back("LK", 9, 0, 2, 4, 0);
    v.emplace_back("LK", 10, 0, 2, -2, 2);
    v.emplace_back("LK", 11, 0, 2, -2, 0);
    v.emplace_back("LK", 3, 0, -2, 2, 0);
    v.emplace_back("LK", 4, 0, 0, -2, 0);
    v.emplace_back("LK", 5, -2, 2, 0, 0);
    v.emplace_back("LK", 8, -2, 0, -2, 0);
    litchfieldLetterPosMap["LK"] = v;
    v.clear();

    // LL
    v.emplace_back("LL", 0, -1, 0, -2, 0);
    v.emplace_back("LL", 1, -1, 0, -2, 0);
    v.emplace_back("LL", 2, -2, 0, -2, 0);
    v.emplace_back("LL", 5, -2, 2, 2, 0);
    v.emplace_back("LL", 6, 0, 0, 0, -2);
    v.emplace_back("LL", 7, 0, 0, 0, -2);
    v.emplace_back("LL", 8, -2, -2, -2, -2);
    v.emplace_back("LL", 9, 1, 0, -2, 0);
    v.emplace_back("LL", 11, -3, 2, -4, 2);
    v.emplace_back("LL", 3, 0, -2, -2, -1);
    v.emplace_back("LL", 4, -2, -3, -1, 1);
    v.emplace_back("LL", 10, 2, 2, 2, 2);
    litchfieldLetterPosMap["LL"] = v;
    v.clear();

    // MA
    v.emplace_back("MA", 0, -2, 0, -1, 2);
    v.emplace_back("MA", 1, -2, 0, -1, 2);
    v.emplace_back("MA", 2, -2, 0, -2, 0);
    v.emplace_back("MA", 4, -2, 2, 4, 0);
    v.emplace_back("MA", 5, 0, 0, 2, 1);
    v.emplace_back("MA", 6, 2, 2, 0, 0);
    v.emplace_back("MA", 8, -2, 0, 0, 0);
    v.emplace_back("MA", 9, 2, 2, -2, -2);
    v.emplace_back("MA", 10, 2, 2, -2, 0);
    v.emplace_back("MA", 11, 0, 2, 0, 0);
    v.emplace_back("MA", 3, 0, 0, 0, 0);
    v.emplace_back("MA", 7, -2, 0, -2, 0);
    litchfieldLetterPosMap["MA"] = v;
    v.clear();

    // MB
    v.emplace_back("MB", 0, -2, 0, -1, 2);
    v.emplace_back("MB", 1, -2, 0, -1, 2);
    v.emplace_back("MB", 2, 0, 0, -2, 2);
    v.emplace_back("MB", 4, 0, 2, 0, 1);
    v.emplace_back("MB", 5, 0, 0, 0, 0);
    v.emplace_back("MB", 6, 1, 0, 0, 0);
    v.emplace_back("MB", 7, 0, 2, -2, 2);
    v.emplace_back("MB", 9, 0, -2, -2, 2);
    v.emplace_back("MB", 11, 2, 2, -2, 2);
    v.emplace_back("MB", 3, 0, 0, -3, 2);
    v.emplace_back("MB", 8, -2, 0, 0, 0);
    v.emplace_back("MB", 10, 0, 0, -2, 0);
    litchfieldLetterPosMap["MB"] = v;
    v.clear();

    // MC
    v.emplace_back("MC", 0, -2, 0, 0, -2);
    v.emplace_back("MC", 1, -2, 0, 0, -2);
    v.emplace_back("MC", 3, -2, 2, 0, -2);
    v.emplace_back("MC", 4, -2, 0, 0, -2);
    v.emplace_back("MC", 5, -2, 0, -1, -2);
    v.emplace_back("MC", 6, 2, 3, -2, 1);
    v.emplace_back("MC", 8, -1, 1, 0, -2);
    v.emplace_back("MC", 9, 2, 0, -3, 0);
    v.emplace_back("MC", 11, -1, 2, -2, 0);
    v.emplace_back("MC", 2, -2, 0, 2, -2);
    v.emplace_back("MC", 7, -2, 1, -1, -2);
    v.emplace_back("MC", 10, 0, 2, -2, 0);
    litchfieldLetterPosMap["MC"] = v;
    v.clear();


    // MD
    v.emplace_back("MD", 0, 0, 0, -2, 0);
    v.emplace_back("MD", 1, 0, 0, -2, 0);
    v.emplace_back("MD", 2, 0, 0, 0, 2);
    v.emplace_back("MD", 3, -2, 0, 0, 1);
    v.emplace_back("MD", 4, 0, -2, -2, 0);
    v.emplace_back("MD", 5, 0, 0, -2, 2);
    v.emplace_back("MD", 6, 0, 3, 0, 0);
    v.emplace_back("MD", 7, 0, 0, 0, 0);
    v.emplace_back("MD", 8, -2, -1, 0, 2);
    v.emplace_back("MD", 10, -1, 2, -2, 0);
    v.emplace_back("MD", 11, 3, 1, -2, 2);
    v.emplace_back("MD", 9, -3, 2, -4, 2);
    litchfieldLetterPosMap["MD"] = v;
    v.clear();

    // ME
    v.emplace_back("ME", 0, 0, 0, 0, 2);
    v.emplace_back("ME", 1, 0, 0, 0, 2);
    v.emplace_back("ME", 2, -2, 0, 0, 2);
    v.emplace_back("ME", 4, -2, 1, 2, -2);
    v.emplace_back("ME", 5, -2, 0, 0, -2);
    v.emplace_back("ME", 6, -2, 3, -2, -2);
    v.emplace_back("ME", 8, -2, 0, 0, -1);
    v.emplace_back("ME", 9, -2, -2, 0, 0);
    v.emplace_back("ME", 11, -2, 2, -4, 2);
    v.emplace_back("ME", 3, -1, 0, -3, 4);
    v.emplace_back("ME", 7, -1, 2, -2, -2);
    v.emplace_back("ME", 10, 1, 2, 2, 0);
    litchfieldLetterPosMap["ME"] = v;
    v.clear();


    // MF
    v.emplace_back("MF", 0, 0, -1, 0, 0);
    v.emplace_back("MF", 1, 0, -1, 0, 0);
    v.emplace_back("MF", 2, -3, -2, 0, 2);
    v.emplace_back("MF", 3, 0, 0, 4, 0);
    v.emplace_back("MF", 4, 0, 0, 3, -2);
    v.emplace_back("MF", 5, -2, 1, 0, 2);
    v.emplace_back("MF", 6, 2, 0, 2, 0);
    v.emplace_back("MF", 8, -2, 0, 0, 0);
    v.emplace_back("MF", 9, 0, 2, 0, -2);
    v.emplace_back("MF", 10, 2, 2, 0, -2);
    v.emplace_back("MF", 11, 4, 0, -4, 0);
    v.emplace_back("MF", 7, -2, 0, 0, -2);
    litchfieldLetterPosMap["MF"] = v;
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

    // MH
    v.emplace_back("MH", 0, -2, 0, 2, 0);
    v.emplace_back("MH", 1, -2, 0, 2, 0);
    v.emplace_back("MH", 2, -2, 0, -3, 1);
    v.emplace_back("MH", 3, -2, 2, -2, 0);
    v.emplace_back("MH", 4, 0, 2, 0,-2);
    v.emplace_back("MH", 6, 0, 0, 0, 2);
    v.emplace_back("MH", 8, -2, 0, -2, 0);
    v.emplace_back("MH", 9, -3, -2, -2, -2);
    v.emplace_back("MH", 11, 3, 2, -2, 0);
    v.emplace_back("MH", 5, -2, 2, -3, 1);
    v.emplace_back("MH", 7, 0, 0, -2, -3);
    v.emplace_back("MH", 10, -2, 2, 4, 0);
    litchfieldLetterPosMap["MH"] = v;
    v.clear();

    // MI
    v.emplace_back("MI", 0, 0, 0, 2, 2);
    v.emplace_back("MI", 1, 0, 0, 2, 2);
    v.emplace_back("MI", 3, -2, 0, 0, 0);
    v.emplace_back("MI", 4, 0, 2, 0, -2);
    v.emplace_back("MI", 6, 0, 2, 1, -2);
    v.emplace_back("MI", 7, -2, 0, 2, -2);
    v.emplace_back("MI", 8, -2, 0, 0, -2);
    v.emplace_back("MI", 9, 0, 2, -2, 2);
    v.emplace_back("MI", 10, 0, 2, -2, 0);
    v.emplace_back("MI", 11, 3, 2, -3, 2);
    v.emplace_back("MI", 2, -2, 0, -2, 0);
    v.emplace_back("MI", 5, -2, 0, 2, 2);
    litchfieldLetterPosMap["MI"] = v;
    v.clear();

    // MJ
    v.emplace_back("MJ", 0, 1, 1, 0, -1);
    v.emplace_back("MJ", 1, 1, 1, 0, -1);
    v.emplace_back("MJ", 3, -2, 2, -3, -2);
    v.emplace_back("MJ", 4, 0, 0, 0, -2);
    v.emplace_back("MJ", 6, 0, 0, 1, -1);
    v.emplace_back("MJ", 9, 3, 0, 0, 0);
    v.emplace_back("MJ", 10, 2, 2, 0, -2);
    v.emplace_back("MJ", 11, 1, 2, -2, 0);
    v.emplace_back("MJ", 2, -1, 0, -3, 0);
    v.emplace_back("MJ", 5, 0, 0, -2, -2);
    v.emplace_back("MJ", 7, -1, 2, -2, -1);
    v.emplace_back("MJ", 8, -2, 0, -3, 0);
    litchfieldLetterPosMap["MJ"] = v;
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

    // ML
    v.emplace_back("ML", 2, -1, 1, -1, 0);
    v.emplace_back("ML", 3, 1, -3, -2, -1);
    v.emplace_back("ML", 4, 0, 2, 0, 0);
    v.emplace_back("ML", 5, 0, 0, 2, -2);
    v.emplace_back("ML", 6, -1, 0, -3, -1);
    v.emplace_back("ML", 8, -2, -1, -1, 0);
    v.emplace_back("ML", 9, 0, 1, 0, 0);
    v.emplace_back("ML", 11, 4, 2, -3, 2);
    v.emplace_back("ML", 0, -2, 0, -2, 0);
    v.emplace_back("ML", 1, -2, 0, -2, 0);
    v.emplace_back("ML", 7, 0, 0, 2, -2);
    v.emplace_back("ML", 10, -2, 2, -2, 2);
    litchfieldLetterPosMap["ML"] = v;
    v.clear();

    // NA
    v.emplace_back("NA", 0, -2, 0, 2, 2);
    v.emplace_back("NA", 1, -2, 0, 2, 2);
    v.emplace_back("NA", 2, -2, 0, 2, 1);
    v.emplace_back("NA", 4, 0, 2, 3, 0);
    v.emplace_back("NA", 5, -2, 2, 3, 0);
    v.emplace_back("NA", 6, 4, 0, 0, 0);
    v.emplace_back("NA", 7, 0, 0, 2, 1);
    v.emplace_back("NA", 8, -2, -2, 0, 0);
    v.emplace_back("NA", 9, -3, 2, 1, 0);
    v.emplace_back("NA", 10, 2, 0, -3, 2);
    v.emplace_back("NA", 11, 0, 0, -2, 2);
    v.emplace_back("NA", 3, 0, 2, 0, 2);
    litchfieldLetterPosMap["NA"] = v;
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

    // NC
    v.emplace_back("NC", 0, 0, 0, 0, 0);
    v.emplace_back("NC", 1, 0, 0, 0, 0);
    v.emplace_back("NC", 2, 0, -2, 0, -2);
    v.emplace_back("NC", 3, 0, 0, 0, -1);
    v.emplace_back("NC", 4, 2, 2, 0, -2);
    v.emplace_back("NC", 5, 0, 0, -2, -2);
    v.emplace_back("NC", 8, -3, -2, -2, -1);
    v.emplace_back("NC", 9, 0, 0, -3, -1);
    v.emplace_back("NC", 11, -2, -2, -2, -1);
    v.emplace_back("NC", 6, 0, 0, 4, -1);
    v.emplace_back("NC", 7, 0, 0, -1, -2);
    v.emplace_back("NC", 10, 0, -2, -2, -1);
    litchfieldLetterPosMap["NC"] = v;
    v.clear();

    // ND
    v.emplace_back("ND", 0, -2, 1, -2, -2);
    v.emplace_back("ND", 1, -2, 1, -2, -2);
    v.emplace_back("ND", 4, 0, 0, 2, 2);
    v.emplace_back("ND", 5, 0, 2, -2, 2);
    v.emplace_back("ND", 6, 2, 1, 4, 0);
    v.emplace_back("ND", 8, -2, -1, 0, 2);
    v.emplace_back("ND", 9, -2, 2, -3, 2);
    v.emplace_back("ND", 10, -2, -2, -3, 2);
    v.emplace_back("ND", 11, 0, -2, 0, -2);
    v.emplace_back("ND", 2, 0, 0, -1, 0);
    v.emplace_back("ND", 3, 0, 2, -2, 2);
    v.emplace_back("ND", 7, 0, 0, 0, 0);
    litchfieldLetterPosMap["ND"] = v;
    v.clear();

    // NE
    v.emplace_back("NE", 0, 0, 0, 0, 2);
    v.emplace_back("NE", 1, 0, 0, 0, 2);
    v.emplace_back("NE", 2, 1, -2, -4, 2);
    v.emplace_back("NE", 4, 0, 0, 0, 0);
    v.emplace_back("NE", 7, 0, 0, -1, 1);
    v.emplace_back("NE", 9, -2, 2, 0, 3);
    v.emplace_back("NE", 10, 0, 0, 1, -2);
    v.emplace_back("NE", 11, 2, 0, 3, 2);
    v.emplace_back("NE", 3, 2, 1, -2, 2);
    v.emplace_back("NE", 5, 0, -3, -2, 0);
    v.emplace_back("NE", 6, 3, 2, -2, -2);
    v.emplace_back("NE", 8, -2, -2, -1, -1);
    litchfieldLetterPosMap["NE"] = v;
    v.clear();

    // NF
    v.emplace_back("NF", 0, -2, 0, 0, 0);
    v.emplace_back("NF", 1, -2, 0, 0, 0);
    v.emplace_back("NF", 4, 3, 0, 2, -2);
    v.emplace_back("NF", 5, -2, 2, 3, 2);
    v.emplace_back("NF", 7, 0, 0, 4, -3);
    v.emplace_back("NF", 8, -2, 0, 0, 0);
    v.emplace_back("NF", 9, -2, 2, 0, 0);
    v.emplace_back("NF", 10, -2, 0, 0, 0);
    v.emplace_back("NF", 11, 0, -2, -4, 2);
    v.emplace_back("NF", 2, 0, -2, 0, -2);
    v.emplace_back("NF", 3, 0, 2, 2, 2);
    v.emplace_back("NF", 6, 2, 0, 0, -2);
    litchfieldLetterPosMap["NF"] = v;
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

    // NH
    v.emplace_back("NH", 0, -2, 2, 2, -2);
    v.emplace_back("NH", 1, -2, 2, 2, -2);
    v.emplace_back("NH", 4, 0, -2, -2, 0);
    v.emplace_back("NH", 5, -2, 2, 2, 0);
    v.emplace_back("NH", 6, 0, -2, -1, 2);
    v.emplace_back("NH", 9, -2, 0, -2, 0);
    v.emplace_back("NH", 10, 1, -2, 1, 2);
    v.emplace_back("NH", 11, -2, -1, 2, -2);
    v.emplace_back("NH", 2, 0, 0, -3, 2);
    v.emplace_back("NH", 3, -2, 2, 0, 2);
    v.emplace_back("NH", 7, -2, 1, -2, -2);
    v.emplace_back("NH", 8, -2, 0, -2, 0);
    litchfieldLetterPosMap["NH"] = v;
    v.clear();

    // NI
    v.emplace_back("NI", 0, 2, -2, 2, 1);
    v.emplace_back("NI", 1, 2, -2, 2, 1);
    v.emplace_back("NI", 5, -2, 2, 2, -2);
    v.emplace_back("NI", 6, 0, 1, 1, 0);
    v.emplace_back("NI", 7, 0, 0, 1, -2);
    v.emplace_back("NI", 8, -2, 0, 0, -2);
    v.emplace_back("NI", 9, -3, 2, 3, 2);
    v.emplace_back("NI", 10, -2, -2, 2, 0);
    v.emplace_back("NI", 11, 0, -1, -1, 2);
    v.emplace_back("NI", 2, -2, -2, -2, 0);
    v.emplace_back("NI", 3, -2, 0, 0, 2);
    v.emplace_back("NI", 4, -2, -2, 1, -2);
    litchfieldLetterPosMap["NI"] = v;
    v.clear();

    // NJ
    v.emplace_back("NJ", 0, -2, 2, -2, 0);
    v.emplace_back("NJ", 1, -2, 2, -2, 0);
    v.emplace_back("NJ", 2, -1, -2, -2, 0);
    v.emplace_back("NJ", 3, -2, 0, 0, -2);
    v.emplace_back("NJ", 4, 0, 0, 0, -2);
    v.emplace_back("NJ", 5, -3, 0, 0, -2);
    v.emplace_back("NJ", 6, 3, 2, 2, -2);
    v.emplace_back("NJ", 9, -2, 2, 2, -2);
    v.emplace_back("NJ", 10, -2, -2, -2, 0);
    v.emplace_back("NJ", 11, -2, 0, -4, 0);
    v.emplace_back("NJ", 7, 0, 0, 0, 0);
    v.emplace_back("NJ", 8, -3, -2, -2, 0);
    litchfieldLetterPosMap["NJ"] = v;
    v.clear();

    // NK
    v.emplace_back("NK", 0, -2, 2, 0, 0);
    v.emplace_back("NK", 1, -2, 2, 0, 0);
    v.emplace_back("NK", 2, 0, 0, -2, 2);
    v.emplace_back("NK", 4, 0, 0, 0, 0);
    v.emplace_back("NK", 6, 2, 0, 2, -2);
    v.emplace_back("NK", 9, -1, 2, -2, 0);
    v.emplace_back("NK", 10, -2, 0, -2, 2);
    v.emplace_back("NK", 11, -4, 0, 4, 0);
    v.emplace_back("NK", 3, -2, 2, 0, 2);
    v.emplace_back("NK", 5, -2, 2, 2, -2);
    v.emplace_back("NK", 7, 0, -2, 2, 2);
    v.emplace_back("NK", 8, -2, -1, 0, -2);
    litchfieldLetterPosMap["NK"] = v;
    v.clear();

    // NL
    v.emplace_back("NL", 0, -1, 1, -2, -2);
    v.emplace_back("NL", 1, -1, 1, -2, -2);
    v.emplace_back("NL", 2, -1, 0, -2, -2);
    v.emplace_back("NL", 3, -2, 2, 0, 0);
    v.emplace_back("NL", 4, -2, 0, -2, 0);
    v.emplace_back("NL", 5, -4, 2, 0, -2);
    v.emplace_back("NL", 7, 0, 0, -2, 0);
    v.emplace_back("NL", 8, -1, 0, -2, 0);
    v.emplace_back("NL", 9, -2, 2, 0, 0);
    v.emplace_back("NL", 11, 0, 0, 2, 2);
    v.emplace_back("NL", 6, 3, 2, 0, -2);
    v.emplace_back("NL", 10, -2, -2, 0, 2);
    litchfieldLetterPosMap["NL"] = v;
    v.clear();

    // OA
    v.emplace_back("OA", 0, 1, 0, 0, 0);
    v.emplace_back("OA", 1, 1, 0, 0, 0);
    v.emplace_back("OA", 5, 0, 0, 0, 2);
    v.emplace_back("OA", 6, 0, 0, 0, 2);
    v.emplace_back("OA", 9, 2, 0, -2, -2);
    v.emplace_back("OA", 10, 2, 2, -2, 2);
    v.emplace_back("OA", 11, 2, 2, 0, 0);
    v.emplace_back("OA", 2, 0, 0, 0, 1);
    v.emplace_back("OA", 3, 0, 0, 2, -2);
    v.emplace_back("OA", 4, 0, 0, 2, 2);
    v.emplace_back("OA", 7, -2, 0, 0, 0);
    v.emplace_back("OA", 8, -3, -1, 2, -2);
    litchfieldLetterPosMap["OA"] = v;
    v.clear();

    // OB
    v.emplace_back("OB", 0, 0, -1, 0, 2);
    v.emplace_back("OB", 1, 0, -1, 0, 2);
    v.emplace_back("OB", 2, -1, -1, 0, 2);
    v.emplace_back("OB", 3, 0, 0, 0, 2);
    v.emplace_back("OB", 4, -2, -2, 0, 2);
    v.emplace_back("OB", 5, 3, -2, -2, 0);
    v.emplace_back("OB", 6, -2, 2, 0, 0);
    v.emplace_back("OB", 7, -1, -1, 2, 0);
    v.emplace_back("OB", 9, 3, -2, 1, 0);
    v.emplace_back("OB", 11, 2, 2, -2, 0);
    v.emplace_back("OB", 8, -2, -2, 0, -2);
    v.emplace_back("OB", 10, 0, -2, -2, 2);
    litchfieldLetterPosMap["OB"] = v;
    v.clear();

    // OC
    v.emplace_back("OC", 0, 0, 0, 0, -2);
    v.emplace_back("OC", 1, 0, 0, 0, -2);
    v.emplace_back("OC", 2, -1, -1, 2, -1);
    v.emplace_back("OC", 4, 0, -2, 0, -1);
    v.emplace_back("OC", 5, -2, 2, -3, -2);
    v.emplace_back("OC", 7, -1, -2, -2, 0);
    v.emplace_back("OC", 9, 3, -1, -3, 0);
    v.emplace_back("OC", 10, 2, -2, 0, -2);
    v.emplace_back("OC", 11, 2, 0, -1, -2);
    v.emplace_back("OC", 3, 0, 0, 0, -2);
    v.emplace_back("OC", 6, 0, 2, 0, -1);
    v.emplace_back("OC", 8, 0, -2, 1, -1);
    litchfieldLetterPosMap["OC"] = v;
    v.clear();

    // OD
    v.emplace_back("OD", 0, 0, 0, -2, 0);
    v.emplace_back("OD", 1, 0, 0, -2, 0);
    v.emplace_back("OD", 2, -1, 0, -2, 2);
    v.emplace_back("OD", 4, 2, -1, 0, 0);
    v.emplace_back("OD", 5, -2, 2, -2, 0);
    v.emplace_back("OD", 6, -1, 0, -1, 1);
    v.emplace_back("OD", 8, -1, 0, 0, 0);
    v.emplace_back("OD", 9, 2, 0, 3, 0);
    v.emplace_back("OD", 11, 0, 0, -2, 2);
    v.emplace_back("OD", 3, 0, 0, -2, 1);
    v.emplace_back("OD", 7, -1, 0, 0, 0);
    v.emplace_back("OD", 10, -2, 0, -2, 0);
    litchfieldLetterPosMap["OD"] = v;
    v.clear();

    // OE
    v.emplace_back("OE", 0, 0, 0, 2, 2);
    v.emplace_back("OE", 1, 0, 0, 2, 2);
    v.emplace_back("OE", 2, 3, -3, -3, 2);
    v.emplace_back("OE", 4, 0, 0, 0, 0);
    v.emplace_back("OE", 7, -2, 0, -2, 0);
    v.emplace_back("OE", 8, -2, -2, 0, -3);
    v.emplace_back("OE", 9, 4, 0, 1, 1);
    v.emplace_back("OE", 11, 0, 2, -2, 0);
    v.emplace_back("OE", 3, 0, 0, -2, 4);
    v.emplace_back("OE", 5, -4, 2, 0, -2);
    v.emplace_back("OE", 6, 3, 2, 0, 2);
    v.emplace_back("OE", 10, -3, 2, 2, 0);
    litchfieldLetterPosMap["OE"] = v;
    v.clear();

    // OF
    v.emplace_back("OF", 0, -2, 0, -2, 0);
    v.emplace_back("OF", 1, -2, 0, -2, 0);
    v.emplace_back("OF", 2, -1, -2, 0, 0);
    v.emplace_back("OF", 4, 0, -2, 0, 0);
    v.emplace_back("OF", 5, 0, 1, -3, 2);
    v.emplace_back("OF", 8, -2, -2, 0, -1);
    v.emplace_back("OF", 9, 2, 0, -4, 0);
    v.emplace_back("OF", 10, 4, 0, 3, -2);
    v.emplace_back("OF", 11, 0, 2, 0, 0);
    v.emplace_back("OF", 3, 2, 2, 0, -2);
    v.emplace_back("OF", 6, 0, -4, 4, -2);
    v.emplace_back("OF", 7, -2, -1, 0, -3);
    litchfieldLetterPosMap["OF"] = v;
    v.clear();

    // OG
    v.emplace_back("OG", 0, -2, 0, -2, -2);
    v.emplace_back("OG", 1, -2, 0, -2, -2);
    v.emplace_back("OG", 4, -2, 0, 0, -2);
    v.emplace_back("OG", 7, -1, -2, -2, -2);
    v.emplace_back("OG", 9, 0, -2, -2, -2);
    v.emplace_back("OG", 11, 0, 0, -3, 0);
    v.emplace_back("OG", 2, 0, 0, -2, -2);
    v.emplace_back("OG", 3, 0, 1, -3, -2);
    v.emplace_back("OG", 5, -3, 2, 3, -2);
    v.emplace_back("OG", 6, 2, 2, -1, 0);
    v.emplace_back("OG", 8, 0, -2, -2, 0);
    v.emplace_back("OG", 10, -2, 0, 2, -2);
    litchfieldLetterPosMap["OG"] = v;
    v.clear();

    // OH
    v.emplace_back("OH", 0, 0, 0, 2, -2);
    v.emplace_back("OH", 1, 0, 0, 2, -2);
    v.emplace_back("OH", 2, -1, 0, -2, 3);
    v.emplace_back("OH", 4, 2, 0, 0, -2);
    v.emplace_back("OH", 5, -3, 0, 0, 0);
    v.emplace_back("OH", 6, -2, 2, -2, 0);
    v.emplace_back("OH", 9, 0, 1, 1, -1);
    v.emplace_back("OH", 11, 0, 2, -2, -2);
    v.emplace_back("OH", 3, 0, 0, 0, 1);
    v.emplace_back("OH", 7, 0, -2, -2, -2);
    v.emplace_back("OH", 8, -3, -2, -2, 0);
    v.emplace_back("OH", 10, -2, 0, 2, 0);
    litchfieldLetterPosMap["OH"] = v;
    v.clear();

    // OI
    v.emplace_back("OI", 0, 0, 0, 2, 0);
    v.emplace_back("OI", 1, 0, 0, 2, 0);
    v.emplace_back("OI", 2, 0, 2, 0, 2);
    v.emplace_back("OI", 4, 0, 0, 2, -1);
    v.emplace_back("OI", 6, 0, -2, 0, -2);
    v.emplace_back("OI", 8, -2, 0, 0, -1);
    v.emplace_back("OI", 9, 2, -2, 2, 2);
    v.emplace_back("OI", 11, 2, 1, -4, 0);
    v.emplace_back("OI", 3, 0, 0, 0, -2);
    v.emplace_back("OI", 5, 0, -3, 3, -2);
    v.emplace_back("OI", 7, 3, -4, -2, 0);
    v.emplace_back("OI", 10, 2, 0, -1, 2);
    litchfieldLetterPosMap["OI"] = v;
    v.clear();

    // OJ
    v.emplace_back("OJ", 0, -1, 0, -2, -1);
    v.emplace_back("OJ", 1, -1, 0, -2, -1);
    v.emplace_back("OJ", 3, 0, 1, -2, 0);
    v.emplace_back("OJ", 5, -3, 2, -1, -2);
    v.emplace_back("OJ", 6, 0, -2, 0, 0);
    v.emplace_back("OJ", 7, 0, 0, 3, -2);
    v.emplace_back("OJ", 8, 0, 0, -4, 0);
    v.emplace_back("OJ", 10, 1, 0, 3, 2);
    v.emplace_back("OJ", 11, 0, 1, -4, 0);
    v.emplace_back("OJ", 2, -1, 1, -2, -1);
    v.emplace_back("OJ", 4, -1, 0, 0, -1);
    v.emplace_back("OJ", 5, 3, 0, 0, 0);
    litchfieldLetterPosMap["OJ"] = v;
    v.clear();

    // OK
    v.emplace_back("OK", 0, 0, 0, -2, 0);
    v.emplace_back("OK", 1, 0, 0, -2, 0);
    v.emplace_back("OK", 3, 1, 0, 0, -2);
    v.emplace_back("OK", 7, 0, 0, 0, 0);
    v.emplace_back("OK", 8, -2, -1, 0, 0);
    v.emplace_back("OK", 9, -2, 2, -2, 2);
    v.emplace_back("OK", 10, 0, 1, 3, 0);
    v.emplace_back("OK", 11, 3, 0, 2, 2);
    v.emplace_back("OK", 2, -2, -1, 2, 0);
    v.emplace_back("OK", 4, -2, 2, 0, -2);
    v.emplace_back("OK", 5, -2, 4, 0, -4);
    v.emplace_back("OK", 6, -2, -2, 0, -2);
    litchfieldLetterPosMap["OK"] = v;
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

    // PA
    v.emplace_back("PA", 0, -2, 2, -2, 0);
    v.emplace_back("PA", 1, 0, -2, 0, -2);
    v.emplace_back("PA", 2, -2, -2, 2, 2);
    v.emplace_back("PA", 3, 0, 1, -2, -1);
    v.emplace_back("PA", 4, 0, 2, 0, 0);
    v.emplace_back("PA", 5, 0, 0, 0, 2);
    v.emplace_back("PA", 6, 3, 0, -3, 0);
    v.emplace_back("PA", 7, 0, 4, 0, 0);
    v.emplace_back("PA", 8, -4, 2, 0, 0);
    v.emplace_back("PA", 10, 0, 0, -4, 0);
    v.emplace_back("PA", 11, 0, 1, -2, 2);
    v.emplace_back("PA", 9, 2, 0, -2, 0);
    litchfieldLetterPosMap["PA"] = v;
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

    // PD
    v.emplace_back("PD", 0, 0, 1, -2, -2);
    v.emplace_back("PD", 1, 0, 1, -2, -2);
    v.emplace_back("PD", 2, 0, 0, 0, 0);
    v.emplace_back("PD", 3, 1, 2, -1, 2);
    v.emplace_back("PD", 4, 0, 2, 0, 2);
    v.emplace_back("PD", 5, 2, 0, -2, 2);
    v.emplace_back("PD", 6, -1, 2, -2, 0);
    v.emplace_back("PD", 8, -3, -2, -4, 2);
    v.emplace_back("PD", 11, 4, -2, -2, 4);
    v.emplace_back("PD", 7, 0, 1, -2, 0);
    v.emplace_back("PD", 9, -2, 0, 0, 2);
    v.emplace_back("PD", 10, 0, 0, -3, 2);
    litchfieldLetterPosMap["PD"] = v;
    v.clear();

    // PE
    v.emplace_back("PE", 0, 0, 2, 0, 2);
    v.emplace_back("PE", 1, 0, 2, 0, 2);
    v.emplace_back("PE", 2, 0, 2, -2, -2);
    v.emplace_back("PE", 3, -1, 2, -2, -2);
    v.emplace_back("PE", 4, 0, 0, 0, 0);
    v.emplace_back("PE", 5, 1, 0, -2, 0);
    v.emplace_back("PE", 6, 0, 2, -2, 3);
    v.emplace_back("PE", 7, 0, 2, -2, -1);
    v.emplace_back("PE", 8, -2, 0, -1, 0);
    v.emplace_back("PE", 9, 0, 0, 3, 0);
    v.emplace_back("PE", 11, 0, 0, -2, 0);
    v.emplace_back("PE", 10, -2, 1, 2, 0);
    litchfieldLetterPosMap["PE"] = v;
    v.clear();

    // PF
    v.emplace_back("PF", 0, -1, 2, -2, -1);
    v.emplace_back("PF", 1, -1, 2, -2, -1);
    v.emplace_back("PF", 2, -2, 2, 1, 0);
    v.emplace_back("PF", 3, 2, 1, 0, 0);
    v.emplace_back("PF", 4, 1, 0, 2, -2);
    v.emplace_back("PF", 5, 2, 1, 0, 0);
    v.emplace_back("PF", 6, -1, 0, 0, 0);
    v.emplace_back("PF", 9, 0, 0, 4, -2);
    v.emplace_back("PF", 11, 3, -1, -4, 0);
    v.emplace_back("PF", 7, 2, -2, 0, -2);
    v.emplace_back("PF", 8, -2, -2, 0, 0);
    v.emplace_back("PF", 10, 4, 0, 2, 0);
    litchfieldLetterPosMap["PF"] = v;
    v.clear();

    // PG
    v.emplace_back("PG", 0, 2, -1, -2, -1);
    v.emplace_back("PG", 1, 2, -1, -2, -1);
    v.emplace_back("PG", 2, 0, 2, -2, -2);
    v.emplace_back("PG", 3, 0, 2, -2, 0);
    v.emplace_back("PG", 4, -1, 2, -2, 1);
    v.emplace_back("PG", 5, 2, 0, 2, -3);
    v.emplace_back("PG", 6, -2, 0, -2, 0);
    v.emplace_back("PG", 7, -2, 1, -2, -3);
    v.emplace_back("PG", 8, -2, -2, -2, -2);
    v.emplace_back("PG", 10, -2, 0, 0, -2);
    v.emplace_back("PG", 11, 3, 0, 1, -2);
    v.emplace_back("PG", 9, 1, 0, 3, 0);
    litchfieldLetterPosMap["PG"] = v;
    v.clear();

    // PH
    v.emplace_back("PH", 0, -2, 2, 2, -1);
    v.emplace_back("PH", 1, -2, 2, 2, -1);
    v.emplace_back("PH", 3, 0, 0, -2, 0);
    v.emplace_back("PH", 5, 4, -2, -2, -2);
    v.emplace_back("PH", 6, -2, -1, -2, 4);
    v.emplace_back("PH", 8, -3, -3, -3, 4);
    v.emplace_back("PH", 11, 4, -2, -2, 0);
    v.emplace_back("PH", 2, -2, 2, 0, 0);
    v.emplace_back("PH", 4, 0, 2, -2, -2);
    v.emplace_back("PH", 7, -1, 0, -2, -2);
    v.emplace_back("PH", 9, 0, 2, -3, 1);
    v.emplace_back("PH", 10, 2, 2, 4, 2);
    litchfieldLetterPosMap["PH"] = v;
    v.clear();

    // PI
    v.emplace_back("PI", 0, -2, 2, 2, 2);
    v.emplace_back("PI", 1, -2, 2, 2, 2);
    v.emplace_back("PI", 2, 0, 2, -3, 2);
    v.emplace_back("PI", 5, 3, 2, 4, -2);
    v.emplace_back("PI", 6, -2, 2, 0, -2);
    v.emplace_back("PI", 8, -3, -2, 0, -1);
    v.emplace_back("PI", 9, 0, 2, 0, 0);
    v.emplace_back("PI", 11, 4, -1, -2, 2);
    v.emplace_back("PI", 3, 0, 0, -1, -2);
    v.emplace_back("PI", 4, -2, 2, 0, 0);
    v.emplace_back("PI", 7, -2, 0, 0, -2);
    v.emplace_back("PI", 10, -1, 0, -1, 0);
    litchfieldLetterPosMap["PI"] = v;
    v.clear();

    // PJ
    v.emplace_back("PJ", 0, 0, 2, -2, -2);
    v.emplace_back("PJ", 1, 0, 2, -2, -2);
    v.emplace_back("PJ", 2, 0, 1, 0, -1);
    v.emplace_back("PJ", 4, 3, 2, -4, 0);
    v.emplace_back("PJ", 5, 0, 0, 0, 0);
    v.emplace_back("PJ", 8, -4, 0, -3, 1);
    v.emplace_back("PJ", 9, -1, 0, -2, 0);
    v.emplace_back("PJ", 10, -2, 2, 2, 2);
    v.emplace_back("PJ", 11, 4, 0, -4, 0);
    v.emplace_back("PJ", 3, 0, 0, -1, 0);
    v.emplace_back("PJ", 6, 0, 2, 2, -2);
    v.emplace_back("PJ", 7, -2, 2, 0, -2);
    litchfieldLetterPosMap["PJ"] = v;
    v.clear();

    // PK
    v.emplace_back("PK", 0, 0, 2, -2, -2);
    v.emplace_back("PK", 1, 0, 2, -2, -2);
    v.emplace_back("PK", 2, 0, 0, 2, 0);
    v.emplace_back("PK", 3, 0, 0, 0, 2);
    v.emplace_back("PK", 4, 0, 2, -1, 2);
    v.emplace_back("PK", 5, 2, 0, 0, 2);
    v.emplace_back("PK", 6, 4, 0, 4, -2);
    v.emplace_back("PK", 8, -2, -2, -2, 0);
    v.emplace_back("PK", 9, 2, -2, 2, -2);
    v.emplace_back("PK", 10, 4, 0, -2, 4);
    v.emplace_back("PK", 11, 0, 0, 4, 2);
    v.emplace_back("PK", 7, 1, -2, 1, 2);
    litchfieldLetterPosMap["PK"] = v;
    v.clear();

    // PL
    v.emplace_back("PL", 0, 0, 0, -2, 0);
    v.emplace_back("PL", 1, 0, 0, -2, 0);
    v.emplace_back("PL", 2, 1, 0, 0, -2);
    v.emplace_back("PL", 3, 1, 2, -2, 0);
    v.emplace_back("PL", 4, 0, 3, 0, 0);
    v.emplace_back("PL", 5, 1, 2, 0, -1);
    v.emplace_back("PL", 6, -1, 0, -2, 0);
    v.emplace_back("PL", 7, 0, 0, 0, -2);
    v.emplace_back("PL", 8, -4, -2, 0, 0);
    v.emplace_back("PL", 11, 0, 0, 2, 0);
    v.emplace_back("PL", 9, 2, -2, 2, 0);
    v.emplace_back("PL", 10, 0, 0, 2, 2);
    litchfieldLetterPosMap["PL"] = v;
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

    // QB
    v.emplace_back("QB", 0, -3, 0, 0, 0);
    v.emplace_back("QB", 1, -3, 0, 0, 0);
    v.emplace_back("QB", 2, -4, 0, -1, 1);
    v.emplace_back("QB", 3, 0, 0, 0, 2);
    v.emplace_back("QB", 4, 0, 0, 0, 2);
    v.emplace_back("QB", 5, 0, 0, 2, 0);
    v.emplace_back("QB", 6, -1, 0, -2, 0);
    v.emplace_back("QB", 7, 0, 0, -1, 2);
    v.emplace_back("QB", 8, -2, 1, 0, -1);
    v.emplace_back("QB", 9, 2, 0, -2, -2);
    v.emplace_back("QB", 10, 4, 2, -2, 2);
    v.emplace_back("QB", 11, 3, 0, 0, 2);

    // QC
    v.emplace_back("QC", 4, 0, 3, 0, 0);
    v.emplace_back("QC", 5, -1, -2, 0, -2);
    v.emplace_back("QC", 6, -2, -1, -3, -1);
    v.emplace_back("QC", 7, 0, 0, -2, -2);
    v.emplace_back("QC", 8, 0, 0, 0, -1);
    v.emplace_back("QC", 10, 0, 0, -2, -2);
    v.emplace_back("QC", 11, -2, 2, 0, 1);
    v.emplace_back("QC", 0, -2, 0, 2, -1);
    v.emplace_back("QC", 1, -2, 0, 2, -1);
    v.emplace_back("QC", 2, 0, 2, -2, 0);
    v.emplace_back("QC", 3, -2, 0, -2, 0);
    v.emplace_back("QC", 9, 0, -2, -2, 0);

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

    // QF
    v.emplace_back("QF", 0, -2, 0, -2, -1);
    v.emplace_back("QF", 1, -2, 0, -2, -1);
    v.emplace_back("QF", 3, 0, 0, -2, -1);
    v.emplace_back("QF", 4, 0, 2, 0, -2);
    v.emplace_back("QF", 5, -1, 2, 0, 0);
    v.emplace_back("QF", 6, -2, -2, 1, 0);
    v.emplace_back("QF", 7, 0, 0, 0, 0);
    v.emplace_back("QF", 8, 2, 1, 0, 0);
    v.emplace_back("QF", 9, -2, 0, 0, 0);
    v.emplace_back("QF", 10, 2, 0, 0, 2);
    v.emplace_back("QF", 11, -2, 0, -4, 0);
    v.emplace_back("QF", 2, 0, 0, 0, 0);
    litchfieldLetterPosMap["QF"] = v;
    v.clear();

    // QG
    v.emplace_back("QG", 4, 0, 2, -2, -2);
    v.emplace_back("QG", 6, 0, -2, -2, 0);
    v.emplace_back("QG", 8, 2, 1, -3, -2);
    v.emplace_back("QG", 9, 0, -3, 0, -1);
    v.emplace_back("QG", 11, -4, 2, -3, 2);
    v.emplace_back("QG", 0, 2, 0, -2,  -2);
    v.emplace_back("QG", 1, 2, 0, -2,  -2);
    v.emplace_back("QG", 2, -4, 0, -4, 0);
    v.emplace_back("QG", 3, -2, 0, -2, -2);
    v.emplace_back("QG", 5, 0, 0, -2, -4);
    v.emplace_back("QG", 7, 1, 2, -2, -2);
    v.emplace_back("QG", 10, 4, 0, -1, 2);
    litchfieldLetterPosMap["QG"] = v;
    v.clear();

    //QH
    v.emplace_back("QH", 0, 0, 0, 2, -1);
    v.emplace_back("QH", 1, 0, 0, 2, -1);
    v.emplace_back("QH", 2, 0, 0, -2, 2);
    v.emplace_back("QH", 4, 0, 2, -3, -1);
    v.emplace_back("QH", 5, 0, 2, 0, -2);
    v.emplace_back("QH", 8, 4, 2, -2, -2);
    v.emplace_back("QH", 9, 2, 0, 2, 0);
    v.emplace_back("QH", 10, -2, 0, 0, -2);
    v.emplace_back("QH", 11, 0, 2, -2, 0);
    v.emplace_back("QH", 3, 0, 0, -3, 2);
    v.emplace_back("QH", 6, -1, -1, -1, 3);
    v.emplace_back("QH", 7, 0, -2, -1, -1);
    litchfieldLetterPosMap["QH"] = v;
    v.clear();

    // QI
    v.emplace_back("QI", 0, 0, 0, 2, 0);
    v.emplace_back("QI", 1, 0, 0, 2, 0);
    v.emplace_back("QI", 2, 2, 2, -3, 1);
    v.emplace_back("QI", 3, 0 ,0, -2, -2);
    v.emplace_back("QI", 7, 0, 2, 0, 0);
    v.emplace_back("QI", 8, 2, 0, -1, 2);
    v.emplace_back("QI", 9, -2, 0, 3, 0);
    v.emplace_back("QI", 10, 2, 2, 0, 2);
    v.emplace_back("QI", 11, 0, 2, -2, 2);
    v.emplace_back("QI", 4, -2, -2, 0, 0);
    v.emplace_back("QI", 5, 0, 0, 3, -2);
    v.emplace_back("QI", 6, -2, -2, 0, -2);
    litchfieldLetterPosMap["QI"] = v;
    v.clear();

    // QJ
    v.emplace_back("QJ", 0, 0, 0, -2, 0);
    v.emplace_back("QJ", 1, 0, 0, -2, 0);
    v.emplace_back("QJ", 4, 0, 2, -1, 0);
    v.emplace_back("QJ", 6, -2, -2, 2, 0);
    v.emplace_back("QJ", 7, 0, 2, -2, 0);
    v.emplace_back("QJ", 8, 4, 0, -3, -1);
    v.emplace_back("QJ", 10, 2, 0, 2, 2);
    v.emplace_back("QJ", 11, -4, -1, -2, 0);
    v.emplace_back("QJ", 2, 2, 2, -4, 2);
    v.emplace_back("QJ", 3, 0 ,0, -1, 0);
    v.emplace_back("QJ", 5, 0, -1, -2, 0);
    v.emplace_back("QJ", 9, 0, 0, 1, -1);
    litchfieldLetterPosMap["QJ"] = v;
    v.clear();

    // QK
    v.emplace_back("QK", 0, 2, -2, -2, 2);
    v.emplace_back("QK", 1, 2, -2, -2, 2);
    v.emplace_back("QK", 4, -2, 2, -1, 2);
    v.emplace_back("QK", 5, 0, 0, 0, 0);
    v.emplace_back("QK", 6, 0, -2, 0, 0);
    v.emplace_back("QK", 8, 2, 0, 0, 0);
    v.emplace_back("QK", 9, -2, 0, 2, -2);
    v.emplace_back("QK", 11, -2, -1, -2, 0);
    v.emplace_back("QK", 2, 2, 0, 3, 0);
    v.emplace_back("QK", 3, -2, -2, 0, -2);
    v.emplace_back("QK", 7, 0, 0, 0, 0);
    v.emplace_back("QK", 10, -2, 1, -2, 2);
    litchfieldLetterPosMap["QK"] = v;
    v.clear();

    // QL
    v.emplace_back("QL", 0, 0, 0, -2, -2);
    v.emplace_back("QL", 1, 0, 0, -3, 1);
    v.emplace_back("QL", 2, 2, 2, -2, 0);
    v.emplace_back("QL", 3, 2, 1, -1, 0);
    v.emplace_back("QL", 4, 0, 0, 0, -2);
    v.emplace_back("QL", 5, 2, 2, 2, -2);
    v.emplace_back("QL", 6, -2, -2, 0, -2);
    v.emplace_back("QL", 7, 0, 0, -1, -2);
    v.emplace_back("QL", 8, 4, 0, -2, 0);
    v.emplace_back("QL", 11, 0, 0, 4, 0);
    v.emplace_back("QL", 9, -3, -2, -2, 0);
    v.emplace_back("QL", 10, 0, 2, 0, 2);
    litchfieldLetterPosMap["QL"] = v;
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

    // RB
    v.emplace_back("RB", 0, 0, 2, 0, 0);
    v.emplace_back("RB", 1, 0, 2, 0, 0);
    v.emplace_back("RB", 2, 0, 0, -3, 2);
    v.emplace_back("RB", 3, -2, 0, 0, 2);
    v.emplace_back("RB", 4, 1, 1, 0, 2);
    v.emplace_back("RB", 5, 2, 0, -1, 0);
    v.emplace_back("RB", 6, 0, 0, 0, 0);
    v.emplace_back("RB", 7, 0, 2, -2, 1);
    v.emplace_back("RB", 8, 0, 0, 0, -1);
    v.emplace_back("RB", 11, -2, 2, -3, 0);
    v.emplace_back("RB", 9, 3, -2, 0, -1);
    v.emplace_back("RB", 10, -2, 2, -2, 0);
    litchfieldLetterPosMap["RB"] = v;
    v.clear();

    // RC
    v.emplace_back("RC", 0, 1, 2, 0, -1);
    v.emplace_back("RC", 1, 1, 2, 0, -1);
    v.emplace_back("RC", 3, 0, 0, 0, -2);
    v.emplace_back("RC", 5, 0, 0, -2, -2);
    v.emplace_back("RC", 6, 0, 2, 3, -2);
    v.emplace_back("RC", 7, 2, 2, 0, -2);
    v.emplace_back("RC", 8, 3, -4, -3, 2);
    v.emplace_back("RC", 9, -2, 1, -4, 0);
    v.emplace_back("RC", 10, 0, 2, 0, -2);
    v.emplace_back("RC", 11, -3, 1, 0, 0);
    v.emplace_back("RC", 2, -2, 2, 2, -2);
    v.emplace_back("RC", 4, 0, 2, 0, -2);
    litchfieldLetterPosMap["RC"] = v;
    v.clear();

    // RD
    v.emplace_back("RD", 0, 0, 2, 0, -2);
    v.emplace_back("RD", 1, 0, 2, 0, -2);
    v.emplace_back("RD", 2, 0, 0, -1, 2);
    v.emplace_back("RD", 4, 0, 2, 0, 2);
    v.emplace_back("RD", 6, 0, 2, -2, 0);
    v.emplace_back("RD", 8, 2, 0, 0, 0);
    v.emplace_back("RD", 9, 2, 0, -2, 1);
    v.emplace_back("RD", 11, 0, 3, -1, 4);
    v.emplace_back("RD", 3, -4, 2, 2, 1);
    v.emplace_back("RD", 5, 0, 1, -2, 0);
    v.emplace_back("RD", 7, 0, 2, 0, 0);
    v.emplace_back("RD", 10, -2, 0, -2, 0);
    litchfieldLetterPosMap["RD"] = v;
    v.clear();

    // RE
    v.emplace_back("RE", 0, -2, 0, 1, 2);
    v.emplace_back("RE", 1, -2, 0, 1, 3);
    v.emplace_back("RE", 2, -2, 3, 0, 2);
    v.emplace_back("RE", 4, 0, 0, -2, 1);
    v.emplace_back("RE", 5, 3, 2, -1, -2);
    v.emplace_back("RE", 6, 0, 0, 0, 0);
    v.emplace_back("RE", 7, 0, 0, -2, 0);
    v.emplace_back("RE", 8, 0, 0, -1, 0);
    v.emplace_back("RE", 9, 0, -2, 2, 0);
    v.emplace_back("RE", 11, 0, 3, 0, 0);
    v.emplace_back("RE", 3, -2, 2, -2, 0);
    v.emplace_back("RE", 10, -3, 2, -2, -2);
    litchfieldLetterPosMap["RE"] = v;
    v.clear();

    // RF
    v.emplace_back("RF", 0, -2, 2, -3, -2);
    v.emplace_back("RF", 1, -2, 2, -3, -2);
    v.emplace_back("RF", 2, 0, 0, 0, 0);
    v.emplace_back("RF", 3, -2, 2, 0, 2);
    v.emplace_back("RF", 4, 1, 2, 0, 0);
    v.emplace_back("RF", 5, -2, 2, 2, 0);
    v.emplace_back("RF", 6, 0, 0, 0, -2);
    v.emplace_back("RF", 7, 0, 2, 0, -2);
    v.emplace_back("RF", 8, -1, -2, 0, -2);
    v.emplace_back("RF", 9, 1, -2, 2, -2);
    v.emplace_back("RF", 10, -2, 0, 0, 0);
    v.emplace_back("RF", 11, 2, 2, 3, -2);
    litchfieldLetterPosMap["RF"] = v;
    v.clear();

    //RG
    v.emplace_back("RG", 0, -2, 2, -2, -2);
    v.emplace_back("RG", 1, -2, 2,-2, -2);
    v.emplace_back("RG", 2, 0, 2, 0, -2);
    v.emplace_back("RG", 4, 0, 2, -3, 0);
    v.emplace_back("RG", 5, -3, 2, 0, -4);
    v.emplace_back("RG", 6, 0, 0, -3, -1);
    v.emplace_back("RG", 7, 0, 2, 1, -2);
    v.emplace_back("RG", 8, 0, -2, -2, 2);
    v.emplace_back("RG", 10, 0, 2, 0, 0);
    v.emplace_back("RG", 11, 3, 0, -2, 0);
    v.emplace_back("RG", 3, -2, 0, -2, -2);
    v.emplace_back("RG", 9, -2, -2, -2, 0);
    litchfieldLetterPosMap["RG"] = v;
    v.clear();

    // RH
    v.emplace_back("RH", 0, 0, 0, 0, -1);
    v.emplace_back("RH", 1, 0, 0, 0, -1);
    v.emplace_back("RH", 2, 0, 2, -2, 2);
    v.emplace_back("RH", 4, -1, 1, -3, -3);
    v.emplace_back("RH", 5, 0, 0, 0, -2);
    v.emplace_back("RH", 6, 0, 0, -3, 2);
    v.emplace_back("RH", 7, 0, 2, -2, -1);
    v.emplace_back("RH", 11, 0, 2, -2, 0);
    v.emplace_back("RH", 3, -2, 2, 0, 0);
    v.emplace_back("RH", 8, 1, -2, -2, 2);
    v.emplace_back("RH", 9, 2, -2, 0, 0);
    v.emplace_back("RH", 10, 0, 0, 0, -2);
    litchfieldLetterPosMap["RH"] = v;
    v.clear();

    //RI
    v.emplace_back("RI", 0, 2, 0, 3, 2);
    v.emplace_back("RI", 1, 2, 0, 3, 2);
    v.emplace_back("RI", 2, 0, 2, 0, 2);
    v.emplace_back("RI", 4, 0, 0, -2, 0);
    v.emplace_back("RI", 5, 0,0, 0, -2);
    v.emplace_back("RI", 6, 0,0, 0, -1);
    v.emplace_back("RI", 7, 0, 2, 0, -1);
    v.emplace_back("RI", 8, 0, 0, 0, 0);
    v.emplace_back("RI", 10, -2, 2, -4, 2);
    v.emplace_back("RI", 11, 0, 0, 0, 2);
    v.emplace_back("RI", 3, 1, 0, 3, -2);
    v.emplace_back("RI", 9, -3, -2, 2, 0);
    litchfieldLetterPosMap["RI"] = v;
    v.clear();

    //RJ
    v.emplace_back("RJ", 0, 0, 0, -2, 0);
    v.emplace_back("RJ", 1, 0, 0, -2, 0);
    v.emplace_back("RJ", 2, -2, 2, 3, 0);
    v.emplace_back("RJ", 4, 0, 2, -2, 0);
    v.emplace_back("RJ", 5, 2, 1, 1, 0);
    v.emplace_back("RJ", 6, 3, 2, 0, -1);
    v.emplace_back("RJ", 7, 0, 2, 0, 2);
    v.emplace_back("RJ", 8, 2, -2, 0, 0);
    v.emplace_back("RJ", 10, 0, 0, 0, 0);
    v.emplace_back("RJ", 11, -2, 2, -2, 0);
    v.emplace_back("RJ", 3, 0, 2, -2, 0);
    v.emplace_back("RJ", 9, 2, -2, 1, 0);
    litchfieldLetterPosMap["RJ"] = v;
    v.clear();

    //RK
    v.emplace_back("RK", 0, -2, 2, -2, 0);
    v.emplace_back("RK", 1, -2, 2, -2, 0);
    v.emplace_back("RK", 2, 0, 2, 0, 2);
    v.emplace_back("RK", 4, 0, 0, 0, 0);
    v.emplace_back("RK", 5, 0, 0, 0, 0);
    v.emplace_back("RK", 7, 0, 2, 0, -1);
    v.emplace_back("RK", 8, 0, -2, 0, 0);
    v.emplace_back("RK", 10, 0, 2, -1, 2);
    v.emplace_back("RK", 11, -2, 0, 0, 0);
    v.emplace_back("RK", 3, -2, 0, -3, 2);
    v.emplace_back("RK", 6, 1, -1, 0, -2);
    v.emplace_back("RK", 9, -2, -2, 0, 0);
    litchfieldLetterPosMap["RK"] = v;
    v.clear();


    //RL
    v.emplace_back("RL", 0, -2, 0, -1, -2);
    v.emplace_back("RL", 1, -2, 0, -1, -2);
    v.emplace_back("RL", 2, 0, 2, -2, -2);
    v.emplace_back("RL", 3, 0, 2, -2, -1);
    v.emplace_back("RL", 4, 0, 2, 0, -2);
    v.emplace_back("RL", 5, 0, 0, 2, -2);
    v.emplace_back("RL", 6, 2, 0, 0, -3);
    v.emplace_back("RL", 7, 0, 2, 0, -2);
    v.emplace_back("RL", 8, 1, 0, -2, -2);
    v.emplace_back("RL", 9, -2, -2, -4, -2);
    v.emplace_back("RL", 10, -2, 0, 3, 0);
    v.emplace_back("RL", 11, 0, 2, 3, 2);
    litchfieldLetterPosMap["RL"] = v;
    v.clear();

    // SA
    v.emplace_back("SA", 0, -2, 0, 2, 0);
    v.emplace_back("SA", 1, -2, 0, 2, 0);
    v.emplace_back("SA", 2, -2, 1, 0, 0);
    v.emplace_back("SA", 3, 0, 0, 0, 0);
    v.emplace_back("SA", 4, -2, 2, 0, 0);
    v.emplace_back("SA", 6, -2, -2, 0, 1);
    v.emplace_back("SA", 7, -2, 2, -2, -2);
    v.emplace_back("SA", 8, -2, -2, 0, 0);
    v.emplace_back("SA", 9, 0, 0, 0, 0);
    v.emplace_back("SA", 10, -2, 0, 0, 0);
    v.emplace_back("SA", 11, 0, 0, 2, 2);
    v.emplace_back("SA", 5, 3, -2, 0, 0);
    litchfieldLetterPosMap["SA"] = v;
    v.clear();

    // SB
    v.emplace_back("SB", 0, -2, 0, 0, 2);
    v.emplace_back("SB", 1, -2, 0, 0, 2);
    v.emplace_back("SB", 2, -2, 2, 0, 2);
    v.emplace_back("SB", 6, -2, -1, 0, 0);
    v.emplace_back("SB", 7, 0, -1, -2, 1);
    v.emplace_back("SB", 8, -2, -2, 0, 2);
    v.emplace_back("SB", 9, 0, 0, 2, -1);
    v.emplace_back("SB", 10, 0, 0, -2, 2);
    v.emplace_back("SB", 11, 4, -3, 2, 2);
    v.emplace_back("SB", 3, 0, 0, 0, 3);
    v.emplace_back("SB", 4, -2, 1, 0, 2);
    v.emplace_back("SB", 5, -2, -1, 2, 0);
    litchfieldLetterPosMap["SB"] = v;
    v.clear();

    // SC
    v.emplace_back("SC", 0, 1, 2, 2, -1);
    v.emplace_back("SC", 1, 1, 2, 2, -1);
    v.emplace_back("SC", 2, -2, 0, -1, -2);
    v.emplace_back("SC", 3, -2, 1, -2, -2);
    v.emplace_back("SC", 4, -3, -2, -2, 0);
    v.emplace_back("SC", 5, -3, 0, 2, -2);
    v.emplace_back("SC", 6, -2, 0, 0, 0);
    v.emplace_back("SC", 8, -1, -2, -2, -2);
    v.emplace_back("SC", 9, 0, -3, -4, 0);
    v.emplace_back("SC", 10, 0, 0, -2, -2);
    v.emplace_back("SC", 11, 0, 1, 3, -2);
    v.emplace_back("SC", 7, 0, 0, 0, -2);
    litchfieldLetterPosMap["SC"] = v;
    v.clear();

    // SD
    v.emplace_back("SD", 0, -1, 0, -2, 2);
    v.emplace_back("SD", 1, -1, 0, -2, 2);
    v.emplace_back("SD", 2, 0, 2, -1, 0);
    v.emplace_back("SD", 3, 2, 0, -2, 2);
    v.emplace_back("SD", 4, -2, 0, 2, 2);
    v.emplace_back("SD", 6, -2, 2, 0, 1);
    v.emplace_back("SD", 8, -2, -3, 0, 2);
    v.emplace_back("SD", 9, -2, 0, 0, 2);
    v.emplace_back("SD", 10, 0, -2, 0, 2);
    v.emplace_back("SD", 11, -3, 2, -1, 4);
    v.emplace_back("SD", 5, 0, 0, -2, 2),
    v.emplace_back("SD", 7, -2, 1, -2, 2);
    litchfieldLetterPosMap["SD"] = v;
    v.clear();

    //SE
    v.emplace_back("SE", 0, 0, 0, 0, 3);
    v.emplace_back("SE", 1, 0, 0, 0, 3);
    v.emplace_back("SE", 2, -2, 0, -2, 2);
    v.emplace_back("SE", 4, 0, -1, 0, 3);
    v.emplace_back("SE", 5, 0, 0, 0, -1);
    v.emplace_back("SE", 6, 0, 2, 0, -2);
    v.emplace_back("SE", 8, -2, -2, 0, 0);
    v.emplace_back("SE", 9, -2, 0, -2, 0);
    v.emplace_back("SE", 11, 0, 2, 2, -1);
    v.emplace_back("SE", 3, -2, 0, -2, 0);
    v.emplace_back("SE", 7, -2, 0, -2, 0);
    v.emplace_back("SE", 10, 2, -1, 0, -2);
    litchfieldLetterPosMap["SE"] = v;
    v.clear();

    // SF
    v.emplace_back("SF", 0, -2, 0, -1, 0);
    v.emplace_back("SF", 1, -2, 0, -1, 0);
    v.emplace_back("SF", 2, 0, -2, 0, 2);
    v.emplace_back("SF", 4, -2, -2, 0, 2);
    v.emplace_back("SF", 6, -2, 0, 0, -2);
    v.emplace_back("SF", 11, -2, 2, -2, 2);
    v.emplace_back("SF", 3, -2, 0, -3, 0);
    v.emplace_back("SF", 5, -2, 0, 4, -2);
    v.emplace_back("SF", 7, -2, -1, 0, 0);
    v.emplace_back("SF", 8, 2, -1, 0, 0);
    v.emplace_back("SF", 9, 0, 0, 3, -2);
    v.emplace_back("SF", 10, 0, 1, 0, 0);
    litchfieldLetterPosMap["SF"] = v;
    v.clear();

    // SG
    v.emplace_back("SG", 0, -2, 0, -2, 0);
    v.emplace_back("SG", 1, -2, 0, -2, 0);
    v.emplace_back("SG", 2, -3, 0, -4, 0);
    v.emplace_back("SG", 5, -3, 0, -1, -4);
    v.emplace_back("SG", 6, -3, 0, -2, 0);
    v.emplace_back("SG", 8, -1, -2, -2, -1);
    v.emplace_back("SG", 10, 2, 1, 2, -2);
    v.emplace_back("SG", 11, 0, 1, 0, 0);
    v.emplace_back("SG", 3, 0, 1, -2, -2);
    v.emplace_back("SG", 4, -2, 0, -2, -1);
    v.emplace_back("SG", 7, 4, -2, -2, -4);
    v.emplace_back("SG", 9, 2, -2, 2, 0);
    litchfieldLetterPosMap["SG"] = v;
    v.clear();

    // SH
    v.emplace_back("SH", 0, 2, -2, 2, -2);
    v.emplace_back("SH", 1, 2, -2, 2, -2);
    v.emplace_back("SH", 2, 2, 2, 0, 0);
    v.emplace_back("SH", 5, -2, -2, 0, 0);
    v.emplace_back("SH", 7, -2, 0, -2, -2);
    v.emplace_back("SH", 11, 0, 0, -3, 2);
    v.emplace_back("SH", 3, -2, 0, -2, 2);
    v.emplace_back("SH", 4, -2, 0, -2, -2);
    v.emplace_back("SH", 6, -2, 0, 0, 0);
    v.emplace_back("SH", 8, -2, -2, -2, 0);
    v.emplace_back("SH", 9, -2, -2, 0, -2);
    v.emplace_back("SH", 10, 0, 0, 2, 0);
    litchfieldLetterPosMap["SH"] = v;
    v.clear();

    // SI
    v.emplace_back("SI", 0, 0, -2, 2, 0);
    v.emplace_back("SI", 1, 0, -2, 2, 0);
    v.emplace_back("SI", 2, -2, 1, 0, 2);
    v.emplace_back("SI", 3, 0, 0, -2, 0);
    v.emplace_back("SI", 5, 0, 1, 2, -2);
    v.emplace_back("SI", 9, -2, -3, -3, 0);
    v.emplace_back("SI", 10, 3, 0, -4, 2);
    v.emplace_back("SI", 11, 2, 1, 1, 1);
    v.emplace_back("SI", 4, -2, -2, 1, -1);
    v.emplace_back("SI", 6, -2, 3, 1, 0);
    v.emplace_back("SI", 7, -2, -1, 0, 0);
    v.emplace_back("SI", 8, -2, -2, 0, 2);
    litchfieldLetterPosMap["SI"] = v;
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

    // SK
    v.emplace_back("SK", 0, -2, 0, -2, -2);
    v.emplace_back("SK", 1, -2, 0, -2, -2);
    v.emplace_back("SK", 2, -2, 0, -2, 0);
    v.emplace_back("SK", 3, 0, 2, 0, -2);
    v.emplace_back("SK", 4, -4, -1, 0, 0);
    v.emplace_back("SK", 5, -2, 0, 3, -2);
    v.emplace_back("SK", 6, -2, 1, 0, -2);
    v.emplace_back("SK", 11, 2, 1, -2, 0);
    v.emplace_back("SK", 7, -2, -2, 1, -1);
    v.emplace_back("SK", 8, -2, -2, 0, -2);
    v.emplace_back("SK", 9, 2, -2, 1, -2);
    v.emplace_back("SK", 10, 0, -2, 0, -2);
    litchfieldLetterPosMap["SK"] = v;
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

    // TA
    v.emplace_back("TA", 0, 0, 0, 0, 0);
    v.emplace_back("TA", 1, 0, 0, 0, 0);
    v.emplace_back("TA", 2, 0, -2, -2, 1);
    v.emplace_back("TA", 3, -2, 2, 0, 0);
    v.emplace_back("TA", 4, 0, 2, 0, 0);
    v.emplace_back("TA", 6, 0, -2, 0, 0);
    v.emplace_back("TA", 8, -3, -2, 1, 1);
    v.emplace_back("TA", 9, -2, 0, -1, 0);
    v.emplace_back("TA", 10, 2, -2, -2, 0);
    v.emplace_back("TA", 11, 2, 2, -2, 2);
    v.emplace_back("TA", 5, 0, 3, 0, -2);
    v.emplace_back("TA", 7, 1, 3, -2, -2);
    litchfieldLetterPosMap["TA"] = v;
    v.clear();

    // TB
    v.emplace_back("TB", 0, -2, 2, 2, 1);
    v.emplace_back("TB", 1, -2, 2, 2, 1);
    v.emplace_back("TB", 8, -1, -2, 0, 0);
    v.emplace_back("TB", 9, 0, -2, -2, 0);
    v.emplace_back("TB", 10, 2, 0, -2, 0);
    v.emplace_back("TB", 11, 0, 2, -2, 0);
    v.emplace_back("TB", 2, 0, -2, -2, 2);
    v.emplace_back("TB", 3, -2, 2, -1, 2);
    v.emplace_back("TB", 4, -2, 2, 0, 2);
    v.emplace_back("TB", 5, 0, 2, 0, 0);
    v.emplace_back("TB", 6, 2, 3, 1, 0);
    v.emplace_back("TB", 7, 0, 3, -2, 2);
    litchfieldLetterPosMap["TB"] = v;
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

    // TD
    v.emplace_back("TD", 0, 0, -2, -2, 0);
    v.emplace_back("TD", 1, 0, -2, -2, 0);
    v.emplace_back("TD", 2, 0, 2, 0, 0);
    v.emplace_back("TD", 4, -2, 0, 0, 1);
    v.emplace_back("TD", 6, -2, 2, -3, 1);
    v.emplace_back("TD", 7, 0, 2, 0, 0);
    v.emplace_back("TD", 8, 3, 0, 0, 0);
    v.emplace_back("TD", 9, -2, -2, -1, 2);
// XXX TODO MISSING    11,
    v.emplace_back("TD", 3, 0, 2, 0, 0);
    v.emplace_back("TD", 5, 2, -2, -2, 2);
    v.emplace_back("TD", 10, 2, 0, -2, 0);
    litchfieldLetterPosMap["TD"] = v;
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

    // TG
    v.emplace_back("TG", 0, 0, 0, -2, 0);
    v.emplace_back("TG", 1, 0, 0, -2, 0);
    v.emplace_back("TG", 2, 1, -2, -1, 0);
    v.emplace_back("TG", 3, 2, 0, -2, 0);
    v.emplace_back("TG", 4, 0, 2, -2, -3);
    v.emplace_back("TG", 5, 2, 2, -1, -2);
    v.emplace_back("TG", 6, -2, 2, -2, -2);
    v.emplace_back("TG", 7, 0, 2, -3, 0);
    v.emplace_back("TG", 8, 2, -2, -2, -2);
    v.emplace_back("TG", 11, -2, 2, -2, -2);
    v.emplace_back("TG", 9, 0, -2, 0, 0);
    v.emplace_back("TG", 10, 2, 0, 2, 0);
    litchfieldLetterPosMap["TG"] = v;
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

    // TI
    v.emplace_back("TI", 0, -2, 2, 2, 2);
    v.emplace_back("TI", 1, -2, 2, 2, 2);
    v.emplace_back("TI", 2, 0, -1, -2, 0);
    v.emplace_back("TI", 5, -2, 2, 1, -1);
    v.emplace_back("TI", 6, 0, 4, 2, 0);
    v.emplace_back("TI", 7, 0, 2, -2, -2);
    v.emplace_back("TI", 8, -2, 0, -2, -1);
    v.emplace_back("TI", 9, 2, -2, 2, 0);
    v.emplace_back("TI", 10, 3, 0, -2, 0);
    v.emplace_back("TI", 11, -2, 2, 0, 2);
    v.emplace_back("TI", 3, 0, 0, -2, -1);
    v.emplace_back("TI", 4, 0, 0, -2, 0);
    litchfieldLetterPosMap["TI"] = v;
    v.clear();

    //TJ
    v.emplace_back("TJ", 0, 0, 0, 0, 0);
    v.emplace_back("TJ", 1, 0, 0, 0, 0);
    v.emplace_back("TJ", 2, 0, 0, -2, -1);
    v.emplace_back("TJ", 4, -2, 0, -3, -2);
    v.emplace_back("TJ", 5, 1, 2, 0, -1);
    v.emplace_back("TJ", 6, 2, 2, 0, -2);
    v.emplace_back("TJ", 7, 0, 2, 0, -2);
    v.emplace_back("TJ", 8, 2, 0, -2, 2);
    v.emplace_back("TJ", 10, 0, 0, 0, -1);
    v.emplace_back("TJ", 11, -2, 2, 4, 0);
    v.emplace_back("TJ", 3, -1, 2, -3, -2);
    v.emplace_back("TJ", 9, 2, -2, 0, 0);
    litchfieldLetterPosMap["TJ"] = v;
    v.clear();

    // TK
    v.emplace_back("TK", 0, 0, -2, 0, -2);
    v.emplace_back("TK", 1, 0, -2, 0, -2);
    v.emplace_back("TK", 2, 0, 0, -2, 0);
    v.emplace_back("TK", 3, 0, -3, 0, 0);
    v.emplace_back("TK", 4, -2, -2, 2, 0);
    v.emplace_back("TK", 5, 2, 0, 0, -2);
    v.emplace_back("TK", 8, -2, -1, -1, -2);
    v.emplace_back("TK", 10, 0, 2, 0, -2);
    v.emplace_back("TK", 11, -2, 2, 2, 2);
    v.emplace_back("TK", 6, -1, 2, -2, -3);
    v.emplace_back("TK", 7, -2, 2, -2, -2);
    v.emplace_back("TK", 9, -2, -3, 2, -1);
    litchfieldLetterPosMap["TK"] = v;
    v.clear();

    // TL
    v.emplace_back("TL", 0, 0, -1, -2, 0);
    v.emplace_back("TL", 1, 0, -1, -2, 0);
    v.emplace_back("TL", 2, -1, 2, -2, -1);
    v.emplace_back("TL", 3, -2, -2, -2, 0);
    v.emplace_back("TL", 4, 0, -2, 0, -2);
    v.emplace_back("TL", 7, 0, 0, 0, -2);
    v.emplace_back("TL", 8, -2, 2, -2, 0);
    v.emplace_back("TL", 11, -1, 2, 1, -2);
    v.emplace_back("TL", 5, 0, -1, -1, -2);
    v.emplace_back("TL", 6, 0, 2, 0, 0);
    v.emplace_back("TL", 9, 0, -2, -2, 0);
    v.emplace_back("TL", 10, -2, 2, 2, 0);
    litchfieldLetterPosMap["TL"] = v;
    v.clear();
}

