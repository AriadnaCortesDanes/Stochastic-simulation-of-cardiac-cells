/* This file defines the functions that can be performed with the Variable object defined in
   Variables.h*/

#include "Header.h"
extern double NTna;
extern double NTkr;
extern double NTCaL;
extern double NTto;
extern double NTks;
extern double NTCa;
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
  Nh=0.75*NTna;
  J= 0.75; 
  Nj=0.75*NTna;
  Xr1= 0.;
  Nsxr1=0;
  Xr2= 1.;
  Nsxr2=0.5*NTkr;
  Xs= 0.;
  Nxs=0;
  R= 0.;
  Nr=0;
  S= 1.;
  Ns=NTto;
  D= 0.;
  Nd=0;
  F= 1.;
  Nf=NTCaL;
  FCa= 1.;
  Nfca=NTCaL;                                        
  G=1.;
  Ng=NTCa;  

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
  //oo << std::endl;
  oo.close();
  
}




