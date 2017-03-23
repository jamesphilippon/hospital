// Definition of class patient in patient.h 
#ifndef PATIENT_H
#define PATIENT_H
#include <iostream>
#include <string>
#include "date.h"

using namespace std;

struct procedure
{
	Date dateOfProcedure;
	int procedureID;
	int procedureProviderID;
};

class Patient {
public:
	//Patient (int, const char* , const char*, Date, int);
	Patient(int id = -1, const char* f = "fffff", const char* l = "lllll", Date d = NULL, int pId = -1);
	~Patient() {};

	Patient & setID ( int );
	Patient & setFirstName ( const char *); // shorten to 14 letters
	Patient & setLastName (const char *);  // shorten to 14 letters
	Patient & setBirthDate(Date);
	Patient & setPrimaryDoctorID(int);

	int getID();
	const char * getFirstName();
	const char * getLastName();
	Date getBirthDate();
	int getPrimaryDoctorID();

	bool enterProcedure (Date procedureDate, int procedureID, int procedureProviderID);
		// tries to add new entry to record array, returns true if added

	void printAllProcedures();
private:
	int ID;
	char firstName[15];
	char lastName[15];
	Date birthdate;
	int primaryDoctorID;
	procedure record[500];
	int currentCountOfProcedures; // how many procedures have been done

};
#endif