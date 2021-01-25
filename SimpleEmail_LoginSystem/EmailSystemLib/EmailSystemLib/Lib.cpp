#include "EmailSystem.h";

loginSystem::loginSystem() {
	cout << "=========Welcome to  Entrance 1.0 System=========\n\nInitialising...\n\n";

	ifstream udf("userdata.txt");

	int i = 0;
	char *temp[50];
	for (i = 0; i < 50; i++) {
		temp[i] = new char[50];
		username[i] = new char[25];
		password[i] = new char[25];
		for (int m = 0; m < 25; m++) {
			username[i][m] = NULL;
			password[i][m] = NULL;
		}
	}

	i = 0;
	while (udf.getline(temp[i], 50) && i < 50) {
		int pos = 0;
		while (temp[i][pos] != ':' && temp[i][pos] != NULL && pos < 25) {
			username[i][pos] = temp[i][pos];
			pos++;
		}
		pos++;
		int sp = pos;
		while (temp[i][pos] != NULL && pos < 50) {
			password[i][pos - sp] = temp[i][pos];
			pos++;
		}
		i++;
	}
	udf.close();

	char un[25], pw[25];
	cout << "Ready.\n\nUsername: ";
	cin.getline(un, 25);
	for (i = 0; i < 50; i++) {
		if (strcmp(username[i], un) == 0) {
			cout << "\nvalid username, input your password: ";
			cin.getline(pw, 25);
			int rec = 0;
			while (strcmp(password[i], pw) != 0 && rec <= 2) {
				rec++;
				if (rec <= 2) {
					cout << "\n\ninvalid password, remaining attempt( " << 3 - rec << " ), please enter again: ";
					cin.getline(pw, 25);
				}
			}
			if (rec > 2) {
				cout << "\nFailed to input a valid password to account: " << username[i] << " for 3 times.";
				break;
			}
			cout << "\n\nLogin Successful.\n\n";
			pass = true;
			break;
		}
		else if (i == 49) {
			cout << "\n\nIt appears you are a new user.\nPlease create your password: ";
			cin.getline(pw, 25);
			ofstream write;
			write.open("userdata.txt", ios::app);
			write << un << ':' << pw << endl;
			write.close();
			cout << "\n\nAccount successfully created, you are logged in.\n\n";
			strcpy_s(loginuser, username[i]);
			pass = true;
		}
	}
	delete[] * temp;
}

cMail::cMail() {
	Subject = new char[50];
	Name = new char[50];
	Email = new char[50];
}

void cMail::setData(char *subject, char *name, char *email, char sd, int date) {
	strncpy(Subject, subject, 50);
	strncpy(Name, name, 50);
	strncpy(Email, email, 50);
	send = sd;
	Date = date;
}

void Em_Han::openAndReadFile(char *file) {
	int i;
	rdb.open(file);
	char* tempRoll[50];
	for (i = 0; i < 50; i++) {
		tempRoll[i] = new char[100];
		subject[i] = new char[25];
		name[i] = new char[25];
		email[i] = new char[25];
		for (int m = 0; m < 25; m++) {
			subject[i][m] = NULL;
			name[i][m] = NULL;
			email[i][m] = NULL;
		}
	}

	i = 0;
	while (rdb.getline(tempRoll[i], 75) && i<50) {
		int pos = 0;
		while (tempRoll[i][pos] != ':' && pos < 25) {
			subject[i][pos] = tempRoll[i][pos];
			pos++;
		}
		pos++;
		int sp = pos;
		while (tempRoll[i][pos] != ':' && pos < 50) {
			name[i][pos - sp] = tempRoll[i][pos];
			pos++;
		}
		pos++;
		sp = pos;
		while (tempRoll[i][pos] != ':' && pos < 75) {
			email[i][pos - sp] = tempRoll[i][pos];
			pos++;
		}
		pos++;
		sp = pos;
		date[i] = 0;
		while (tempRoll[i][pos] != NULL && pos - sp < 8) {
			char dateStr[8];
			dateStr[pos - sp] = tempRoll[i][pos];
			for (int m = 0; m < 10; m++) {
				if (dateStr[pos - sp] == char(48 + m)) {
					date[i] += (int)m * pow(10, 7 - pos + sp);
				}
			}
			pos++;
		}
		send[i] = tempRoll[i][pos + 1];
		i++;
	}
	rolls = i;
	rdb.close();
	delete[] * tempRoll;
}

void Em_Han::sortAndSaveMailBySubject(cMail *list, int no) {
	int mn = 0, mx = 0, *d = new int[no];
	for (int c = 0; c < no; c++)
		if (int(list[c].getSubject()[0]) >= 97 && int(list[c].getSubject()[0]) <= 122)
			list[c].getSubject()[0] = char(int(list[c].getSubject()[0]) - 32);
	for (int c = 0; c < no; c++) {
		d[c] = 0;
		for (int i = 0; i < no; i++) {
			if (strncmp(list[c].getSubject(), list[i].getSubject(), 1) < 0) {
				d[c]--;
			}
		}
		if (d[c] > mx)
			mx = d[c];
		else if (d[c] < mn)
			mn = d[c];
	}
	ofstream file;
	file.open("db.txt");
	cout << "\nList of Mail in Ascending Order of Subject:\n";
	int cnt = 1;
	for (int i = mn; i <= mx; i++) {
		for (int c = 0; c < no; c++) {
			if (d[c] == i) {
				cout << "\nMail(" << cnt << ") Subject: " << list[c].getSubject() << "\nName: " << list[c].getName() <<
					"\tEmail: " << list[c].getEmail() << "\tDate: " << list[c].getDate() << "\tStatus: ";
				file << list[c].getSubject() << ':' << list[c].getName() << ':' << list[c].getEmail() << ':' << list[c].getDate() << ':';
				if (list[c].getSend() == '0') {
					cout << "Send\n";
					file << "0\n";
				}
				else {
					cout << "Recieve\n";
					file << "1\n";
				}
				cnt++;
			}
		}
	}
	delete[] d;
}

bool Em_Han::checkEmail(char* data) {
	int ch = 0, ch1 = 0;
	for (int i = 0; i < strlen(data); i++) {
		if (data[i + 1] == '.' && data[i + 2] != NULL && ch == 1)
			ch1 = 1;
		if (data[i] == '@')
			ch = 1;
	}
	if (ch*ch1 == 1)
		return true;
	else
		return false;
}

cMail* Em_Han::buildToDb() {
	cMail *dbMail = new cMail[rolls];
	for (int i = 0; i < rolls; i++)
		dbMail[i].setData(subject[i], name[i], email[i], send[i], date[i]);
	return dbMail;
}

void Em_Han::writeToDb(char *data) {
	ofstream file;
	file.open("db.txt", ios::app);
	file << data;
	file.close();
}

void Em_Han::writeToDb() {
	ofstream file;
	file.open("db.txt", ios::app);
	file << endl;
	file.close();
}
