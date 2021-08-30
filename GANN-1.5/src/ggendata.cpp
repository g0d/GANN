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

//Geeks Generate Data (Function)
float GGenData(int FuncType, float Val1, float Val2)
{

    //Variable
    float RandVal;				//Random Value
    
    //Randomize
    GRand();
    
    if (FuncType == 0)
        RandVal = rand() % (int)Val2;
    
    else if (FuncType == 1)
    {
    
        RandVal = rand() % (int)Val2;
        
        if (RandVal == 0.0)
	{
	
	    RandVal = -rand() % (int)Val2;
	    
	    if (RandVal == 0.0)
	    	RandVal = -1.0;
	
	}
    
    }
    
    else if (FuncType == 2)
	RandVal = ((Val2 - Val1 + 1) *\
	(rand() / (RAND_MAX + 1.0))) / 10;
    
    else
        GExit("Error: Wrong Function Type Specified!\n", 1);
    
    //Results
    return RandVal;

}

#endif

/* ------------------------------------------------------------------------ */
