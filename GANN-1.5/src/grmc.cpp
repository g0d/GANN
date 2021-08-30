/* 

   Geeks Artificial Neural Network (G.A.N.N) - Runtime Manager Console
   
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



#ifndef __GRMC__
#define __GRMC__

//Libraries
#include <stdio.h>

//Headers
#include "headers/gglobdec.h"
#include "headers/grmc.h"
#include "headers/gexit.h"

//Geeks Runtime Manager Console (Function)
void GRMC(int RMCFunc)
{

    //Variables
    int i, j, k;
    int *REGS, *OFFSETS;
    REGS = new int[MAX_REG];
    OFFSETS = new int[MAX_REG];
    FILE *FileToCheck;
    
    //Reset
    i = 0;
    j = 0;
    k = 0;
    
    //Initialize GKDB
    FileToCheck = fopen("GKDB/nets/NewGKDB", "r");
    
    //Error Check
    if (FileToCheck == NULL)
        GExit("Error: GKDB Is Empty!\n", 1);
    
    //Close GKDB
    fclose(FileToCheck);
    
    //Initialize GRegs
    FileToCheck = fopen("GKDB/GRegs", "r");
    
    //Get GRegs
    while ((i = feof(FileToCheck)) == FALSE)
    {
    
        fscanf(FileToCheck, "%i\n", &REGS[j]);
        
        j++;
    
    }
    
    //Close GRegs
    fclose(FileToCheck);
    
    //Show Registrations
    printf("-----------------------------------------\n\n");
    
    for (i = 0; i < j; i++)
        printf("Registration:%i   Serial Number:%i\n\n", i + 1, REGS[i]);
    
    printf("-----------------------------------------\n\n");
    
    //User Interaction
    printf("# Geeks Runtime Manager Console #\n");
    printf("Please Specify A Registration\n");
    printf("Choice: ");
    
    scanf("%i", &i);
    
    if (i < 1 OR i > j)
        GExit("Error: The Registration You Specified Does Not Exist!\n", 1);
    else
        RegSerNum = REGS[i - 1];
    
    printf("\n");
    
    //Reset j
    j = 0;
    
    //Initialize GHT
    FileToCheck=fopen("GKDB/GHT", "r");
    
    //Get The Right Offset By Searching With RegSerNum
    while ((i = feof(FileToCheck)) == FALSE)
    {
    
        fscanf(FileToCheck, "%i\n", &k);
        fscanf(FileToCheck, "%i\n", &OFFSETS[j]);
        
        if (k == RegSerNum)
            break;
        
        j++;
    
    }
    
    //Close GHT
    fclose(FileToCheck);
    
    //Fixate Offset
    if (RegSerNum == REGS[0])
        Offset = 0;
    else
        Offset = OFFSETS[j - 1];
    
    //Check Function
    if (RMCFunc == 0)
    {
    
        printf("Please Specify Running Mode Threshold\n");
        printf("(Threshold Must Be A Value Between: 1%% - 100%%)\n");
        printf("Choice: ");
        
        scanf("%f", &NewGANN.RunTH);
        
        if (NewGANN.RunTH < 1.0 OR NewGANN.RunTH > 100.0)
            GExit("Error: Threshold Value Must Be Between: 1% - 100%!\n", 1);
        
        printf("\n");
        
        printf("Please Specify How Many Values Do You Want To Input\n");
        printf("(Input Number May Be A Positive Integer Between 1 - %i)\n", MAX_PIN);
        printf("Choice: ");
        
        scanf("%i", &i);
        
        if (i < 1 OR i > MAX_PIN)
            GExit("Error: Wrong Input Number Specified!\n", 1);
        
        printf("\n");
        
        for (j = 0; j < i; j++)
        {
        
            printf("Please Specify Test Value %i\n", j + 1);
            printf("(Test Value May Be Of Any Type)\n");
            printf("Choice: ");
            
            scanf("%f", &UserVal[j]);
            
            printf("\n");
        
        }
        
        printf("\n");
        
        //Keep User Inputs
        UserInp = i;
    
    }
    
    else if (RMCFunc == 1)
    {
    
        printf("Removing Registration...\n");
        
        NewGKDB.RemData(RegSerNum, Offset);
    
    }
    
    else
        GExit("Error: Wrong Function Specified!\n", 1);
    
    //Clean Up
    delete []REGS;
    delete []OFFSETS;

}

#endif

/* ------------------------------------------------------------------------ */
