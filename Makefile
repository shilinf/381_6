CC = g++
LD = g++

CFLAGS = -c -pedantic -std=c++11 -Wall -fno-elide-constructors
LFLAGS = -pedantic -Wall

OBJS = p6_main.o Model.o Controller.o Sim_object.o Island.o Ship_factory.o Ship.o Tanker.o Warship.o Cruiser.o View.o Utility.o Track_base.o Geometry.o Navigation.o Map_view.o Sailing_view.h Bridge_view.h Cruise_ship.o
PROG = p6exe

default: $(PROG)

$(PROG): $(OBJS)
	$(LD) $(LFLAGS) $(OBJS) -o $(PROG)

p6_main.o: p6_main.cpp Model.h Controller.h
	$(CC) $(CFLAGS) p6_main.cpp

Sim_object.o: Sim_object.cpp Sim_object.h Utility.h
	$(CC) $(CFLAGS) Sim_object.cpp

Island.o: Island.cpp Island.h Model.h
	$(CC) $(CFLAGS) Island.cpp

Ship.o: Ship.cpp Ship.h Model.h Utility.h Island.h
	$(CC) $(CFLAGS) Ship.cpp

Cruise_ship.o: Cruise_ship.cpp Cruise_ship.h Model.h Ship.h Island.h Utility.h
	$(CC) $(CFLAGS) Cruise_ship.cpp

Tanker.o: Tanker.cpp Tanker.h Ship.h Model.h Utility.h Island.h
	$(CC) $(CFLAGS) Tanker.cpp

Warship.o: Warship.cpp Warship.h Ship.h Model.h Utility.h
	$(CC) $(CFLAGS) Warship.cpp

Cruiser.o: Cruiser.cpp Cruiser.h Warship.h Utility.h
	$(CC) $(CFLAGS) Cruiser.cpp

Model.o: Model.cpp Model.h Island.h Utility.h Ship.h Ship_factory.h View.h
	$(CC) $(CFLAGS) Model.cpp

Controller.o: Controller.cpp Controller.h Island.h Utility.h Ship.h Ship_factory.h View.h Geometry.h
	$(CC) $(CFLAGS) Controller.cpp

View.o: View.cpp View.h Ship.h Utility.h Geometry.h
	$(CC) $(CFLAGS) View.cpp

Map_view.o: Map_view.cpp Map_view.h Ship.h Utility.h Geometry.h Island.h
	$(CC) $(CFLAGS) Map_view.cpp

Sailing_view.o: Sailing_view.cpp Sailing_view.h Ship.h Utility.h Geometry.h Island.h
	$(CC) $(CFLAGS) Sailing_view.cpp

Bridge_view.o: Bridge_view.cpp Bridge_view.h Ship.h Utility.h Geometry.h Island.h
	$(CC) $(CFLAGS) Bridge_view.cpp

Utility.o: Utility.cpp Utility.h
	$(CC) $(CFLAGS) Utility.cpp

Ship_factory.o: Ship_factory.cpp Ship_factory.h Geometry.h Utility.h Tanker.h Cruiser.h
	$(CC) $(CFLAGS) Ship_factory.cpp

Track_base.o: Track_base.cpp Track_base.h Geometry.h Navigation.h
	$(CC) $(CFLAGS) Track_base.cpp

Geometry.o: Geometry.cpp Geometry.h
	$(CC) $(CFLAGS) Geometry.cpp

Navigation.o: Navigation.cpp Navigation.h Geometry.h
	$(CC) $(CFLAGS) Navigation.cpp


clean:
	rm -f *.o
	rm -f *exe

real_clean:
	rm -f *.o
	rm -f *exe
