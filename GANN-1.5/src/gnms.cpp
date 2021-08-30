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
#include "headers/gidsr.h"
#include "headers/gerrc.h"
#include "headers/gerrstat.h"
#include "headers/grmc.h"
#include "headers/gkdb.h"
#include "headers/gexit.h"

//Geeks Neural Map Simulator (Function)
void GNMS(int SimFunc, int SimMode)
{

    //Variables
    register int i, j;				//Fast Counters
    int n, k, p;				//Simple Counters
    int StartLayer;				//Starting Layer
    int EpC;					//Epochs Counter
    int GNC;					//GNeurons Counter
    int LHP;					//Layer Head Pointer
    int LEP;					//Layer End Pointer
    int LHT;					//Layer Head Temp
    int GNFT;					//GNeuron Function Type
    int RSN;					//Registration Serial Number
    int Sims;					//Simulations Number
    float *NewData;				//New Data From Inputs GSocket
    NewData = new float[MAX_PIN];
    float AccErr;				//Acceptable Error (%)
    float GErr;					//G.A.N.N Error (%)
    float GMin, GMax;				//Min,Max Values
    float Tmp;					//Temporary Float Values
    FILE *FileToCheck;				//A File Pointer
    
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
        
            printf("[GPin: %i]\n", i + 1);
            printf("Minimum Value: %f\n", InSocket.GetPV(i, 0));
            
	    if (InSocket.GetPT(i) == 0)
		printf("Maximum Value: N/A\n\n");
	    
	    else
	    {
	    
            	if (InSocket.GetPV(i, 0) == InSocket.GetPV(i, 1))
                    printf("Maximum Value: N/A\n\n");
            	else
                    printf("Maximum Value: %f\n\n", InSocket.GetPV(i, 1));
            
	    }
	
        }
        
        printf("--------------------------\n\n");
        
        //Start Simulation
        printf("Learning...\n");
        
        //Simulations Loop
        for (n = 0; n < SimNum; n++)
        {
        
            //Create New Geeks Network In Memory (G.A.N.N Matrix)
            GNeuron *GNet;
            GNet = new GNeuron[MAX_MATRIX];
            
            printf("\n* Simulation %i *\n\n", n + 1);
            
	    //Reset Starting Layer
	    StartLayer = 0;
	    
            //Reset Layer Head Temp
            LHT = 0;
	    
            //Reset Epochs
            EpC = 1;
	    
	    //Reset GNC
	    GNC = -1;
	    
            //Escape Caption
            ReRoute:;
	    
            //Check For Maximum Epochs
            if (EpC > MAX_EPX)
                GExit("Error: G.A.N.N Has Reached Maximum Epochs!\n", 1);
            
            printf("# Epoch %i #\n\n", EpC);
            
	    //Reset LHP
	    if (NewGANN.Layers > 1 AND EpC > 1)
	    	LHP = (LHT + NewGANN.GMap[0]) - (NewGANN.GMap[StartLayer] +\
		NewGANN.GMap[StartLayer - 1]);
	    else
            	LHP = 0;
            
            //Reset LEP
	    if (NewGANN.Layers > 1 AND EpC > 1)
	    	LEP = NewGANN.GMap[StartLayer - 1];
	    else
            	LEP = 0;
	    
	    //Reset GNC
	    if (NewGANN.Layers > 1 AND EpC > 1)
	    	GNC = GNC - NewGANN.GMap[StartLayer];
            else
		GNC = -1;
	    
            //Start Routing Through The Layers
            for (i = StartLayer; i < NewGANN.Layers; i++)
            {
            
                //Get GNeurons Of Current Layer
                k = NewGANN.GMap[i];
                
                //Check GMap Connections Type (0: Auto, 1: Manual)
                if (NewGANN.GMCType == 0)
                {
                
                    //Enable All GNeurons In This Layer
                    for (j = LEP; j < (k + LEP); j++)
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
                                
                                    if (InSocket.GetPV(p, 0) != InSocket.GetPV(p, 1))
                                        Tmp = GIDSR(InSocket, p, Steps[p]);
                                    
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
                        printf("LHP: %i     LEP: %i     k: %i\n\n", LHP, LEP, k);
			    //Give Data To This GNeuron
                            for (p = LHP; p < (LHP + LEP); p++)
                            	GNet[GNC].InData(p - LHP, GNet[p].OutData());
                        
			}
                        
                        //Enable This GNeuron
                        GNet[GNC].Enable(GNFT);
                        
                        printf("GNeuron %i Enabled!\n\n", GNC + 1);
                    
                    }
                    
                    //Next Layer Head
                    LHP += LEP;
                    
                    //Next Layer End
                    LEP = k;
                
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
            for (i = LHP; i < (LHP + LEP); i++)
            {
            
                GMinData[j] = GNet[i].OutData() * OutSocket.GetPV(j, 0);
                GMaxData[j] = GNet[i].OutData() * OutSocket.GetPV(j, 1);
                
                printf("[GPin %i]\n", j + 1);
                printf("Min: %f\n", GMinData[j]);
		
		if (OutSocket.GetPT(j) == 0)
		    printf("Max: N/A\n\n");
		
		else
                {
		
		    if (GMinData[j] == GMaxData[j])
		    	printf("Max: N/A\n\n");
		    else
		    	printf("Max: %f\n\n", GMaxData[j]);
                
		}
		
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
                        RegSerNum = abs((int)GGenData(0, 0.0,\
			(Inputs + Outputs) * (GNC + 1) *\
			EpC * SimNum * time(NULL)));
                        
			//Fixate Less Digits
			while (RegSerNum < 1000000000)
			    RegSerNum += 999;
                        
			//Initialize GSims
                        FileToCheck = fopen("GKDB/GSims", "a");
                        
                        //Save Registration Serial Number
                        fprintf(FileToCheck, "%i\n", RegSerNum);
                        
                        //Save Simulations Number
                        fprintf(FileToCheck, "%i\n", SimNum);
                        
                        //Close GSims
                        fclose(FileToCheck);
                    
                    }
                    
                    //Save This G.A.N.N To The GKDB
                    NewGKDB.SaveData(GNet, RegSerNum, n + 1);
                    
                    //Print Outputs GSocket
                    printf("----- Outputs GSocket -----\n\n");
                    
                    for (i = 0; i < Outputs; i++)
                    {
                    
                        printf("[GPin: %i]\n", i + 1);
                        printf("Minimum Value: %f\n", GMinData[i]);
            		
			if (OutSocket.GetPT(i) == 0)
			    printf("Maximum Value: N/A\n\n");
			
			else
			{
			
                            if (GMinData[i] == GMaxData[i])
                            	printf("Maximum Value: N/A\n\n");
                            else
                            	printf("Maximum Value: %f\n\n", GMaxData[i]);
                    	
			}
		    
                    }
                    
                    printf("---------------------------\n\n");
                    
                    printf("Learning Successfully Completed!\n");
                
                }
                
                else
                {
                
                    //Error Correction
		    for (i = LHP; i < (LHP + LEP); i++)
		    {
		    
			printf("Error Correction [Output GPin %i]\n\n", i - LHP + 1);
			
			GMin = OutSocket.GetPV(i - LHP, 0);
			GMax = OutSocket.GetPV(i - LHP, 1);
			
			if ((GNet[i].OutData() * GMin) < GMin\
			OR (GNet[i].OutData() * GMax) > GMax)
			{
			
			    if (NewGANN.GMSType == 0 OR NewGANN.GMSType == 1)
				GErrC(GNet, i, GErr, 1);
			    else
				GErrC(GNet, i, GErr, 0);
                        
			}
                    	
			else
			    printf("* GNeuron %i is Correct *\n\n", i + 1);
		    
                    }
		    
		    if (NewGANN.Layers > 1)
		    {
		    
		    	StartLayer = NewGANN.Layers - 1;
			
			if (LHT == 0)
			    LHT = LHP - abs(NewGANN.GMap[StartLayer] - NewGANN.GMap[0]);
	    	    
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
        FileToCheck = fopen("GKDB/GRegs", "a");
        
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
        GNet = new GNeuron[MAX_MATRIX];
        
        //Run GRMC (User Interaction - Load Offset And RegSerNum)
        GRMC(0);
        
        //Initialize GSims
        FileToCheck = fopen("GKDB/GSims", "r");
        
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
        NewGKDB.ReadData(GNet, RegSerNum, Offset, n);
        
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
        LHP = 0;
        
        //Reset NLE
        LEP = 0;
        
        //Start Routing Through The Layers
        for (i = 0; i < NewGANN.Layers; i++)
        {
        
            //Get GNeurons Of Current Layer
            k = NewGANN.GMap[i];
            
            //Check GMap Connections Type (0: Auto, 1: Manual)
            if (NewGANN.GMCType == 0)
            {
            
                //Enable All GNeurons
                for (j = LEP; j < (k + LEP); j++)
                {
                
                    //GNeurons Counter
                    GNC++;
                    
                    //Give Data To GNeurons Of The First Layer
                    if (i == 0)
                    {
                    
                        for (p = 0; p < Inputs; p++)
                        {
                        
                            GNet[GNC].InData(p - LHP, UserVal[p]);
                            printf("Weight %i: %f\n", p - LHP + 1,\
                            GNet[GNC].GetWeights(p - LHP));
                        
                        }
                    
                    }
                    
                    else
                    {
                    
                        //Give Data To GNeurons Of The Rest Layers
                        for (p = LHP; p < (LHP + LEP); p++)
                        {
                        
                            GNet[GNC].InData(p - LHP, GNet[p].OutData());
                            printf("Weight %i: %f\n", p - LHP + 1,\
                            GNet[GNC].GetWeights(p - LHP));
                        
                        }
                    
                    }
                    
                    //Run This GNeuron
                    GNet[GNC].Run(GNFT);
		    
		    printf("\n");
                
                }
                
                //Next Layer Head
                LHP += LEP;
                
                //Next Layer End
                LEP = k;
            
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
        for (i = LHP; i < (LHP + LEP); i++)
        {
        
            printf("[GPin %i]\n", i - LHP + 1);
            printf("Min: %f\n", GNet[i].OutData() * GMinData[i - LHP]);
	    
	    if (OutSocket.GetPT(i - LHP) == 0)
		printf("Max: N/A\n\n");
	    
	    else
	    {
	    
            	if (GMinData[i - LHP] == GMaxData[i - LHP])
		    printf("Max: N/A\n\n");
	    	else
		    printf("Max: %f\n\n", GNet[i].OutData() * GMaxData[i - LHP]);
	    
	    }
	
        }
        
        printf("------------------------\n\n");
        
        //Get G.A.N.N Values
        for (i = LHP; i < (LHP + LEP); i++)
        {
        
            if (GNet[i].OutData() * GMinData[i - LHP] >= GMinData[i - LHP]\
            AND GNet[i].OutData() * GMaxData[i - LHP] <= GMaxData[i - LHP])
            {
            
                if (NewGANN.RunTH < NewGANN.LearnTH)
                {
                
                    printf("* Output GPin %i *\n", i - LHP + 1);
                    printf("Value Found - Little Acurracy!\n\n");
                
                }
                
                else
                {
                
                    printf("* Output GPin %i *\n", i - LHP + 1);
                    printf("Value Found!\n\n");
                
                }
                
                j = 1;
            
            }
            
            else
            {
            
                printf("* Output GPin %i *\n", i - LHP + 1);
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
            printf("%i Simulation(s) Left...System Will Rerun!\n\n", Sims - n);
            
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
