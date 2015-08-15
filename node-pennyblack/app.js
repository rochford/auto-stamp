"use strict";

var express = require('express'),
        morgan = require('morgan'),
        methodOverride = require('method-override'),
        index = require('./routes/index.js'),
        info = require('./routes/info.js'),
        bodyParser = require('body-parser'),
        errorhandler = require('errorhandler'),
        http = require('http'),
        path = require('path');
var app = express();

app.set('port', process.env.PORT || 3000);
app.set('views', __dirname + '/views');
app.set('view engine', 'jade');
app.use(bodyParser.urlencoded({ extended: false })); // to support URL-encoded bodies
// app.use(morgan('dev'));
app.use(methodOverride());
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

http.createServer(app).listen(app.get('port'), function () {
    console.log("Express server listening on port " + app.get('port'));
});
