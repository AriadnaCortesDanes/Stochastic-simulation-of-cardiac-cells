/* This file defines the functions that can be performed with the Variable object defined in
   Variables.h*/

#include "Header.h"

Variables::Variables(double V_init,double Cai_init,double CaSR_init,double Nai_init,double Ki_init)
{
  Volt=V_init;
  Volt2=V_init;
  Cai=0.000080;//Cai_init;
  CaSR=0.56;//CaSR_init;
  Nai=Nai_init;
  Ki=Ki_init;
  M= 0.;
  Nm=0;
  H= 0.75;
  J= 0.75; 
  Xr1= 0.;
  Xr2= 1.;
  Xs= 0.;
  R= 0.;
  S= 1.;
  D= 0.;
  F= 1.;
  FCa= 1.;                                        
  G= 1.;  

  printf("Variables initialized\n");
}



void Variables::writebackup(double *t,char *despath)
{
  static char filename[300];

  sprintf(filename,"%s%s",despath,"/PointBackupData_mod_2.csv"); 
  
  std::ofstream oo(filename,std::ios::app);
  if(!oo)
    {
      printf("cannot open file %s\n",filename);
      exit(1);
    }
     
  oo << (*t) << ",";              
  oo << Volt<< ",";   
  oo << Volt2 << ",";   
  oo << Cai << ",";     
  oo << CaSR << ",";
  oo << Nai << ",";
  oo << Ki << ",";
  oo << M << ",";       
  oo << H << ",";       
  oo << J << ",";       
  oo << Xr1 << ",";     
  oo << Xr2 << ",";     
  oo << Xs << ",";     
  oo << S << ",";       
  oo << R << ",";       
  oo << D << ",";      
  oo << F << ",";       
  oo << FCa << ",";      
  oo << G << ",";      
  oo << Itot;            
  oo << std::endl;
  oo.close();
  
}




