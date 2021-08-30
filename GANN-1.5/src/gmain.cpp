/* 

   Geeks Artificial Neural Network (G.A.N.N) - Main
   
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



#ifndef __GMAIN__
#define __GMAIN__

//Libraries
#include <stdio.h>

//Headers
#include "headers/gglobdec.h"
#include "headers/gmain.h"
#include "headers/gsnmc.h"
#include "headers/gdmloader.h"
#include "headers/gnms.h"
#include "headers/grmc.h"
#include "headers/gexit.h"

//Initiate Global Variables
int SimNum;                      		//Simulations Number
int ECT;                         		//Error Correction Type
int Inputs, Outputs;             		//GSockets I/O
int RegSerNum;                   		//Registration Serial Number
int UserInp;                     		//User Inputs (GRMC)
long Offset;                     		//GHT Offset
float GMinData[MAX_PIN];         		//Minimum Data
float GMaxData[MAX_PIN];         		//Maximum Data
float UserVal[MAX_PIN];          		//User Values
float Steps[MAX_PIN];				//GSocket - GPins Steps

//GSockets
GSocket InSocket;                		//Inputs GSocket
GSocket OutSocket;               		//Outputs GSocket

//New G.A.N.N
GANN NewGANN;

//New GKDB
GKDB NewGKDB;

//Main Function
int main(int argc, char **argv)
{

    //Variables
    int i;					//Simple Counter
    
    //Graphical Menu
    printf("-------------------------\n");
    printf("******   G.A.N.N   ******\n");
    printf("-------------------------\n");
    printf("       Version 1.5       \n");
    printf("=========================\n");
    printf("George Delaportas\n");
    printf("Copyright (C) 2008\n");
    printf("=========================\n\n");
    printf("Please Select An Option\n");
    printf("1.Create A Feed-Forward G.A.N.N (Normal Systems)\n");
    printf("2.Create A Feed-Forward - Feedback G.A.N.N (Prediction Systems) [Beta]\n");
    printf("3.Run An Existing G.A.N.N From GKDB\n");
    printf("4.Create A Feed-Forward G.A.N.N And Run It\n");
    printf("5.Create A Feed-Forward - Feedback G.A.N.N And Run It [Beta]\n");
    printf("6.Remove Registrations From GKDB\n");
    printf("7.Exit\n");
    printf("Choice: ");
    
    scanf("%i", &i);
    
    printf("\n");
    
    //Check Choices
    if (i == 1)    
    {
    
        //Create New G.A.N.N
        GSNMC();
        
        printf("Loading Data...\n");
        
        //Load GIOD And GMap Data
        GDMLoader();
        
        printf("Done!\n\n");
        
        //Simulate G.A.N.N At Learning Mode
        GNMS(0, 0);
    
    }
    
    else if (i == 2)
    {
    
        //Create New G.A.N.N
        GSNMC();
        
        printf("Loading Data...\n");
        
        //Load GIOD And GMap Data
        GDMLoader();
        
        printf("Done!\n\n");
        
        //Simulate G.A.N.N At Learning Mode
        GNMS(0, 1);
    
    }
    
    else if (i == 3)
    {
    
        //Simulate G.A.N.N At Running Mode
        GNMS(1, 0);
    
    }
    
    else if (i == 4)
    {
    
        //Create New G.A.N.N
        GSNMC();
        
        printf("Loading Data...\n");
        
        //Load GIOD And GMap Data
        GDMLoader();
        
        printf("Done!\n\n");
        
        //Simulate G.A.N.N At Learning Mode
        GNMS(0, 0);
        
        //Simulate G.A.N.N At Running Mode
        GNMS(1, 0);
    
    }
    
    else if (i == 5)
    {
    
        //Create New G.A.N.N
        GSNMC();
        
        printf("Loading Data...\n");
        
        //Load GIOD And GMap Data
        GDMLoader();
        
        printf("Done!\n\n");
        
        //Simulate G.A.N.N At Learning Mode
        GNMS(0, 0);
        
        //Simulate G.A.N.N At Running Mode
        GNMS(1, 1);
    
    }
    
    else if (i == 6)
    {
    
        //Remove Specified Registration
        GRMC(1);
        
        printf("Done!\n");
    
    }
    
    else if (i == 7)
    {
    
        printf("Thank You For Using G.A.N.N\n");
        printf("Goodbye!\n");
        
        GExit("", 0);
    
    }
    
    else
        GExit("Error: Wrong Choice Specified!\n", 1);
    
    GExit("", 0);
    
    return 0;

}

#endif

/* ------------------------------------------------------------------------ */
