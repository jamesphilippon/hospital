#include <iostream>
#include <string>
#include <fstream>
#include "date.h"
#include "patient.h"
using namespace std;


void newPatient(Patient** all, Patient** in, int& idAll, int& idIn)
{
	system("CLS");
	char fName[20];
	char lName[30];
	int bDateM, bDateD, bDateY, provID = 0;
	cout << "The patient ID will be: " << idAll;
	cout << "\nEnter first name: "; cin >> fName;
	cout << "Enter last name: "; cin >> lName;
	cout << "Enter birth date (MM DD YYYY): "; cin >> bDateM >> bDateD >> bDateY;
	Date bdate(bDateM, bDateD, bDateY);
	cout << "Enter provider ID: "; cin >> provID;
	all[idAll] = new Patient(idAll, fName, lName, bdate, provID);
	in[idIn] = new Patient(idAll, fName, lName, bdate, provID);
	idAll++; idIn++;
	cout << "\n\nSuccess!\n"; system("PAUSE");
}

void returnPatient(Patient** all, Patient** in, int& idAll, int& idIn)
{
	system("CLS");
	int retID = -1; int i = 0;
	bool found = false;
	cout << "Enter returning patient ID: "; cin >> retID;

	while (!found && i < idAll)
	{
		if (all[i]->getID() == retID)
		{
			found = true;
			in[idIn] = all[i]; cout << "\nSuccess!\n";
		}
		i++;
		idIn++;
	}
	if (i > idAll)
		cout << "Patient not found, retry."; system("PAUSE");
}

void printPatient(Patient** all, Patient** in, int& idAll, int& idIn)
{
	system("CLS");
	int i = 0;
	cout << "Checked in patients:\n";
	while (i < idIn)
	{
		cout << in[i]->getID() << " " << in[i]->getLastName() << ", " << in[i]->getFirstName() << " " << in[i]->getPrimaryDoctorID();
		i++;
		cout << endl;
	}
	cout << "\n";
	system("PAUSE");
}

void updateInfo(Patient** all, Patient** in, int& idAll, int& idIn, Date curDat)
{
	system("CLS");
	int findID = 0; int  i = 0; int j = 0; bool found = false; bool isFound = false;
	int pID, provID = 0;
	cout << "Enter patient ID: "; cin >> findID;
	int totalIn = idIn;
	while (!found && i < totalIn)
	{
		if (in[i]->getID() == findID)
		{
			cout << "\nPatient found: " << in[i]->getLastName() << ", " << in[i]->getFirstName() << endl;
			cout << "Enter procedure ID: "; cin >> pID; cout << "Enter provider ID: "; cin >> provID;
			found = in[i]->enterProcedure(curDat, pID, provID);
			cout << curDat; system("pause");

			while (!isFound && j < idAll)
			{
				if (all[i]->getID() == findID)
				{
					all[i] = in[i];
					isFound = true;
				}
				else j++;
			}
			in[i] = in[idIn]; idIn--;
		}
		else i++;
	}
}

void printInfo(Patient** all, int idAll)
{
	system("CLS");
	int findID, i = 0; bool found = false;
	cout << "Enter patient ID: "; cin >> findID;
	while (!found && i < idAll)
	{
		if (all[i]->getID() == findID)
		{
			found = true;
			cout << "\nPatient found: " << all[i]->getLastName() << ", "
				<< all[i]->getFirstName() << " \nDOB: " << all[i]->getBirthDate() << "\nPrimary Doctor: "
				<< all[i]->getPrimaryDoctorID();
			cout << endl; 
			all[i]->printAllProcedures();
		}
		else {
			i++; cout << "Patient not found.";
		}
		system("PAUSE");
	}
}

void quit(Patient** all, Patient** in, int& idAll, int& idIn, bool& close)
{
	system("CLS");
	if (idIn != 0)
	{
		cout << "There are still patients checked in!\n"; system("PAUSE");
	}
	else
	{
		cout << "Saving records to file...\n...\n...\n";
		ofstream patients("CurrentPatients.txt", ios::out | ios::binary);
		patients.write((char*)&idAll, sizeof(int));
		for (int i = 0; i < idAll; i++)
		{
			patients.write((char*)all[i], sizeof(Patient));
		}
		cout << "Saved all records.\n"; system("PAUSE");
		patients.close();
		close = true;
	}
}


////////////////////////////////////////////////////////////////////////////////////////////////////


int main(){

	bool close = false;
	int idNumA = 0;
	int numIN = 0;
	Patient * allPatients[200];
	Patient * inPatients[100];

	char menuChoice;
	int numExistingRecords = 0;

	int cMon, cDay, cYear = 0;
	cout << "Enter today's date (MM DD YYYY): "; cin >> cMon >> cDay >> cYear;
	Date cDate(cMon, cDay, cYear);

	ifstream patients("CurrentPatients.txt", ios::in | ios::binary);
	//input patient records
	if (patients.good() && !patients.eof())
	{
		patients.seekg(0);
		patients.read((char*)&numExistingRecords, sizeof(int));
		streampos fileStart = patients.tellg(); patients.seekg(ios::end); streampos fileEnd = patients.tellg();
		int fileSize = (fileEnd - fileStart) / sizeof(Patient);
		patients.close();
		idNumA = fileSize;


		for (int i = 0; i < fileSize; i++)
		{
			allPatients[i] = new Patient;
			patients.read((char*)allPatients[i], sizeof(Patient));
		}
	}

	//enter main menu
	do{
		system("CLS");
		cout << "Welcome to PATIENT SYSTEM\n";
		cout << "N: New patient.\n";
		cout << "R: Returning patient.\n";
		cout << "O: Check out patient.\n";
		cout << "I: Information on patient.\n";
		cout << "P: Print all checked in.\n";
		cout << "Q: Save and quit.\n";
		cout << "\n	MAKE A SELECTION: ";
		cin >> menuChoice;

		if (menuChoice == 'N' || menuChoice == 'n')
		{
			newPatient(allPatients, inPatients, idNumA, numIN);
		}

		if (menuChoice == 'R' || menuChoice == 'r')
		{
			returnPatient(allPatients, inPatients, idNumA, numIN);
		}

		if (menuChoice == 'P' || menuChoice == 'p')
		{
			printPatient(allPatients, inPatients, idNumA, numIN);
		}

		if (menuChoice == 'I' || menuChoice == 'i')
		{
			printInfo(allPatients, idNumA);
		}
		if (menuChoice == 'O' || menuChoice == 'o')
		{
			updateInfo(allPatients, inPatients, idNumA, numIN, cDate);
		}

		if (menuChoice == 'Q' || menuChoice == 'q')
		{
			quit(allPatients, inPatients, idNumA, numIN, close);
		}


	} while (!close);
	return 0;
}

