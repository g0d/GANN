/* 

   Geeks Artificial Neural Network (G.A.N.N) - Neuron
   
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



#ifndef __GNEURON__
#define __GNEURON__

//Libraries
#include <stdio.h>
#include <math.h>

//Headers
#include "headers/gglobdec.h"
#include "headers/gneuron.h"
#include "headers/ggendata.h"
#include "headers/gexit.h"

//Constructor
GNeuron::GNeuron()
{

    //Private Variables
    NFT = -1;
    Counter = 0;
    ISPins = 0;
    Out = 0.0;
    Summary = 0.0;
    Base = 0.0;
    SigFunc = 0.0;
    InSlot = new float[MAX_PIN];
    Weights = new float[MAX_PIN];
    
    //Public Variables
    Mod = 10;

}

//Destructor
GNeuron::~GNeuron()
{

    //Unload Matrices
    delete []InSlot;
    delete []Weights;

}

//Randmomize Weights
void GNeuron::RandWeights()
{

    //Get Random Weights
    for (Counter = 0; Counter < ISPins; Counter++)    
    {
    
        Weights[Counter] = GGenData(NFT, 0, Mod);
        
        printf("Weight %i: %f\n", Counter + 1, Weights[Counter]);
    
    }

}

//Sum Up
void GNeuron::Sum()
{

    //Reset Summary
    Summary = 0;
    
    //New Summary
    for (Counter = 0; Counter < ISPins; Counter++)
        Summary += InSlot[Counter] * Weights[Counter];

}

//Neuron Function
void GNeuron::NFunc(int FType)
{

    //Get Base From The Average Summary
    Base = Summary / ISPins;
    
    if (FType == 0)
    {
    
        //Step Function (Unity Sequence)
        if (Summary > Base)
            Out = 0.0;
        else
            Out = 1.0;
        
        printf("Out: %i\n", (int)Out);
    
    }
    
    else if (FType == 1)
    {
    
        //Sign Function
        if (Summary >= Base)
            Out = 1.0;
        else
            Out = -1.0;
        
        printf("Out: %i\n", (int)Out);
    
    }
    
    else if (FType == 2)
    {
    
        //Sigmoid Function (Real Systems Sequence)
        SigFunc = 1 / (1 + expf(-Summary));
        
        if (Summary >= Base)
            Out = SigFunc;
        else
            Out = -SigFunc;
        
        printf("Out: %f\n", Out);
    
    }
    
    else
        GExit("Error: Wrong Neuron Function Type Specified!\n", 1);

}

//Enable Neuron
void GNeuron::Enable(int NFType)
{

    //Set Neuron Function Type Globally
    NFT = NFType;
    
    //Run Functions
    RandWeights();
    Sum();
    NFunc(NFT);

}

//Run Neuron
void GNeuron::Run(int NFType)
{

    //Set Neuron Function Type Globally
    NFT = NFType;
    
    //Run Functions
    Sum();
    NFunc(NFT);

}

//Input Data
void GNeuron::InData(int InputPin, float Data)

{

    InSlot[InputPin] = Data;
    
    ISPins = InputPin + 1;
    
    printf("Input %i: %f\n", ISPins, InSlot[InputPin]);

}

//Output Data
float GNeuron::OutData()

{

    return Out;

}

//Set Neuron Function Type
void GNeuron::SetNFT(int NewNFT)

{

    NFT = NewNFT;

}

//Set Weights
void GNeuron::SetWeights(int WPin, float Weight)

{

    Weights[WPin] = Weight;

}

//Get Neuron Function Type
int GNeuron::GetNFT()

{

    return NFT;

}

//Get Sum
float GNeuron::GetSum()

{

    return Summary;

}

//Get Base
float GNeuron::GetBase()

{

    return Base;

}

//Get Input Slot Pins
int GNeuron::GetISPins()

{

    return ISPins;

}

//Get Weights
float GNeuron::GetWeights(int WIndex)

{

    return Weights[WIndex];

}

#endif

/* ------------------------------------------------------------------------ */
