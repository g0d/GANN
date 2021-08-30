/* 

   Geeks Artificial Neural Network (G.A.N.N) - Generate Random Data
   
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



#ifndef __GGENDATA__
#define __GGENDATA__

//Libraries
#include <stdlib.h>

//Headers
#include "headers/gglobdec.h"
#include "headers/ggendata.h"
#include "headers/grand.h"
#include "headers/gexit.h"

//Global Varialbe
static float RandomData;	//Random Values

//Geeks Generate Data (Function)
float GGenData(int FuncType, float Val1, float Val2)
{

    //Randomize
    GRand();
    
    if (FuncType == 0)
        RandomData = rand() % (int)Val2;
    
    else if (FuncType == 1)
    {
    
        RandomData = rand() % (int)Val2;
        
        if (RandomData == 0.0)
        {
        
            RandomData = rand() % (-(int)Val2);
            
            if (RandomData == 0.0)
                RandomData = -1.0;
        
        }
    
    }
    
    else if (FuncType == 2)
    {
    
	//Produce Random Real Data
	RandomData = ((Val2 - Val1 + 1) *\
	(rand() / (RAND_MAX + 1.0))) / 10;
    
    }
    
    else
        GExit("Error: Wrong Function Type Specified!\n", 1);
    
    //Resutls
    return RandomData;

}

#endif

/* ------------------------------------------------------------------------ */
