/* This file contains the object description for the Variables object
   that is intended both to be able to send all state variables as a
   package to functions needing it and allowing efficient handling of
   the set of state variables. */

class Variables
{
public:
  //voltage + backup
  double   Volt;
  double   Volt2;
  double   Cai;
  double   CaSR;
  double   Nai;
  double   Ki;

 
  //states of voltage and time dependent gates
  //INa
  double   M;
  double   H;
  double   J;
  //IKr
  //IKr1
  double   Xr1;
  //IKr2
  double   Xr2;
  //IKs
  double   Xs;
  //Ito1
  double   R;
  double   S;
  //ICa
  double   D;
  double   F;
  double   FCa;
  //Irel
  double   G;

  //total current
  double   Itot;

  
public:
  Variables(double V_init,double Cai_init,double CaSR_init,double Nai_init,double Ki_init);
  void writebackup(double *t,char *despath);
};
