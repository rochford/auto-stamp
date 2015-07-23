"use strict";

var express = require('express'),
        mongodb = require('mongojs'),
        http = require('http'),
        _ = require('underscore'),
        request = require('request'),
        sentiment = require('sentiment'),
        stats = require("stats-lite"),
        rejectwords = require('./rejectwords.js');

var KEYWORDS = "penny black stamp";

var sentimentDictionary = {
    'tear': -3,
    'crease': -2,
    'repaired': -2,
    'creased': -2,
    'stain': -2,
    'bend': -1,
    'qv': 1,
    'close to 4 margins': 2,
    'almost 4 margins': 2,
    ' 4 margins': 4,
    'vfu': 3,
    'fu': 2,
    'mnh': 2,
    'wide': 2,
    'lightly struck': 1,
    'spacefiller': -1,
    'cancelled': 1,
    'crisp': 2
};

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
    var percentiles = [0.2,0.4,0.5,0.6,0.8,0.9];
    for (var i = 0; i < percentiles.length; i++) {
        console.log( "" + percentiles[i] + " percentile: %s", stats.percentile(totalPrice, percentiles[i]))
    }
    console.log('');
}

function handleItems(items) {
    for (var i = 0; i < items.length; ++i) {
        var myItem = {};
        var excludeItem = false;
        var item = items[i];
        myItem.itemid     = item.itemId[0];
        myItem.title    = item.title[0];
        myItem.condition      = item.condition;
        //myItem.sellingStatus = item.sellingStatus;
        myItem.currency =  item.sellingStatus[0].currentPrice[0]['@currencyId'];
        myItem.currentPrice =  parseFloat(item.sellingStatus[0].currentPrice[0]['__value__']);
        var result = sentiment(myItem.title, sentimentDictionary);
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
        if (rejectwords.rejectCheck(myItem.title)) {
            excludeItem = true;
        }

        if (!excludeItem && null !== myItem.title) {
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
    // Construct the request
    // Replace MyAppID with your Production AppID
    var url = "http://svcs.ebay.com/services/search/FindingService/v1";
    url += "?OPERATION-NAME=findCompletedItems";
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

    var cb = callback || request_cb;
    var tmpUrl = url + "&paginationInput.pageNumber="+page;
    request(tmpUrl, cb);
}

function request_first_cb(error, response, body) {
    if (!error && response.statusCode == 200) {
        var root = JSON.parse(body);
        var totalEntries = parseInt(root.findCompletedItemsResponse[0].paginationOutput[0].totalEntries[0]);
        var pageNumber = parseInt(root.findCompletedItemsResponse[0].paginationOutput[0].pageNumber[0]);
        totalPages = parseInt(root.findCompletedItemsResponse[0].paginationOutput[0].totalPages[0]);

        for (var i=1; i<=totalPages; i++) {
            sendRequest(i);
        }
    }
}

function request_cb(error, response, body, cb) {
    if (!error && response.statusCode == 200) {
        var root = JSON.parse(body);
        var items = root.findCompletedItemsResponse[0].searchResult[0].item || [];
        handleItems(items);
        calculateAvgPrice();
    } else {
        console.log(error);
    }
}

console.log('started');
var timeoutTimer = setTimeout(function() {
    console.log("Timeout");
    totalPages = 1;
    totalPrice = [];
    sendRequest(1, request_first_cb);
}, 60*1000);

var gracefulShutdown = function() {
    console.log("Received signal, shutting down gracefully.");
    db.close();
    process.exit();
}

// listen for TERM signal .e.g. kill
process.on ('SIGTERM', gracefulShutdown);

// listen for INT signal e.g. Ctrl-C
process.on ('SIGINT', gracefulShutdown);
