# Computational stochastic modeling of human ventricular myocardium  

**Keywords**: Computational biology, electrophysiology, stochastic modeling, spiral waves   
### Linux   
To compile (through *Makefile*)   
 &nbsp;&nbsp;  `make model`   
To run   
  &nbsp;&nbsp; `./model dataDestinationFolder`   
### Windows   
To compile   
  &nbsp;&nbsp;  `g++ -O2 -o model Header.h Step.cc Variables.h Variables.cc Main.cc`    
To run   
  &nbsp;&nbsp; `./model dataDestinationFolder`   
the folder needs to be a previously existing one (code will not dynamically create it).   

## Project overview   
Mathematical models of the action potential of human heart cells have been of great importance
in the study of the electrophysiological behaviour of the human ventricular myocardium. In this
work, we present the extension of the known Ten Tusscher model to study stochastic evolution via
the implementation of binomial gating dynamics, analysing the limits of the commonly used deterministic approach. Also, it is presented the study of the deterministic 1D and 2D tissue simulations
calculating propagation speeds and the creation and propagation of spiral waves responsible for
reentry arrhythmias, as well as an stochastic 2D tissue simulation. Finally, a pseudo-ECG signal is
computed and compared with real ECG signals for reentry tachycardias.   

For a general quantitative overview, please read the project paper `Projecte_Pef2_v1.pdf`.   

*Simulation of 2-D tissue, propagation of a spiral potential wave simulating a reentry tachycardia*
![Spiral](https://github.com/user-attachments/assets/77ed8688-639c-4b9e-a5b2-daaaa64d778b)   

*Computed regular ECG signal vs ECG for the simulated reentry tachycaardia*
![ECG_comparison](https://github.com/user-attachments/assets/c3c764e3-c6bc-4257-8a98-9727062f9133)


*Studying spontaneous stimulations due to stochastic limit behavior (1D potential and gate analysis and 2D visualization)*
![Comparison2](https://github.com/user-attachments/assets/f828f1ef-8cbc-49ad-b684-da77cadf6ac9)
![binomicevolution](https://github.com/user-attachments/assets/6297e34c-864a-4daa-bd97-356373025486)


Contact information:    
- Arnau Marzabal Gatell: arnau.marzabal@estudiantat.upc.edu
- Ana Pons Ferrer: ana.pons@estudiantat.upc.edu
- Ariadna Cortes Danes: ariadna.cortes.danes@estudiantat.upc.edu
