link: SortedList Student SortedListDr.cpp
	g++ -Wall -g -pedantic-errors -o p2 SortedList.o Student.o SortedListDr.cpp

Student: Student.cpp Student.h
	g++ -c -Wall -g -pedantic-errors Student.cpp

SortedList: SortedList.cpp SortedList.h
	g++ -c -Wall -g -pedantic-errors SortedList.cpp

run:
	./p2

clean:
	/bin/rm *.o p2