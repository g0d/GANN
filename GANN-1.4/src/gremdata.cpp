/* 

   Geeks Artificial Neural Network (G.A.N.N) - Remove Data From GKDB
   
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



#ifndef __GREMDATA__
#define __GREMDATA__

//Libraries
#include <stdio.h>

//Headers
#include "headers/gglobdec.h"
#include "headers/gremdata.h"
#include "headers/gexit.h"

//Geeks Remove Data (Function)
void GRemData(int GRegSerNum, long GOffset)
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
    FileToUpdate = fopen("GKDB", "r");
    
    //Error Check
    if (FileToUpdate == NULL)
        GExit("Error: GKDB Was Not Found!\n", 1);
    
    //Close GKDB
    fclose(FileToUpdate);
    
    //Initialize GHT
    FileToUpdate = fopen("GHT", "r");
    
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
    FileToUpdate = fopen("GHT", "w");
    
    //Save New GHT
    for (j = 0; j < k; j++)
        fprintf(FileToUpdate, "%i\n", iTemp[j]);
    
    //Close GHT
    fclose(FileToUpdate);
    
    //Initialize GHT
    FileToUpdate = fopen("GHT", "r");
    
    //Read GHT
    fscanf(FileToUpdate, "%i\n", &i);
    
    //GKDB And Other Files Removal Check
    if ((n = feof(FileToUpdate)) != FALSE)
    {
    
        printf("Notice: All The Registrations Were Removed\n");
        printf("Removing GKDB...\n");
        
        remove("GKDB");
	remove("GHT");
	remove("GRegs");
	remove("GSims");
	remove("GIOD");
        
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
    FileToUpdate = fopen("GSims", "r");
    
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
    FileToUpdate = fopen("GSims", "w");
    
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
    FileToUpdate = fopen("GRegs", "r");
    
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
    FileToUpdate = fopen("GRegs", "w");
    
    //Save New GRegs
    for (j = 0; j < k; j++)
        fprintf(FileToUpdate, "%i\n", iTemp[j]);
    
    //Close GRegs
    fclose(FileToUpdate);
    
    //Initialize GRegs
    FileToUpdate = fopen("GRegs", "r");
    
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
    FileToUpdate = fopen("GKDB", "r");
    
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
    FileToUpdate = fopen("GKDB", "w");
    
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
