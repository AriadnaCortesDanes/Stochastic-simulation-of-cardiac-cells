OBJECTS =	 Step.cc  Variables.cc Main.cc

OPTIONSL =	-O2

IDIRL	=	/usr/X11R6/include/

LDIRL	=	/usr/X11R6/lib/ 

LIBS	=	-lm 

DEPS =	 Header.h Step.cc Variables.h Variables.cc Main.cc makefile

RDIR	=	-rpath,/local/freeware/lib32/:/local/lib32/

model: $(DEPS)
	g++ $(OPTIONSL) -I$(IDIRL) -o model $(OBJECTS) -L$(LDIRL) $(LIBS)


# En windows, compilem executant (des del directori corresponent)
# 		g++ -O2 -o model Header.h Step.cc Variables.h Variables.cc Main.cc
