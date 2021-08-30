/* 

   Geeks Artificial Neural Network (G.A.N.N) - Error Correction
   
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



#ifndef __GERRC__
#define __GERRC__

//Libraries
#include <stdio.h>
#include <stdlib.h>

//Headers
#include "headers/gglobdec.h"
#include "headers/gerrc.h"
#include "headers/gneuron.h"
#include "headers/gexit.h"

//Geeks Error Correction (Function)
void GErrC(GNeuron *GMatrix, int GNIndex, float Err, int CheckType)
{

    //Variables
    int GNFT;			//GNeuron Function Type
    float e;			//Random Values Variable
    float GNFB;			//GNeuron Function Base
    float GNS;			//GNeuron Summary
    
    //Print Message
    printf("* Trying To Correct GNeuron %i... *\n\n", GNIndex + 1);
    
    //Get GNeuron Function Type
    GNFT = GMatrix[GNIndex].GetNFT();
    
    //Get GNeuron Sum
    GNS = GMatrix[GNIndex].GetSum();
    
    //Get GNeuron Base
    GNFB = GMatrix[GNIndex].GetBase();
    
    //Compare GNeuron Summary With GNeuron Base
    if (GNS > GNFB)
    {
    
        //Statistically Weighted Neurons
        if (CheckType == 0)
        {
        
            //Random e
            if (Err <= 25.0)
                e = rand() % -(int)Err;
            else
                e = rand() % (int)(50.0 - Err - 1);
            
	    if (e > 0.0)
		e = -e;
	    
            //Make Summary Smaller Than NFunc Base (Output:--->0)
            GMatrix[GNIndex].Mod = e;
        
        }
        
        //Statically Weighted Neurons
        else if (CheckType == 1)    
        {
        
            //Make Summary Smaller Than GNFB (Output:0)
            GMatrix[GNIndex].Mod = -2.0;
        
        }
        
        else
            GExit("Error: Wrong Check Type Specified!\n", 1);
    
    }
    
    else
    {
    
        //Statistically Weighted Neurons
        if (CheckType == 0)
        {
        
            //Random e
            if (Err >= 25.0)
                e = rand() % (int)Err;
            else
                e = rand() % (int)(100.0 - Err);
            
            //Make Summary Bigger Than NFunc Base (Output:--->1)
            GMatrix[GNIndex].Mod = e;
        
        }
        
        //Statically Weighted Neurons
        else if (CheckType == 1)
        {
        
            //Make Summary Bigger Than NFunc Base (Output:1)
            GMatrix[GNIndex].Mod = 2.0;
        
        }
        
        else
            GExit("Error: Wrong Check Type Specified!\n", 1);
    
    }

}

#endif

/* ------------------------------------------------------------------------ */
