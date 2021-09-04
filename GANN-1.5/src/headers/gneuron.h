/*
   Geeks Artificial Neural Network (G.A.N.N) - Neuron
   
   Copyright (C) 2008 - 2021 George Delaportas (G0D/ViR4X)
   
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



#ifndef __GNEURON_H__
#define __GNEURON_H__

//Geeks Neuron (Class - Model)
class GNeuron
{
    private:

    //Private Variables
    int NFT;                    //Neuron Function Type
    int Counter;                //A Counter
    int ISPins;					//InSlot Pins
    float Out;					//GNeuron Output
    float *InSlot;				//Inputs Slot (Data Inputs)
    float *Weights;				//Random Inputs Weights
    float Summary;				//A Summary
    float Base;					//Functions Base
    float SigFunc;				//Sigmoid Function Results

    //Randmomize Weights
    void RandWeights();

    //Sum Up
    void Sum();

    //Neuron Function
    void NFunc(int FType);



    public:

    //Constructor
    GNeuron();

    //Destructor
    ~GNeuron();    

    //Modulo
    float Mod;

    //Enable Neuron
    void Enable(int NFType);

    //Run Neuron
    void Run(int NFType);

    //Input Data
    void InData(int InputPin, float Data);

    //Output Data
    float OutData();

    //Set Neuron Function Type
    void SetNFT(int NewNFT);

    //Set Weights
    void SetWeights(int WPin, float Weight);

    //Get Neuron Function Type
    int GetNFT();

    //Get Sum
    float GetSum();

    //Get Base
    float GetBase();

    //Get Input Slot Pins
    int GetISPins();

    //Get Weights
    float GetWeights(int WIndex);
};

#endif

/* ------------------------------------------------------------------------ */
