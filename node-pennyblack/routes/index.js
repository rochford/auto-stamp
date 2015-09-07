"use strict";

var cv = require('opencv'),
        request = require('request'),
        async = require('async'),
        plate = require('../../node-litchfield-plate/plate.js'),
        tmp = require('tmp');

exports.initialize = function() {
    plate.initialize();
}

exports.index =  function (req, res) {
    res.render('index', { path: req.path,
                   pageTitle: '1d plate'});
}

exports.postUrl = function(req, res){
    var url = req.body.stampurl;

    res.render('uploadedstamp', { path: req.path,
                   stampImg: url,
                   pageTitle: 'Uploaded Image'});
}

function validateForm(body) {
    var leftArray = ['A','B','C','D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T'];
    var rightArray = ['A','B','C','D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L'];
    if (leftArray.indexOf(body.letterleft) == -1)
        return false;
    if (rightArray.indexOf(body.letterright) == -1)
        return false;
    if (body.leftx < 1 || body.lefty < 1 || body.rightx < 1 || body.righty < 1)
        return false;
    if (!body.stampurl)
        return false;
    return true;
}

exports.postStampData = function(req, res){
    console.log(req.body);
    if (!validateForm(req.body)) {
        res.render('error', { pageTitle: 'Error'});
        return;
    }

    var url = req.body.stampurl;
    var s = new cv.ImageDataStream();

    s.on('load', function(matrix){
        var lPoint = new cv.Point(Math.round(req.body.leftx), Math.round(req.body.lefty));
        var rPoint = new cv.Point(Math.round(req.body.rightx), Math.round(req.body.righty));
        processStampImage(null, matrix, req, res,
                          req.body.letterleft,
                          req.body.letterright,
                          lPoint,
                          rPoint);
    })

    s.on('error', function(err){
        res.render('error', { pageTitle: 'Error'});
    })

    request(url).pipe(s);
}

function stampInfoCallback(req, res, leftData, rightData, plates) {
    var leftAlignText = plate.printAlignment(leftData.verticalAlignment, leftData.horizontalAlignment);
    var rightAlignText = plate.printAlignment(rightData.verticalAlignment, rightData.horizontalAlignment);

    res.render('result', { path: req.path,
                   pageTitle: 'Result',
                   stampImg: req.body.stampurl,
                   leftLetterImg: leftData.cornerImage,
                   leftAlignment: leftAlignText,
                   rightLetterImg: rightData.cornerImage,
                   rightAlignment: rightAlignText,
                   plates: plates
               });
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

function alignmentMaxLimit(n) {
    if (n > 0)
        n = Math.min(4, n);
    else
        n = Math.max(-4, n);
    return n;
}

function cornerSquare(img, square, letter) {
    var wfx = 1.0/(square.boundingBox.width/20.0);
    var hfx = 1.0/(square.boundingBox.height/20.0);
    var lleft = square.childTl.x*wfx - square.boundingBox.x*wfx;
    var lright = (square.boundingBox.x+square.boundingBox.width)*wfx - square.childBr.x*wfx;
    var ltop = square.childTl.y*hfx - square.boundingBox.y*hfx;
    var lbottom =  (square.boundingBox.y+square.boundingBox.height)*hfx - square.childBr.y*hfx;
    var vert = ltop - lbottom;
    var horiz = lleft - lright;
    vert = alignmentMaxLimit(vert);
    horiz = alignmentMaxLimit(horiz);

    var im_crop = img.crop(square.boundingBox.x, square.boundingBox.y,
                           square.boundingBox.width, square.boundingBox.height);
    var tmp = randomFileName(im_crop);
    return {vertical: vert, horizontal:horiz, image: tmp};
}

function getAlignment(img, arr, letter) {
    var croppedImage = 'images/unknowncorner.jpg';
    var vert = -1000, horiz = -1000;

    var corner = arr[Math.floor(arr.length / 2)];
    if (corner) {
        var ret = cornerSquare(img, corner, letter);
        console.log(letter, corner);
        vert = Math.round(ret.vertical);
        horiz = Math.round(ret.horizontal);
        croppedImage = ret.image;
    }
    console.log(letter, vert, horiz);
    return {cornerImage : croppedImage, verticalAlignment : vert, horizontalAlignment : horiz};
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

    for (var thresh= 20; thresh < 200; thresh += 3) {
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
                    //contours.approxPolyDP(childContour, 0.001, true);
                    var childBB = contours.boundingRect(childContour[2]);
                    if ( (childBB.x < tl.x)
                        && (childBB.x > bb.x))
                        tl = new cv.Point(childBB.x, tl.y);
                    if ( (childBB.y < tl.y)
                        && (childBB.y > bb.y))
                        tl = new cv.Point(tl.x, childBB.y);

                    if ( ((childBB.x + childBB.width ) > br.x)
                        && ((childBB.x + childBB.width ) < (bb.x + bb.width)))
                        br = new cv.Point(childBB.x + childBB.width, br.y);
                    if ( ((childBB.y + childBB.height ) > br.y )
                            && ((childBB.y + childBB.height ) < (bb.y + bb.height)))
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

    var leftSq = getAlignment(im_gray, leftArray, leftLetter);
    var rightSq = getAlignment(im_gray, rightArray, rightLetter);

    var buf = [];
    var offset = 1;
    while (offset< 3)
    {
        var plateResult = plate.calculate(leftLetter + rightLetter,
                                          leftSq.verticalAlignment, leftSq.horizontalAlignment,
                                          rightSq.verticalAlignment, rightSq.horizontalAlignment,
                                          offset);
        console.log("result["+ offset + "] " + plateResult.toString());
        buf[offset++] = plateResult;
    }

    stampInfoCallback(req, res,
                      leftSq,
                      rightSq,
                      buf);
}

function randomFileName(im_crop) {
    var name = tmp.tmpNameSync() + ".jpg";
    im_crop.save('public/images'+ name);
    return name;
}
