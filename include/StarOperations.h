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

class StarOperations
{
public:
    char choice;
    std::string latValue;
    std::string lonValue;
    std::string raValue;
    std::string decValue;
    std::string fast;
	std::vector<std::string> v;
	std::vector<std::string> v1;
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
    std::string r;
    long double setJDToNow();
    double earthRotationAngle(long double jd);
    long double * raDecToAltAz(double ra,double dec,double lat,double lon,long double jd_ut);
    std::string degreesToDMS(double d);

};

#endif // STAROPERATIONS_H
