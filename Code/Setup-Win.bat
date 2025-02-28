:: Messages
@echo "***********************************"
@echo "* Geeks Artificial Neural Network *"
@echo "*           (G.A.N.N)             *"
@echo "***********************************"
@echo ""
@echo "George Delaportas (G0D/ViR4X)"
@echo "Copyright (C) 2006 - 2025"
@echo ""
@echo "Installing..."

:: Compile
g++ -ansi -pedantic -O3 -c src/gmain.cpp src/gann.cpp src/gdmloader.cpp src/gerrc.cpp src/gerrstat.cpp src/gexit.cpp src/ggendata.cpp src/gneuron.cpp src/gnms.cpp src/grand.cpp src/grmc.cpp src/gsleep.cpp src/gsnmc.cpp src/gsocket.cpp src/gidsr.cpp src/gkdb.cpp

:: Link
g++ -W -o GANN gmain.o gann.o gdmloader.o gerrc.o gerrstat.o gexit.o ggendata.o gneuron.o gnms.o grand.o grmc.o gsleep.o gsnmc.o gsocket.o gidsr.o gkdb.o

:: Clean up
del *.o

:: Finalization
@echo "Done!"
