auto-stamp
==========
I wanted to see if I could write a webserver that would correctly identify
the printing press used to print the rare penny black stamp. Human experts
charge about 5GBP to identify the printing press used and the service can take
weeks. I wanted a webserver that could do it in seconds. The printing press used
to print the penny black stamp impacts the value of the stamp.

Here is the webpage and a video showing it work:
http://www.qvplate.com


Project modules:

/node-litchfield-plate
A Node.js C++ plugin module that uses the /calc_plate/alignment.{c,h} functions
and data to calculate the printing press plate used.

/node-pennyblack
The Node.js webserver, uses node-litchfield-plate plugin to list the likely
printing press plates.

/calc_plate
OpenCV test UI application

/letterdetect
This directory includes algorithms to extract key points from the input stamp
image. Most of these files are not used in the webserver because the algorithm
was not good.
alignment.cpp - includes the alignment data for all of the penny
black stamps.
threshold.cpp - this file includes the logic to find the important data from
the input stamp image.
test_threshold.cpp includes unit tests for a variety of stamps in the /data
directory.

Project component backlogs:
===========================

(C++) threshold backlog
=======================
- unit test case cleanup threshold.h and main_threshold.cpp
- more stamps in test suite
- If red MX cancel is in Letter corner squares, try to filter it out.
- better blacklist - exclude all but corner letters
- test main() to test all ../data/ images
- if a child contour in a corner square goes out of the square then ignore it - probably a MX cancel
- O Flaw thinking
- node.js plugin considerations
- valgrind checking


node-pennyblack backlog
=======================
- threshold does not test so many thresholds, eg thres +=6
- security input validation of corner letter files (as deleting them).
- UI user experience cleanup (UX point click directive)
- use async series with async tmp file names.
- paypal donate button
- samples jade file
- Draft UI flow.
- file upload feature
- containizer the webserver.


node-litchfield-plate
=====================
- api to display letter alignment
