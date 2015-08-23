"use strict";

var cv = require('../../node-opencv/lib/opencv'),
        request = require('request'),
        async = require('async'),
        plate = require('../../node-litchfield-plate/plate.js'),
        tmp = require('tmp');

exports.initialize = function() {
    plate.initialize();
}

exports.index =  function (req, res) {
    console.log("app.get(/index) ");

    res.render('index', { path: req.path,
                   pageTitle: 'Upload'});
}

exports.postUrl = function(req, res){
    console.log("postUrl");
    console.log(req.body);
    var url = req.body.stampurl;

    res.render('uploadedstamp', { path: req.path,
                   stampImg: url,
                   pageTitle: 'Upload'});
}

exports.postStampData = function(req, res){
    console.log("postStampData");
    console.log(req.body);
    var url = req.body.stampurl;
    var s = new cv.ImageDataStream();

    s.on('load', function(matrix){
        console.log('loaded');

        var lPoint = new cv.Point(parseInt(req.body.leftx), parseInt(req.body.lefty));
        var rPoint = new cv.Point(parseInt(req.body.rightx), parseInt(req.body.righty));
        console.log(lPoint.x);
        processStampImage(null, matrix, req, res,
                          req.body.letterleft,
                          req.body.letterright,
                          lPoint,
                          rPoint);
    })

    request(url).pipe(s);
}

function stampInfoCallback(req, res, leftData, rightData, plates) {
    console.log("callback");
    var leftAlignText = plate.printAlignment(leftData.verticalAlignment, leftData.horizontalAlignment);
    var rightAlignText = plate.printAlignment(rightData.verticalAlignment, rightData.horizontalAlignment);
    res.render('result', { path: req.path,
                   pageTitle: 'result',
                   stampImg: req.body.stampurl,
                   leftLetterImg: leftData.cornerImage,
                   leftAlignment: leftAlignText,
                   rightLetterImg: rightData.cornerImage,
                   rightAlignment: rightAlignText,
                   plates: plates});
}

var constanttl = new cv.Point(1000, 1000);
var constantbr = new cv.Point(0, 0);

function angle(pt1, pt2, pt0) {
    var dx1 = pt1.x - pt0.x;
    var dy1 = pt1.y - pt0.y;
    var dx2 = pt2.x - pt0.x;
    var dy2 = pt2.y - pt0.y;
    return (dx1*dx2 + dy1*dy2)/Math.sqrt((dx1*dx1 + dy1*dy1)*(dx2*dx2 + dy2*dy2) + 1e-10);
}

function cornerSquare(img, square) {
    var fx = 1.0/(square.boundingBox.width/20.0);
    var lleft = square.childTl.x*fx - square.boundingBox.x*fx;
    var lright = (square.boundingBox.x+square.boundingBox.width)*fx - square.childBr.x*fx;
    var ltop = square.childTl.y*fx - square.boundingBox.y*fx;
    var lbottom =  (square.boundingBox.y+square.boundingBox.height)*fx - square.childBr.y*fx;
    var vert = ltop - lbottom;
    var horiz = lleft - lright;
    var im_crop = img.crop(square.boundingBox.x, square.boundingBox.y,
                           square.boundingBox.width, square.boundingBox.height);
    var tmp = randomFileName(im_crop);
    return {vertical: vert, horizontal:horiz, image: tmp};
}

function processStampImage(err, im, req, res, leftLetter, rightLetter, lPoint, rPoint) {
    var leftArray = [];
    var rightArray = [];

    if (err) throw err;
    var width = im.width();
    var height = im.height();
    if (width < 1 || height < 1) throw new Error('Image has no size');

    var im_gray = new cv.Matrix(height, width);

    im_gray = im.copy();
    im_gray.resize(540,660);
    im_gray.convertGrayscale();

    for (var thresh= 20; thresh < 200; thresh++) {
        var dst = im_gray.threshold(thresh, 255, "Binary Inverted");
        dst.medianBlur(3);
        dst.canny(thresh, thresh*3);

        var contours = dst.findContours(3);
        for(var j = 0; j < contours.size(); j++) {
            contours.approxPolyDP(j, 4, true);
            var bb = contours.boundingRect(j);
            if (!(bb.x < lPoint.x)
                    || !(lPoint.x < (bb.x + bb.width))
                    || !(bb.y < lPoint.y)
                    ||  !(lPoint.y < (bb.y + bb.height) )) {
                if (!(bb.x < rPoint.x)
                        || !(rPoint.x < (bb.x + bb.width))
                        || !(bb.y < rPoint.y)
                        ||  !(rPoint.y < (bb.y + bb.height) )) {
                    continue;
                }
            }
            if (!(bb.x < rPoint.x)
                    || !(rPoint.x < (bb.x + bb.width))
                    || !(bb.y < rPoint.y)
                    ||  !(rPoint.y < (bb.y + bb.height) )) {
                if (!(bb.x < lPoint.x)
                        || !(lPoint.x < (bb.x + bb.width))
                        || !(bb.y < lPoint.y)
                        ||  !(lPoint.y < (bb.y + bb.height) )) {
                    continue;
                }
            }
            var maxCosine = 0;
            for( var k = 2; k < contours.cornerCount(j)+1; k++ )
            {
                // find the maximum cosine of the angle between joint edges
                var cosine = Math.abs(angle(contours.point(j, k%4), contours.point(j, k-2), contours.point(j, k-1)));
                maxCosine = Math.max(maxCosine, cosine);
            }

            if (maxCosine < 0.3) {

                // child checking.
                var childContour = contours.hierarchy(j);
                var tl = new cv.Point(1000, 1000);
                var br = new cv.Point(0, 0);
                while (childContour[2] !== -1) {
                    contours.approxPolyDP(childContour, 0.001, true);
                    var childBB = contours.boundingRect(childContour[2]);

                    if ( childBB.x < tl.x)
                        tl = new cv.Point(childBB.x, tl.y);
                    if ( childBB.y < tl.y)
                        tl = new cv.Point(tl.x, childBB.y);

                    if ( (childBB.x + childBB.width ) > br.x)
                        br = new cv.Point(childBB.x + childBB.width, br.y);
                    if ( (childBB.y + childBB.height ) > br.y)
                        br = new cv.Point(br.x, childBB.y + childBB.height);

                    childContour = contours.hierarchy(childContour[2]);
                }
                if (tl.x === constanttl.x || br.x === constantbr.x ||
                        tl.y === constanttl.y || br.y === constantbr.y)
                    continue;

                if ((bb.x < lPoint.x)
                        && (lPoint.x < (bb.x + bb.width))
                        && (bb.y < lPoint.y)
                        && (lPoint.y < (bb.y + bb.height) )) {
                    leftArray.push({boundingBox: bb, threshold: thresh, contour: j,
                                       childTl: { x: tl.x, y:tl.y}, childBr:{ x: br.x, y:br.y}});
                } else if ((bb.x < rPoint.x)
                           && (rPoint.x < (bb.x + bb.width))
                           && (bb.y < rPoint.y)
                           && (rPoint.y < (bb.y + bb.height) )) {
                    rightArray.push({boundingBox: bb, threshold: thresh, contour: j,
                                        childTl:{ x: tl.x, y:tl.y}, childBr:{ x: br.x, y:br.y}});
                }

                //                console.log('total child rect: ' + tl.x + ', ' + tl.y);
            }
        }
    }

    var leftImg = 'images/unknowncorner.jpg';
    var rightImg = 'images/unknowncorner.jpg';

    var lvert = -1000;
    var lhoriz = -1000;
    var rvert = -1000;
    var rhoriz = -1000;

    var left = leftArray[Math.floor(leftArray.length / 2)];
    if (left) {
        var ret = cornerSquare(im_gray, left);
        lvert = ret.vertical;
        lhoriz = ret.horizontal;
        leftImg = ret.image;
    }
    var right = rightArray[Math.floor(rightArray.length / 2)];
    if (right) {
        var ret = cornerSquare(im_gray, right);
        rvert = ret.vertical;
        rhoriz = ret.horizontal;
        rightImg = ret.image;
    }

    var buf = "";
    var offset = 0;
    while (buf.toString().length < 2 && offset< 3) {
        buf = plate.calculate(leftLetter + rightLetter, lvert, lhoriz, rvert, rhoriz, offset++);
    }
    console.log("result: " + buf.toString());

    var leftData = {};
    leftData.cornerImage = leftImg;
    leftData.verticalAlignment = lvert;
    leftData.horizontalAlignment = lhoriz;
    var rightData = {};
    rightData.cornerImage = rightImg;
    rightData.verticalAlignment = rvert;
    rightData.horizontalAlignment = rhoriz;
    console.log('done');
    stampInfoCallback(req, res,
                      leftData,
                      rightData,
                      buf);
}

function randomFileName(im_crop)
{
    var name = tmp.tmpNameSync();
    im_crop.save('public/images'+ name + ".jpg" );
    return name + ".jpg"
}
