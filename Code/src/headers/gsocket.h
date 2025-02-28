/*
   Geeks Artificial Neural Network (G.A.N.N) - I/O Socket
   
   Copyright (C) 2006 - 2025 George Delaportas (G0D/ViR4X)
   
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



#ifndef __GSOCKET_H__
#define __GSOCKET_H__

//Geeks Socket (Class - Model)
class GSocket
{
    private:

    //Private Variables
    int SockType;				//Socket Type
    int SockPins;				//Socket Pins

    //Structure Of A Geeks Pin
    struct GPin
    {
        int Type;
        int State;
        float MinVal;
        float MaxVal;
    };

    //Load Pins Matrix
    GPin *Pins;					//New Pins
    
    
    
    public:

    //Constructor
    GSocket();

    //Destructor
    ~GSocket();

    //Set Socket Type (I/O)
    void SetST(int SType);

    //Set Pins Number
    void SetPins(int Num);

    //Set Pin Type
    void SetPT(int Pin, int PinType);

    //Set Pin State
    void SetPS(int Pin, int PinState);

    //Set Pin Single Value Or Value With Range
    void SetPV(int Pin, float Val1, float Val2);

    //Get Socket Type (I/O)
    int GetST();

    //Get Pins Number
    int GetPins();

    //Get Pin Type
    int GetPT(int Pin);

    //Get Pin State
    int GetPS(int Pin);

    //Get Pin Value Or Pin Value With Range
    float GetPV(int Pin, int Choice);
};

#endif

/* ------------------------------------------------------------------------ */
