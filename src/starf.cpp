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
#include <atomic>
#include "include/StringOperations.h"
#include "include/StarOperations.h"
#include <windows.h>

void clearScreen(){

   #if defined(_WIN32)
       HANDLE                     hStdOut;
       CONSOLE_SCREEN_BUFFER_INFO csbi;
       DWORD                      count;
       DWORD                      cellCount;
       COORD                      homeCoords = { 0, 0 };

       hStdOut = GetStdHandle( STD_OUTPUT_HANDLE );
       if (hStdOut == INVALID_HANDLE_VALUE) return;

       /* Get the number of cells in the current buffer */
       if (!GetConsoleScreenBufferInfo( hStdOut, &csbi )) return;
           cellCount = csbi.dwSize.X *csbi.dwSize.Y;

       /* Fill the entire buffer with spaces */
       if (!FillConsoleOutputCharacter(
           hStdOut,
           (TCHAR) ' ',
           cellCount,
           homeCoords,
           &count
        )) return;

        /* Fill the entire buffer with the current colors and attributes */
        if (!FillConsoleOutputAttribute(
            hStdOut,
            csbi.wAttributes,
            cellCount,
            homeCoords,
            &count
        )) return;

        /* Move the cursor home */
        SetConsoleCursorPosition( hStdOut, homeCoords );
   #elif defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
       //system("clear");
       std::cout<< u8"\033[2J\033[1;1H"; //Using ANSI Escape Sequences
   #elif defined (__APPLE__)
       system("clear");
   #endif
}

std::atomic<bool> stop = false;
std::string latValue;
std::string lonValue;
std::string fast;
char choice;

void start(StarOperations* so, size_t so_size){
  while(!stop){
      clearScreen();
      for (size_t i = 0; i < (so_size); i++) {
         so[i].jd= so[i].setJDToNow();
         so[i].altaz= so[i].raDecToAltAz(so[i].ra, so[i].dec, so[i].lat, so[i].lon, so[i].jd);
         so[i].printer= so[i].celName + "\t-\tAlt:"+so[i].degreesToDMS(so[i].altaz[1]/so[i].toRad)+" Az: "+so[i].degreesToDMS(so[i].altaz[0]/so[i].toRad);
         std::cout << so[i].printer << "\n";
       }
	  std::cout << "Press c and enter to break" << "\n";
      std::this_thread::sleep_for(std::chrono::milliseconds(std::stoi(fast)));
  }
}

void initiateUserDataInputs(StarOperations* so, size_t so_size){
    std::cout << "\nPlease input How fast you want new Alt/Az values in milliseconds: ";
    getline(std::cin, fast);
    std::cout << "\n" << R"(Do you wish to Start running the Alt/Az numbers? (Y/N): )";

    while(true){
        std::cin >> choice;
        if(choice =='Y' || choice =='y'){
            break;
        }
        else if(choice =='N' || choice =='n'){
            exit(10);
        }
    }

    std::cout << "\n";
    for (size_t i = 0; i < (so_size); i++) {
        split(so[i].raValue, so[i].raStringSplit, ' ' );
        split(so[i].decValue, so[i].decStringSplit, ' ' );

        so[i].ratod = std::stold(so[i].raStringSplit[0]) + std::stold(so[i].raStringSplit[1])/60 + std::stold(so[i].raStringSplit[2])/3600;
        so[i].dectos = so[i].decStringSplit[0] + std::to_string(std::stold(so[i].decStringSplit[1]) + std::stold(so[i].decStringSplit[2])/60 + std::stold(so[i].decStringSplit[3])/3600);
        so[i].dectod = std::stold(so[i].dectos);
        so[i].lat=std::stold(latValue)*so[i].toRad;
        so[i].lon=std::stold(lonValue)*so[i].toRad;
        so[i].ra=so[i].ratod*so[i].toRad*15; //Convert RA from hours to degrees, then to radians
        so[i].dec=so[i].dectod*so[i].toRad;
    }

    std::thread t(start, so, so_size);
    t.detach();
	while(std::cin.get() != 'c'){
	}
	stop = true;
}

int main(){

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
    std::string noToTrack;
    std::string raValue;
    std::string decValue;
    std::string celName;
    std::cout << "\nInput Latitude in decimal: ";
    getline(std::cin, latValue);
    std::cout << "Input Longitude in decimal: ";
    getline(std::cin, lonValue);
    std::cout << "How many celestial bodies you want to track?: ";
    getline(std::cin, noToTrack);
    static const size_t N = std::stoi(noToTrack);
    StarOperations* so = new StarOperations[N];

    for (size_t i = 0; i < N; i++) {
       std::cout << "\nInput Celestial body name: ";
       getline(std::cin, celName);
       std::cout << "Please input RA in \"HH MM SS\" format for " << celName << ": ";
       getline(std::cin, raValue);
       std::cout << "Please input DEC in \"+/- DD MM SS\" format for " << celName << ": ";
       getline(std::cin, decValue);
       so[i] = StarOperations(celName, raValue, decValue);
    }

    initiateUserDataInputs(so, N);

    return 0;
}
