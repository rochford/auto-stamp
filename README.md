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
- Draft UI flow.
- UI user experience cleanup (UX point click directive)
- security input validation of corner letter files (as deleting them).
- use async series with async tmp file names.
- file upload feature
- samples jade file
- error page
- update limitations file
- NGINX DNS- share server with animalguess.com
- analytics

node-litchfield-plate
=====================
- javascript wrapper for the c++
- alignment to text functions
