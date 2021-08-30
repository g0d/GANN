/* 

   Geeks Artificial Neural Network (G.A.N.N) - Artificial Neural Network
   
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



#ifndef __GANN_H__
#define __GANN_H__

//Geeks Artificial Neural Network (Class - Model)
class GANN
{

    public:
    
    //Variables
    int GNNum;					//GNeurons Number
    int GMSType;				//GMap Simulation Type
    int GMCType;				//GMap Connections Type
    int Layers;					//GMap Layers
    int *GMap;					//The GMap
    float LearnTH;				//Learning Threshold
    float RunTH;				//Running Threshold
    
    //Constructor
    GANN();
    
    //Destructor
    ~GANN();

};

#endif

/* ------------------------------------------------------------------------ */
