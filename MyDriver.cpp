
// Test driver for the Sorted Linked List

#include <fstream>
#include <iostream>
#include <string>
using namespace std;
#include "SortedList.cpp"
#include "Student.h"
ostream& operator<<(ostream& out, Student& s) {
    out << s.id << "  " << s.name;
    return out;
}
istream& operator>>(istream& in, Student& s) {
    in >> s.id >> s.name;
    return in;
}
void testIntegersList();
void testStudentsList();
int main() {
	SortedList<int> list1;	
	ofstream outFile;
	outFile.open("testOutFile.txt");
	list1.putItem(32);
	list1.putItem(400);		
	list1.putItem(123);		
	list1.putItem(50);
	list1.putItem(200);		
	list1.putItem(256);			
	list1.printList(outFile);	

	SortedList<int> list2;
	list2.putItem(32);
	list2.putItem(64);
	list2.putItem(128);
	list2.putItem(200);
	list2.putItem(400);
	list2.printList(outFile);
	
	outFile << endl << "Merging lists" << endl << endl;
	list1.merge(list2);
	outFile << "list1" << endl;
	list1.printList(outFile);
	outFile << "list2" << endl;
	list2.printList(outFile);

	return 0;
}
