/* 

   Geeks Artificial Neural Network (G.A.N.N) - Neural Map Simulator
   
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



#ifndef __GNMS__
#define __GNMS__

//Libraries
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//Headers
#include "headers/gglobdec.h"
#include "headers/gnms.h"
#include "headers/gneuron.h"
#include "headers/grand.h"
#include "headers/ggendata.h"
#include "headers/gerrc.h"
#include "headers/gerrstat.h"
#include "headers/grmc.h"
#include "headers/greaddata.h"
#include "headers/gsavedata.h"
#include "headers/gexit.h"

//Geeks Neural Map Simulator (Function)
void GNMS(int SimFunc, int SimMode)
{

    //Variables
    register int i, j;		//Fast Counters
    int n, k, p;		//Simple Counters
    int EpC;			//Epochs Counter
    int GNC;			//GNeurons Counter
    int NLH;			//Next Layer Head
    int NLE;			//Next Layer End
    int GNFT;			//GNeuron Function Type
    int RSN;			//Registration Serial Number
    int Sims;			//Simulations Number
    float *NewData;		//New Data From Inputs GSocket
    NewData=new float[MAX_PIN];
    float AccErr;		//Acceptable Error (%)
    float GErr;			//G.A.N.N Error (%)
    float GMin, GMax;		//Min,Max Values
    float Tmp;			//Temporary Float Values
    FILE *FileToCheck;		//A File Pointer
    
    //Check For Wrong Simulation Function
    if (SimFunc < 0 OR SimFunc > 2)
        GExit("Error: Wrong Simulation Function Specified!\n", 1);
    
    //Check For Wrong Simulation Function
    if (SimMode < 0 OR SimMode > 1)
        GExit("Error: Wrong Simulation Mode Specified!\n", 1);
    
    //Reset Registration Serial Number
    RegSerNum = 0;
    RSN = 0;
    
    //Learn
    if (SimFunc == 0)
    {
    
        //Get I/O From GSockets Loaded In Memory
        Inputs = InSocket.GetPins();
        Outputs = OutSocket.GetPins();
        
        //Compute Acceptable Error
        AccErr = 100.0 - NewGANN.LearnTH;
        
        //Fill NData With Inputs GSocket Data (Only For Uniform Checks)
        for (i = 0; i < Inputs; i++)
            NewData[i] = InSocket.GetPV(i, 0);
        
        //Check GMap Simulation Type So As To Set GNeurons Function Type
        if (NewGANN.GMSType == 0)
            GNFT = 0;
        else if (NewGANN.GMSType == 1)
            GNFT = 1;
        else
            GNFT = 2;
        
        //Print Inputs GSocket
        printf("----- Inputs GSocket -----\n\n");   
        
        for (i = 0; i < Inputs; i++)
        {
        
            printf("GPin: %i\n", i + 1);
            printf("Minimum Value: %f\n", InSocket.GetPV(i, 0));
            
            if (InSocket.GetPV(i, 1) == 0.0)
                printf("Maximum Value: N/A [0.0]\n\n");
            else
                printf("Maximum Value: %f\n\n", InSocket.GetPV(i, 1));
        
        }
        
        printf("--------------------------\n\n");
        
        //Start Simulation
        printf("Learning...\n");
        
        //Simulations Loop
        for (n = 0; n < SimNum; n++)
        {
        
            //Create New Geeks Network In Memory (G.A.N.N Matrix)
            GNeuron *GNet;
            GNet = new GNeuron[NewGANN.MAX_MATRIX];
            
            printf("\n* Simulation %i *\n\n", n + 1);
            
            //Reset Epochs
            EpC = 1;
	    
            //Escape Caption
            ReRoute:;
	    
            //Check For Maximum Epochs
            if (EpC > MAX_EPX)
                GExit("Error: G.A.N.N Has Reached Maximum Epochs!\n", 1);
            
            printf("# Epoch %i #\n\n", EpC);
            
	    //Randomize
            GRand();
            
            //Reset GNC
            GNC = -1;
            
            //Reset NLH
            NLH = 0;
            
            //Reset NLE
            NLE = 0;
            
            //Start Routing Through The Layers
            for (i = 0; i < NewGANN.Layers; i++)
            {
            
                //Get GNeurons Of Current Layer
                k = NewGANN.GMap[i];
                
                //Check GMap Connections Type (0: Auto, 1: Manual)
                if (NewGANN.GMCType == 0)
                {
                
                    //Enable All GNeurons In This Layer
                    for (j = NLE; j < (k + NLE); j++)
                    {
                    
                        //GNeurons Counter
                        GNC++;
                        
                        //Get Data From InSocket (First Layer)
                        if (i == 0)
                        {
                        
                            for (p = 0; p < Inputs; p++)
                            {
                            
                                //Get Data Or Data Range
                                if (InSocket.GetPT(p) == 0)
                                    Tmp = InSocket.GetPV(p, 0);
                                
                                else
                                {
                                
                                    if (InSocket.GetPV(p, 1) != 0.0)
                                        Tmp = GGenData(2, InSocket.GetPV(p, 0),\
                                        InSocket.GetPV(p, 1));
                                    
                                    else
                                        Tmp = InSocket.GetPV(p, 0);
                                
                                }
                                
                                //Give Data To This GNeuron
                                GNet[GNC].InData(p, Tmp);
                            
                            }
                        
                        }
                        
                        //Get Data From Previous Layer
                        else
                        {
                        
                            for (p = NLH; p < (NLH + NLE); p++)
                            
                            {
                            
                                //Give Data To This GNeuron
                                GNet[GNC].InData(p - NLH, GNet[p].OutData());
                            
                            }
                        
                        }
                        
                        //Enable This GNeuron
                        GNet[GNC].Enable(GNFT);
                        
                        printf("GNeuron %i Enabled!\n\n", GNC + 1);
                    
                    }
                    
                    //Next Layer Head
                    NLH += NLE;
                    
                    //Next Layer End
                    NLE = k;
                
                }
                
                else
                {
                
                    //User Defined Connections
                    GExit("Notice: No Connections Specified!\n", 1);
                
                }
            
            }
            
            //Reset j
            j = 0;
            
            printf("----- Outputs Data -----\n\n");
            
            //Fill GData
            for (i = NLH; i < (NLH + NLE); i++)
            {
            
                GMinData[j] = GNet[i].OutData() * OutSocket.GetPV(j, 0);
                GMaxData[j] = GNet[i].OutData() * OutSocket.GetPV(j, 1);
                
                printf("[GPin %i]\n", j + 1);
                printf("Min: %f\n", GMinData[j]);
                printf("Max: %f\n\n", GMaxData[j]);
                
                j++;
            
            }
            
            printf("------------------------\n\n");
            
            //Check Simulation Mode
            if (SimMode == 0)
            {
            
                //Gather Error Statistics (ECT - 0: Uniform, 1: Non-Uniform)
                GErr = GErrStat(NewData, GMinData, GMaxData, ECT);
                
                //Check Error Statistics
                if (GErr <= AccErr)
                {
                
                    if (RegSerNum == 0)
                    {
                    
                        //Produce A Registration Serial Number
                        RegSerNum = abs((int)GGenData(2, 0.0,\
			(Inputs + Outputs) * (GNC + 1) *\
			EpC * SimNum * time(NULL)));
                        
			//Fixate Less Digits
			while (RegSerNum < 1000000000)
			    RegSerNum += 999;
                        
			//Initialize GSims
                        FileToCheck = fopen("GSims", "a");
                        
                        //Save Registration Serial Number
                        fprintf(FileToCheck, "%i\n", RegSerNum);
                        
                        //Save Simulations Number
                        fprintf(FileToCheck, "%i\n", SimNum);
                        
                        //Close GSims
                        fclose(FileToCheck);
                    
                    }
                    
                    //Save This G.A.N.N To The GKDB
                    GSaveData(GNet, RegSerNum, n + 1);
                    
                    //Print Outputs GSocket
                    printf("----- Outputs GSocket -----\n\n");
                    
                    for (i = 0; i < Outputs; i++)
                    {
                    
                        printf("GPin: %i\n", i + 1);
                        printf("Min Value: %f\n", GMinData[i]);
                        
                        if (GMaxData[i] == 0.0)
                            printf("Maximum Value: N/A [0.0]\n\n");
                        else
                            printf("Maximum Value: %f\n\n", GMaxData[i]);
                    
                    }
                    
                    printf("---------------------------\n\n");
                    
                    printf("Learning Successfully Completed!\n");
                
                }
                
                else
                {
                
                    //Error Correction
                    for (i = 0; i < Outputs; i++)
                    {
                    
                        k = 0;
                        
                        printf("Error Correction [Output GPin %i]\n\n", i + 1);
                        
                        for (j = 0; j < NewGANN.GNNum; j++)
                        {
                        
                            GMin = OutSocket.GetPV(i, 0);
                            GMax = OutSocket.GetPV(i, 1);
                            
                            if ((GNet[j].OutData() * GMin) < GMin\
                            OR (GNet[j].OutData() * GMax) > GMax)
                            {
                            
                                if (NewGANN.GMSType == 0 OR\
				NewGANN.GMSType == 1)
                                    GErrC(GNet, j, GErr, 1);
                                else
                                    GErrC(GNet, j, GErr, 0);
                                
                                k = 1;
                            
                            }
                        
                        }
                        
                        if (k == 0)
                            printf("* All The GNeurons Are Correct *\n\n");
                    
                    }
		    
                    EpC++;                    
                    
		    goto ReRoute;
                
                }
            
            }
            
            else
            {
            
		//Feed - Forward With Feedback G.A.N.N
            	printf("FEED - FORWARD WITH FEEDBACK CODE\n");
            
            }
            
            //Unload GNet From Memory
            delete []GNet;
        
        }
        
        //Initialize GRegs
        FileToCheck = fopen("GRegs", "a");
        
        //Save G.A.N.N Registrations
        fprintf(FileToCheck, "%i\n", RegSerNum);
        
        //Close GRegs
        fclose(FileToCheck);
    
    }
    
    //Run
    else if (SimFunc == 1)
    {
    
        //Create New Geeks Network In Memory (G.A.N.N Matrix)
        GNeuron *GNet;
        GNet = new GNeuron[NewGANN.MAX_MATRIX];
        
        //Run GRMC (User Interaction - Load Offset And RegSerNum)
        GRMC(0);
        
        //Initialize GSims
        FileToCheck = fopen("GSims", "r");
        
        //Get Simulations Number
        while ((i = feof(FileToCheck)) == FALSE)
        {
        
            fscanf(FileToCheck, "%i\n", &RSN);
            fscanf(FileToCheck, "%i\n", &Sims);
            
            if (RegSerNum == RSN)
                break;
        
        }
        
        //Close GSims
        fclose(FileToCheck);
        
        //Reset n
        n = 0;
        
        //Escape Caption
        ReRun:;
        
        //Start Simulation
        printf("Running...\n\n");
        
        //Increase Simulations Pointer
        n++;
        
        //Read GKDB
        GReadData(GNet, RegSerNum, Offset, n);
        
        //Compare User Inputs With G.A.N.N Inputs
        if (UserInp > Inputs)
            GExit("Error: Too Many Inputs For This Registration!\n", 1);
        
	//Check GMap Simulation Type So As To Set GNeurons Function Type
	if (NewGANN.GMSType == 0)
	    GNFT = 0;
	else if (NewGANN.GMSType == 1)
	    GNFT = 1;
	else
	    GNFT = 2;
        
        //Reset GNC
        GNC = -1;
        
        //Reset NLH
        NLH = 0;
        
        //Reset NLE
        NLE = 0;
        
        //Start Routing Through The Layers
        for (i = 0; i < NewGANN.Layers; i++)
        {
        
            //Get GNeurons Of Current Layer
            k = NewGANN.GMap[i];
            
            //Check GMap Connections Type (0: Auto, 1: Manual)
            if (NewGANN.GMCType == 0)
            {
            
                //Enable All GNeurons
                for (j = NLE; j < (k + NLE); j++)
                {
                
                    //GNeurons Counter
                    GNC++;
                    
                    //Give Data To GNeurons Of The First Layer
                    if (i == 0)
                    {
                    
                        for (p = 0; p < Inputs; p++)
                        {
                        
                            GNet[GNC].InData(p - NLH, UserVal[p]);
                            printf("Weight %i: %f\n", p - NLH + 1,\
                            GNet[GNC].GetWeights(p - NLH));
                        
                        }
                    
                    }
                    
                    else
                    {
                    
                        //Give Data To GNeurons Of The Rest Layers
                        for (p = NLH; p < (NLH + NLE); p++)
                        {
                        
                            GNet[GNC].InData(p - NLH, GNet[p].OutData());
                            printf("Weight %i: %f\n", p - NLH + 1,\
                            GNet[GNC].GetWeights(p - NLH));
                        
                        }
                    
                    }
                    
                    //Run This GNeuron
                    GNet[GNC].Run(GNFT);
		    
		    printf("\n");
                
                }
                
                //Next Layer Head
                NLH += NLE;
                
                //Next Layer End
                NLE = k;
            
            }
            
            else
            {
            
                //User Defined Connections
                printf("CUSTOM CONNECTIONS\n");
            
            }
        
        }
        
        //Reset j
        j = 0;
        
        printf("----- Outputs Data -----\n\n");
        
        //Print G.A.N.N Values
        for (i = NLH; i < (NLH + NLE); i++)
        {
        
            printf("[GPin %i]\n", i - NLH + 1);
            printf("Min: %f\n", GNet[i].OutData() * GMinData[i - NLH]);
            printf("Max: %f\n\n", GNet[i].OutData() * GMaxData[i - NLH]);
        
        }
        
        printf("------------------------\n\n");
        
        //Get G.A.N.N Values
        for (i = NLH; i < (NLH + NLE); i++)
        {
        
            if (GNet[i].OutData() * GMinData[i - NLH] >= GMinData[ i - NLH]\
            AND GNet[i].OutData() * GMaxData[i - NLH] <= GMaxData[i - NLH])
            {
            
                if (NewGANN.RunTH < NewGANN.LearnTH)
                {
                
                    printf("* Output GPin %i *\n", i - NLH + 1);
                    printf("Value Found - Little Acurracy!\n\n");
                
                }
                
                else
                {
                
                    printf("* Output GPin %i *\n", i - NLH + 1);
                    printf("Value Found!\n\n");
                
                }
                
                j = 1;
            
            }
            
            else
            {
            
                printf("* Output GPin %i *\n", i - NLH + 1);
                printf("Value Not Found!\n\n");
            
            }
        
        }
        
        //Final Checks
        if (j == 1 AND n != Sims)
        {
        
            printf("%i Simulation(s) Left...System Will Rerun!\n\n", Sims - n);
            
            goto ReRun;
        
        }
        
        else if (j == 0 AND n != Sims)
        {
        
            printf("Nothing Found!\n");
            printf("%i Simulation(s) Left...System Will Rerun!\n\n",Sims - n);
            
            goto ReRun;
        
        }
        
        else
            printf("Finished!\n");
        
        //Unload GNet From Memory
        delete []GNet;
    
    }

    else
        GExit("Error: Wrong Function Specified!\n", 1);
    
    //Clean Up
    delete []NewData;

}

#endif

/* ------------------------------------------------------------------------ */
