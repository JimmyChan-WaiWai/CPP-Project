// ProgrammingAppDev.cpp : Defines the entry point for the console application.
#define _CRT_SECURE_NO_WARNINGS 1
#include "EmailSystem.h";
#include <iostream>
#include <fstream>
#include <math.h>
#include <string.h>
using namespace std;
int main()
{
	Em_Han eh;
	eh.openAndReadFile("db.txt");
	eh.buildToDb();

	loginSystem *login = new loginSystem();
	if (login->login()) {//validates the login info given by the user and decide whether giving access to the email system
		cout << "\n\nWelcome to the email system!!!\n\n";
		bool flag = true;
		while (flag) {
			eh.openAndReadFile("db.txt");//Open and read the db.txt database every time to update the data.
			char choice;
			cout << "***************************************************************************************";
			cout << "\n[a] Perform Sorting of Mails based on ascending order of subject and save to file.\n";
			cout << "[b] Input a new mail.\n";
			cout << "[q] Exit the program.\nPlease Input Your Choice: ";
			cin >> choice;
			switch (choice) {
			case 'a':
				//Sort the array of cMail object given by the most up to data set of data from the database from the email handler
				cout << "***************************************************************************************";
				eh.sortAndSaveMailBySubject(eh.buildToDb(), eh.getNoOfMails());
				break;
			case 'b':
				//Input a new Mail data to the database db.txt
				cout << "***************************************************************************************\n";
				while (cin.get() != '\n')
					continue;
				char line[75];
				cout << "Please input a Subject: ";
				cin.getline(line, 75);
				eh.writeToDb(line);
				eh.writeToDb(":");
				cout << "Please input a Name: ";
				cin >> line;
				eh.writeToDb(line);
				eh.writeToDb(":");
				while (!eh.checkEmail(line)) {
					cout << "Please input a Email: ";
					cin >> line;
				}
				eh.writeToDb(line);
				eh.writeToDb(":");
				cout << "Please input a date: ";
				cin >> line;
				eh.writeToDb(line);
				eh.writeToDb(":");
				cout << "Please input the status (Send = 0, Receive = 1): ";
				cin >> line;
				eh.writeToDb(line);
				eh.writeToDb();
				break;
			case 'q':
				flag = false;
				break;
			default:
				cout << "***************************************************************************************";
				cout << "\nWrong Input, Please Input Again: ";
				break;
			}

		}
	}
	//free the memory used by the program
	eh.clearMem();
	delete login;
	return 0;
}

