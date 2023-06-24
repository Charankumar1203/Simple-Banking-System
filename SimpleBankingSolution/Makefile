CPP = g++
FLAGS = -O5 -Wall -W
RM = rm -f
EXEC = BankingSolution
OBJECTS = main.o account.o bank.o atm.o

all : $(OBJECTS) compile

main.o : main.cpp
	$(CPP) $(FLAGS) -c main.cpp

account.o : account.cpp
	$(CPP) $(FLAGS) -c account.cpp

bank.o : bank.cpp
	$(CPP) $(FLAGS) -c bank.cpp

atm.o : atm.cpp
	$(CPP) $(FLAGS) -c atm.cpp


compile :
	$(CPP) $(FLAGS) $(OBJECTS) -o $(EXEC)

clean :
	$(RM) $(OBJECTS) $(EXEC)
