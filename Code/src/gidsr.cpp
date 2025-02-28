/*
   Geeks Artificial Neural Network (G.A.N.N) - Inputs Distribution Step Reader
   
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



#ifndef __GIDSR__
#define __GIDSR__

//Libraries
#include <stdio.h>

//Headers
#include "headers/gsocket.h"
#include "headers/gidsr.h"

//Geeks Inputs Distribution Step Reader (Function)
float GIDSR(GSocket &ShadowSocket, int Pin, float Step)
{
    //Variable
    float Result;				//Current Result

    Result = ShadowSocket.GetPV(Pin, 0) + Step;

    return Result;
}

#endif

/* ------------------------------------------------------------------------ */
