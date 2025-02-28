/*
   Geeks Artificial Neural Network (G.A.N.N) - Knowledge Data Base
   
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



#ifndef __GKDB__
#define __GKDB__

//Libraries
#include <stdio.h>

//Headers
#include "headers/gglobdec.h"
#include "headers/gkdb.h"
#include "headers/gexit.h"

//Constructor
GKDB::GKDB()
{
    //Blank
}

//Destructor
GKDB::~GKDB()
{
    //Blank
}

//Read Data
void GKDB::ReadData(GNeuron *GMatrix, int GRegSerNum, long GOffset, int GSimNum)
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
    FileToOpen = fopen("GKDB/nets/NewGKDB", "r");

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

//Save Data (Function)
void GKDB::SaveData(GNeuron *GMatrix, int GRegSerNum, int GSimNum)
{
    //Variables
    int i, j;
    long GOffset;
    FILE *FileToSave;

    //Initialize GKDB
    FileToSave = fopen("GKDB/nets/NewGKDB", "a");

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
    FileToSave = fopen("GKDB/GHT", "a");

    //Save Registration Serial Number
    fprintf(FileToSave, "%i\n", GRegSerNum);

    //Save Offset
    fprintf(FileToSave, "%i\n", GOffset);

    //Close GHT
    fclose(FileToSave);
}

//Remove Data (Function)
void GKDB::RemData(int GRegSerNum, long GOffset)
{
    //Variables
    int i, j, k, n, m, s;
    int Tmp;
    int *iTmp, *iTemp;
    iTmp = new int[MAX_REG + 1];
    iTemp = new int[MAX_REG];
    float *fTmp, *fTemp;
    fTmp = new float[MAX_REG + 1];
    fTemp = new float[MAX_REG];
    FILE *FileToUpdate;

    //Reset
    i = 0;
    j = 0;
    k = 0;
    n = 0;
    m = 0;
    s = 0;
    Tmp = -1;

    //Initialize GKDB
    FileToUpdate = fopen("GKDB/nets/NewGKDB", "r");

    //Error Check
    if (FileToUpdate == NULL)
        GExit("Error: GKDB Was Not Found!\n", 1);

    //Close GKDB
    fclose(FileToUpdate);

    //Initialize GHT
    FileToUpdate = fopen("GKDB/GHT", "r");

    while ((n = feof(FileToUpdate)) == FALSE)
    {
        //Read GHT
        fscanf(FileToUpdate, "%i\n", &iTmp[i]);

        if (GRegSerNum == iTmp[i] AND Tmp == -1)
        {
            Tmp = i;

            fscanf(FileToUpdate, "%i\n", &s);
        }

        i++;
    }

    //Close GHT
    fclose(FileToUpdate);

    //Remove Specified Registration
    for (j = Tmp; j < i; j++)
    {
        if (GRegSerNum == iTmp[j])
        {
            iTmp[j] = 0;
            iTmp[j + 1] = 0;
        }
    }

    //Produce Updated GHT
    for (j = 0; j < i; j++)
    {
        if (iTmp[j] != 0)
        {
            iTemp[k] = iTmp[j];

            k++;
        }
    }

    //Initialize GHT
    FileToUpdate = fopen("GKDB/GHT", "w");

    //Save New GHT
    for (j = 0; j < k; j++)
        fprintf(FileToUpdate, "%i\n", iTemp[j]);

    //Close GHT
    fclose(FileToUpdate);

    //Initialize GHT
    FileToUpdate = fopen("GKDB/GHT", "r");

    //Read GHT
    fscanf(FileToUpdate, "%i\n", &i);

    //GKDB And Other Files Removal Check
    if ((n = feof(FileToUpdate)) != FALSE)
    {
        printf("All Registrations Have Been Removed...\n");

        remove("GKDB/nets/NewGKDB");
        remove("GKDB/GHT");
        remove("GKDB/GRegs");
        remove("GKDB/GSims");
        remove("GKDB/GIOD");

        printf("Done!\n");

        GExit("", 0);
    }

    //Close GHT
    fclose(FileToUpdate);

    //Reset
    i = 0;
    j = 0;
    k = 0;
    n = 0;
    Tmp = -1;

    //Initialize GSims
    FileToUpdate = fopen("GKDB/GSims", "r");

    while ((n = feof(FileToUpdate)) == FALSE)
    {
        //Read GSims
        fscanf(FileToUpdate, "%i\n", &iTmp[i]);

        if (GRegSerNum == iTmp[i] AND Tmp == -1)
            Tmp = i;

        i++;
    }

    //Close GSims
    fclose(FileToUpdate);

    //Remove Specified Registration
    for (j = Tmp; j < i; j++)
    {
        if (GRegSerNum == iTmp[j])
        {
            iTmp[j] = 0;
            iTmp[j + 1] = 0;
        }
    }

    //Produce Updated GSims
    for (j = 0; j < i; j++)
    {
        if (iTmp[j] != 0)
        {
            iTemp[k] = iTmp[j];

            k++;
        }
    }

    //Initialize GSims
    FileToUpdate = fopen("GKDB/GSims", "w");

    //Save New GSims
    for (j = 0; j < k; j++)
        fprintf(FileToUpdate, "%i\n", iTemp[j]);

    //Close GSims
    fclose(FileToUpdate);

    //Reset
    i = 0;
    j = 0;
    k = 0;
    n = 0;
    Tmp = -1;

    //Initialize GRegs
    FileToUpdate = fopen("GKDB/GRegs", "r");

    while ((n = feof(FileToUpdate)) == FALSE)
    {
        //Read GRegs
        fscanf(FileToUpdate, "%i\n", &iTmp[i]);

        if (GRegSerNum == iTmp[i] AND Tmp == -1)
            Tmp = i;

        i++;
    }

    //Close GRegs
    fclose(FileToUpdate);

    //Remove Specified Registration
    for (j = Tmp; j < i; j++)
    {
        if (GRegSerNum == iTmp[j])
            iTmp[j] = 0;
    }

    //Produce Updated GRegs
    for (j = 0; j < i; j++)
    {
        if (iTmp[j] != 0)
        {
            iTemp[k] = iTmp[j];

            k++;

        }
    }

    //Initialize GRegs
    FileToUpdate = fopen("GKDB/GRegs", "w");

    //Save New GRegs
    for (j = 0; j < k; j++)
        fprintf(FileToUpdate, "%i\n", iTemp[j]);

    //Close GRegs
    fclose(FileToUpdate);

    //Initialize GRegs
    FileToUpdate = fopen("GKDB/GRegs", "r");

    //Read Next Registration
    fscanf(FileToUpdate, "%i\n", &m);

    //Close GRegs
    fclose(FileToUpdate);

    //Reset
    i = 0;
    j = 0;
    k = 0;
    n = 0;
    Tmp = -1;

    //Initialize GKDB
    FileToUpdate = fopen("GKDB/nets/NewGKDB", "r");

    //Set Pointer At Specified Registration
    fseek(FileToUpdate, GOffset, SEEK_SET);

    while ((n = feof(FileToUpdate)) == FALSE)
    {
        //Read GKDB
        fscanf(FileToUpdate, "%f\n", &fTmp[i]);

        if (GRegSerNum == (int)fTmp[i] AND Tmp == -1)
            Tmp = i;

        i++;
    }

    //Close GKDB
    fclose(FileToUpdate);

    //Remove Specified Registration
    for (j = Tmp; j < i; j++)
    {
        if ((int)fTmp[j] == m)
            break;

        else if ((int)fTmp[j] != m)
            fTmp[j] = 0.0;
    }

    //Produce Updated GKDB
    for (j = 0; j < i; j++)
    {
        if (fTmp[j] != 0.0)
        {
            fTemp[k] = fTmp[j];

            k++;
        }
    }

    //Initialize GKDB
    FileToUpdate = fopen("GKDB/nets/NewGKDB", "w");

    //Save New GKDB
    for (j = 0; j < k; j++)
        fprintf(FileToUpdate, "%f\n", fTemp[j]);

    //Close GKDB
    fclose(FileToUpdate);

    //Clean Up
    delete []iTmp;
    delete []iTemp;
    delete []fTmp;
    delete []fTemp;
}

#endif

/* ------------------------------------------------------------------------ */
