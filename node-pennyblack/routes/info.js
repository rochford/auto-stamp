"use strict";

var pjson = require('../package.json');

exports.limitations =  function (req, res) {
    res.render('limitations', { path: req.path,
                           pageTitle: 'Limitations'});
}

exports.about =  function (req, res) {
    res.render('about', { path: req.path,
                           version: pjson.version,
                           pageTitle: 'About'});
}

exports.privacy =  function (req, res) {
    res.render('privacy-policy', { path: req.path,
                           version: pjson.version,
                           pageTitle: 'Privacy Policy'});
}
