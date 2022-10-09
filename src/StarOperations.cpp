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

/**
The code I have written in this file is derived from the JavaScript code written by Greg Miller (gmiller@gregmiller.net) 2021
Released as public domain
http://www.celestialprogramming.com/
**/

#include "include/StarOperations.h"

long double timeSinceEpochMillisec(){
    using namespace std::chrono;
    return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}

long double JulianDateFromUnixTime(long double t){
    //Not valid for dates before Oct 15, 1582
    return (double(t) / 86400000.0) + 2440587.5;
}

long double StarOperations::setJDToNow(){
    return JulianDateFromUnixTime(timeSinceEpochMillisec());;
}

double earthRotationAngle(long double jd){
    //IERS Technical Note No. 32
    const double t = jd- 2451545.0;
    const double f = fmod(jd,1.0);
    double theta = 2*M_PI * (f + 0.7790572732640 + 0.00273781191135448 * t); //eq 14
    theta = fmod(theta, 2*M_PI);
    if(theta<0)theta+=2*M_PI;

    return theta;
}

double greenwichMeanSiderealTime(long double jd){
    //"Expressions for IAU 2000 precession quantities" N. Capitaine1,P.T.Wallace2, and J. Chapront
    const long double t = ((jd - (double) 2451545.0)) / (double) 36525.0;
    double gmst=earthRotationAngle(jd)+(0.014506 + 4612.156534*t + 1.3915817*t*t - 0.00000044 *t*t*t - 0.000029956*t*t*t*t - 0.0000000368*t*t*t*t*t)/60.0/60.0*M_PI/180.0;  //eq 42
    gmst= fmod(gmst, 2*M_PI);
    if(gmst<0) gmst+=2*M_PI;

    return gmst;
}

long double * StarOperations::raDecToAltAz(double ra,double dec,double lat,double lon,long double jd_ut){
    const double gmst=greenwichMeanSiderealTime(jd_ut);
    double localSiderealTime=fmod((gmst+lon),(2*M_PI));
    double H=(localSiderealTime - ra);
    if(H<0){
        H+=2*M_PI;
    }
    if(H>M_PI){
        H=H-2*M_PI;
    }
    double az = (atan2(sin(H), cos(H)*sin(lat) - tan(dec)*cos(lat)));
    double a = (asin(sin(lat)*sin(dec) + cos(lat)*cos(dec)*cos(H)));
    az-=M_PI;
    if(az<0){
        az+=2*M_PI;
    }
    static long double p[4];
    p[0]=az;
    p[1]=a;
    p[2]=localSiderealTime;
    p[3]=H;

    return p;
}

std::string StarOperations::degreesToDMS(double d)
{
    std::string sign="+";
    if(d<0){
        sign="-";
    }
    d=abs(d);
    double deg=(floor(d));
    d-=deg;
    d*=60;
    double min=(floor(d));
    d-=min;
    d*=60;
    double sec=(d);
    std::string degs = std::to_string((int)deg);
    std::string mins = std::to_string((int)min);
    std::string secs = std::to_string(sec);
    if(deg<100.0){
        degs= ("0"+ (degs));
    }
    if(deg<10.0){
        degs= ("0"+ (degs));
    }
    if(min<10){
        mins=("0"+ (mins));
    }
    if(sec<10){
        secs=("0"+ (secs));
    }

    return sign+(degs)+"\370 "+(mins)+"' "+(secs)+"\"";
}
