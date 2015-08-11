#ifndef ALIGNMENT_H
#define ALIGNMENT_H

#include <string>
#include <vector>

enum HorizontalPos {
    HUnknown = -1000,
    ExtremelyLeft = -4,
    VeryLeft = -3, // well to left?
    Left = -2, // Quite?
    SlightlyLeft = -1,
    HCentral = 0,
    SlightlyRight = +1,
    Right = +2, // Quite?
    VeryRight = +3,  // and well to right?
    ExtremelyRight = +4
};

enum VerticalPos {
    VUnknown = -1000,
    ExtremelyHigh = -4,
    VeryHigh = -3, // well to?
    High = -2, // Quite?
    SlightlyHigh = -1,
    VCentral = 0,
    SlightlyLow = +1,
    Low = +2, // Quite?
    VeryLow = +3, // well to?
    ExtremelyLow = +4
};

void printAlignment(int offsetVertical,
                    int offsetHorizontal);
void setup();
std::vector<int> calculatePlate(const std::string& letterPair,
                    int leftVertical,
                    int leftHoriz,
                    int rightVert,
                    int rightHoriz);

#endif // ALIGNMENT_H
