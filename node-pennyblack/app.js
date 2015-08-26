"use strict";

var express = require('express'),
        morgan = require('morgan'),
        methodOverride = require('method-override'),
        index = require('./routes/index.js'),
        info = require('./routes/info.js'),
        bodyParser = require('body-parser'),
        errorhandler = require('errorhandler'),
        http = require('http'),
        fs = require('fs'),
        path = require('path');
var app = express();

app.set('port', process.env.PORT || 3000);
app.set('views', __dirname + '/views');
app.set('view engine', 'jade');
app.use(bodyParser.urlencoded({ extended: false })); // to support URL-encoded bodies
// app.use(morgan('dev'));
app.use(methodOverride());

app.get('/tmp/:file', function(req, res) {
    console.log(req.params);
    res.sendFile(__dirname + '/public/images/tmp/'+ req.params.file, {}, function (err) {
        if (err) {
            console.log(err);
            res.status(err.status).end();
        }
        else {
            fs.unlink(__dirname + '/public/images/tmp/'+ req.params.file, function(err) {
                if (err) {
                    console.log(err);
                }
            });
        }
    });
});

app.use(express.static(path.join(__dirname, 'public')));

var env = process.env.NODE_ENV || 'development';
if ('development' == env) {
    app.use(errorhandler());
}

app.get('/', index.index);
app.post('/upload', index.postUrl);
app.post('/stampdata', index.postStampData);
app.get('/limitations', info.limitations);
app.get('/about', info.about);
app.get('/privacy-policy', info.privacy);

// create directory
fs.mkdirSync('public/images/tmp');

http.createServer(app).listen(app.get('port'), function () {
    index.initialize();
    console.log("Express server listening on port " + app.get('port'));
});
