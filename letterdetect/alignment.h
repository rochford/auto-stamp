#ifndef ALIGNMENT_H
#define ALIGNMENT_H

enum HorizontalPos {
    HUnknown = -1000,
    ExtremelyLeft = -4,
    VeryLeft = -3,
    Left = -2,
    SlightlyLeft = -1,
    HCentral = 0,
    SlightlyRight = +1,
    Right = +2,
    VeryRight = +3,
    ExtremelyRight = +4
};

enum VerticalPos {
    VUnknown = -1000,
    ExtremelyHigh = -4,
    VeryHigh = -3,
    High = -2,
    SlightlyHigh = -1,
    VCentral = 0,
    SlightlyLow = +1,
    Low = +2,
    VeryLow = +3,
    ExtremelyLow = +4
};

void verticalAlignment(int a);
void horizontalAlignment(int a);

#endif // ALIGNMENT_H
