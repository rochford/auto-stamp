#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <vector>
#include <string>
#include <iostream>
#include <memory>

#include <stdexcept>

#include "recognition.h"
#include "alignment.h"

using namespace cv;
using namespace std;

static void help()
{
    cout << "Using OpenCV version %s\n" << CV_VERSION << "\n" << endl;
}

struct InputArgs {
    string leftLetter; // e.g. AL
    string rightLetter; // e.g. AL
    Point leftTopLeft;
    Point leftBottomRight;
    Point rightTopLeft;
    Point rightBottomRight;
    int expectedResult;
};

int letterPositions(std::string inputImage,
                    std::string leftLetter,
                    Rect leftLetterBox,
                    std::string rightLetter,
                    Rect rightLetterBox)
{
    int plate = -1;

    // open file
    const Mat image = imread(inputImage, 1);
    if( image.empty() )
    {
        cout << "Couldn't load " << inputImage << endl;
        return -1;
    }
    Mat image_gray, dst;
    /// Convert image to gray and blur it
    cvtColor( image, image_gray, CV_BGR2GRAY );

    // create recognizer
    std::shared_ptr<Recognition> recog(new Recognition());
    // recogize
    Mat leftRoi, rightRoi;
    try {
        leftRoi = image_gray(leftLetterBox).clone();
        rightRoi = image_gray(rightLetterBox).clone();
    }
    catch (cv::Exception& e) {
        cout << e.what() << endl;
        return -1;
    }

    imshow("xxx", image_gray(leftLetterBox));
    waitKey(0);
    imshow("xxx", image_gray(rightLetterBox));
    waitKey(0);
    // get alignment
    recog->setWhitelist(leftLetter);
    struct tess_data_struct td = recog->recognize(leftRoi);
    if (td.x1 == -1) {
        cout << "recognize problem" << endl;
        return -1;
    }
    cout << leftLetterBox.width << endl;
    // calculate offset amount
    int offTop = td.y1;
    int offBottom = leftLetterBox.height - td.y2;
    int offLeft = td.x1 + 1;
    int offRight = leftLetterBox.width - td.x2 -1;
    td.hOffset = offLeft - offRight;
    td.vOffset = offTop - offBottom;

    printf("Align: %d,%d [%d,%d,%d,%d]\t",
           td.hOffset,
           td.vOffset,
           td.x1,
           td.y1,
           td.x2,
           td.y2);
    printAlignment(offTop - offBottom, offLeft -offRight);

    // get alignment
    recog->setWhitelist(rightLetter);
    struct tess_data_struct tdRight = recog->recognize(rightRoi);
    if (tdRight.x1 == -1) {
        cout << "recognize problem" << endl;
        return -1;
    }

    cout << rightLetterBox.width << endl;
    // calculate offset amount
    offTop = tdRight.y1;
    offBottom = rightLetterBox.height - tdRight.y2;
    offLeft = tdRight.x1 + 1;
    offRight = rightLetterBox.width - tdRight.x2 - 1;
    tdRight.hOffset = offLeft - offRight;
    tdRight.vOffset = offTop - offBottom;

    printf("Align: %d,%d [%d,%d,%d,%d]\t",
           tdRight.hOffset,
           tdRight.vOffset,
           td.x1,
           td.y1,
           td.x2,
           td.y2);
    printAlignment(tdRight.vOffset, tdRight.hOffset);
    // calculate plate
    setup();
    string letters = leftLetter;
    letters.append(rightLetter);
    cout << letters << endl;
    auto litch = calculatePlate(letters, td.vOffset, td.hOffset, tdRight.vOffset, tdRight.hOffset);
    return litch.front().plate;
}

int main(int argc, char** argv)
{

    InputArgs al { "A", "L", Point(7,195), Point(26,215), Point(153,195), Point(173,215), 7 };
    InputArgs kl { "K", "L", Point(12,190), Point(30,210), Point(154,189), Point(173,208), 3 };
    InputArgs id { "I", "D", Point(23,193), Point(40,213), Point(170,194), Point(190,212), 6 };
    vector<InputArgs> data { al, kl, id
                };
    //    namedWindow( wndname, 1 );

    for (InputArgs item : data) {

        Rect left(item.leftTopLeft, item.leftBottomRight);
        Rect right(item.rightTopLeft, item.rightBottomRight);
        int actualPlate = letterPositions("../data/" + item.leftLetter + item.rightLetter + ".jpg",
                        item.leftLetter, left,
                        item.rightLetter, right);
        cout << item.leftLetter << item.rightLetter;
        cout << "\tResult: " << actualPlate << ", Expected: " << item.expectedResult << endl;

    }
    return 0;
}
