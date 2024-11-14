CXX=g++
CPPFLAGS=-std=c++11 -fopenmp -mavx -Wall -O0 -O2 -lboost_iostreams -lboost_system -lboost_date_time -lboost_thread -lpthread
#CPPFLAGS=-lboost_iostreams -lboost_system -lboost_date_time -lboost_thread -lpthread 
LIBSEARCHPATH=-L/opt/local/lib/ -lcrypto

OBJECTS=$(PROJECT).o utils.o chaotic_maps.o 
PROJECT=main_time

$(PROJECT) : $(OBJECTS)
	$(CXX)  $(OBJECTS) -o $@ $(LIBSEARCHPATH) $(LIBS) $(CPPFLAGS)

.cpp.o :
	$(CXX) -c $(CPPFLAGS) -o $@ $<

clean :
	rm -f $(OBJECTS)
