"use strict";

var excludeWords = [
            'Enschede',
            'hill', // recent publisher?
            'europhilex', // recent publisher?
            'rowland', // rowland hill recent publisher?
            'roland', // rowland hill recent publisher?
            'by wadham',
            'DOUGLAS N MUIR',
            '1940',
            '1970',
            '1971', // postal strike
            '1975',
            '1978',
            '1979',
            '1990',
            '1994',
            '1996',
            '2013',
            '2015',
            'half penny',
            'halfpenny',
            'Air Letter',
            'Litchfield',
            'Wright & Creeke',
            'PLATING Nissens Photos',
            'THE STORY OF THE PENNY BLACK',
            'GREAT BRITAIN: LINE ENGRAVED STAMPS 3rd Edition',
            'Magazine',
            'William Docwra Dockwra',
            'ivory',
            'mini sheet',
            'Investment',
            'exhibition',
            'isle of man',
            'St Vincent',
            'Guernsey',
            'barbados',
            'King Edward',
            'King George',
            'QEII',
            '1d pinks',
            'Sg8',
            'Sg 8',
            'miniture',
            'bpma',
            'machin',
            'booklet',
            'nude lady',
            'plating service',
            'plating express',
            'Plating Aid',
            'Stamp Mounts',
            'rare book',
            'postal history',
            'overprint',
            'plating service',
            'special event cover',
            'centenary',
            'reprint',
            'reissue',
            'perforated',
            'perfs',
            'plating of the penny black',
            'forgery',
            'forgeries',
            'necklace',
            'follies',
            'Facsimile',
            'drink coaster',
            'mug',
            'CeramicTiles',
            'gents tie',
            'rubber stamp',
            'slap',
            'cling',
            'barcode',
            'postage stamp cushion',
            'reproduction',
            'replica',
            'museum',
            'auction catalogue',
            'presentation packs',
            'first day cover',
            'perfs',
            'anniv',
            'anniv.',
            'anniversary',
            'anniversay',
            'annivesay',
            '150th',
            '150 th',
            '150 year',
            '175th',
            '175 th',
            '175 year',
            'printing in red',
            'penny red',
            'penny post',
            'red penny',
            'red brown plate',
            'penny blue',
            ' 2d ',
            'liberia',
            'palau',
            'William Docwra Dockwra'
        ];

exports.rejectCheck = function rejectCheck(text) {
    var str = text.toLowerCase();
    for(var y=0; y < excludeWords.length; y++) {
        if(str.indexOf(excludeWords[y].toLowerCase()) !== -1) {
            return true;
        }
    }
//    var thenum = str.replace( /^\D+/g, ''); // replace all leading non-digits with nothing
//    var num = parseInt(thenum);
//    if ((num !== 1840) && (num !== 1841)) {
//        console.log('rejecting ' + text);
//        return true;
//    }
    return false;
}
