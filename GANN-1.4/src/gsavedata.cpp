/* 

   Geeks Artificial Neural Network (G.A.N.N) - Save Data To GKDB
   
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



#ifndef __GSAVEDATA__
#define __GSAVEDATA__

//Libraries
#include <stdio.h>

//Headers
#include "headers/gglobdec.h"
#include "headers/gsavedata.h"
#include "headers/gneuron.h"

//Geeks Save Data (Function)
void GSaveData(GNeuron *GMatrix, int GRegSerNum, int GSimNum)
{

    //Variables
    int i, j;
    long GOffset;
    FILE *FileToSave;
    
    //Initialize GKDB
    FileToSave = fopen("GKDB", "a");
    
    //Save Registration Serial Number
    fprintf(FileToSave, "%i\n", GRegSerNum);
    
    //Set Starting Header
    fprintf(FileToSave, "%i\n%i\n%i\n%i\n%f\n%i\n%i\n%i\n%i\n",\
    GSimNum, ECT, NewGANN.GMSType, NewGANN.GMCType, NewGANN.LearnTH,\
    NewGANN.GNNum, NewGANN.Layers, Inputs, Outputs);
    
    //Save GMap Layers
    for (i = 0; i < NewGANN.Layers; i++)
        fprintf(FileToSave, "%i\n", NewGANN.GMap[i]);
    
    //Save GNeurons Options
    for (i = 0; i < NewGANN.GNNum; i++)
    {
    
        //Save Input Slot Pins Of This GNeuron
        fprintf(FileToSave, "%i\n", GMatrix[i].GetISPins());
        
        //Save Weights
        for (j = 0; j < GMatrix[i].GetISPins(); j++)
            fprintf(FileToSave, "%f\n", GMatrix[i].GetWeights(j));
        
        //Save Neuron Specific Options
        fprintf(FileToSave, "%i\n", GMatrix[i].GetNFT());
        fprintf(FileToSave, "%f\n", GMatrix[i].Mod);
    
    }
    
    //Save Output Socket Values
    for (i = 0; i < Outputs; i++)
    {
    
        fprintf(FileToSave, "%f\n", GMinData[i]);
        fprintf(FileToSave, "%f\n", GMaxData[i]);
    
    }
    
    //Get File Position Indicator
    GOffset = ftell(FileToSave);
    
    //Close GKDB
    fclose(FileToSave);
    
    //Initialize GHT
    FileToSave = fopen("GHT", "a");
    
    //Save Registration Serial Number
    fprintf(FileToSave, "%i\n", GRegSerNum);
    
    //Save Offset
    fprintf(FileToSave, "%i\n", GOffset);
    
    //Close GHT
    fclose(FileToSave);

}

#endif

/* ------------------------------------------------------------------------ */
