"use strict";

var express = require('express'),
        mongodb = require('mongojs'),
        http = require('http'),
        _ = require('underscore'),
        request = require('request'),
        sentiment = require('sentiment'),
        stats = require("stats-lite");
var KEYWORDS = "penny black stamp";
var excludeWords = [
            'Enschede',
            'hill', // recent publisher?
            'europhilex', // recent publisher?
            'rowland', // rowland hill recent publisher?
            'by wadham',
            '1970',
            '1971', // postal strike
            '1975',
            '1978',
            '1990',
            '1994',
            '2015',
            'half penny',
            'Litchfield',
            'Wright & Creeke',
            'PLATING Nissens Photos',
            'THE STORY OF THE PENNY BLACK',
            'GREAT BRITAIN: LINE ENGRAVED STAMPS 3rd Edition',
            'isle of man',
            'St Vincent',
            'Guernsey',
            'barbados',
            'King Edward',
            'bpma',
            'machin',
            'booklet',
            'rare book',
            'postal history',
            'overprint',
            'plating service',
            'special event cover',
            'centenary',
            'reprint',
            'reissue',
            'perforated',
            'forgery',
            'forgeries',
            'necklace',
            'follies',
            'drink coaster',
            'mug',
            'CeramicTiles',
            'gents tie',
            'rubber stamp',
            'barcode',
            'postage stamp cushion',
            'reproduction',
            'replica',
            'auction catalogue',
            'presentation packs',
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
            'penny red',
            'red brown plate',
            'liberia'
        ];

// Array to hold async tasks
var asyncTasks = [];

// Create a JavaScript array of the item filters you want to use in your request
var filterarray = [
            {"name":"MinPrice",
                "value":"0.10",
                "paramName":"Currency",
                "paramValue":"GBP"},
            {"name":"MaxPrice",
                "value":"99999",
                "paramName":"Currency",
                "paramValue":"GBP"},
            {"name":"HideDuplicateItems",
                "value":"true",
                "paramName":"",
                "paramValue":""},
            {"name":"ListingType",
                "value":["Auction","AuctionWithBIN", "FixedPrice", "StoreInventory"],
                "paramName":"",
                "paramValue":""}
        ];

// Define global variable for the URL filter
var urlfilter = "";

// Generates an indexed URL snippet from the array of item filters
function  buildURLArray() {
    // Iterate through each filter in the array
    for(var i=0; i<filterarray.length; i++) {
        //Index each item filter in filterarray
        var itemfilter = filterarray[i];
        // Iterate through each parameter in each item filter
        for(var index in itemfilter) {
            // Check to see if the paramter has a value (some don't)
            if (itemfilter[index] !== "") {
                if (itemfilter[index] instanceof Array) {
                    for(var r=0; r<itemfilter[index].length; r++) {
                        var value = itemfilter[index][r];
                        urlfilter += "&itemFilter\(" + i + "\)." + index + "\(" + r + "\)=" + value ;
                    }
                }
                else {
                    urlfilter += "&itemFilter\(" + i + "\)." + index + "=" + itemfilter[index];
                }
            }
        }
    }
}  // End buildURLArray() function

// Execute the function to build the URL filter
buildURLArray(filterarray);

// Construct the request
// Replace MyAppID with your Production AppID
var url = "http://svcs.ebay.com/services/search/FindingService/v1";
url += "?OPERATION-NAME=findItemsByKeywords";
url += "&SERVICE-VERSION=1.0.0";
url += "&SECURITY-APPNAME="+process.env.APP_ID;
url += "&GLOBAL-ID=EBAY-GB";
url += "&RESPONSE-DATA-FORMAT=JSON";
//url += "&callback=_cb_findItemsByKeywords";
url += "&REST-PAYLOAD";
url += "&outputSelector=SellerInfo";
url += "&keywords=" + encodeURIComponent(KEYWORDS);
url += "&paginationInput.entriesPerPage=100";
url += urlfilter;

var totalPages = 1;
var totalPrice = [];

var databaseUrl = process.env.MONGO_SERVER_URL, // "username:password@example.com/mydb"
        collections = ["stamps"];
var db = require("mongojs").connect(databaseUrl, collections);

sendRequest(1, request_first_cb);

function calculateAvgPrice()
{
    console.log('Total Items: ' + totalPrice.length);
    //    console.log("sum: %s", stats.sum(totalPrice))
    console.log("mean: %s", stats.mean(totalPrice))
    console.log("median: %s", stats.median(totalPrice))
    console.log("mode: %s", stats.mode(totalPrice))
    //    console.log("variance: %s", stats.variance(totalPrice))
    console.log("standard deviation: %s", stats.stdev(totalPrice))
    console.log("20th percentile: %s", stats.percentile(totalPrice, 0.20))
    console.log("30th percentile: %s", stats.percentile(totalPrice, 0.30))
    console.log("40th percentile: %s", stats.percentile(totalPrice, 0.40))
    console.log("50th percentile: %s", stats.percentile(totalPrice, 0.50))
    console.log("60th percentile: %s", stats.percentile(totalPrice, 0.60))
    console.log("70th percentile: %s", stats.percentile(totalPrice, 0.70))
    console.log("80th percentile: %s", stats.percentile(totalPrice, 0.80))
    console.log("85th percentile: %s", stats.percentile(totalPrice, 0.85))
    console.log("90th percentile: %s", stats.percentile(totalPrice, 0.90))
    console.log("95th percentile: %s", stats.percentile(totalPrice, 0.95))
    console.log("98th percentile: %s", stats.percentile(totalPrice, 0.98))
    console.log('');
}

function handleItems(items) {
    for (var i = 0; i < items.length; ++i) {
        var myItem = {};
        var excludeItem = false;
        var item     = items[i];
        myItem.itemid     = item.itemId[0];
        myItem.title    = item.title[0];
        myItem.condition      = item.condition;
        //myItem.sellingStatus = item.sellingStatus;
        myItem.currency =  item.sellingStatus[0].currentPrice[0]['@currencyId'];
        myItem.currentPrice =  parseFloat(item.sellingStatus[0].currentPrice[0]['__value__']);
        var result = sentiment(myItem.title);
        myItem.sentiment = result.score;

        if (myItem.currency != "GBP") {
            //            console.log(myItem.title);
            continue;
        }
        if (item.condition) {
            //            console.log(myItem.title);
            continue;
        }
        myItem.galleryURL      = item.galleryURL;
        myItem.viewitem = item.viewItemURL;
        for(var y=0; y < excludeWords.length; y++) {
            if(myItem.title.toLowerCase().indexOf(excludeWords[y]) !== -1) {
                excludeItem = true;
                break;
            }
            if(myItem.title.toLowerCase().indexOf("VR") !== -1) {
                console.log(myItem.title);
            }
        }

        if (!excludeItem && null != myItem.title) {
            //        console.log(myItem.title);
            db.stamps.update({itemid: myItem.itemid}, myItem, {upsert: true}, function (err, lastErrorObject) {
                if (err)
                    return;
                //              process.stdout.write(".");
                totalPrice.push(myItem.currentPrice);
            });
        }
    }
}

function sendRequest(page, callback) {
    var cb = callback || request_cb;
    var tmpUrl = url + "&paginationInput.pageNumber="+page;
    request(tmpUrl, cb);
}

function request_first_cb(error, response, body) {
    if (!error && response.statusCode == 200) {
        var root = JSON.parse(body);
        var totalEntries = parseInt(root.findItemsByKeywordsResponse[0].paginationOutput[0].totalEntries[0]);
        //        console.log('totalEntries: ' +totalEntries);
        var pageNumber = parseInt(root.findItemsByKeywordsResponse[0].paginationOutput[0].pageNumber[0]);
        //        console.log('pageNumber: ' +pageNumber);

//        console.log(root);
        totalPages = parseInt(root.findItemsByKeywordsResponse[0].paginationOutput[0].totalPages[0]);

        for (var i=1; i<=totalPages; i++) {
            sendRequest(i);
        }
    }
}

function request_cb(error, response, body, cb) {
    if (!error && response.statusCode == 200) {
        var root = JSON.parse(body);
        var items = root.findItemsByKeywordsResponse[0].searchResult[0].item || [];
        handleItems(items);
        process.stdout.write(".");
        calculateAvgPrice();
    } else {
        console.log(error);
    }
}

console.log('started');
var timeoutTimer = setTimeout(function() { console.log("Timeout"); db.close(); }, 50*1000);
