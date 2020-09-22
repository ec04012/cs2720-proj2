#include "Student.h"

// Class constructors
// Default constructor, uses placeholder name and id
Student::Student() {
    this->setID(1111);
    this->setName("John Smith");
}
// Param constructor, gets name and id as param
Student::Student(int const& id, string const& name) {
    this->setID(id);
    this->setName(name);
}

// get methods
int Student::getID() const {
    return id;
}
string Student::getName() const {
    return name;
}

// set methods
void Student::setID(int const& newID) {
    this->id = newID;
}
void Student::setName(string const& newName) {
    this->name = newName;
}

// Operator overloads
bool Student::operator==(Student& s) {
    return id == s.getID();
}

bool Student::operator!=(Student& s) {
    return !(id == s.getID());
}

bool Student::operator<(Student& s) {
    return id < s.getID();
}

bool Student::operator>(Student& s) {
    return id > s.getID();
}

ostream& operator<<(ostream& out, const Student& stu) {
    out << stu.getID() << " " << stu.getName();
    return out;
}