/*
   Geeks Artificial Neural Network (G.A.N.N) - Artificial Neural Network
   
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



#ifndef __GANN__
#define __GANN__

//Headers
#include "headers/gglobdec.h"
#include "headers/gann.h"

//Constructor
GANN::GANN()
{
    GNNum = 0;
    GMSType = 0;
    GMCType = 0;
    Layers = 0;
    LearnTH = 0.0;
    RunTH = 0.0;
    GMap = new int[MAX_LAYERS];
}

//Destructor
GANN::~GANN()
{
    delete []GMap;
}

#endif

/* ------------------------------------------------------------------------ */
