/* 

   Geeks Artificial Neural Network (G.A.N.N) - Read Data From GKDB 
   
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



#ifndef __GREADDATA__
#define __GREADDATA__

//Libraries
#include <stdio.h>

//Headers
#include "headers/gglobdec.h"
#include "headers/greaddata.h"
#include "headers/gneuron.h"
#include "headers/gexit.h"

//Geeks Read Data (Function)
void GReadData(GNeuron *GMatrix, int GRegSerNum, long GOffset, int GSimNum)
{

    //Variables
    int i, j, k, n;
    int RSN;
    float d;
    FILE *FileToOpen;
    
    //Reset
    i = 0;
    j = 0;
    k = 0;
    n = 0;
    SimNum = 0;
    
    //Error Checks
    if (GOffset < 0)
        GExit("Error: Wrong Offset Specified!\n", 1);
    
    //Initialize GKDB
    FileToOpen = fopen("GKDB", "r");
    
    //Set Pointer To The Right Offset
    fseek(FileToOpen, GOffset, SEEK_SET);
    
    while ((i = feof(FileToOpen)) == FALSE)
    {
    
        //Read Registration Serial Number
        fscanf(FileToOpen, "%i\n", &RSN);
        
        //Read The Rest Of The Starting Header
        fscanf(FileToOpen, "%i\n%i\n%i\n%i\n%f\n%i\n%i\n%i\n%i\n", &SimNum, &ECT,\
        &NewGANN.GMSType, &NewGANN.GMCType, &NewGANN.LearnTH, &NewGANN.GNNum,\
        &NewGANN.Layers, &Inputs, &Outputs);
        
        //Read GMap Layers
        for (i = 0; i < NewGANN.Layers; i++)
            fscanf(FileToOpen, "%i\n", &NewGANN.GMap[i]);
        
        //Read GNeurons Options
        for (i = 0; i < NewGANN.GNNum; i++)
        {
        
            //Read Input Slot Pins Of This GNeuron
            fscanf(FileToOpen, "%i\n", &k);
            
            //Read Weights
            for (j = 0; j < k; j++)
            {
            
                fscanf(FileToOpen, "%f\n", &d);
                GMatrix[i].SetWeights(j, d);
            
            }
            
            //Read Neuron Specific Options
            fscanf(FileToOpen, "%i\n", &j);
            GMatrix[i].SetNFT(j);
            fscanf(FileToOpen, "%f\n", &d);
            GMatrix[i].Mod = d;
        
        }
        
        //Read Output Socket Values
        for (i = 0; i < Outputs; i++)
        {
        
            fscanf(FileToOpen, "%f\n", &GMinData[i]);
            fscanf(FileToOpen, "%f\n", &GMaxData[i]);
        
        }
    
    }
    
    //Close GKDB
    fclose(FileToOpen);

}

#endif

/* ------------------------------------------------------------------------ */
