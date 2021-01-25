#pragma once
#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <fstream>
#include <math.h>
#include <string.h>
using namespace std;
class loginSystem {
public:
	loginSystem();	 // Constructor
	~loginSystem() {
		delete[] * username;
		delete[] * password;
		if (!pass)
			cout << "\n\nExits from LoginSystem.\n\n";
	}	// Destructor
	bool login() { return pass; }	// Checking the username and password
private:
	char loginuser[50];
	char *username[50];
	char *password[50];
	bool pass = false;
};
class cMail {	//Stored database
public:
	cMail();	//Constructor
	~cMail() { delete Subject; delete Name; }	//Destructor
	void setData(char*, char*, char*, char, int);	//Set all variables in the cMail object
	int getDate() { return Date; }
	char *getSubject() { return Subject; }	//Get value for use 
	char *getName() { return Name; }
	char *getEmail() { return Email; }
	char getSend() { return send; }
private:
	int Date;	//Stored value
	char *Subject;
	char *Name;
	char *Email;
	char send;
};
class Em_Han {
public:
	Em_Han() {}
	void clearMem() {	//Clear temporary memory stored
		delete[] * subject;
		delete[] * name;
		delete[] * email;
	}
	void openAndReadFile(char *fileName);	//Open file and read data by consider the character of a txt file into a [i,m] matrix
	void sortAndSaveMailBySubject(cMail *list, int no);//perform sorting of email data by asc order of subject and save the result to db.txt
	bool checkEmail(char*);		//Check that '@' must have a character before and after
	cMail* buildToDb();		//Return a pointer pointed to an array of cMail objects created from db.txt
	void writeToDb();	//Override function of writeToDb to perform next line within the file db.txt
	void writeToDb(char *data);	//Write data to file db.txt
	int getNoOfMails() { return rolls; }	//Return the number of cMail object based on the database db.txt


private:
	cMail *dbMail;
	ifstream rdb;
	ofstream wdb;
	char *subject[50];
	char *name[50];
	char *email[50];
	char send[50];
	int date[50], rolls;
};