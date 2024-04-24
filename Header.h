/* Header file, forms a generalized header file containing headers of libraries that are used,
   function definitions and the cell type specification */ 

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string.h>

#include "Variables.h"

/*------------------------------------------------------------------------------
FLAG TO CHOOSE BETWEEN EPICARDIAL ENDOCARDIAL AND MIDMYOCARDIAL CELL TYPES
------------------------------------------------------------------------------*/
#define EPI
//#define ENDO
//#define MCELL


void Step(Variables *V,double HT,char *despath,double *t,int step,
	      double Istim);