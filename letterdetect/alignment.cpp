#include <iostream>

using namespace std;

void verticalAlignment(int a) {
    switch (a) {
    case -4:
        cout << "ext high" ;
        break;
    case -3:
        cout << "very high" ;
        break;
    case -2:
        cout << "high" ;
        break;
    case -1:
        cout << "sl high" ;
        break;
    case 0:
        cout << "central" ;
        break;
    case 1:
        cout << "sl low" ;
        break;
    case 2:
        cout << "low" ;
        break;
    case 3:
        cout << "very low" ;
        break;
    case 4:
        cout << "ext low" ;
        break;
    default:
        cout << "XXX: " << a ;
    }
}

void horizontalAlignment(int a)
{
    switch (a) {
    case -4:
        cout << ", ext left" << endl;
        break;
    case -3:
        cout << ", very left" << endl;
        break;
    case -2:
        cout << ", left" << endl;
        break;
    case -1:
        cout << ", sl left" << endl;
        break;
    case 0:
        cout << ", central" << endl;
        break;
    case 1:
        cout << ", sl right" << endl;
        break;
    case 2:
        cout << ", right" << endl;
        break;
    case 3:
        cout << ", very right" << endl;
        break;
    case 4:
        cout << ", ext right" << endl;
        break;
    default:
        cout << "XXX: " << a << endl;
    }
}

