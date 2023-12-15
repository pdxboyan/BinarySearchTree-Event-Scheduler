/***********************************************************************
Class: CS202
Assignment: Project03
Author: Boyan Gankov
File: event.h
Purpose: Header file for the Event hierarchy
Defines: The base class Event, acts as the virtual class in the 
hierarchy allowing for dynamic binding for it's derived classes. These
include a Safari, Aviary, and PetZoo. 
***********************************************************************/
#include <iostream>
#include <iomanip>
#include <cstring>
#include <string>
#include <vector>

using namespace std;

const int MAX = 101;



/***********************************************************************

Class: Event

Purpose: Base virtual class for the Event hierarchy

Contains: A name char array, a date string, as well as price and slots
integers.

***********************************************************************/
class Event {

	public:
		Event();
		Event(char* name, string& date, int slots, int price);
		Event(const Event& source);
		virtual ~Event();
		

		virtual ostream& display(ostream& out) const;
		void queryBase(istream& in);
		int compareName(const char* compareName);
		const char* getName();
		bool compareGLT(const Event& ev2) const; // Greater & Less Than
		bool compareGLTE(const Event& ev2) const; // Greater & Less Than, or Equal to
		bool compareE(const Event& ev2) const; // Equal to
		bool compareNE(const Event& ev2) const; // Not equal to

		friend ostream& operator<< (ostream& out, const Event& event);
		friend bool operator< (const Event& ev1, const Event& ev2);
		friend bool operator> (const Event& ev1, const Event& ev2);
		friend bool operator<= (const Event& ev1, const Event& ev2);
		friend bool operator>= (const Event& ev1, const Event& ev2);
		friend bool operator== (const Event& ev1, const Event& ev2);
		friend bool operator!= (const Event& ev1, const Event& ev2);
		virtual Event& operator= (const Event& ev2);

	protected:
		string valiDATE(int month, int day, int year);

		char* name;
		string date;
		int slots;
		int price;	
};



/***********************************************************************

Class: Safari

Purpose: Contains information

Contains: All of the Base variables, in addition to an integer route 
length

***********************************************************************/
class Safari : public Event {

	public:
		Safari();
		Safari(char* name, string& date, int slots, int price, int routeLength);
		Safari(const Safari& source);
		~Safari();

		ostream& display(ostream& out) const;
		void query(istream& in);
		friend istream& operator>> (istream& in, Safari& safari);
		friend ostream& operator<< (ostream& out, const Safari& safari);

	protected:
		int routeLength;
};



/***********************************************************************

Class: Aviary

Purpose: Contains information

Contains: All of the Base variables, in addition to a number of species

***********************************************************************/
class Aviary : public Event {

	public:
		Aviary();
		Aviary(char* name, string& date, int slots, int price, int numSpecies);
		Aviary(const Aviary& source);
		~Aviary();

		ostream& display(ostream& out) const;
		void query(istream& in);
		friend istream& operator>> (istream& in, Aviary& aviary);
		friend ostream& operator<< (ostream& out, const Aviary& aviary);

	protected:
		int numSpecies;
};



/***********************************************************************

Class: PetZoo

Purpose: Contains information

Contains: All of the Base variables, in addition to an integer age
requirment

***********************************************************************/
class PetZoo : public Event {

	public:
		PetZoo();
		PetZoo(char* name, string& date, int slots, int price, int ageReq);
		PetZoo(const PetZoo& source);
		~PetZoo();

		ostream& display(ostream& out) const;
		void query(istream& in);
		friend istream& operator>> (istream& in, PetZoo& petZoo);
		friend ostream& operator<< (ostream& out, const PetZoo& petZoo);

	protected:
		int ageReq;
};