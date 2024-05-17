#include "Header.h"
#include <ctime>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
using namespace std;





void Patient::menu() {
	int i = 0;
	do {
		system("CLS");
		cout << "****Patient****\n";
		cout << "0->Back\n1->Register\n2->Login:";
		cin >> i;
		if (i == 1)
			this->Register();
		else if (i == 2) {
			this->login();
			
		}

	} while (i != 0);
}
void Patient::Register() {

	string c;
	char p[20];
	system("CLS");
	cout << "***Patient Register***\n";
	cout << "Enter cnic:";
	cin >> c;

	while (c.length() != 13) {
		system("CLS");
		cout << "***Patient Register***\n";
		cout << "\n\n*!*!*!INVALID CNIC!*!*!*\n\n";
		cout << "Enter Again:";
		cin >> c;
	}

	bool ch = false;
	Patient obj;
	ifstream in("Patient.dat", ios::binary);
	while (in.read((char*)&obj, sizeof(obj))) {
		if (c == obj.getCnic()) {
			ch = true;
			break;
		}
	}
	in.close();

	if (ch) {
		system("CLS");
		cout << "***Patient Register***\n";
		cout << "\n\n*!*!*!CNIC ALREADY USED TO CREATE ACCOUNT!*!*!*\n";
		cout << "0->continue:";
		cin >> ch;
		return ;
	}
	system("CLS");
	cout << "***Patient Register***\n";
	cout << "Enter CNIC: " << c << endl;
	cout << "Enter Password(Atleast 8 Digits)\n";
	cout << "Must include UpperCase,LowerCase,Digit,SpecialKey:";
	cin >> p;
	int i = 0;
	bool f1=false, f2 = false, f3 = false, f4 = false;
	for (; p[i] != '\0'; i++) {
		int c = int(p[i]);
		if (c >= 65 && c <= 90)
			f1 = true;
		else if (c >= 91 && c <= 122)
			f2 = true;
		else if (c >= 48 && c <= 57)
			f3 = true;
		else if ( (c >= 33 && c <= 47) || (c >= 58 && c <= 64))
			f4 = true;
	}
	int k = 0;
	while ( (i < 8) || !f1 || !f2 || !f3 || !f4)   {
		system("CLS");
		cout << "\n\n\n*!*!*!INVALID Password!*!*!*\n";
		
		cout << "***Patient Register***\n";
		cout << "Enter CNIC: " << c << endl;
		cout << "Enter Again:";
		cin >> p;
		i = 0;
		f1 = false, f2 = false, f3 = false, f4 = false;
		for (; p[i] != '\0'; i++) {
			int c = int(p[i]);
			if (c >= 65 && c <= 90)
				f1 = true;
			else if (c >= 91 && c <= 122)
				f2 = true;
			else if (c >= 48 && c <= 57)
				f3 = true;
			else if ((c >= 33 && c <= 47) || (c >= 58 && c <= 64))
				f4 = true;
		}
	}

	string x;
	string s(p);
	system("CLS");
	cout << "***Patient Register***\n";
	cout << "Enter CNIC: " << c << endl;
	cout << "Re-Enter Password to confirm:";
	cin >> x;
	
	while (x.compare(s) != 0) {
		system("CLS");
		cout << "***Patient Register***\n";
		cout << "\n\n!!*****Wrong Password*****!!\n\n";
		cout << "Enter CNIC: " << c << endl;
		cout << "Re-Enter Password to confirm:";
		cin >> x;
	}
	string n;
	system("CLS");
	cout << "***Patient Register***\n";
	cout << "Enter CNIC: " << c << endl;
	cout << "Enter Password: " << s << endl;
	cout << "Enter Name: ";
	getline(cin,n);
	getline(cin, n);
	
	Wallet acc(c, 3500);
	ofstream out("PWallet.dat", ios::binary | ios::app);
	out.write((char*)&acc, sizeof(acc));
	out.close();
	Patient temp(c, s, n);
	write("Patient.dat", temp);
	system("CLS");
	cout << "***Patient Register***\n";
	cout << "\n\n****Operation Succesful Account created****\n";
	cout << "*****Kindly Wait For Admins to Approve*****\n";
	cout << "0->Continue:";
	cin >> i;
	return;
}
void Patient::login() {
	//Cread("Patient.dat");
	string c, p;
	system("CLS");
	cout << "***Patient Login***\n";
	cout << "Enter CNIC: ";
	cin >> c;
	bool ch = true;
	Patient obj;
	ifstream in("Patient.dat", ios::binary);
	while (in.read((char*)&obj, sizeof(obj))) {
		if (c == obj.getCnic()) {
			ch = false;
			break;
		}
	}

	in.close();
	while (ch) {
		system("CLS");
		cout << "***Patient Login***\n";
		cout << "\n\nCNIC NOT REGISTERED\n\n";
		cout << "0->Back\n";
		cout << "Enter CNIC to Login:";
		cin >> c;
		if (c == "0")
			return;
		ch = true;
		ifstream in("Patient.dat", ios::binary);
		while (in.read((char*)&obj, sizeof(obj))) {
			if (c == obj.getCnic()) {
				ch = false;
				break;
			}
		}in.close();
	}
	system("CLS");
	cout << "***Patient Login***\n";
	cout << "CNIC: " << c << endl;
	cout << "Enter Password:";
	cin >> p;
	string s(obj.getPassword());
	while (p != s) {
		system("CLS");
		cout << "***Patient Login***\n";
		cout << "\n\n*****WRONG PASSWORD*****\n";
		cout << "0->Back\n\n";
		cout << "CNIC: " << c << endl;
		cout << "Re-Enter Password:";
		cin >> c;
		if (c == "0")
			return;
	}
	this->set(obj);
	cout << "Logged In successfully\n.";
	this->submenu();
}
void Patient::submenu() {
	int i=0;

	do {
		system("CLS");
		cout << "*****Welcome " << this->getName() << "*****" << endl;
		cout << "1->Find Doctor By city" << endl;
		cout << "2->Find Doctor By Specialization" << endl;
		cout << "3->View/Edit Information" << endl;
		cout << "4->View/Edit Appointments" << endl;
		cout << "0->Logout\nInput:";

		cin >> i;

		switch (i) {
		case 1:this->findDoc(); break;
		case 2:this->findDoc1(); break;
		case 3:this->display(); break;
		case 4:this->viewApp(); break;
		case 0:this->Update(); return;
		}

	} while (i != 0);

}
void Patient::findDoc() {
	int i = 0;;
	do{
		system("CLS");
		cout << "*****Select City*****\n";
		cout << "1->Islamabad" << endl;
		cout << "2->Rawalpindi" << endl;
		cout << "3->Lahore" << endl;
		cout << "4->Karachi";
		cout << "0->Back\nInput:";
		cin >> i;
		string ch;
		switch (i) {
		case 0:return;
		case 1:ch = "Islamabad"; break;
		case 2:ch = "Rawalpindi"; break;
		case 3:ch = "Lahore"; break;
		case 4:ch = "Karachi"; break;
		default: cout << "\nNO Doctor Registered in your city\n"; return;
		}

		Doctor x[20];
		Doctor obj;
		int xval = 0;

		ifstream in("Doctor.dat", ios::binary);
		while (in.read((char*)&obj, sizeof(obj))) {
			string s(obj.getCity());
			if (ch == s) {
				x[xval].set(obj);
				xval++;
			}
		}
		if (xval == 0) {
			system("CLS");
			cout << "\nNO Doctor Registered in your city\n0->Back"; cin >> i; continue; }

		system("CLS");
		cout << "*****Doctors in " << ch << "*****" << endl;
		cout << "No    ";
		cout << setw(20) << "Doctor Name" << "  ";
		cout << setw(20) << "Specialization" << "  ";
		cout << setw(20) << "Years of Practice";
		cout << setw(6) << "  Rating\n";

		for (int i = 0; i < xval; i++) {

			cout << setw(4) << i + 1 << "->";
			cout << setw(20) << x[i].getName() << "  ";
			cout << setw(20) << x[i].getSpecialization() << "  ";
			cout << setw(20) <<left <<x[i].getYear();
			int q = x[i].getRating();
			for (int i = 0; i < q; i++) {
				cout << "*";
			}
			cout << endl;
		}

		int j = 0;
		cout << "   O->Back\nInput:";
		cin >> j;

		if (j == 0)
			return;
		else;
			x[j - 1].displayP(*this);
	}while (i != 0);
	
	return;
	

}
void Patient::findDoc1() {


	int i = 0;;

	do {
		system("CLS");
		cout << "*****Select Specialization*****\n";
		cout << "1->Gynaecologist" << endl;
		cout << "2->Dermotoligist" << endl;
		cout << "3->Oncologist" << endl;
		cout << "4->Orthopedic" << endl;
		cout << "0->Back\n";
		cout << "Input:";
		cin >> i;
		string ch;
		switch (i) {
		case 0:return;
		case 1:ch = "Gynaecologist"; break;
		case 2:ch = "Dermotologist"; break;
		case 3:ch = "Oncologist"; break;
		case 4:ch = "Orthopedic"; break;
		default: cout << "\nNO Doctor Registered in this Category\n"; return;
		}

		Doctor x[20];
		Doctor obj;
		int xval = 0;

		ifstream in("Doctor.dat", ios::binary);
		while (in.read((char*)&obj, sizeof(obj))) {
			string s(obj.getSpecialization());
			if (ch == s) {
				x[xval].set(obj);
				xval++;
			}
		}

		if (xval == 0) {
			system("CLS");
			cout << "*************************************\n";
			cout << "\nNo Doctor Registered in this Category\n";
			cout << "*************************************\n0->Back:";
			cin >> xval;
			if (i == 0)
				return;
			continue;
		}

		system("CLS");
		cout << "*****Doctors in " << ch << "*****" << endl;
		cout << "No    ";
		cout << setw(20) << "Doctor Name" << "  ";
		cout << setw(20) << "City" << "  ";
		cout << setw(20) << "Years of Practice";
		cout << setw(6) << "Rating\n";

		for (int i = 0; i < xval; i++) {

			cout << setw(4) << i + 1 << "->";
			cout << setw(20) << x[i].getName() << "  ";
			cout << setw(20) << x[i].getCity() << "  ";
			cout << setw(20) << x[i].getYear();
			cout << setw(6) << x[i].getRating() << endl;
		}

		int j = 0;
		cout << "   O->Back\nInput:";
		cin >> j;

		if (j == 0)
			return;
		else;
			x[j - 1].displayP(*this);

		
	} while (i != 0);
	return;
}
void Patient::Update() {
	
	string d(this->getCnic());
	Patient obj;
	
	fstream f("Patient.dat", ios::in | ios::out | ios::binary);
	while (f.read((char*)&obj, sizeof(obj))) {
		string p(obj.getCnic());
		if (p == d) {
			int a = f.tellg();
			int s = sizeof(obj);
			f.seekp(a - s, ios::beg);
			obj.set(*this);
			f.write((char*)&obj, sizeof(obj));
			break;
		}
	}
	f.close();

}
void Patient::dp1() {
	int x;
	cout << name << " " << status << endl;
	cin >> x;
}
void Patient::display() {
	int i;
	string s, p;
	do {
		Wallet obj;
		obj.read(this->getCnic());
		system("CLS");
		cout << "\n*****Select Number to edit Information*****\n";
		cout << "\n1->User Name: " << this->getName();
		cout << "\n2->CNIC:" << this->getCnic();
		cout << "\n3->Edit Password\n";
		cout << "\n4->Deposit Amount: " << obj.getAmount();
		cout << "0->Back\nInput:";
		cin >> i;

		if (i == 0 || i > 4) {
			this->Update();
			return;
		}

		if (i == 1) {
			cout << "Enter new name:";
			getline(cin, s);
			getline(cin, s);
			setName(s);
		}

		if (i == 2) {
			cout << "Enter new CNIC:";
			getline(cin, s);
			getline(cin, s);
			setCnic(s);
		}

		if (i == 3) {
			cout << "Enter new Password:";
			cin >> s;
			cout << "Re-enter new password:";
			cin >> p;
			if (p == s)
				setPassword(s);
			else
				cout << "Passwords Dont Match\n";
		}
		if (i == 4) {
			int l;
			cout << "Amount to be deposited: ";
			cin >> l;
			obj.Add(l);
			obj.Update();
		}
		
	} while (i != 0);
	this->Update();
}
void Patient::viewApp() {
	int i = 0;
	do {
		string dc(this->getCnic());
		Appointment app[10];
		Date day[10];
		Time st[10], et[10];
		int a = 0;
		ifstream in("Appointment.dat", ios::binary);
		while (in.read((char*)&app[a], sizeof(app[a]))) {
			in.read((char*)&day[a], sizeof(day[a]));
			in.read((char*)&st[a], sizeof(st[a]));
			in.read((char*)&et[a], sizeof(et[a]));
			if (dc == app[a].getPatient()) {
				a++;
			}
		}in.close();

		Doctor d[10];
		int dVal = 0;
		for (int l = 0; l < a; l++) {
			string cd(app[l].getDoctor());
			bool flag = cd.compare(cd.length() - 9, 9, "@gmail.com");
			
			ifstream in("Doctor.dat", ios::binary);
			while (in.read((char*)&d[dVal], sizeof(d[dVal]))) {
				if (!flag) {
					string t(d[dVal].getCnic());
					if (t == cd) { dVal++; }
					else continue;
				}
			
				if (flag) {
					string t(d[dVal].getEmail());
					if (t == cd) { dVal++; }
					else continue;
				}
			}in.close();
		
		}

		system("CLS");
		cout << "*****Scheduled Appointments*****\n";
		cout << "Sr.No    " << setw(20) << left << "Doctor Name" << setw(10) << "Date" << "Start Time\n";
		for (int l = 0; l < a; l++) {
			cout << " " << l + 1 << "->    " << setw(20) << left << d[l].getName() << setw(10) <<left << string(day[l]);
			cout << string(st[l]);
			cout << "\n";
		}
		cout << "0->Go Back\nEnter Sr.No to Select Aapointment:";
		cin >> i;
		
		if (i == 0)
			return;
		else if (i > a)
			continue;
		else {
			app[i - 1].Display(*this, d[i - 1], day[i - 1], st[i - 1], et[i - 1]);
		}

		} while (i != 0);
}




void Doctor::menu() {
	int i = 0;
	do {
		system("CLS");
		cout << "*****Doctor****\n";
		cout << "0->Back\n1->Register\n2->Login\nInput:";
		cin >> i;
		if (i == 1)
			this->Register();
		else if (i == 2) {
			this->login();
		}
		else
			continue;
	} while (i != 0);
}
void Doctor::Register() {
	int i = 0;
	string c = "";
	string e = "";
	int o = 0;
	do {
		system("CLS");
		cout << "****Doctor Registration****\n";
		cout << "1->Register Using Email\n2->Register Using CNIC\nInput:";
		cin >> o;

		if (o == 1) {
			cout << "Enter Email:";
			cin >> e;
			bool flag;
			if (e.length() < 10)
				flag = false;
			else
				flag = e.compare(e.length() - 9, 9, "@gmail.com");

			while (!flag) {
				system("CLS");
				cout << "****Doctor Registration****\n";
				cout << "\n*!*!*!INVALID EMAIL!*!*!*\n\n";
				cout << "Enter Again:";
				cin >> e;
				if (e.length() < 10)
					flag = false;
				else
					flag = e.compare(e.length() - 9, 9, "@gmail.com");
			}

			int ch = 1;
			Doctor obj;
			ifstream in("Doctor.dat", ios::binary);
			while (in.read((char*)&obj, sizeof(obj))) {
				if (e == obj.getEmail()) {
					ch = 0;
					break;
				}
			}
			in.close();

			if (ch == 0) {
				system("CLS");
				cout << "****Doctor Registration****\n";
				cout << "\n*!*!*!EMAIL ALREADY USED TO CREATE ACCOUNT!*!*!*\n0->Continue:";
				cin >> o;
				return;
			}

		}

		else if (o == 2) {
			system("CLS");
			cout << "****Doctor Registration****\n";
			cout << "Enter cnic:";
			cin >> c;

			while (c.length() != 13) {
				system("CLS");
				cout << "****Doctor Registration****\n";
				cout << "\n\n*!*!*!INVALID CNIC!*!*!*\n\n\n";
				cout << "Enter Again:";
				cin >> c;
			}

			int ch = 1;
			Doctor obj;
			ifstream in("Doctor.dat", ios::binary);
			while (in.read((char*)&obj, sizeof(obj))) {
				if (c == obj.getCnic()) {
					ch = 0;
					break;
				}
			}
			in.close();

			if (ch == 0) {
				system("CLS");
				cout << "****Doctor Registration****\n";
				cout << "\n*!*!*!CNIC ALREADY USED TO CREATE ACCOUNT!*!*!*\n\0->Continue:";
				cin >> o;
				return;
			}

		}

		else
			continue;
		char p[20];
		cout << "Enter Password(Atleast 8 Digits)\n";
		cout << "Must include UpperCase,LowerCase,Digit,SpecialKey:";
		cin >> p;
		int i = 0;
		bool f1 = false, f2 = false, f3 = false, f4 = false;
		for (; p[i] != '\0'; i++) {
			int c = int(p[i]);
			if (c >= 65 && c <= 90)
				f1 = true;
			else if (c >= 91 && c <= 122)
				f2 = true;
			else if (c >= 48 && c <= 57)
				f3 = true;
			else if ((c >= 33 && c <= 47) || (c >= 58 && c <= 64))
				f4 = true;
		}
		int k = 0;
		while ((i < 8) || !f1 || !f2 || !f3 || !f4) {
			cout << "\n*!*!*!INVALID Password!*!*!*\n";
			cout << "Enter Again:";
			cin >> p;
			i = 0;
			f1 = false, f2 = false, f3 = false, f4 = false;
			for (; p[i] != '\0'; i++) {
				int c = int(p[i]);
				if (c >= 65 && c <= 90)
					f1 = true;
				else if (c >= 91 && c <= 122)
					f2 = true;
				else if (c >= 48 && c <= 57)
					f3 = true;
				else if ((c >= 33 && c <= 47) || (c >= 58 && c <= 64))
					f4 = true;
			}
		}
		string x;
		string s(p);
		cout << "Re-Enter Password to confirm:";
		cin >> x;

		while (x.compare(s) != 0) {
			cout << "!!*****Wrong Password*****!!";
			cout << "Re-Enter Password to confirm:";
			cin >> x;
		}
		char nv[20];
		char hv[20];

		int fx = 0, y = 0;

		cout << "Enter User Name: ";
		cin.getline(nv, 20);
		cin.getline(nv, 20);
		cout << "Enter Hospital Name: ";
		cin.getline(hv, 20);
		cout << "Enter Practicing Years: ";
		cin >> y;
		cout << "Enter Fee:";
		cin >> fx;

		string ci, sp;
		cout << "*****Select City*****\n";
		cout << "1->Islamabad" << endl;
		cout << "2->Rawalpindi" << endl;
		cout << "3->Lahore" << endl;
		cout << "4->Karachi";
		cout << "\nInput:";
		cin >> i;
		switch (i) {
		case 0:return;
		case 1:ci = "Islamabad"; break;
		case 2:ci = "Rawalpindi"; break;
		case 3:ci = "Lahore"; break;
		case 4:ci = "Karachi"; break;
		}

		cout << "*****Select Specialization*****\n";
		cout << "1->Gynaecologist" << endl;
		cout << "2->Dermotoligist" << endl;
		cout << "3->Oncologist" << endl;
		cout << "4->Orthopedic" << endl;
		cout << "Input:";
		cin >> i;
		switch (i) {
		case 1:sp = "Gynaecologist"; break;
		case 2:sp = "Dermotologist"; break;
		case 3:sp = "Oncologist"; break;
		case 4:sp = "Orthopedic"; break;
		}

		string n(nv), h(hv), ev(e);
		Doctor temp(c, s, n, ev, ci, h, sp, y, fx);
		temp.setTime();
		this->set(temp);

		write("Doctor.dat", temp);
		cout << "****Operation Succesful Account created****\n";
		cout << "*****Kindly Wait For Admins to Approve*****\n";
		cout << "0->Conitnue:";
		cin >> o;
	} while (o != 0);
}
void Doctor::login() {
	string c, p,e;
	int x;
	int i = 0;
	do {
		system("CLS");
		cout << "*****Doctor Login*****\n";
		cout << "1->Login using Email\n2->login using CNIC\nInput:";
		cin >> x;

		Doctor obj;

		if (x == 1) {
			system("CLS");
			cout << "*****Doctor Login*****\n";
			cout << "Enter Email: ";
			cin >> e;
			bool ch = true;
			ifstream in("Doctor.dat", ios::binary);
			while (in.read((char*)&obj, sizeof(obj))) {
				if (e == obj.getEmail()) {
					ch = false;
					break;
				}
			}
			in.close();
			while (ch) {
				system("CLS");
				cout << "*****Doctor Login*****\n";
				cout << "\n\nEmail NOT REGISTERED\n\n";
				cout << " 0->back\n";
				cout << "Enter  a Registered Email:";
				cin >> e;
				ch = true;
				if (e == "0")
					return;
				ifstream in("Doctor.dat", ios::binary);
				while (in.read((char*)&obj, sizeof(obj))) {
					if (e == obj.getEmail()) {
						ch = false;
						break;
					}
				}in.close();
			}
		}

		if (x == 2) {
			system("CLS");
			cout << "*****Doctor Login*****\n";
			cout << "Enter CNIC: ";
			cin >> c;
			bool ch = true;
			ifstream in("Doctor.dat", ios::binary);
			while (in.read((char*)&obj, sizeof(obj))) {
				if (c == obj.getCnic()) {
					ch = false;
				}
			}

			in.close();
			while (ch) {
				system("CLS");
				cout << "*****Doctor Login*****\n";
				cout << "\nCNIC NOT REGISTERED\n\n";
				cout << " 0->Back\n";
				cout << "Enter  a Registered CNIC:";
				cin >> c;
				if (c == "0")
					return;
				ch = true;
				ifstream in("Doctor.dat", ios::binary);
				while (in.read((char*)&obj, sizeof(obj))) {
					if (c == obj.getCnic()) {
						ch = false;
						break;
					}
				}in.close();
			}
		}
		system("CLS");
		cout << "*****Doctor Login*****\n";
		cout << "Enter Password:";
		cin >> p;
		string s(obj.getPassword());
		while (p != s) {
			system("CLS");
			cout << "*****Doctor Login*****\n";
			cout << "\nIncorrect Password\n";
			cout << "Enter 0 to Go back\n";
			cout << "Enter Password:";
			cin >> p;
			if (p == "0")
				return;
		}

		this->set(obj);
		cout << "Logged In successfully\n.";
		this->submenu();
	} while (i != 0);
}
void Doctor::submenu() {
	int i = 0;
	do {
		system("CLS");
		cout << "*****Welcome " << this->getName() << "*****" << endl;
		cout << "1->View/Edit Information" << endl;
		cout << "2->View/Edit Appointments" << endl;
		cout << "3->Logout\nInput:";
		cin >> i;

		switch (i) {
		case 1:this->display(); break;
		case 2:this->viewApp(); break;
		case 3:return;
		}

	} while (i != 0);

}
void Doctor::display() {
	int i;
	string s, p;
	do {
		system("CLS");
		cout << "\n*****Select Number to edit Information*****\n";
		cout << "\n 1->User Name: " << this->getName();
		if (cnic == "")
			cout << "\n 2->CNIC Not Enetered";
		else
			cout << "\n2->CNIC:" << this->getCnic();

		if (getEmail() == "")
			cout << "\n 3->Email Not Enetered";
		else
			cout << "\n 3->Email:" << this->getEmail();

		cout << "\n 4->Edit Password\n";
		cout << " 5->Hospital: " << this->hospital << endl;
		cout << " 6->Specialization: " << this->getSpecialization() << endl;
		cout << " 7->City: " << this->getCity() << endl;
		cout << " 8->Year: " << this->getYear() << endl;
		cout << " 9->Fee In-Person: " << this->getFee();
		cout << "10->Change Timings\n";
		cout << "\n-->Rating:" << this->getRating() << endl;
		cout << "11->***Delete Account***\n";
		cout << " 0->Back\nInput:";
		cin >> i;

		if (i == 0) {
			this->Update();
			return;
		}
		
		if (i == 1) {
			cout << "Enter new name:";
			getline(cin, s);
			getline(cin, s);
			setName(s);
			this->Update();
		}
		
		if (i == 2) {
			cout << "Enter new CNIC:";
			getline(cin, s);
			getline(cin, s);
			setCnic(s);
			this->Update();
		}
		
		if (i == 3) {
			cout << "Enter new Email:";
			getline(cin, s);
			getline(cin, s);
			setEmail(s);
			this->Update();
		}
		
		if (i == 4) {
			cout << "Enter new Password:";
			cin >> s;
			cout << "Re-enter new password:";
			cin >> p;
			if (p == s) {
				setPassword(s);
				this->Update();
			}
			else
				cout << "Passwords Dont Match\n";
		}
		
		if (i == 5) {
			cout << "Enter new Hospital Name:";
			getline(cin, s);
			getline(cin, s);
			setHospital(s);
			this->Update();
		}
		
		if (i == 6) {
			int a;
			cout << "*****Select Specialization*****\n";
			cout << "1->Gynaecologist" << endl;
			cout << "2->Dermotoligist" << endl;
			cout << "3->Oncologist" << endl;
			cout << "4->Orthopedic" << endl;
			cout << "Input:";
			cin >> a;
			switch (a) {
			case 1:s = "Gynaecologist"; break;
			case 2:s = "Dermotologist"; break;
			case 3:s = "Oncologist"; break;
			case 4:s = "Orthopedic"; break;
			}
			setSpecialization(s);
			this->Update();
		}
	
		if (i == 7) {
			int b;
			cout << "*****Select City*****\n";
			cout << "1->Islamabad" << endl;
			cout << "2->Rawalpindi" << endl;
			cout << "3->Lahore" << endl;
			cout << "4->Karachi";
			cout << "\nInput:";
			cin >> b;
			switch (b) {
			case 0:return;
			case 1:s = "Islamabad"; break;
			case 2:s = "Rawalpindi"; break;
			case 3:s = "Lahore"; break;
			case 4:s = "Karachi"; break;
			}
			setCity(s);
			this->Update();
		}

		if (i == 8) {
			cout << "Enter Practicing Years:";
			cin >> i;
			setYear(i);
			i = 8;
		}	this->Update();


		if(i==9) {
			cout << "Enter New Fee:";
			cin >> i;
			setFee(i);
			i = 9;
			this->Update();
		}
		if (i == 10) {
			this->setTime();
			this->Update();
			return;
		}

		if (i == 11) {
			this->Delete();
			return;
		}

	} while (i != 0);
	this->Update();
}
void Doctor::Update() {
	
	string c(this->getCnic());
	string e(this->getEmail());
	string x("");
	Doctor obj;
	obj.set(*this);
	
	if (e == x) {
		fstream f("Doctor.dat", ios::in | ios::out | ios::binary);
		while (f.read((char*)&obj, sizeof(obj))) {
			string p(obj.getCnic());
			if (p == c) {

		
		f.close();
				int a = f.tellg();
				int size = sizeof(obj);
				f.seekp(a-size, ios::beg);
				f.write((char*)&obj, sizeof(obj));
				break;
			}
		}
		f.close();
	}
	else {

		fstream f("Doctor.dat", ios::in | ios::out | ios::binary);
		while (f.read((char*)&obj, sizeof(obj))) {
			string p(obj.getEmail());
			if (p == e) {
				int a = f.tellg();
				int s = sizeof(obj);
				f.seekp(a - s, ios::beg);
				obj.set(*this);
				f.write((char*)&obj, sizeof(obj));
				break;
			}
		}
		f.close();

	}

}
void Doctor::Delete() {
	Doctor obj, t;
	obj.set(*this);
	string x("");
	string a(obj.getCnic());
	string b(obj.getEmail());
	bool flag = a == x;
	ifstream in("Doctor.dat", ios::in | ios::out | ios::binary);
	while (in.read((char*)&t, sizeof(t))) {
		if (flag) {
			string k(t.getEmail());
			if (k == b) {
				continue;
			}
			else {
				ofstream out("temp.dat", ios::binary | ios::app);
				out.write((char*)&obj, sizeof(obj));
				out.close();
			}
		}

		if (!flag) {
			string k(t.getCnic());
			if (k == a) {
				continue;
			}
			else {
				ofstream out("temp.dat", ios::binary | ios::app);
				out.write((char*)&obj, sizeof(obj));
				out.close();
			}
		}

	}in.close();
	remove("Doctor.dat");
	int i=rename("temp.dat", "Doctor.dat");
	return;
}
void Doctor::setTime() {
	int i = 0;
	do {
		system("CLS");
		cout << "*****SET TIMINGS*****\n";
		cout << "01->0900-0930";
		if (slot[0]) { cout << "OPEN\n"; }
		if (!slot[0]) { cout << "CLOSED\n"; }
		cout << "02->0930-1000";
		if (slot[1]) { cout << "OPEN\n"; }
		if (!slot[1]) { cout << "CLOSED\n"; }
		cout << "03->1000-1030";
		if (slot[2]) { cout << "OPEN\n"; }
		if (!slot[2]) { cout << "CLOSED\n"; }
		cout << "04->1030-1100";
		if (slot[3]) { cout << "OPEN\n"; }
		if (!slot[3]) { cout << "CLOSED\n"; }
		cout << "05->1100-1130";
		if (slot[4]) { cout << "OPEN\n"; }
		if (!slot[4]) { cout << "CLOSED\n"; }
		cout << "06->1130-1200";
		if (slot[5]) { cout << "OPEN\n"; }
		if (!slot[5]) { cout << "CLOSED\n"; }
		cout << "Enter Sr.No to Toggle Status,\n0->Back\nInput:";
		cin >> i;
		if (i == 0 || i>6)
			continue;
		else {
			slot[i - 1] = !slot[i - 1];
		}
	} while (i != 0);
}
void Doctor::displayP(Patient p) {
	int i = 0;
	do {
		string x(this->getCnic());
		if (x == "")
			x = this->getEmail();
		system("CLS");
		int a = 0;
		Feedback f[15];
		Date d[15];
		ifstream in("Feedback", ios::binary);
			while (in.read((char*)&f[a],sizeof(f[a]))) {
				in.read((char*)&d[a], sizeof(d[a]));
				string d(f[a].getDoc());
				if (d == x) {
					a++;
				}
				else
					continue;
			}

		cout << "Name: " << "Dr." << getName() << endl;
		cout << "Hospital: " << getHospital() << endl;
		cout << "Specialization: " << getSpecialization() << endl;
		cout << "Year: " << getYear() << endl;
		cout << "Rating: " << getRating() << endl;
		cout << "City: " << getCity() << endl;
		cout << "Fee In-Person: " << getFee();
		cout << "\nFee Online: " << getFee() - ((.3) * getFee());
		cout << "\n\n******Reviews*****\n";
		if (a == 0)
			cout << "\n*****NO REVIEWS*****\n";
		else {
			for (int k = 0; k < a; k++) {
				cout << "\n"<< left << setw(60) << f[k].getPat() << string(d[k]) << endl;
				cout << f[k].getF() << endl;
			}
		}
		
		cout << "\n\n1->Book Appointment\n0->Back\nInput:";
		cin >> i;
		switch (i) {
		case 0:return;
		case 1:this->book(p); break;
		}
	} while (i != 0);
}
void Doctor::book(Patient p) {
	int i = 0;
	do {
		Appointment app[6];
		struct tm newtime;
		time_t now = time(0);
		localtime_s(&newtime, &now);
		int y = 1900 + newtime.tm_year;
		int d, m = 1 + newtime.tm_mon;
		int td = newtime.tm_mday;
		Date today(newtime.tm_mday,m),dat[6];
		Time objs[6], obje[6];
		int a = 0;
		string dc(this->getCnic());
		if (dc == "")
			dc = this->getEmail();

		system("CLS");
		cout << "***Appointment Booking***\n";
		cout << "Enter Date to Check Doctor Availibility\n";
		cin >> d;
		cout << "Enter Month:";
		cin >> m;
		Date checkd(d, m);
		
		ifstream in("Appointment.dat", ios::binary);
		while (in.read((char*)&app[a], sizeof(app[a]))) {
			in.read((char*)&dat[a], sizeof(dat[a]));
			in.read((char*)&objs[a], sizeof(objs[a]));
			in.read((char*)&objs[a], sizeof(obje[a]));
			if (checkd == dat[a] && dc == app[a].getDoctor()) {
				a++;
			}
		}in.close();

		bool f[6]{ 1,1,1,1,1,1 };
		for (int l = 0; l < a; l++) {
			int q = app[i].getSlot();
			f[q-1] = 0;
		}

		system("CLS");
		cout << "***Doctor Schedule for " << string(checkd) << " ***\n";
		cout << "Sr.No   Start  End  Status\n";

		for (int l = 0; l < 6; l++) {
			switch (l) {
			case 0:
				cout << " " << l + 1 << "->   0900   0930  ";
				if (this->slot[l]) { if (f[l]) cout << "Available"; else cout << "Boooked"; }
				else cout << "UnAvailable";
				cout << "\n";
				break;
			case 1:
				cout << " " << l + 1 << "->   0930   1000  ";
				if (this->slot[l]) { if (f[l]) cout << "Available"; else cout << "Boooked"; }
				else cout << "UnAvailable";
				cout << "\n";
				break;
			case 2:
				cout << " " << l + 1 << "->   1000   1030  ";
				if (this->slot[l]) { if (f[l]) cout << "Available"; else cout << "Boooked"; }
				else cout << "UnAvailable";
				cout << "\n";
				break;
			case 3:
				cout << " " << l + 1 << "->   1030   1100  ";
				if (this->slot[l]) { if (f[l]) cout << "Available"; else cout << "Boooked"; }
				else cout << "UnAvailable";
				cout << "\n";
				break;
			case 4:
				cout << " " << l + 1 << "->   1100   1130  ";
				if (this->slot[l]) { if (f[l]) cout << "Available"; else cout << "Boooked"; }
				else cout << "UnAvailable";
				cout << "\n";
				break;
			case 5:
				cout << " " << l + 1 << "->   1130   1200  ";
				if (this->slot[l]) { if (f[l]) cout << "Available"; else cout << "Boooked"; }
				else cout << "UnAvailable";
				cout << "\n";
				break;
			}
		}
		cout << "0->Back\n-->Enter Sr.No to Book Appointment:";
		cin >> i;
		if (i == 0 )
			return;
		
		if ((this->slot[i - 1] && !f[i - 1]) || !this->slot[i - 1] || i>6) {
			do {
				cout << "****Slot Unavailble*****\n0->Back-->Enter Again:";
				cin >> i;
				if (i == 0)
					return;
			} while ((this->slot[i - 1] && !f[i - 1]) || !this->slot[i - 1] || i > 6);
		}
		

		Time st, et;
		switch (i) {
		case 1: st.set(9, 0); et.set(9, 30); break;
		case 2: st.set(9, 30); et.set(10, 0); break;
		case 3: st.set(10, 0); et.set(10, 30); break;
		case 4: st.set(10, 30); et.set(11, 0); break;
		case 5: st.set(11, 0); et.set(11, 30); break;
		case 6: st.set(11, 30); et.set(12, 0); break;
		}

		Appointment apt(p.getCnic(), dc, i);
		ofstream out("Appointment.dat", ios::binary | ios::app);
		out.write((char*)&apt, sizeof(apt));
		out.write((char*)&checkd, sizeof(checkd));
		out.write((char*)&st, sizeof(st));
		out.write((char*)&et, sizeof(et));
		out.close();
		system("CLS");
		cout << "*****Appointment Booked*****\n0->Continue:";
		cin >> i;
		return;

	} while (i != 0);

}
void Doctor::viewApp(){
	int i = 0;
	do {
		string dc(this->getCnic());
		if (dc == "")
			dc = this->getEmail();

		Appointment app[10];
		Date day[10];
		Time st[10], et[10];
		int a = 0;
		
		ifstream in("Appointment.dat", ios::binary);
		while (in.read((char*)&app[a], sizeof(app[a]))) {
			in.read((char*)&day[a], sizeof(day[a]));
			in.read((char*)&st[a], sizeof(st[a]));
			in.read((char*)&et[a], sizeof(et[a]));
			if (dc == app[a].getDoctor()) {
				a++;
			}
		}in.close();

		Patient d[10];
		int dVal = 0;
		for (int l = 0; l < a; l++) {
			string cd(app[l].getPatient());
			
			ifstream in("Patient.dat", ios::binary);
			while (in.read((char*)&d[dVal], sizeof(d[dVal]))) {
					string t(d[dVal].getCnic());
					if (t == cd) { dVal++; }
					else continue;
			}in.close();

		}

		system("CLS");
		cout << "*****Scheduled Appointments*****\n";
		cout << "Sr.No    " << setw(20) << left << "Patient Name" << setw(10) << "Date" << "Start Time\n";
		for (int l = 0; l < a; l++) {
			cout << " " << l + 1 << "->    " << setw(20) << left << d[l].getName() << setw(10) << left << string(day[l]);
			cout << string(st[l]);
			cout << "\n";
		}
		cout << "0->Go Back\nEnter Sr.No to Select Appointment:";
		cin >> i;

		if (i == 0)
			return;
		else if (i > a)
			continue;
		else {

			app[i - 1].Display(d[i - 1], *this, day[i - 1], st[i - 1], et[i - 1],0);
		}

	} while (i != 0);


}





void Admin::menu() {
	string c, p;
	system("CLS");
	cout << "*****Admin Login Window*****\n";
	cout << "Enter CNIC: ";
	cin >> c;
	bool ch = true;
	Admin obj;
	ifstream in("Admin.dat", ios::binary);
	while (in.read((char*)&obj, sizeof(obj))) {
		if (c == obj.getCnic()) {
			ch = false;
			break;
		}
	}

	in.close();
	while (ch) {
		system("CLS");
		cout << "*****Admin Login Window*****\n";
		cout << "CNIC NOT REGISTERED\n";
		cout << "Press 0 to Go back\n";
		cout << "Enter CNIC to Login:";
		cin >> c;
		if (c == "0")
			return;
		ch = true;
		ifstream in("Admin.dat", ios::binary);
		while (in.read((char*)&obj, sizeof(obj))) {
			if (c == obj.getCnic()) {
				ch = false;
				break;
			}
		}in.close();
	}

	system("CLS");
	cout << "*****Admin Login Window*****\n";
	cout << "CNIC:" << c << endl;
	cout << "Enter Password:";
	cin >> p;
	string s(obj.getPassword());
	while (p != s) {
		system("CLS");
		cout << "*****Admin Login Window*****\n";
		cout << "\n\n*****WRONG PASSWORD*****\n\n";
		cout << "CNIC:" << c << endl;
		cout << "Enter 0 to Go back\n";
		cout << "Re-Enter Password:";
		cin >> c;
		if (c == "0")
			return;
	}
	this->set(obj);
	cout << "Logged In successfully\n.";
	this->submenu();
}
void Admin::submenu() {
	int i = 0;

	do {
		system("CLS");
		cout << "*****Welcome " << getName() << "*****\n";
		cout << "1->View Pending Patients" << endl;
		cout << "2->View Pending Doctors" << endl;
		cout << "3->View Patients" << endl;
		cout << "4->View/Edit Doctor" << endl;
		cout << "5->View/Edit Appointments" << endl;
		cout << "0->Logout\nInput:";

		cin >> i;

		switch (i) {
		case 1:this->PPatient(); break;
		case 2:this->PDoctor(); break;
		case 3:this->VPatient(); break;
		case 4:this->VDoctor(); break;
		case 5:this->viewApp(); break;
		case 0:return;
		}
	} while (i != 0);

}
void Admin::PPatient() {
	int i = 0;
	int a = 0;
	Patient obj[20],p;
	ifstream in("Patient.dat", ios::binary);
	while (in.read((char*)&p, sizeof(p))) {
		if (!p.getStatus()) {
			obj[a].set(p);
			a++;
		}
	}in.close();

	do{
		system("CLS");
		cout << "*****Pending Patients*****\n";
		
		if (a == 0) {
			cout << "No Pending Requests\n";
			cout << " 0->Back\nInput:";
			cin >> i;
			return;
		}
		string x("x");
		cout << " 0->Back\n";
		cout << "50->Approve All\n";
		cout << setw(20) << "    Name" << setw(14) << "CNIC" << endl;
			for (int l = 0; l < a; l++) {
				cout << setw(2) << l + 1 << "->";
				cout << left << setw(20) << obj[l].getName();
				cout << obj[l].getCnic();
				cout << "\n";
			}
			cout << "Input:";
			cin >> i;
			if (i == 0)
				return;
			else if (i == 50) {
				for (int l = 0; l < a; l++) {
					obj[l].setStatus(true);
					obj[l].Update();
				}
				return;
			}

			else if (i > a) {
				continue;
			}

			else if (i <= a) {
				obj[i - 1].setStatus(true);
				obj[i - 1].Update();
				//obj[i-1].dp1();
				
				for (int l = i - 1; l < a - 1; l++) {
					obj[l].set(obj[l + 1]);
				}
				a--;
			}
	}while (i != 0);
}
void Admin::PDoctor() {

	int i = 0;
	int a = 0;
	Doctor obj[20], p;
	ifstream in("Doctor.dat", ios::binary);
	while (in.read((char*)&p, sizeof(p))) {
		if (!p.getStatus()) {
			obj[a].set(p);
			a++;
		}
	}in.close();

	do {
		system("CLS");
		cout << "*****Pending Doctors*****\n";

		if (a == 0) {
			cout << "No Pending Requests\n";
			cout << " 0->Back\nInput:";
			cin >> i;
			return;
		}
		string x("");
		cout << " 0->Back\n";
		cout << "50->Approve All\n";
		cout << left << setw(20) << "    Name" << "      CNIC/Email" << endl;
		for (int l = 0; l < a; l++) {
			cout << setw(2) << l + 1 << "->";
			cout << left << setw(20) << obj[l].getName();
			string q(obj[l].getCnic());
			if (q == x)
				cout << obj[l].getEmail();
			else 
				cout << obj[l].getCnic();
			cout << "\n";
		}

		cout << "Input:";
		cin >> i;
		if (i == 0)
			return;
		else if (i == 50) {
			for (int l = 0; l < a; l++) {
				obj[l].setStatus(true);
				obj[l].Update();
			}
			return;
		}

		else if (i > a) {
			continue;
		}

		else if (i <= a) {
			obj[i - 1].setStatus(true);
			obj[i - 1].Update();
			//obj[i-1].dp1();

			for (int l = i - 1; l < a - 1; l++) {
				obj[l].set(obj[l + 1]);
			}
			a--;
		}
	} while (i != 0);

}
void Admin::VPatient() {
	system("CLS");
	cout << "*****Patients Record*****\n";
	
	Patient obj[50];
	int p = 0;
	Patient t;

	ifstream in("Patient.dat", ios::binary);
	while (in.read((char*)&t, sizeof(t))) {
		obj[p].set(t);
		p++;
	}in.close();

	cout << "Sr.No" << setw(18) << left << "  Name" << setw(14) << "    CNIC" << "        Password\n";
	for (int i = 0; i < p; i++) {
		cout << setw(2) << i + 1 << "-> ";
		cout << "  " << setw(20) << obj[i].getName();
		cout << setw(14) << obj[i].getCnic();
		cout << "    " << setw(20) << obj[i].getPassword();
		cout << "\n";
	
	}

	cout << " 0->Back\n:Input:";
	cin >> p;
	return;

}
void Admin::VDoctor() {
	int i = 0;
	do {
		Doctor obj[50];
		int p = 0;
		Doctor t;

		ifstream in("Doctor.dat", ios::binary);
		while (in.read((char*)&t, sizeof(t))) {
			obj[p].set(t);
			p++;
		}in.close();
		
		system("CLS");
		cout << "*****Doctor Record*****\n";
		cout << "Sr.No" << setw(20) << left << "  Name" << setw(20) << "  Email/CNIC" << "      Password\n";
		for (int l = 0; l < p; l++) {
			cout << setw(2) << l + 1 << "-> ";
			cout << "  " << setw(20) << obj[l].getName();
			string q(obj[l].getCnic());
			if (q == "") { cout << setw(20) << obj[l].getEmail(); }
			else { cout << setw(20) << obj[l].getCnic(); }
			cout << "    " << setw(20) << obj[l].getPassword();
			cout << "\n";

		}
		
		cout << " 0->Back\n:Input Sr.No to View/Edit Details:";
		cin >> i;
		if (i==0 || i>p)
			return;
		else {
			obj[i - 1].display();
		}
	} while (i != 0);
}
void Admin::viewApp() {
	int i = 0;
	do {
		
		int a = 0;
		Appointment app[15];
		Doctor doc[15];
		Patient pat[15];
		Date day[15];
		Time st[15], et[15];
		
		ifstream in("Appointment.dat", ios::binary);
		while (in.read((char*)&app[a], sizeof(app[a]))) {
				in.read((char*)&day[a], sizeof(day[a]));
				in.read((char*)&st[a], sizeof(st[a]));
				in.read((char*)&et[a], sizeof(et[a]));
				a++;
		}in.close();
		
		for (int l = 0; l < a; l++) {
			string d(app[i].getDoctor());
			if (d.compare(d.length() - 9, 9, "@gmail.com")==0) {
				ifstream in("Doctor.dat", ios::binary);
				while (in.read((char*)&doc[l], sizeof(doc[l]))) {
					if (d == doc[l].getEmail()) {
						break;
					}

				}in.close();
			}
			else {
				ifstream in("Doctor.dat", ios::binary);
				while (in.read((char*)&doc[l], sizeof(doc[l]))) {
					if (d == doc[l].getCnic()) {
						break;
					}

				}in.close();
			}
		}
		
		for (int l = 0; l < a; l++) {
			string d(app[i].getPatient());

			ifstream in("Patient.dat", ios::binary);
			while (in.read((char*)&pat[l], sizeof(pat[l]))) {
				if (d == pat[l].getCnic()) {
					break;
				}
			}in.close();
		}
		system("CLS");
		cout << "*****Appointments Record*****\n";
		cout << "Sr.No    " << setw(20) << left << "Patient Name" << setw(20) << left << "Doctor Name" << setw(10) << "Date" << "Start Time\n";
		for (int l = 0; l < a; l++) {
			for (int l = 0; l < a; l++) {
				cout << " " << l + 1 << "->    " << setw(20) << left << pat[l].getName() << setw(20) << left << doc[l].getName() << setw(10) << left << string(day[l]);
				cout << string(st[l]);
				cout << "\n";
			}
		}

		cout << "0->Go Back\nEnter Sr.No to Select Appointment:";
		cin >> i;

		if (i == 0)
			return;
		else if (i > a)
			continue;
		
		else {
			app[i - 1].Display(pat[i - 1], doc[i - 1], day[i - 1], st[i - 1], et[i - 1], 0);
		}


		
		
	} while (i != 0);
}




void Appointment::Display(Patient p, Doctor doc, Date day, Time s, Time e,bool f) {
	int i = 0;
	do {
		system("CLS");
		cout << "****Appointment Information*****\n";
		cout << "\n-->Patient Name:" << p.getName();
		cout << "\n-->Doctor Name:" << doc.getName();
		cout << "\n-->Time" << string(s);
		cout << "\n1->Date:" << string(day);
		cout << "\n2->***Cancel***";
		struct tm newtime;
		time_t now = time(0);
		localtime_s(&newtime, &now);
		int  m = newtime.tm_mon;
		int td = newtime.tm_mday;
		Date today(newtime.tm_mday, m);
		if (today == day) {
			cout << "\n3->Take Appointment";
		}
		cout << "\n0->Back:";
		cin >> i;
		Date dld;
		switch (i) {
		case 0:return;
		case 1: 
			int ld,lm;
			cout << "Enter new date:";
			cin >> ld;
			cout << "Enter Next Month:";
			cin >> lm;
			dld.set(ld, lm);
			this->Update(p,doc,day,s,dld);
			continue;
		case 2: this->cancel(p, doc, day, s, e); return;
		case 3: if (f) { this->take(p, doc, day, s, e); this->cancel(p, doc, day, s, e); return; } continue;
		default:continue; break;
		}

	} while (i != 0);
}
void Appointment::cancel(Patient p, Doctor doc, Date day, Time s, Time e) {
	string pc(p.getCnic());
	string dc(doc.getCnic());
	if (dc == "") dc = doc.getEmail();
	string cday(string(day));
	int q = this->getSlot();
	int move = sizeof(s) + sizeof(e);
	Appointment app;
	Date dd;
	Time st, es;
	fstream in("Appointment.dat", ios::out|ios::in|ios::binary);
	while (in.read((char*)&app, sizeof(app))) {
		in.read((char*)&app, sizeof(app));
		in.read((char*)&dd, sizeof(dd));
		in.read((char*)&st, sizeof(st));
		in.read((char*)&es, sizeof(es));
		if (pc == app.getPatient() && dc == app.getDoctor() && day == dd && app.getSlot() == q && st == s) {
			continue;
		}
		else {
			ofstream out("temp.dat", ios::binary|ios::app);
			out.write((char*)&app, sizeof(app));
			out.write((char*)&app, sizeof(app));
			out.write((char*)&dd, sizeof(dd));
			out.write((char*)&st, sizeof(st));
			out.write((char*)&es, sizeof(es));
			out.close();
		}
	}in.close();

	remove("Appointment.dat");
	int i = rename("temp.dat", "Appointment.dat");
	return;
}
void Appointment::take(Patient p, Doctor doc, Date day, Time s, Time e) {
	int i = 0;
	do {
		system("CLS");
		char ff[100];
		float r;
		cout << "****Thank You For Using Oladoc***\n";
		cout << "Please Give Review of the Doctor: ";
		cin.getline(ff, 100);
		cin.getline(ff, 100);
		cout << "How was your Experience with the doctor(Out of 5):";
		cin >> r;
		string ffx(ff);
		system("CLS");
		cout << "Thankyou For your Feedback\nFee Paid From Your Account\n-->Continue:";
		cin >> i;
		int k = doc.getR();
		k++;
		float re = doc.getRating();
		re += r;
		doc.setRating(re);
		doc.setR(k);
		doc.Update();
		string x(doc.getCnic());
		if (x == "")
			x = doc.getEmail();
		Feedback f(p.getName(),x ,ffx);
		ofstream out("FeeBack", ios::binary | ios::app);
		out.write((char*)&f, sizeof(f));
		out.write((char*)&day, sizeof(day));
		out.close();
		Wallet obj;
		obj.read(p.getCnic());
		obj.Pay(doc.getFee());
		
	} while(i != 0);
}
void Appointment::Update(Patient p, Doctor doc, Date day, Time s, Date dnew) {
	
	string pc(p.getCnic());
	string dc(doc.getCnic());
	
	if (dc == "") dc = doc.getEmail();
	string cday(string(day));
	int q = this->getSlot();
	int move = sizeof(day)+sizeof(s) + sizeof(s);
	
	Appointment app;
	Date dd;
	Time st, es;
	
	fstream in("Appointment.dat", ios::out | ios::in | ios::binary);
	while (in.read((char*)&app, sizeof(app))) {
		in.read((char*)&app, sizeof(app));
		in.read((char*)&dd, sizeof(dd));
		in.read((char*)&st, sizeof(st));
		in.read((char*)&es, sizeof(es));
		if (pc == app.getPatient() && dc == app.getDoctor() && day == dd && st == s) {
			int a = in.tellg();
			in.seekp(a - move, ios::beg);
			in.write((char*)&dnew, sizeof(dnew));
			break;
		}
		else continue;
	
	}in.close();

}




void Wallet::read(string c) {
	Wallet obj;
	ifstream in("PWallet.dat", ios::binary);
	while (in.read((char*)&obj, sizeof(obj))) {
		if (c == obj.getPat())
			break;
		else continue;
	}in.close();
	this->set(obj);
	return;
}
void Wallet::Update() {

	string d(this->getPat());
	Wallet obj;

	fstream f("PWallet.dat", ios::in | ios::out | ios::binary);
	while (f.read((char*)&obj, sizeof(obj))) {
		string p(obj.getPat());
		if (p == d) {
			int a = f.tellg();
			int s = sizeof(obj);
			f.seekp(a - s, ios::beg);
			obj.set(*this);
			f.write((char*)&obj, sizeof(obj));
			break;
		}
	}
	f.close();

}




void Oladoc::menu() {
	int i = 0;

	do {
		system("CLS");
		cout << "*****Welcome to Oladoc*****\n";
		cout << "1->Admin\n2->Doctor\n3->Patient\n0->Exit\nInput:";
		cin >> i;
		if (i == 1) {
			ptr = new Admin;
		}
		if (i == 2) {
			ptr = new Doctor;
		}

		if (i == 3) {
			ptr = new Patient;
		}

		if (i == 0) {
			return;
		}
		ptr->menu();
		ptr = NULL;
	} while (i != 0);
}
int main() {
	
	Admin a1("123", "0000", "Zian");
	Admin a2("456", "0000" ,"Muazzam");
	Admin a3("789", "0000" ,"Asmat");

	write("Admin.dat", a1);
	write("Admin.dat", a2);
	write("Admin.dat", a3);

	Oladoc obj;
}


