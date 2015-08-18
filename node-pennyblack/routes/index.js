"use strict";

var cv = require('../../node-opencv/lib/opencv'),
        request = require('request'),
        plate = require('../../node-litchfield-plate/plate.js');

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

function stampInfoCallback(req, res, l, r, img, leftImg, rightImg, plates) {
    console.log("callback");
    res.render('result', { path: req.path,
                   pageTitle: 'result',
                   stampImg: req.body.stampurl,
                   leftLetterImg: leftImg,
                   rightLetterImg: rightImg,
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

    var stampImg = 'images/gray.jpg';
    var leftImg = 'images/unknowncorner.jpg';
    var rightImg = 'images/unknowncorner.jpg';
    im_gray.save(stampImg);

    var fx = 1.0;
    var lvert = -1000;
    var lhoriz = -1000;
    var rvert = -1000;
    var rhoriz = -1000;

    var left = leftArray[Math.floor(leftArray.length / 2)];
    if (left) {
        fx = 1.0/(left.boundingBox.width/20.0);
        var lleft = left.childTl.x*fx - left.boundingBox.x*fx;
        var lright = (left.boundingBox.x+left.boundingBox.width)*fx - left.childBr.x*fx;
        var ltop = left.childTl.y*fx - left.boundingBox.y*fx;
        var lbottom =  (left.boundingBox.y+left.boundingBox.height)*fx - left.childBr.y*fx;
        lvert = ltop - lbottom;
        lhoriz = lleft - lright;
        var im_crop = im_gray.crop( left.boundingBox.x, left.boundingBox.y, left.boundingBox.width, left.boundingBox.height);
        im_crop.save('public/images/qvplate'+ left.threshold +  'left' + '.jpg' );
        leftImg = 'images/qvplate'+ left.threshold +  'left' + '.jpg';
    }
    var right = rightArray[Math.floor(rightArray.length / 2)];
    if (right) {
        fx = 1.0/(right.boundingBox.width/20.0);
        var rleft = right.childTl.x*fx - right.boundingBox.x*fx;
        var rright = (right.boundingBox.x+right.boundingBox.width)*fx - right.childBr.x*fx;
        var rtop = right.childTl.y*fx - right.boundingBox.y*fx;
        var rbottom =  (right.boundingBox.y+right.boundingBox.height)*fx - right.childBr.y*fx;
        rvert = rtop - rbottom;
        rhoriz = rleft - rright;

        im_crop = im_gray.crop( right.boundingBox.x, right.boundingBox.y, right.boundingBox.width, right.boundingBox.height);

        im_crop.save('public/images/qvplate'+ right.threshold +  'right' + '.jpg' );
        rightImg = 'images/qvplate'+ right.threshold +  'right' + '.jpg';
    }
    var buf = plate.calculate(leftLetter + rightLetter, lvert, lhoriz, rvert, rhoriz);
    console.log(plate.printAlignment(lvert, lhoriz));
    console.log(plate.printAlignment(rvert, rhoriz));
    console.log("result: " + buf.toString());

    console.log('done');
    stampInfoCallback(req, res, left, right, stampImg,
                      leftImg,
                      rightImg,
                      buf);
}
