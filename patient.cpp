#include "patient.h"
#include <iostream>
#include <string>
using namespace std;



Patient::Patient(int id, const char* a, const char* b, Date date, int pID)
{
	setID(id);
	setFirstName(a);
	setLastName(b);
	setBirthDate(date);
	setPrimaryDoctorID(pID);
	currentCountOfProcedures = 0;
};


Patient &Patient::setID(int a)
{
	ID = a;
	return (*this);
}

Patient &Patient::setFirstName(const char* fn)
{
	strncpy(firstName, fn, 14);
	return (*this);
}

Patient &Patient::setLastName(const char* ln)
{
	strncpy(lastName, ln, 14);
	return (*this);
}

Patient &Patient::setBirthDate(Date dat)
{
	birthdate = dat;
	return (*this);
}

Patient &Patient::setPrimaryDoctorID(int pid)
{
	primaryDoctorID = pid;
	return (*this);
}

int Patient::getID()
{
	return ID;
}

const char * Patient::getFirstName()
{
	return firstName;
}

const char * Patient::getLastName()
{
	return lastName;
}

Date Patient::getBirthDate()
{
	return birthdate;
}

int Patient::getPrimaryDoctorID()
{
	return primaryDoctorID;
}

void Patient::printAllProcedures()
{
	cout << "Procedure history: " << endl;
	for (int i = 0; i < currentCountOfProcedures; i++)
	{
		cout << "   " << record[i].dateOfProcedure << " " << record[i].procedureID << " " << record[i].procedureProviderID;
		cout << endl;
	}
}

bool Patient::enterProcedure(Date dat, int procID, int providerID)
{
	record[currentCountOfProcedures].dateOfProcedure = dat;
	record[currentCountOfProcedures].procedureID = procID;
	record[currentCountOfProcedures].procedureProviderID = providerID;
	currentCountOfProcedures++;

	if (currentCountOfProcedures <=500)
	{
		return true;
	}
	else return false;	
}