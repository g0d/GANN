/* 

   Geeks Artificial Neural Network (G.A.N.N) - Exit
   
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



#ifndef __GEXIT__
#define __GEXIT__

//Libraries
#include <stdio.h>
#include <stdlib.h>

//Headers
#include "headers/gglobdec.h"
#include "headers/gexit.h"

//Geeks Exit (Function)
void GExit(char *ExitMsg, int ExitCode)
{

    printf("%s\n", ExitMsg);
    printf("G.A.N.N Terminated (Code:%i)\n", ExitCode);
    
    exit(ExitCode);

}

#endif

/* ------------------------------------------------------------------------ */
