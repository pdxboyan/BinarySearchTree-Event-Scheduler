/***********************************************************************
Class: CS202
Assignment: Project03
Author: Boyan Gankov
File: event.cpp
Purpose: Implementation file for the event heirarchy
Contains: Functions which define and manipulate classes in the Event
heirerarchy; Safari, Aviary, and PetZoo. This is done through
dynamic binding and virtual functions, the base being the virtual class.
***********************************************************************/
#include "event.h"



/***********************************************************************
Description: Constructs an empty Event object

Parameters: None

Returned: Nothing
***********************************************************************/
Event::Event() : name(nullptr), date(""), slots(0), price(0) {}



/***********************************************************************
Description: Constructs a filled Event object

Parameters: A char array name, string date, and integers for slots and
price

Returned: Nothing
***********************************************************************/
Event::Event(char* name, string& date, int slots, int price) : date(date), slots(slots), price(price) {
	this->name = new char[strlen(name)+1];
	strcpy(this->name, name);
}



/***********************************************************************
Description: Copy constructor for the Event class

Parameters: A constant Event object by reference

Returned: Nothing
***********************************************************************/
Event::Event(const Event& source) {
	this->name = new char[strlen(source.name)+1];
	strcpy(this->name, source.name);

	this->date = source.date;
	this->slots = source.slots;
	this->price = source.price;
}



/***********************************************************************
Description: Destructs and deallocates the memory allocated for an 
Event object

Parameters: None

Returned: Nothing
***********************************************************************/
Event::~Event() {
	if(name) delete [] name;
}



/***********************************************************************
Description: Virtual wrapper function for dynamic binding to point to
derived class' display functions

Parameters: Ostream object by reference

Returned: Ostream object
***********************************************************************/
ostream& Event::display(ostream& out) const {
	out << "\nName: " << name
	<< "\nDate: " << date
	<< "\nSlots: " << slots
	<< "\nPrice: $" << price;

	return out;
}



/***********************************************************************
Description: Takes and validates user input for all of the base class 
variables

Parameters: An istream object by reference

Returned: Nothing
***********************************************************************/
void Event::queryBase(istream& in) {
	
	char tempName[MAX];
	int month = 0;
	int day = 0;
	int year = 0;

	// Date input
	// _________________________________________

	cout << "\n - Please enter the date of the event - \n"
		 << "Month: ";
	in >> month;

	while(month <= 0 || month > 12) {
		cout << "\nInvalid month!" << endl;

		cout << "Month: ";
		in >> month;
		if(!cin) throw "\nCannot cast type char as type int";
	}

	cout << "Day: ";
	in >> day;

	switch(month) {
		case 1:
		case 3:
		case 5:
		case 7:
		case 8:
		case 10:
		case 12:
			while(day <= 0 || day > 31) {
				cout << "\nInvalid day!" << endl;

				cout << "Day: ";
				in >> day;
				if(!cin) throw "\nCannot cast type char as type int";
			}
			break;

		case 4:
		case 6:
		case 9:
		case 11:	
			while(day <= 0 || day > 30) {
				cout << "\nInvalid day!" << endl;

				cout << "Day: ";
				in >> day;
				if(!cin) throw "\nCannot cast type char as type int";
			}
			break;

		case 2:
			while(day <= 0 || day > 28) {
				cout << "\nInvalid day!" << endl;

				cout << "Day: ";
				in >> day;
				if(!cin) throw "\nCannot cast type char as type int";
			}
			break;

		default:
			cout << "\nYou seriously fucked up... how did you get down here.." << endl;
	}

	cout << "Year: ";
	in >> year;

	while(year < 0 || year > 99) {
		cout << "\nInvalid year!" << endl;

		cout << "Year: ";
		in >> year;
		if(!cin) throw "\nCannot cast type char as type int";
	}

	date = valiDATE(month, day, year);


	// Name input
	// _________________________________________

	cout << "\nWhat is the event name? ";
	in.ignore(MAX, '\n');
	in.get(tempName, MAX, '\n');

	name = new char[strlen(tempName)+1];
	strcpy(name, tempName);
	

	// Slots input and validation
	// _________________________________________

	cout << "\nHow many slots are there? ";
	in >> slots;
	if(!cin) throw "\nCannot cast type char as type int";

	while(slots <= 0) {
		cout << "\nInvalid slot amount!" << endl;

		cout << "\nHow many slots are there? ";
		in >> slots;
		if(!cin) throw "\nCannot cast type char as type int";
	}
	

	// Slots input and validation
	// _________________________________________

	cout << "\nHow much does it cost? (in dollars): ";
	in >> price;
	if(!cin) throw "\nCannot cast type char as type int";

	while(price < 0) {
		cout << "\nInvalid price!" << endl;

		cout << "\nHow much does it cost? ";
		in >> price;
		if(!cin) throw "\nCannot cast type char as type int";
	}
	
}



/***********************************************************************
Description: Combines a set of integers into a date string

Parameters: Three integer componenets of a date

Returned: A validated date string
***********************************************************************/
string Event::valiDATE(int month, int day, int year) { 
	string mm;
	string dd;
	string yy;

	if(month < 10) {
		mm = '0' + to_string(month);
	}
	else mm = to_string(month);

	if(day < 10) {
		dd = '0' + to_string(day);
	}
	else dd = to_string(day);

	if(year < 10) {
		yy = '0' + to_string(year);
	}
	else yy = to_string(year);

	string realDate = mm + "/" + dd + "/" + yy;

	return realDate;
}



/***********************************************************************
Description: Returns an event name

Parameters: None

Returned: A const char event name
***********************************************************************/
const char* Event::getName() {
	return this->name;
}



/***********************************************************************
Description: Compares a string to the name char array of an Event
object

Parameters: String by reference

Returned: True or false
***********************************************************************/
int Event::compareName(const char* compareName) {
	if(strcmp(this->name, compareName) == 0) return 1;
	return 0;
}



/***********************************************************************
Description: Overloads the insertion operator for the Event class for 
use with cout

Parameters: Ostream object by reference

Returned: Ostream object
***********************************************************************/
ostream& operator<<(ostream& out, const Event& event) {
	event.display(out);
	return out;
}


/***********************************************************************
Description: Does the comparison for the overloaded greater than and 
less than operators

Parameters: Const Event object by reference

Returned: True or false
***********************************************************************/
bool Event::compareGLT(const Event& ev2) const {
	if(this->slots > ev2.slots) return 1;
	return 0;
}



/***********************************************************************
Description: Does the comparison for the overloaded greater than and 
less than or equal to operators

Parameters: Const Event object by reference

Returned: True or false
***********************************************************************/
bool Event::compareGLTE(const Event& ev2) const {
	if(this->slots >= ev2.slots) return 1;
	return 0;
}



/***********************************************************************
Description: Does the comparison for the overloaded equivalance operator

Parameters: Const Event object by reference

Returned: True or false
***********************************************************************/
bool Event::compareE(const Event& ev2) const {
	if(this->slots == ev2.slots) return 1;
	return 0;
}



/***********************************************************************
Description: Does the comparison for the overloaded not equal to operator

Parameters: Const Event object by reference

Returned: True or false
***********************************************************************/
bool Event::compareNE(const Event& ev2) const {
	if(this->slots != ev2.slots) return 1;
	return 0;
}



/***********************************************************************
Description: Overloads greater than operator

Parameters: Two const Event objects by reference

Returned: True or false
***********************************************************************/
bool operator> (const Event& ev1, const Event& ev2) {
	return ev1.compareGLT(ev2);
}



/***********************************************************************
Description: Overloads less than operator

Parameters: Two const Event objects by reference

Returned: True or false
***********************************************************************/
bool operator< (const Event& ev1, const Event& ev2) {
	return ev2.compareGLT(ev1);
}



/***********************************************************************
Description: Overloads greater than or equal to operator

Parameters: Two const Event objects by reference

Returned: True or false
***********************************************************************/
bool operator>= (const Event& ev1, const Event& ev2) {
	return ev1.compareGLTE(ev2);
}



/***********************************************************************
Description: Overloads less than or equal to operator

Parameters: Two const Event objects by reference

Returned: True or false
***********************************************************************/
bool operator<= (const Event& ev1, const Event& ev2) {
	return ev2.compareGLTE(ev1);
}



/***********************************************************************
Description: Overloads equivalence operator

Parameters: Two const Event objects by reference

Returned: True or false
***********************************************************************/
bool operator== (const Event& ev1, const Event& ev2) {
	return ev1.compareE(ev2);
}



/***********************************************************************
Description: Overloads not equal to operator

Parameters: Two const Event objects by reference

Returned: True or false
***********************************************************************/
bool operator!= (const Event& ev1, const Event& ev2) {
	return ev1.compareNE(ev2);
}



/***********************************************************************
Description: Overloads assignemnt operator

Parameters: Const Event object by reference

Returned: An event object by reference
***********************************************************************/
Event& Event::operator= (const Event& ev2) {
	if(*this == ev2) return *this;

	if(this->name) delete [] this->name;

	this->name = new char[strlen(ev2.name)+1];
	strcpy(this->name, ev2.name);

	this->date = ev2.date;
	this->slots = ev2.slots;
	this->price = ev2.price;

	return *this;
}




//___________________________________________________________________________________________________________________________________
//___________________________________________________________________________________________________________________________________




/***********************************************************************
Description: Constructor for an empty Safari object

Parameters: None

Returned: Nothing
***********************************************************************/
Safari::Safari() : Event(), routeLength(0) {}



/***********************************************************************
Description: Constructor for a filled Safari object

Parameters: All of the base class variables plus an integer route length

Returned: Nothing
***********************************************************************/
Safari::Safari(char* name, string& date, int slots, int price, int routeLength) : Event(name, date, slots, price), routeLength(routeLength) {}



/***********************************************************************
Description: Copy constructor for the Safari class

Parameters: Const Safari object by reference

Returned: Nothing
***********************************************************************/
Safari::Safari(const Safari& source) : Event(source) {
	this->routeLength = source.routeLength;
}



/***********************************************************************
Description: Destructor for the Safari class, implicitly calls the base
constructor

Parameters: None

Returned: Nothing
***********************************************************************/
Safari::~Safari() {}



/***********************************************************************
Description: Displays a Safari object to the console

Parameters: Ostream object by reference

Returned: Ostream object
***********************************************************************/
ostream& Safari::display(ostream& out) const {
	out << "\nEvent Type: Safari";
	Event::display(out);
	out << "\nRoute Length: " << routeLength
	<< " miles" << endl << endl;

	return out;
}



/***********************************************************************
Description: Query function for the Safari class, calls the Base class
query

Parameters: Istream object by reference

Returned: Nothing
***********************************************************************/
void Safari::query(istream& in) {
	queryBase(in);

	cout << "\nWhat is the route length? (in miles): ";
	in >> this->routeLength;
	if(!cin) throw "\nCannot cast type char as type int";

	while(routeLength <= 0) {
		cout << "\nInvalid route length!" << endl;

		cout << "\nWhat is the route length? (in miles): ";
		in >> this->routeLength;
		if(!cin) throw "\nCannot cast type char as type int";
	}
}



/***********************************************************************
Description: Overloads the extraction operator for the Safari class to 
use with cin

Parameters: Istream object by reference and a Safari object by reference

Returned: Istream object
***********************************************************************/
istream& operator>> (istream& in, Safari& safari) {
	safari.query(in);
	return in;
}



/***********************************************************************
Description: Overloads the insertion operator for Safari with use with
cout

Parameters: Ostream object by reference and a Const Safari object by 
reference

Returned: Ostream object
***********************************************************************/
ostream& operator<< (ostream& out, const Safari& safari) {
	safari.display(out);
	return out;
}




//___________________________________________________________________________________________________________________________________
//___________________________________________________________________________________________________________________________________




/***********************************************************************
Description: Constructor for an empty Aviary object

Parameters: None

Returned: Nothing
***********************************************************************/
Aviary::Aviary() : Event(), numSpecies(0) {}



/***********************************************************************
Description: Constructor for a filled Aviary object

Parameters: All of the base class variables plus an integer number of
species

Returned: Nothing
***********************************************************************/
Aviary::Aviary(char* name, string& date, int slots, int price, int numSpecies) : Event(name, date, slots, price), numSpecies(numSpecies) {}



/***********************************************************************
Description: Copy constructor for the Aviary class

Parameters: Const Aviary object by reference

Returned: Nothing
***********************************************************************/
Aviary::Aviary(const Aviary& source) : Event(source) {
	this->numSpecies = source.numSpecies;
}



/***********************************************************************
Description: Destructor for the Aviary class, implicitly calls the base
constructor

Parameters: None

Returned: Nothing
***********************************************************************/
Aviary::~Aviary() {}



/***********************************************************************
Description: Displays a Aviary object to the console

Parameters: Ostream object by reference

Returned: Ostream object
***********************************************************************/
ostream& Aviary::display(ostream& out) const {
	out << "\nEvent Type: Aviary";
	Event::display(out);
	out << "\nNumber Of Species: " << numSpecies
	<< endl << endl;

	return out;
}



/***********************************************************************
Description: Query function for the Aviary class, calls the Base class
query

Parameters: Istream object by reference

Returned: Nothing
***********************************************************************/
void Aviary::query(istream& in) {
	queryBase(in);

	cout << "\nHow many species will there be? ";
	in >> this->numSpecies;
	if(!cin) throw "\nCannot cast type char as type int";

	while(numSpecies < 1) {
		cout << "\nInvalid number of species!" << endl;

		cout << "\nHow many species will there be? ";
		in >> this->numSpecies;
		if(!cin) throw "\nCannot cast type char as type int";
	}
}



/***********************************************************************
Description: Overloads the extraction operator for the Aviary class to 
use with cin

Parameters: Istream object by reference and a Aviary object by reference

Returned: Istream object
***********************************************************************/
istream& operator>> (istream& in, Aviary& aviary) {
	aviary.query(in);
	return in;
}



/***********************************************************************
Description: Overloads the insertion operator for Aviary with use with
cout

Parameters: Ostream object by reference and a Const Aviary object by 
reference

Returned: Ostream object
***********************************************************************/
ostream& operator<< (ostream& out, const Aviary& aviary) {
	aviary.display(out);
	return out;
}




//___________________________________________________________________________________________________________________________________
//___________________________________________________________________________________________________________________________________




/***********************************************************************
Description: Constructor for an empty PetZoo object

Parameters: None

Returned: Nothing
***********************************************************************/
PetZoo::PetZoo() : Event(), ageReq(0) {}



/***********************************************************************
Description: Constructor for a filled PetZoo object

Parameters: All of the base class variables plus an integer age 
requirment

Returned: Nothing
***********************************************************************/
PetZoo::PetZoo(char* name, string& date, int slots, int price, int ageReq) : Event(name, date, slots, price), ageReq(ageReq) {}



/***********************************************************************
Description: Copy constructor for the PetZoo class

Parameters: Const PetZoo object by reference

Returned: Nothing
***********************************************************************/
PetZoo::PetZoo(const PetZoo& source) : Event(source) {
	this->ageReq = source.ageReq;
}



/***********************************************************************
Description: Destructor for the PetZoo class, implicitly calls the base
constructor

Parameters: None

Returned: Nothing
***********************************************************************/
PetZoo::~PetZoo() {}



/***********************************************************************
Description: Displays a PetZoo object to the console

Parameters: Ostream object by reference

Returned: Ostream object
***********************************************************************/
ostream& PetZoo::display(ostream& out) const {
	out << "\nEvent Type: Petting Zoo";
	Event::display(out);
	out << "\nAge Requirement: " << ageReq 
	<< endl << endl;

	return out;
}



/***********************************************************************
Description: Query function for the PetZoo class, calls the Base class
query

Parameters: Istream object by reference

Returned: Nothing
***********************************************************************/
void PetZoo::query(istream& in) {
	queryBase(in);

	cout << "\nWhat is the minimum age requirement? ";
	in >> this->ageReq;
	if(!cin) throw "\nCannot cast type char as type int";

	while(ageReq <= 0) {
		cout << "\nInvalid age requirement!" << endl;

		cout << "\nWhat is the minimum age requirement? ";
		in >> this->ageReq;
		if(!cin) throw "\nCannot cast type char as type int";
	}
}



/***********************************************************************
Description: Overloads the extraction operator for the PetZoo class to 
use with cin

Parameters: Istream object by reference and a PetZoo object by reference

Returned: Istream object
***********************************************************************/
istream& operator>> (istream& in, PetZoo& petzoo) {
	petzoo.query(in);
	return in;
}



/***********************************************************************
Description: Overloads the insertion operator for PetZoo with use with
cout

Parameters: Ostream object by reference and a Const PetZoo object by 
reference

Returned: Ostream object
***********************************************************************/
ostream& operator<< (ostream& out, const PetZoo& petzoo) {
	petzoo.display(out);
	return out;
}