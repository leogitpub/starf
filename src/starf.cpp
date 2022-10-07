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

-----------------------------------------------------------------------------------
Hi, I am an Amateur Astronomer writing code as an Amateur C++ Programmer for my community.
If you plan to use this program code, it is very much appreciated if you recognize my efforts
and consider giving this project a Star. Also, please visit http://www.celestialprogramming.com/
for more interesting Astronomy based programs. Thanks to Greg Miller (gmiller@gregmiller.net)
for providing the Mathematical functions in Javascript release as public domain,
which can be found in "StarOperations.cpp"

If you think this program can be improved, please be my guest and submit your changes.
Thanks in advance.
**/

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
#include "include/StringOperations.h"
#include "include/StarOperations.h"


start(StarOperations& so){
while(true){
    so.jd= so.setJDToNow();
    so.altaz= so.raDecToAltAz(so.ra, so.dec, so.lat, so.lon, so.jd);
    so.r="Alt:"+so.degreesToDMS(so.altaz[1]/so.toRad)+" Az: "+so.degreesToDMS(so.altaz[0]/so.toRad);
	std::cout << so.r << "\r";
    fflush ( stdin );
	std::this_thread::sleep_for(std::chrono::milliseconds(std::stoi(so.fast)));
    }
}

 void initiateUserDataInputs(StarOperations& so){
    std::cout << "\nPlease input Latitude in decimal: ";
    getline(std::cin, so.latValue);
    std::cout << "Please input Longitude in decimal: ";
    getline(std::cin, so.lonValue);
    std::cout << "Please input RA in \"HH MM SS\" format: ";
    getline(std::cin, so.raValue);
    std::cout << "Please input DEC in \"+/- DD MM SS\" format: ";
    getline(std::cin, so.decValue);
	std::cout << "Please input How fast you want new Alt/Az values in milliseconds: ";
    getline(std::cin, so.fast);

    split(so.raValue, so.v, ' ' );
    split(so.decValue, so.v1, ' ' );

    so.ratod = std::stold(so.v[0]) + std::stold(so.v[1])/60 + std::stold(so.v[2])/3600;
    so.dectos = so.v1[0] + std::to_string(std::stold(so.v1[1]) + std::stold(so.v1[2])/60 + std::stold(so.v1[3])/3600);
    so.dectod = std::stold(so.dectos);
	so.lat=std::stold(so.latValue)*so.toRad;
    so.lon=std::stold(so.lonValue)*so.toRad;
    so.ra=so.ratod*so.toRad*15; //Convert RA from hours to degrees, then to radians
    so.dec=so.dectod*so.toRad;
    while(true){
        std::cout << "\n" << R"(Do you wish to Start running the Alt/Az numbers? (Y/N): )";
        std::cin >> so.choice;
        if(so.choice =='Y' || so.choice =='y'){
            break;
        }
        else if(so.choice =='N' || so.choice =='n'){
            exit(10);
        }
    }
    std::cout << "\n";
    start(so);
}

int main()
{

std::cout << R"(

Welcome to Starf, a celestial-body finder program written in C++.

Author: Omkaram Venkatesh.

How it works?
-------------
1. In order to find Alt/Az (Altitude and Azimuth) of any celestial object, you need to know the Ra/Dec (Right Ascension and Declination) of that object. There are plenty of sources on the Internet which can give you those details.
2. The Ra/Dec in Degrees/Hours/Minutes format.
3. Next, you need to know your Latitude and Longitude in decimal.
4. Finally, enter the values as prompted on the screen and start execution.
5. The program will display Alt/Az in realtime only.

Here are some popular and my favourite RA/DEC values:
-------------

M31 (Andromeda)	-> RA: 00h 42m 44.3s	 / Dec: +41 16' 9''
M45 (Pleiades	-> RA: 03h 47m 24s	 / Dec: +24 07' 00'
M15 (Pegasus)	-> RA: 21h 29m 58.33s	 / Dec: +12 10' 01.2''
M44 (Beehive)	-> RA: 08h 40.4m	 / Dec: +19 59'
Vega		-> RA: 18h 36m 56.33635s / Dec: +38 47' 01.2802''
Betelgeuse	-> RA: 05h 55m 10.30536s / Dec: +07 24' 25.4304''
Sirius		-> RA: 06h 45m 08.917s   / Dec: ~16 42' 58.02''
Rigel		-> RA: 05h 14m 32.27210s / Dec: ~08 12' 05.8981''
)" << '\n';

StarOperations so;
initiateUserDataInputs(so);

return 0;
}
