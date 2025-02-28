/*
   Geeks Artificial Neural Network (G.A.N.N) - GIOD And GMap Loader
   
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



#ifndef __GDMLOADER__
#define __GDMLOADER__

//Libraries
#include <stdio.h>

//Headers
#include "headers/gglobdec.h"
#include "headers/gdmloader.h"
#include "headers/gann.h"
#include "headers/gsocket.h"

//Geeks [I/O] Distribution And Map Loader (Function)
void GDMLoader()
{
    //Variables
    int i;						//Counter
    float Val;					//A Float Value
    float Tmp;					//Temp Values
    FILE *FileToOpen;			//A File Pointer

    //Initialize GIOD
    FileToOpen = fopen("GKDB/GIOD", "r");

    //Read Starting Header
    fscanf(FileToOpen, "%i\n%i\n", &Inputs, &Outputs);

    //Set Values To The Inputs GSocket
    for (i = 0; i < Inputs; i++)
    {
        fscanf(FileToOpen, "%f\n", &Val);
        InSocket.SetST((int)Val);

        fscanf(FileToOpen, "%f\n", &Val);
        InSocket.SetPT(i, (int)Val);

        fscanf(FileToOpen, "%f\n", &Val);
        InSocket.SetPS(i, (int)Val);

        fscanf(FileToOpen, "%f\n", &Val);
        if (InSocket.GetPT(i) == 0)
            InSocket.SetPV(i, Val, 0.0);
        else
            InSocket.SetPV(i, Val, Val + 1);

        Tmp = Val;

        fscanf(FileToOpen, "%f\n", &Val);
        InSocket.SetPV(i, Tmp, Val);
    }

    //Set Values To The Outputs GSocket
    for (i = 0; i < Outputs; i++)
    {
        fscanf(FileToOpen, "%f\n", &Val);
        OutSocket.SetST((int)Val);

        fscanf(FileToOpen, "%f\n", &Val);
        OutSocket.SetPT(i, (int)Val);

        fscanf(FileToOpen, "%f\n", &Val);
        OutSocket.SetPS(i, (int)Val);

        fscanf(FileToOpen, "%f\n", &Val);
        if (OutSocket.GetPT(i) == 0)
            OutSocket.SetPV(i, Val, 0.0);
        else
            OutSocket.SetPV(i, Val, Val + 1);

        Tmp = Val;

        fscanf(FileToOpen, "%f\n", &Val);
        OutSocket.SetPV(i, Tmp, Val);
    }

    //Close GIOD
    fclose(FileToOpen);

    //Initialize GMap
    FileToOpen = fopen("GKDB/GMap", "r");

    //Read Starting Header
    fscanf(FileToOpen, "%i\n%i\n%i\n%i\n%i\n%i\n%f\n%i\n",\
    &SimNum, &ECT, &NewGANN.GMSType, &NewGANN.GMCType,\
    &Inputs, &Outputs, &NewGANN.LearnTH, &NewGANN.Layers);

    //Get GNeurons From Layers
    for (i = 0; i < NewGANN.Layers; i++)
    {
        fscanf(FileToOpen, "%f\n", &Tmp);
        NewGANN.GMap[i] = (int)Tmp;
    }

    //Get GNNum
    fscanf(FileToOpen, "%i\n", &NewGANN.GNNum);

    //Close GMap
    fclose(FileToOpen);

    //Clean Up
    remove("GKDB/GMap");
}

#endif

/* ------------------------------------------------------------------------ */
