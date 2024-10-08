/* This is the main file of the program, it contains the values of all paramaters,
   initial values of the state variables, size of the time step, duration of the
   simulation, and the specification of a dynamic and S1S2 restitution protocol.
   It contains the function Start which serves to get the name of the destinationpath
   (where output files should be put) from the commandline (if you do not supply this
   pathname the program aborts) and the function Main which contains a time loop in which 
   the other functions are called:
   Step: in which the computations of currents and the updating of voltage, intracellular
   concentrations and states of gates takes place and in which an output file of the currents
   is generated. (See file Step.cc)
   Var.writebackup: this is a function of the Variable object Var. The Variable object
   merely serves to create a single object that contains the different state variables that
   together describe the state of the cell and to be able to pass them on as a single item
   to other functions. The function writebackup writes to file a backup of the states of all
   variables at the times it is called (each row corresponds to a single point in time, the
   columns correspond to the different variables). (See files Variables.h and Variables.cc)
   In addition there is a file Header.h which contains the function definitions and in which we
   can define whether we want to simulate and epicardial endocardial or mid-myocardial human
   ventricular cell. Finally there is a makefile that serves as an example of how the different
   files that make up the program can be linked into a single executable (called model).*/

   

/* ERRATA:
   We found a typo in the parameter values in the ms describing this model.
   Below we list the value the parameter should have and which is used
   in this implementation but that is wrong in the ms:
   GpCa=0.825nS/pF
 */

#include "Header.h"
#include <vector>

/*-----------------------------------------------------------------------------
  FLAG TO CHOOSE BETWEEN DYNAMIC AND S1S2 RESTITUTION PROTOCOL
-----------------------------------------------------------------------------*/
#define DYNRESTPROTOCOL
//#define  S1S2RESTPROTOCOL

/*-----------------------------------------------------------------------------
  ELECTROPHYSIOLOGICAL PARAMETERS:
-----------------------------------------------------------------------------*/

//External concentrations
double Ko=5.4;
double Cao=2.0;
double Nao=140.0;

//Intracellular volumes
double Vc=0.016404;
double Vsr=0.001094;

//Calcium dynamics
double Bufc=0.15;
double Kbufc=0.001;
double Bufsr=10.;
double Kbufsr=0.3;
double taufca=2.;
double taug=2.;
double Vmaxup=0.000425;
double Kup=0.00025;

//Constants
double R=8314.472;
double F=96485.3415;
double T=310.0;
double RTONF=(R*T)/F;

//Cellular capacitance         
double CAPACITANCE=0.185;
double rho = 160; //ohm/cm
double S = 0.2; // mm^(-1)

//Parameters for currents
//Parameters for IKr
double Gkr=0.096;
//Parameters for Iks
double pKNa=0.03;
#ifdef EPI
double Gks=0.245;
#endif
#ifdef ENDO
double Gks=0.245;
#endif
#ifdef MCELL
double Gks=0.062;
#endif
//Parameters for Ik1
double GK1=5.405;
//Parameters for Ito
#ifdef EPI
double Gto=0.294;
#endif
#ifdef ENDO
double Gto=0.073;
#endif
#ifdef MCELL
double Gto=0.294;
#endif
//Parameters for INa
double GNa=14.838;
//Parameters for IbNa
double GbNa=0.00029;
//Parameters for INaK
double KmK=1.0;
double KmNa=40.0;
double knak=1.362;
//Parameters for ICaL
double GCaL=0.000175;
//Parameters for IbCa
double GbCa=0.000592;
//Parameters for INaCa
double knaca=1000;
double KmNai=87.5;
double KmCa=1.38;
double ksat=0.1;
double n=0.35;
//Parameters for IpCa
double GpCa=0.825;
double KpCa=0.0005;
//Parameters for IpK;
double GpK=0.0146;

// Mesh of cells
int n_cells_rows = 10;
int n_cells_cols = 10;
double dx = 0.1; // distance between cells, cm

/*------------------------------------------------------------------------------
                PARAMETER FOR INTEGRATION
------------------------------------------------------------------------------*/
//timestep (ms)
double  HT =0.02;

/*-----------------------------------------------------------------------------
                PARAMETERS FOR INITIAL CONDITIONS 
------------------------------------------------------------------------------*/
//Initial values of state variables
double V_init=-86.2;
double Cai_init=0.0002;
double CaSR_init=0.2;
double Nai_init=11.6;
double Ki_init=138.3;

/*--------------------------------------- ------------------------------------
             PARAMETER FOR SIMULATION DURATION
  ---------------------------------------------------------------------------*/
//duration of the simulation 
double STOPTIME=1000;

/*-----------------------------------------------------------------------------
  PARAMETERS FOR STIMULATION PROTOCOLS 
-----------------------------------------------------------------------------*/

#ifdef DYNRESTPROTOCOL
int i_low=0,i_high=1;
int j_low=0,j_high=1;
double stimduration=1.0;
double stimstrength=-52;
double period=1000;
double sum=period*1000.;
double tbegin=0;
double tend=tbegin+stimduration;
#endif


#ifdef S1S2RESTPROTOCOL
int i_low=0,i_high=1;
int j_low=0,j_high=1;
double stimduration=1.;
double stimstrength=-52;
double tbegin=0;
double tend=tbegin+stimduration;
int counter=1;
double dia=5000;
double basicperiod=1000.;
double basicapd=274;
int repeats=10;
#endif

/*----------------------------------------------------------------------------
                            OTHER PARAMETERS
  ---------------------------------------------------------------------------*/

//destination path to put in output files
char despath[200];

/*---------------------------------------------------------------------------*/


#define FALSE 0
#define TRUE 1



void Start(int argc, char *argv[])
{
  if(argc<2)
    {
      printf("type: model destinationpath\n");
      exit(1);
    }
  else
    {
      strcpy(despath,argv[1]);
    }
}

void write_headers(){

	// Write header of currents.csv
	static char s[200];
	FILE *FF;
	sprintf(s, "%s%s", despath, "/Currents_mod2.csv");
    FF = fopen(s, "w");

	for (int i = 0; i < n_cells_rows; i++) {
		for (int j = 0; j < n_cells_cols; j++) {
			fprintf(FF, "%s%i_%i,", "time_", (char) i, (char) j);
			fprintf(FF, "%s%i_%i,", "IKr_", (char) i, (char) j);
			fprintf(FF, "%s%i_%i,", "IKs_", (char) i,  (char) j);
			fprintf(FF, "%s%i_%i,", "IK1_", (char) i,  (char) j);
			fprintf(FF, "%s%i_%i,", "Ito_", (char) i,  (char) j);
			fprintf(FF, "%s%i_%i,", "INa_", (char) i,  (char) j);
			fprintf(FF, "%s%i_%i,", "IbNa_", (char) i,  (char) j);
			fprintf(FF, "%s%i_%i,", "INaK_", (char) i,  (char) j);
			fprintf(FF, "%s%i_%i,", "ICaL_", (char) i,  (char) j);
			fprintf(FF, "%s%i_%i,", "IbCa_", (char) i,  (char) j);
			fprintf(FF, "%s%i_%i,", "INaCa_", (char) i,  (char) j);
			fprintf(FF, "%s%i_%i,", "Irel_", (char) i,  (char) j);
			fprintf(FF, "%s%i_%i", "Istim_", (char) i,  (char) j);
		}
	}
    fprintf(FF, "\n");
    fclose(FF);

	 static char filename[300];

  sprintf(filename,"%s%s",despath,"/PointBackupData_mod_2.csv"); 
  
  std::ofstream oo(filename);
  if(!oo)
    {
      printf("cannot open file %s\n",filename);
      exit(1);
    }
    
	oo << "time,";              

	for (int i = 0; i < n_cells_rows; i++) {
		for (int j = 0; j < n_cells_cols; j++) {
			//oo << "Volt_"<< i << "_"<< j << ",";   
			/**oo << "Volt2_" << i << "_"<< j << ",";   
			oo << "Cai_" << i << "_"<< j << ",";     
			oo << "CaSR_" << i << "_"<< j << ",";
			oo << "Nai_" << i << "_"<< j << ",";
			oo << "Ki_" << i << "_"<< j << ",";
			oo << "M_" << i << "_"<< j << ",";       
			oo << "H_" << i << "_"<< j << ",";       
			oo << "J_" << i << "_"<< j << ",";       
			oo << "Xr1_" << i << "_"<< j << ",";     
			oo << "Xr2_" << i << "_"<< j << ",";     
			oo << "Xs_" << i << "_"<< j << ",";     
			oo << "S_" << i << "_"<< j << ",";       
			oo << "R_" << i << "_"<< j << ",";       
			oo << "D_" << i << "_"<< j << ",";      
			oo << "F_" << i << "_"<< j << ",";       
			oo << "FCa_" << i << "_"<< j << ",";      
			oo << "G_" << i << "_"<< j << ",";     **/ 
			i == n_cells_rows-1 && j == n_cells_cols-1? oo << "Volt_"<< i << "_" << j : oo << "Volt_"<<i <<"_"<< j<<",";            
		}
	}
	oo << std::endl;
	oo.close();
}

int main(int argc, char *argv[])
{
  static double time=0;
  int step;
  double Istim;

  Start(argc,argv);
  
  std::vector<std::vector<Variables>> cells(n_cells_rows);

  for (int i = 0; i <n_cells_rows; i++) {
	for (int j = 0; j < n_cells_cols; j++) 
		cells[i].push_back(*(new Variables(V_init,Cai_init,CaSR_init,Nai_init,Ki_init)));
  }

  write_headers();
 
  for(step=0;time<=STOPTIME;step++)
    { 
      

#ifdef DYNRESTPROTOCOL
      if(time>sum)
	{
	  if(period>4000)
	    {
	      period=period-1000;
	      sum=sum+period*30;
	    }
	  else if(period>3000)
	    {
	      period=period-1000;
	      sum=sum+period*30;
	    }
	  else if(period>2000)
	    {
	      period=period-1000;
	      sum=sum+period*30;
	    }
	  else if(period>1000)
	    {
	      period=period-1000;
	      sum=sum+period*100;
	    }
	  else if(period>500)
	    {
	     
	      period=period-250;
	      sum=sum+period*100;
	    }
	  else if(period>400)
	    {
	      period=period-50;
	      sum=sum+period*100;
	    }
	  else if(period>300)
	    {
	      period=period-10;
	      sum=sum+period*100;
	    }
	  else if(period>250)
	    {
	      period=period-5;
	      sum=sum+period*100;
	    }
	  else if(period>50)
	    {
	      period=period-1;
	      sum=sum+period*100;
	    }
	  else
	    {
	      printf("restitution protocol finished\n");
	      exit(1);
	    }
	}
	 
      if(time>=tbegin && time<=tend)
	{
	  Istim=stimstrength;
	}
      if(time>tend)
	{
	  Istim=0.;
	  tbegin=tbegin+period;
	  tend=tbegin+stimduration;
	}
#endif


#ifdef S1S2RESTPROTOCOL
      if(counter<repeats)
	{

	  if(time>=tbegin && time<=tend)
	    {
	      Istim=stimstrength;
	    }
	  if(time>tend)
	    {
	      Istim=0.;
	      tbegin=tbegin+basicperiod;
	      tend=tbegin+stimduration;
	      counter++;
	    }
	 
	}
      else if(counter==repeats)
	{

	  if(time>=tbegin && time<=tend)
	    {
	      Istim=stimstrength;
	    }
	  if(time>tend)
	    {
	      Istim=0.;
	      tbegin=tbegin+basicapd+dia;
	      tbeginS2=tbegin;
	      tend=tbegin+stimduration;
	      counter++;
	    }
	}
      else if(counter==repeats+1)
	{
	  if(time>=tbegin && time<=tend)
	    {
	      Istim=stimstrength;
	    }
	  if(time>tend)
	    {
	      Istim=0.;
	      tbegin=tbegin+basicperiod;
	      tend=tbegin+stimduration;
	      counter=0;
	      

	      if(dia>1000)
		{
		  dia=dia-1000;
		}
	      else if(dia>300)
		{
		  dia=dia-100;
		}
	      else if(dia>150)
		{
		  dia=dia-5;
		}
	      else if(dia>5)
		{
		  dia=dia-1;
		}
	      else
		{
		  printf("restitution protocol finished\n");
		  exit(1);
		}
	    } 
	}
#endif

	std::vector<double> v_up(n_cells_cols);
	
	for (int k = 0; k < n_cells_cols; ++k) v_up[k] = cells[0][k].Volt;

	for (int i = 0; i <n_cells_rows; i++) {
		double V_left = cells[i][0].Volt;
		for (int j = 0; j < n_cells_cols; j++) {
			double v_right, v_down;

			if (i < n_cells_rows -1 ) v_down = cells[i+1][j].Volt;
			else v_down = cells[n_cells_rows -1][j].Volt;

			if (j < n_cells_cols -1 ) v_right = cells[i][j+1].Volt;
			else v_right = cells[i][n_cells_cols-1].Volt;

			double V_i_j = cells[i][j].Volt;
			Step(&cells[i][j],HT,despath,&time,step, i == 0 && j == 0? Istim : 0.0);

			cells[i][j].Volt += HT* 0.00154*((v_right+V_left + v_down + v_up[j]-4*V_i_j)/(dx*dx));

			// std::cout<< HT* (1/(rho*S*CAPACITANCE))*((v_right-last_potential)/(dx*dx))<<std::endl;

			V_left = V_i_j;
			v_up[j] = V_i_j;

			// std::cout<<"Cell: "<<i<<std::endl<<HT* (1/(1000*rho*S*CAPACITANCE))*((v_right-last_potential)/(dx*dx))<<std::endl;
			}

	}	  

	// if (step ==5) return 0;

    if(step % 250 ==0) {
		//std::cout<<time<<std::endl;
		static char filename[300];
		sprintf(filename,"%s%s",despath,"/PointBackupData_mod_2.csv"); 
		std::ofstream oo(filename,std::ios::app);
		oo << time << ",";
		for (auto row: cells) {
			for (auto cell : row) {
				//cell.writebackup(&time,despath);
				oo << cell.Volt << ",";
			}
		}	
		oo << std::endl;
		oo.close();
	} 
	
	time+=HT;
    }
  return 0;
}
