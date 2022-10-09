/**
MIT License

Copyright (c) Omkaram Venkatesh

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights to use,
copy, modify, merge, publish, distribute, sublicense, and/or
sell copies of the Software, and to permit persons to whom the Software
is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR
IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
**/

#ifndef STAROPERATIONS_H
#define STAROPERATIONS_H
#define _USE_MATH_DEFINES
#include <cmath>
#include <chrono>
#include <cstdint>
#include <iostream>
#include <iomanip>
#include <math.h>
#include <thread>
#include <cfloat>
#include <string.h>
#include <vector>

class StarOperations{
	
public:
    char choice;
    std::string latValue;
    std::string lonValue;
    std::string raValue;
    std::string decValue;
    std::string fast;
    std::vector<std::string> raStringSplit;
    std::vector<std::string> decStringSplit;
    double ratod;
    std::string dectos;
    double dectod;
    long double toRad=M_PI/180;
    long double lat;
    long double lon;
    long double ra; //Convert RA from hours to degrees, then to radians
    long double dec;
    long double jd;
    long double * altaz;
    std::string printer;
    long double setJDToNow();
    double earthRotationAngle(long double jd);
    long double * raDecToAltAz(double ra,double dec,double lat,double lon,long double jd_ut);
    std::string degreesToDMS(double d);

};

#endif // STAROPERATIONS_H
