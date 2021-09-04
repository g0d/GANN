/* 

   Geeks Artificial Neural Network (G.A.N.N) - I/O Socket
   
   Copyright (C) 2008 George Delaportas (qtgeo)
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program. If not, see <http://www.gnu.org/licenses/>.
   
   E-Mail: g.delaportas@gmail.com

*/



#ifndef __GSOCKET__
#define __GSOCKET__

//Headers
#include "headers/gglobdec.h"
#include "headers/gsocket.h"
#include "headers/gexit.h"

//Constructor
GSocket::GSocket()
{

    //Private Variables
    int SockType = -1;
    int SockPins = 0;
    
    //Load Pins Matrix
    Pins = new GPin[MAX_PIN];

}

//Destructor
GSocket::~GSocket()
{

    //Unload Pins Matrix
    delete []Pins;

}

//Set Socket Type (I/O)
void GSocket::SetST(int SType)
{

    //Check Socket Type (0: Input, 1: Output)
    if (SType < 0 OR SType > 1)
        GExit("Error: Wrong Socket Type Specified!\n", 1);
    
    SockType = SType;

}

//Set Pins Number
void GSocket::SetPins(int Num)
{

    //Check Socket Pins (Not Less Than 1 Or Not More Than MAX_PIN)
    if (Num < 1 OR Num > MAX_PIN)
        GExit("Error: Wrong Number Of Pins Specifed!\n", 1);
    
    SockPins = Num;

}

//Set Pin Type
void GSocket::SetPT(int Pin, int PinType)
{

    //Check Socket Pins
    if (Pin < 0 OR Pin > SockPins)
        GExit("Error: Wrong Pin Specified!\n", 1);
    
    //Socket Pin Type (0: Binary, 1: Real)
    if (PinType < 0 OR PinType > 1)
        GExit("Error: Wrong Pin Type Specified!\n", 1);
    
    Pins[Pin].Type = PinType;

}

//Set Pin State
void GSocket::SetPS(int Pin, int PinState)
{

    //Check Socket Pins
    if (Pin < 0 OR Pin > SockPins)
        GExit("Error: Wrong Pin Specified!\n", 1);
    
    //Socket Pin State (0: Off, 1: On)
    if (PinState < 0 OR PinState > 1)
        GExit("Error: Wrong Pin State Specified!\n", 1);
    
    Pins[Pin].State = PinState;

}

//Set Pin Single Value Or Values With Range
void GSocket::SetPV(int Pin, float Val1, float Val2)
{
	//Check Socket Pins And Values
    if (Pin < 0 OR Pin > SockPins)
        GExit("Error: Wrong Pin Specified!\n", 1);

    if (Pins[Pin].Type == 1 AND Val2 < Val1 AND Val2 > PIN_VAL2_DEFAULT)
        GExit("Error: Wrong Range Specified!\n", 1);

    if (Pins[Pin].Type == 0)
    {
        if (Val1 < 0.0 OR ((Val1 > 0.0 AND Val1 < 1.0)) OR Val1 > 1.0)
            GExit("Error: Not A Binary Number!\n", 1);
    }

	Pins[Pin].MinVal = Val1;
	Pins[Pin].MaxVal = Val2;
}

//Get Socket Type (I/O)
int GSocket::GetST()
{

    return SockType;

}

//Get Pins Number
int GSocket::GetPins()
{

    return SockPins;

}

//Get Pin Type
int GSocket::GetPT(int Pin)
{

    if (Pin < 0 OR Pin > SockPins)
        GExit("Error: Wrong Pin Specified!\n", 1);
    
    return Pins[Pin].Type;

}

//Get Pin State
int GSocket::GetPS(int Pin)
{

    if (Pin < 0 OR Pin > SockPins)
        GExit("Error: Wrong Pin Specified!\n", 1);
    
    return Pins[Pin].State;

}

//Get Pin Value Or Pin Values (Minimum Or Maximum)
float GSocket::GetPV(int Pin, int Choice)
{

    if (Pin < 0 OR Pin > SockPins)
        GExit("Error: Wrong Pin Specified!\n", 1);
    
    if (Choice == 0)
    {
    
        if (Pins[Pin].State == 1)
            return Pins[Pin].MinVal;
        else
            return 0.0;
    
    }
    
    else if (Choice == 1)
    {
    
        if (Pins[Pin].State == 1)
            return Pins[Pin].MaxVal;
        else
            return 0.0;
    
    }
    
    else
        GExit("Error: Wrong Choice Specified!\n", 1);

}

#endif

/* ------------------------------------------------------------------------ */
