/*
   Geeks Artificial Neural Network (G.A.N.N) - Error Statistics
   
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



#ifndef __GERRSTAT__
#define __GERRSTAT__

//Libraries
#include <stdio.h>

//Headers
#include "headers/gglobdec.h"
#include "headers/gerrstat.h"
#include "headers/gsocket.h"
#include "headers/gexit.h"

//Geeks Error Statistics (Function)
float GErrStat(float *FirstData, float *LastData, float *AltData, int StatType)
{
    //Variables
    int i;                      //Counter
    int Faults;                 //Faults Counter
    float OK, Error;            //OK And Error Values (%)

    //Reset Statistics
    OK = 0.0;
    Error = 0.0;

    //Reset Faults Counter
    Faults = 0;

    //Check Statistics Type
    if (StatType < 0 OR StatType > 1)
        GExit("Error: Wrong Statistics Type Specified!\n", 1);

    if (StatType == 0)
    {
        for (i = 0; i < Outputs; i++)
        {
            if (FirstData[i] != LastData[i])
                Faults++;
        }
    }
    else
    {
        for (i = 0; i < Outputs; i++)
        {
	        if (LastData[i] < OutSocket.GetPV(i, 0) OR AltData[i] > OutSocket.GetPV(i, 1))
                Faults++;
	    }
    }

    //Statistics (%)
    OK = ((Outputs - Faults) / Outputs) * 100.0;
    Error = 100.0 - OK;

    //User Messages
    printf("Correct: %f%%\n", OK);
    printf("Error: %f%%\n\n", Error);

    return Error;
}

#endif

/* ------------------------------------------------------------------------ */
