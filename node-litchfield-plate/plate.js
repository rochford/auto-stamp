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
                             rightHoriz)
{
    var ret = plate.calculate(letters,
                              leftVert,
                              leftHoriz,
                              rightVert,
                              rightHoriz);
    return ret;
}

function verticalAlignment(a) {
    switch (a) {
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
        return "ext low" ;
    }
}

function horizontalAlignment(a)
{
    switch (a) {
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
        return ", ext right";
    }
}

exports.printAlignment = function(offsetVertical,
                                  offsetHorizontal)
{
    var ret = verticalAlignment(parseInt(offsetVertical));
    ret = ret + horizontalAlignment(parseInt(offsetHorizontal));
    return ret;
}
