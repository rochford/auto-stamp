"use strict";

var plate = require('bindings')('plate');

exports.initialize = function()
{
    plate.initialize();
}

exports.calculate = function(letters,
                             leftVert,
                             leftHoriz,
                             rightVert,
                             rightHoriz,
                             offset)
{
    if (Math.abs(leftVert) > 6)
        leftVert = -1000;
    if (Math.abs(leftHoriz) > 6)
        leftHoriz = -1000;
    if (Math.abs(rightVert) > 6)
        rightVert = -1000;
    if (Math.abs(rightHoriz) > 6)
        rightHoriz = -1000;
    var ret = plate.calculate(letters,
                              leftVert,
                              leftHoriz,
                              rightVert,
                              rightHoriz,
                              offset);
    return ret;
}

function verticalAlignment(a) {
    switch (a) {
    case -7:
    case -6:
    case -5:
    case -4:
        return "ext high" ;
    case -3:
        return "very high" ;
    case -2:
        return "high" ;
    case -1:
        return "sl high" ;
    case 0:
        return "central" ;
    case 1:
        return "sl low" ;
    case 2:
        return "low" ;
    case 3:
        return "very low" ;
    case 4:
    case 5:
    case 6:
    case 7:
        return "ext low" ;
    default:
        return "?";
    }
}

function horizontalAlignment(a)
{
    switch (a) {
    case -7:
    case -6:
    case -5:
    case -4:
        return ", ext left";
    case -3:
        return ", very left";
    case -2:
        return ", left";
    case -1:
        return ", sl left";
    case 0:
        return ", central";
    case 1:
        return ", sl right";
    case 2:
        return ", right";
    case 3:
        return ", very right";
    case 4:
    case 5:
    case 6:
    case 7:
        return ", ext right";
    default:
        return ", ?";
    }
}

exports.printAlignment = function(offsetVertical,
                                  offsetHorizontal)
{
    var ret = verticalAlignment(Math.round(offsetVertical));
    ret = ret + horizontalAlignment(Math.round(offsetHorizontal));
    return ret;
}
