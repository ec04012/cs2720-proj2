
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

	list1.printList(outFile);
	list1.putItem(123);	
	list1.putItem(5);	
	list1.putItem(50);
	list1.putItem(200);
	list1.putItem(150);
	list1.putItem(1024);
	list1.printList(outFile);

	list1.deleteItem(150);	
	list1.printList(outFile);

	cout << "Here" << endl;

	list1.deleteItem(5);	
	list1.printList(outFile);

	cout << "Here" << endl;

	list1.deleteItem(1024);		
	list1.printList(outFile);

	return 0;
}
