/* 

   Geeks Artificial Neural Network (G.A.N.N) - Sockets And Neural Map Creator
   
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



#ifndef __GSNMC__
#define __GSNMC__

//Libraries
#include <stdio.h>

//Headers
#include "headers/gglobdec.h"
#include "headers/gsnmc.h"
#include "headers/gsocket.h"
#include "headers/gann.h"
#include "headers/gexit.h"

//Geeks Sockets And Neural Map Creator (Function)
void GSNMC()
{

    //Variables
    int i, j, k;				//Counters
    int *APT;					//All Pins Types
    APT = new int[MAX_PIN * 2];
    float v, n, m;              		//Float Values
    FILE *FileToOpen;				//A File Pointer
    
    //Get User Values To Create The I/O GSockets
    printf("# Geeks Sockets And Neural Map Creator #\n");
    printf("New I/O GSockets Have To Be Created\n");
    printf("Please Make Your Choices To Set Up The New GSockets\n\n");
    
    printf("# Input GSocket #\n");
    
    InSocket.SetST(0);
    
    printf("Please Specify Input GPins Number\n");
    printf("(Min: 1, Max: %i)\n", MAX_PIN);
    printf("Choice: ");
    
    scanf("%i", &i);
    
    printf("\n");
    
    InSocket.SetPins(i);
    
    printf("Now Please Specify Type And State Of Every GPin\n");
    printf("(Types - Binary: 0, Real: 1)\n");
    printf("(States - Off: 0, On: 1)\n\n");
    
    for (j = 0; j < i; j++)
    {
    
        printf("GPin %i\n", j + 1);
        printf("Choice (Type): ");
        
        scanf("%i", &k);
        
        printf("\n");
        
        InSocket.SetPT(j, k);
        
        printf("GPin %i\n", j + 1);
        printf("Choice (State): ");
        
        scanf("%i", &k);
        
        printf("\n");
        
        InSocket.SetPS(j, k);
    
    }
    
    printf("Now Please Assign Values To The GPins\n");
    printf("(Examples: '1' Or '5, 20.6')\n\n");
    
    for (j = 0; j < i; j++)
    {
    
		m = PIN_VAL2_DEFAULT;
	
        printf("GPin %i\n", j + 1);
        
        if (InSocket.GetPT(j) == 0)
        {
        
            printf("Choice [Binary]: ");
            
            scanf("%f", &n);
            
	    	printf("\n");
	    
            InSocket.SetPV(j, n, 0.0);
        
        }
        
        else
        {
        
            printf("Choice (Min, Max) [Real]: ");
            
            scanf("%f,%f", &n, &m);
		    
			printf("\n");
			
			InSocket.SetPV(j, n, m);
            
    	    printf("Now Set Step For GPin %i\n", j + 1);
    	    printf("(Min: 0.000001, Max: 1.0)\n\n");
	    
            printf("Choice (Step): ");
	    
            scanf("%f", &n);
	    
	    printf("\n");
            
	    //Check Step Range
            if (n < 0.000001 OR n > 1.0)
            	GExit("Error: Value Is Out Of Range!\n", 1);
	    
            Steps[j] = n;
	
	}
    
    }
    
    printf("# Output GSocket #\n");
    
    OutSocket.SetST(1);
    
    printf("Please Specify Output GPins Number\n");
    printf("(Min: 1, Max: %i)\n", MAX_PIN);
    printf("Choice: ");
    
    scanf("%i", &i);
    
    printf("\n");
    
    OutSocket.SetPins(i);
    
    printf("Now Please Specify Type And State Of Every GPin\n");
    printf("(Types - Binary: 0, Real: 1)\n");
    printf("(States - Off: 0, On: 1)\n\n");
    
    for (j = 0; j < i; j++)
    {
    
        printf("GPin %i\n", j + 1);
        printf("Choice (Type): ");
        
        scanf("%i", &k);
        
        printf("\n");
        
        OutSocket.SetPT(j, k);
        
        printf("GPin %i\n", j + 1);
        printf("Choice (State): ");
        
        scanf("%i", &k);
        
        printf("\n");
        
        OutSocket.SetPS(j, k);
    
    }
    
    printf("Now Please Assign Values To The GPins\n");
    printf("(Examples: '1' Or '5, 20.6')\n\n");
    
    for (j = 0; j < i; j++)
    {
    
		m = PIN_VAL2_DEFAULT;
		
		printf("GPin %i\n", j + 1);
        
        if (OutSocket.GetPT(j) == 0)
        {
        
            printf("Choice [Binary]: ");
            
            scanf("%f", &n);
            
            OutSocket.SetPV(j, n, 0.0);
        
        }
        
        else
        {
        
            printf("Choice (Min, Max) [Real]: ");
            
            scanf("%f,%f", &n, &m);
            
            OutSocket.SetPV(j, n, m);
        
        }
        
        printf("\n");
    
    }
    
    //Get User Opinion To Optimize The GMap Simulation Type
    printf("Please Choose The Simulation Type Of Your A.N.N\n");
    printf("(Critical: 0, Normal: 1, Manual: 2)\n");
    printf("Choice: ");
    
    scanf("%i", &j);
    
    printf("\n");
    
    //Check GMSType
    if (j < 0 OR j > 2)
        GExit("Error: Wrong Simulation Type Specified!\n", 1);
    
    //Get GSockets I/O
    Inputs = InSocket.GetPins();
    Outputs = OutSocket.GetPins();
    
    //Check GSockets Data Types To Set The Simulation Type
    if (j == 2)
    {
    
	//Manual GMap Simulation Type
    	printf("Please Choose A Manual Simulation Type\n");
    	printf("(Step: 0, Sign: 1, Sigmoid: 2)\n");
    	printf("Choice: ");
	
    	scanf("%i", &j);
	
	NewGANN.GMSType = j;
	
    	printf("\n");
    
    }
    
    else
    {
    
	for (i = 0; i < Inputs; i++)
            APT[i] = InSocket.GetPT(i);
    	
    	for (i = Inputs; i < Inputs + Outputs; i++)
            APT[i] = OutSocket.GetPT(i - Inputs);
    	
    	for (i = 0; i < Inputs + Outputs - 1; i++)
    	{
    	
            if (APT[i + 1] == APT[i])
	    {
	    
		if (APT[i] == 0)
                    NewGANN.GMSType = 0;
		else
		    NewGANN.GMSType = 2;
	    
            }
	    
            else if (APT[i + 1] != APT[i])
            {
            
            	NewGANN.GMSType = 2;
            	break;
            
            }
    	
    	}
    	
    	//Fixate GMSType
    	if (j == 0)
            NewGANN.GMSType = 1;
    
    }
    
    //Automatically Check I/O Number-Types-Values-Range To Set ECT
    if (Inputs == Outputs)
    {
    
        for (i = 0; i < Inputs; i++)
        {
        
            if (InSocket.GetPT(i) == OutSocket.GetPT(i))
            {
            
                if (InSocket.GetPV(i, 0) == OutSocket.GetPV(i, 0))
                {
                
                    if (InSocket.GetPV(i, 1) == OutSocket.GetPV(i, 1))
						ECT = 0;
		
                }
                
                else
                {
                
                    ECT = 1;
                    break;
                
                }
            
            }
            
            else
            {
            
                ECT = 1;
                break;
            
            }
        
        }
    
    }
    
    else
    	ECT = 1;
    
    //Get User Values To Create The Neural Map
    printf("# Geeks Neural Map #\n");
    printf("Now The GMap Is Ready To Be Created\n");
    printf("Please Specify GMap Connections Type\n");
    printf("(Automatic: 0, Manual: 1)\n");
    printf("Choice: ");
    
    scanf("%i", &NewGANN.GMCType);
    
    //Check GMap Connections Type
    if (NewGANN.GMCType < 0 OR NewGANN.GMCType > 1)
        GExit("Error: Wrong GMap Connections Type!\n", 1);
    
    printf("\n");
    
    printf("Please Specify How Do You Want To Set GNeurons\n");
    printf("(Automatically: 0, Manually: 1)\n");
    printf("Choice: ");
    
    scanf("%i", &j);
    
    printf("\n");
    
    //Check Choice
    if (j < 0 OR j > 1)
        GExit("Error: Wrong Choice Specified!\n", 1);
    
    if (j == 0)
    	printf("Please Specify An Estimation Of GNeurons\n");
    
    else
        printf("Please Specify GNeurons Number\n");
    
    printf("(GNeurons Must Be Equal Or More Than The Outputs)\n");
    printf("(Min: 1, Max: %i)\n", MAX_GN);
    printf("Choice: ");
    
    scanf("%i", &NewGANN.GNNum);
    
    //Check For Problematic GNNum
    if (NewGANN.GNNum > MAX_GN)
        GExit("Error: Too Many GNeurons!\n", 1);
    
    //Check For Problematic GMap
    if (NewGANN.GNNum < Outputs)
        GExit("Error: GNeurons Are Less Than The Outputs!\n", 1);
    
    printf("\n");
    
    //Fixate GNNum
    NewGANN.GNNum = NewGANN.GNNum + Inputs + Outputs;
    
    //Initialize GIOD
    FileToOpen = fopen("GKDB/GIOD", "w");
    
    //Set Starting Header
    fprintf(FileToOpen, "%i\n%i\n", Inputs, Outputs);
    
    //Save I/O GSockets Distribution
    for (i = 0; i < Inputs; i++)
    {
    
        j = InSocket.GetST();
        
        fprintf(FileToOpen, "%i\n", j);
        
        j = InSocket.GetPT(i);
        
        fprintf(FileToOpen, "%i\n", j);
        
        j = InSocket.GetPS(i);
        
        fprintf(FileToOpen, "%i\n", j);
        
        v = InSocket.GetPV(i, 0);
        
        fprintf(FileToOpen, "%f\n", v);
        
        v = InSocket.GetPV(i, 1);
        
        fprintf(FileToOpen, "%f\n", v);
    
    }
    
    for (i = 0; i < Outputs; i++)
    {
    
        j = OutSocket.GetST();
        
        fprintf(FileToOpen, "%i\n", j);    
        
        j = OutSocket.GetPT(i);
        
        fprintf(FileToOpen, "%i\n", j);
        
        j = OutSocket.GetPS(i);
        
        fprintf(FileToOpen, "%i\n", j);
        
        v = OutSocket.GetPV(i, 0);
        
        fprintf(FileToOpen, "%f\n", v);
        
        v = OutSocket.GetPV(i, 1);
        
        fprintf(FileToOpen, "%f\n", v);
    
    }
    
    //Close GIOD
    fclose(FileToOpen);
    
    //Set Simulations Number
    printf("Please Specify How Many Times The G.A.N.N Will Be Simulated\n");
    printf("(Simulations Must Be Positive - Equal Or Bigger Than 1)\n");
    printf("Choice: ");
    
    scanf("%i", &SimNum);
    
    if (SimNum < 1)
        GExit("Error: Simulations Must Be A Positive Number!\n", 1);
    
    printf("\n");
    
    //Set Threshold
    printf("Please Specify Learning Mode Threshold\n");
    printf("(Threshold Must Be A Value Between: 1%% - 100%%)\n");
    printf("Choice: ");
    
    scanf("%f", &NewGANN.LearnTH);
    
    if (NewGANN.LearnTH < 1.0 OR NewGANN.LearnTH > 100.0)
        GExit("Error: Threshold Value Must Be Between: 1% - 100%!\n", 1);
    
    printf("\n");
    
    //Initialize GMap
    FileToOpen = fopen("GKDB/GMap", "w");
    
    //Set Starting Header
    fprintf(FileToOpen, "%i\n%i\n%i\n%i\n%i\n%i\n%f\n",\
    SimNum, ECT, NewGANN.GMSType, NewGANN.GMCType, Inputs, Outputs, NewGANN.LearnTH);
    
    //GMap Creation And Optimization
    j = NewGANN.GNNum / (Inputs + Outputs);	//Layers
    k = NewGANN.GNNum - (Inputs + Outputs);	//Free GNeurons (Not Used For I/O)
    
    printf("Creating And Optimizing GMap...\n");
    
    //Reset GNNum
    NewGANN.GNNum = 0;
    
    //Keep Fixated Layers
    NewGANN.Layers = j;
    
    //Check Maximum Layers
    if (NewGANN.Layers > MAX_LAYERS)
        GExit("Error: Too Many Layers Allocated For GMap!\n", 1);
    
    //Fixate Free GNeurons
    if (k == 0)
        k++;
    
    //Store Layers
    fprintf(FileToOpen, "%i\n", NewGANN.Layers);
    
    //Rectangle (Orthogonal)
    if (Inputs == Outputs)
    {
    
        for (i = 0; i < NewGANN.Layers; i++)
        {
        
            if (i == NewGANN.Layers - 1)
            {
            
                fprintf(FileToOpen, "%i\n", Outputs);
                
                NewGANN.GNNum += Outputs;
            
            }
            
            else
            {
            
                fprintf(FileToOpen, "%i\n", k);
                
                NewGANN.GNNum += k;
            
            }
        
        }
    
    }
    
    //Delta (Triangle)
    else if (Inputs > Outputs)
    {
    
        for (i = 0; i < NewGANN.Layers; i++)
        {
        
            if (i == NewGANN.Layers - 1)
            {
            
                fprintf(FileToOpen, "%i\n", Outputs);
                
                NewGANN.GNNum += Outputs;
            
            }
            
            else
            {
            
                fprintf(FileToOpen, "%i\n", (k / j) + 1);
                
                NewGANN.GNNum += (k / j) + 1;
            
            }
            
            j++;
        
        }
    
    }
    
    //AnaDelta (UpSide Down Triangle)
    else if (Inputs < Outputs)
    {
    
        for (i = 0; i < NewGANN.Layers; i++)
        {
        
            if (i == NewGANN.Layers - 1)
            {
            
                fprintf(FileToOpen, "%i\n", Outputs);
                
                NewGANN.GNNum += Outputs;
            
            }
            
            else
            {
            
                fprintf(FileToOpen, "%i\n", (k / j) + 1);
                
                NewGANN.GNNum += (k / j) + 1;
            
            }
            
            k++;
        
        }
    
    }
    
    //Write Optimized GNNum
    fprintf(FileToOpen, "%i\n", NewGANN.GNNum);
    
    //Close GMap
    fclose(FileToOpen);
    
    printf("\nOptimized GMap Has:\n");
    printf("%i Layer(s)\n%i GNeuron(s)\n\n", NewGANN.Layers, NewGANN.GNNum);
    
    //Clean Up
    delete []APT;

}

#endif

/* ------------------------------------------------------------------------ */
