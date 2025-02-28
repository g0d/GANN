/*
   Geeks Artificial Neural Network (G.A.N.N) - Global Declarations
   
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



#ifndef __GGLOBDEC_H__
#define __GGLOBDEC_H__

//Headers
#include "gsocket.h"
#include "gann.h"
#include "gkdb.h"

//Set Global Symbols Definitions
#define     TRUE     1
#define     FALSE    0
#define     AND      &&
#define     OR       ||
#define     NOT      !

//Global Constants
const int AUTO = 0;                             //Automatic Definition
const int MAX_REG = 100000;                     //Maximum Database Registrations
const int MAX_SIM = 1000;                       //Maximum Simulations
const int MAX_EPX = 10000;                      //Maximum Epochs
const int MAX_LAYERS = 16;                      //Maximum Layers
const int MAX_GN = 999;                         //Maximum GNeurons In Each Layer
const int MAX_MATRIX = MAX_LAYERS * MAX_GN;     //Maximum Matrix
const int MAX_PIN = 1000;                       //Maximum Pins
const float PIN_VAL2_DEFAULT = -999999.999999;  //Default Value 2 Of Pins

//Global Variables
extern int SimNum;                              //Simulations Number
extern int ECT;                                 //Error Check Type
extern int Inputs, Outputs;                     //GSockets I/O
extern int RegSerNum;                           //Registration Serial Number
extern int UserInp;                             //User Inputs (GRMC)
extern long Offset;                             //GHT Offset
extern float GMinData[MAX_PIN];                 //Minimum Data
extern float GMaxData[MAX_PIN];                 //Maximum Data
extern float UserVal[MAX_PIN];                  //User Values
extern float Steps[MAX_PIN];                    //GSocket - GPins Steps

//GSockets
extern GSocket InSocket;                        //Inputs GSocket
extern GSocket OutSocket;                       //Outputs GSocket

//New G.A.N.N
extern GANN NewGANN;

//New GKDB
extern GKDB NewGKDB;

#endif

/* ------------------------------------------------------------------------ */
