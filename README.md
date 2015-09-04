auto-stamp
==========
Penny black plate detection

threshold backlog
====================
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
