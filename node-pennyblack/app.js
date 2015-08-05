"use strict";
var cv = require('../node-opencv/lib/opencv');
var request = require('request');
var fs = require('fs');

var constanttl = new cv.Point(1000, 1000);
var constantbr = new cv.Point(0, 0);
var lPoint = new cv.Point(54, 468);
var rPoint = new cv.Point(425, 464);

var leftArray = [];
var rightArray = [];

function angle(pt1, pt2, pt0) {
    var dx1 = pt1.x - pt0.x;
    var dy1 = pt1.y - pt0.y;
    var dx2 = pt2.x - pt0.x;
    var dy2 = pt2.y - pt0.y;
    return (dx1*dx2 + dy1*dy2)/Math.sqrt((dx1*dx1 + dy1*dy1)*(dx2*dx2 + dy2*dy2) + 1e-10);
}

function processStampImage(err, im) {
    if (err) throw err;
    var width = im.width();
    var height = im.height();
    if (width < 1 || height < 1) throw new Error('Image has no size');

    var im_gray = new cv.Matrix(height, width);

    im_gray = im.copy();
    im_gray.resize(77*6,88*6);
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
            if ( contours.cornerCount(j) === 4 && contours.isConvex(j)) {

                var maxCosine = 0;
                for( var k = 2; k < 5; k++ )
                {
                    // find the maximum cosine of the angle between joint edges
                    var cosine = Math.abs(angle(contours.point(j, k%4), contours.point(j, k-2), contours.point(j, k-1)));
                    maxCosine = Math.max(maxCosine, cosine);
                }

                if (maxCosine < 0.3) {

                    //                    console.log(bb);
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
                    if (tl.x == constanttl.x || br.x == constantbr.x ||
                            tl.y == constanttl.y || br.y == constantbr.y)
                        continue;

                    if ((bb.x < lPoint.x)
                            && (lPoint.x < (bb.x + bb.width))
                            && (bb.y < lPoint.y)
                            && (lPoint.y < (bb.y + bb.height) )) {
                        leftArray.push({boundingBox: bb, threshold: thresh, contour: j, childTl: { x: tl.x, y:tl.y}, childBr:{ x: br.x, y:br.y}});
                    } else if ((bb.x < rPoint.x)
                               && (rPoint.x < (bb.x + bb.width))
                               && (bb.y < rPoint.y)
                               && (rPoint.y < (bb.y + bb.height) )) {
                        rightArray.push({boundingBox: bb, threshold: thresh, contour: j, childTl:{ x: tl.x, y:tl.y}, childBr:{ x: br.x, y:br.y}});
                    }

                    //console.log('total child rect: ' + tl.x + ', ' + tl.y);
                }
            }
        }
    }

    im_gray.save('gray.jpg');
    var left = leftArray[Math.floor(leftArray.length / 2)];
    if (left) {
        console.log(left);
        var im_crop = im_gray.crop( left.boundingBox.x, left.boundingBox.y, left.boundingBox.width, left.boundingBox.height);
        im_crop.save('qvplate'+ left.threshold +  'left' + '.jpg' );
    }
    var right = rightArray[Math.floor(rightArray.length / 2)];
    if (right) {
        console.log(right);
        im_crop = im_gray.crop( right.boundingBox.x, right.boundingBox.y, right.boundingBox.width, right.boundingBox.height);
        im_crop.save('qvplate'+ right.threshold +  'right' + '.jpg' );
    }
    console.log('done');
}


var s = new cv.ImageDataStream();

s.on('load', function(matrix){
    console.log('loaded');
//    cv.readImage(matrix, processStampImage);
    processStampImage(null, matrix);
})
s.on('end', function(matrix){
    console.log('end');
})

// request('http://thumbs1.ebaystatic.com/d/l225/m/m49DWYRoVidktSF-QxAzsAQ.jpg').pipe(s);
// request('http://thumbs1.ebaystatic.com/d/l225/m/mdmVN2j5ksmcIQQkoZYp35g.jpg').pipe(s);
//request('http://thumbs3.ebaystatic.com/d/l225/m/mkZ4BNd8FNv0wNfSoppQjrw.jpg').pipe(s);
request('http://thumbs3.ebaystatic.com/d/l225/m/mt2WWknJ-Q6xnBVMT0DpGDA.jpg').pipe(s);
