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

using namespace cv;
using namespace std;

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
    VUnknownV = -1000,
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


void verticalAlignment(int a) {
    switch (a) {
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

static int writeSquares(const char* whitelist, Mat& image, const vector<vector<Point> >& squares );

static void help()
{
    cout <<
            "Using OpenCV version %s\n" << CV_VERSION << "\n" << endl;
}

int thresh = 50, N = 200;
const char* wndname = "Square Detection Demo";

// helper function:
// finds a cosine of angle between vectors
// from pt0->pt1 and from pt0->pt2
static double angle( Point pt1, Point pt2, Point pt0 )
{
    double dx1 = pt1.x - pt0.x;
    double dy1 = pt1.y - pt0.y;
    double dx2 = pt2.x - pt0.x;
    double dy2 = pt2.y - pt0.y;
    return (dx1*dx2 + dy1*dy2)/sqrt((dx1*dx1 + dy1*dy1)*(dx2*dx2 + dy2*dy2) + 1e-10);
}

// returns sequence of squares detected on the image.
// the sequence is stored in the specified memory storage
static void findSquares( const Mat& image, vector<vector<Point> >& squares )
{
    squares.clear();

    Mat timg, gray0(image.size(), CV_8U), gray;

    timg = image.clone();
    vector<vector<Point> > contours;

    // find squares in every color plane of the image
    int c =0;
    //    for( int c = 0; c < 3; c++ )
    {
        int ch[] = {c, 0};
        mixChannels(&timg, 1, &gray0, 1, ch, 1);

        // try several threshold levels
        for( int l = 0; l < N; l++ )
        {
            // hack: use Canny instead of zero threshold level.
            // Canny helps to catch squares with gradient shading
            if( l == 0 )
            {
                // apply Canny. Take the upper threshold from slider
                // and set the lower to 0 (which forces edges merging)
                Canny(gray0, gray, 0, thresh, 3);
                // dilate canny output to remove potential
                // holes between edge segments
                dilate(gray, gray, Mat(), Point(-1,-1));
                // imshow("grey", gray);
                // waitKey(0);
            }
            else
            {
                // apply threshold if l!=0:
                //     tgray(x,y) = gray(x,y) < (l+1)*255/N ? 255 : 0
                gray = gray0 >= (l+1)*255/N;
                //                imshow("grey #n", gray);
                //            waitKey(0);
            }

            // find contours and store them all as a list
            findContours(gray, contours, CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE);

            vector<Point> approx;

            // test each contour
            for( size_t i = 0; i < contours.size(); i++ )
            {
                // approximate contour with accuracy proportional
                // to the contour perimeter
                approxPolyDP(Mat(contours[i]), approx, arcLength(Mat(contours[i]), true)*0.1, true);

                // square contours should have 4 vertices after approximation
                // relatively large area (to filter out noisy contours)
                // and be convex.
                // Note: absolute value of an area is used because
                // area may be positive or negative - in accordance with the
                // contour orientation
                //                cout << "shortvec = " << Mat(approx) << endl;
                if( approx.size() == 4 &&
                        fabs(contourArea(Mat(approx))) > 100 &&
                        //                        fabs(contourArea(Mat(approx))) < 4000 &&
                        isContourConvex(Mat(approx)) )
                {
                    double maxCosine = 0;

                    for( int j = 2; j < 5; j++ )
                    {
                        // find the maximum cosine of the angle between joint edges
                        double cosine = fabs(angle(approx[j%4], approx[j-2], approx[j-1]));
                        maxCosine = MAX(maxCosine, cosine);
                    }

                    // if cosines of all angles are small
                    // (all angles are ~90 degree) then write quandrange
                    // vertices to resultant sequence
                    if( maxCosine < 0.3 ) {
                        if(std::find(squares.begin(), squares.end(), approx) != squares.end()) {
                            /* v contains x */
                        } else {
                            squares.push_back(approx);
                            //                        cout << "shortvec = " << Mat(approx) << endl;
                        }
                    }
                }
            }
        }
    }
}

// the function draws all the squares in the image
static void drawSquares( Mat& image, const vector<vector<Point> >& squares )
{
    for( size_t i = 0; i < squares.size(); i++ )
    {
        const Point* p = &squares[i][0];
        int n = (int)squares[i].size();
        polylines(image, &p, &n, 1, true, Scalar(0,255,0), 3, CV_AA);
    }
}

static int writeSquares(const char* whitelist, Mat& image, const vector<vector<Point> >& squares )
{
    char ret[2];
    for( size_t i = 0; i < squares.size(); i++ )
    {
        Point p1 = squares[i][0];
        Point p2 = squares[i][2];
        if (squares[i][0].x < 2)
            continue;
        if (squares[i][2].x < 2)
            continue;
        Point  xp1(p1.x - 1, p1.y -1);
        Point  xp2(p2.x + 1, p2.y + 1);
        Rect rect( p1, p2);
        Rect xrect( xp1, xp2);
        Mat roi = image(xrect).clone();
        Mat textRoi = image(rect).clone();
#if 0
        Size size(120,120);//the dst image size,e.g.100x100
        Mat dst;
        resize(roi,dst,size,3.0,3.0);//resize image
        imshow("roi", dst);
        waitKey(0);
#endif // 0
        // Pass it to Tesseract API
        tesseract::TessBaseAPI *tess = new tesseract::TessBaseAPI();

        tess->Init(NULL, "eng", tesseract::OEM_DEFAULT);
        tess->SetVariable("tessedit_char_whitelist", whitelist);
        tess->SetVariable("tessedit_char_blacklist", "abcdefghijklmnopqrstuvwxyzUVWXYZ0123456789");
        tess->SetPageSegMode(tesseract::PSM_SINGLE_CHAR);
        tess->SetImage((uchar*)textRoi.data, textRoi.cols, textRoi.rows, 1, textRoi.cols);
        //        tess->SetRectangle(xp1.x, xp1.y, xrect.width, xrect.height);
        int ret = tess->Recognize(0);
        if (ret) {
            continue;
        }
        tesseract::ResultIterator* ri = tess->GetIterator();
        tesseract::PageIteratorLevel level = tesseract::RIL_SYMBOL;
        if (ri != 0) {
            do {
                const char* word = ri->GetUTF8Text(level);
                if (!word || !isalpha(*word))
                    continue;
                float conf = ri->Confidence(level);
                int x1, y1, x2, y2;
                ri->BoundingBox(level, &x1, &y1, &x2, &y2);
                //                cout << "rect.w:" << xrect.width << ", rect.h:" << xrect.height << endl;

                int offTop = y1;
                int offBottom = xrect.height -y2;
                int offLeft = x1;
                int offRight = xrect.width -x2;
                printf("word: '%s'(%.2f%); Align: (%d,%d)BoundingBox: %d,%d,%d,%d;\t",
                       word, conf,
                       offLeft - offRight,
                       offTop - offBottom,
                       x1,
                       y1,
                       x2,
                       y2);
                verticalAlignment(offTop - offBottom);
                horizontalAlignment(offLeft -offRight);
                delete[] word;
            } while (ri->Next(level));
        }
        tess->End();
    }
    return 0;
}

int detectLetters(string file, string& lr) {
    cout << "starting: " << lr << endl;
    vector<vector<Point> > squares;

    Mat image = imread(file, 0);
    if( image.empty() )
    {
        cout << "Couldn't load " << file << endl;
        return -1;
    }

    int erosion_size = 1;
    Mat element = getStructuringElement( MORPH_CROSS,
                                         Size( 2*erosion_size + 1, 2*erosion_size+1 ),
                                         Point( erosion_size, erosion_size ) );

    Mat timg;
    erode( image, timg, element );

    //    Mat t1 = image.clone(); //timg.clone();
    Mat t1 = timg.clone();
    Mat t2 = image.clone();
    findSquares(t1, squares);
    int ret = writeSquares(lr.c_str(), t2, squares);
    return ret;
    //    drawSquares(image, squares);
}

int main(int argc, char** argv)
{

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
