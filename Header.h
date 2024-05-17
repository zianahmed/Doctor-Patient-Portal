#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
using namespace std;



class Wallet {
	char pc[20];
	int amount;
public:

	Wallet(string p="", int x = 0) {
		setPat(p);
		setAmount(x);
	}

	void setPat(string p) { strcpy_s(pc, p.length() + 1, p.c_str()); }
	string getPat() { string p(pc); return p; }
	virtual void setAmount(int x) { amount = x; }
	virtual int getAmount() { return amount; }
	virtual void set(Wallet x) {
		amount = x.amount;
		setPat(x.getPat());
	}
	void read(string);
	void Pay(int x) {
		amount -= x;
	}
	void Add(int x) {
		amount += x;
	}

	void Update();
};
class Bank : public Wallet {
public:
	
};
class Etrans : public Wallet {
public:
	
};
class UnionPay : public Bank {
public:
	UnionPay(int i = 0) {
		setAmount(i);
	}
};
class PayPak : public Bank {
public:
	PayPak(int i = 0) {
		setAmount(i);
	}
};
class EasyPaisa : public Etrans {
public:
	EasyPaisa(int i = 0) {
		setAmount(i);
	}
};
class Jazzcash : public Etrans {
public:
	Jazzcash(int i = 0) {
		setAmount(i);
	}
};




class Date {
	int d;
	int m;
public:
	Date(int dv = 0, int mv = 0) {
		d = dv;
		m = mv;
	}

	void setD(int dv) { d = dv; }
	int getD() { return d; }
	void setM(int dv) { m = dv; }
	int getM() { return m; }
	
	bool operator==(Date x) {
		if (d == x.d && m == x.m) { return 1; }
		return 0;
	}
	bool operator>(Date x) {
		if (m > x.m)
			return 1;
		else if (d > x.d)
			return 1;
		return 0;
	}

	operator string() {
		char ptr[6];
		ptr[5] = '\0';
		ptr[0] = d/10 + 48;
		ptr[1] = d % 10+48;
		ptr[3] = m / 10 + 48;
		ptr[4] = m % 10 + 48;
		ptr[2] = '/';
		string q(ptr);
		return q;
	}

	void set(Date x) {
		d = x.d;
		m = x.m;
	}
	
	void set(int x, int y) {
		d = x;
		m = y;
	}
};
class Time {
	int h;
	int m;
public:

	Time(int y = 0, int x = 0) {
		h = x;
		m = y;
	}
	
	bool operator ==(Time x) {
		if (h == x.h && m == x.m) { return 1; }
		return 0;
	}
	bool operator >(Time x) {
		if (h > x.h) { return 1; }
		else { if (m > x.h) { return 1; } }
		return 0;
	}
	
	void set(Time x) {
		h = x.h;
		m = x.m;
	}

	void set(int x, int y) {
		h = x;
		m = y;
	}
	operator string() {
		char ptr[6];
		ptr[5] = '\0';
		ptr[0] = h / 10 + 48;
		
		if (h>10){ ptr[1] = h % 10 + 48; }
		else if (h%10==0) { ptr[1] =48; }
		else { ptr[1] = h + 48; }
		
		ptr[2] = ':';

		ptr[3] = m / 10 + 48;
		if (m > 10) { ptr[4] = m % 10 + 48; }
		else { ptr[4] = m + 48; }
		string q(ptr);
		return q;
	}
};




class User {
protected:
	char cnic[20];
	char password[20];
	char name[20];
public:
	void setCnic(string c) { strcpy_s(cnic, c.length() + 1, c.c_str()); }
	string getCnic() { string s(cnic);  return s; }
	void setName(string c) { strcpy_s(name, c.length() + 1, c.c_str()); }
	string getName() { string s(name);  return s; }
	void setPassword(string c) { strcpy_s(password, c.length() + 1, c.c_str()); }
	string getPassword() { string s(password);  return s; }
	virtual void Register() { }
	virtual void login() { };
	virtual void menu() { };
	virtual void submenu() { };
	virtual void Delete() { };
	virtual void Update() { };
	virtual void viewApp() { };
};
class Patient : public User {
	bool status;
	int type;
public:
	
	Patient(string c = "", string b = "", string n = "",int i=0) {
		strcpy_s(cnic, c.length()+1, c.c_str());
		strcpy_s(name, n.length() + 1, n.c_str());
		strcpy_s(password, b.length() + 1, b.c_str());
		status = false;
		type = i;
	}
	
	void setStatus(bool x) { status = x; }
	bool getStatus() { return status; }
	void set(Patient x) {
		setCnic(x.getCnic());
		setName(x.getName());
		setPassword(x.getPassword());
		setStatus(x.getStatus());
	}
	Patient operator=(Patient x) {
		setCnic(x.getCnic());
		setName(x.getName());
		setPassword(x.getPassword());
		setStatus(x.getStatus());
		type = x.type;
		return *this;
	}
	
	bool operator==(Patient p) {
		string c(cnic);
		string cp(p.cnic);
		if (p == cp) return 1;
		else return 0;
	}

	void dp1();
	void display();
	void findDoc1();
	void findDoc();
	void Register();
	void login();
	void menu();
	void submenu();
	void Update();
	void viewApp();
};
class Doctor : public User {
	char email[20];
	char hospital[20];
	char city[20];
	char specialization[20];
	bool status;
	int years;
	float rating;
	int fee;
	int r;
	bool slot[6];
	
public:
	Doctor(string c = "", string b = "", string n = "",string e="" , string cv = "", string h = "", string s = "",int x=0, int z = 0,float y=5.0) {
		strcpy_s(cnic, c.length() + 1, c.c_str());
		strcpy_s(name, n.length() + 1, n.c_str());
		strcpy_s(password, b.length() + 1, b.c_str());
		strcpy_s(email, e.length() + 1, e.c_str());
		strcpy_s(hospital, h.length() + 1, h.c_str());
		strcpy_s(city, cv.length() + 1, cv.c_str());
		strcpy_s(specialization, s.length() + 1, s.c_str());
		setYear(x);
		setRating(y);
		setFee(z);
		r = 0;
		setStatus(false);
		for (int i = 0; i < 6; i++) {
			slot[i] = false;
		}
	}
	
	void set(Doctor x) {

		setCnic(x.getCnic());
		setName(x.getName());
		setEmail(x.getEmail());
		setPassword(x.getPassword());
		setHospital(x.getHospital());
		setSpecialization(x.getSpecialization());
		setCity(x.getCity());
		setStatus(x.getStatus());
		setYear(x.getYear());
		setRating(x.getRating());
		setFee(x.getFee());
		r = x.r;
		for (int i = 0; i < 6; i++) {
			slot[i] = x.slot[i];
		}
	}

	void setStatus(bool x) { status = x; }
	bool getStatus() { return status; }
	void setEmail(string x) { strcpy_s(email, x.length() + 1, x.c_str()); }
	string getEmail() { string x(email);  return x; }
	void setHospital(string c) { strcpy_s(hospital, c.length() + 1, c.c_str()); }
	string getHospital() { string s(hospital);  return s; }
	void setCity(string c) { strcpy_s(city, c.length() + 1, c.c_str()); }
	string getCity() { string s(city);  return s; }
	void setSpecialization(string c) { strcpy_s(specialization, c.length() + 1, c.c_str()); }
	string getSpecialization() { string s(specialization);  return s; }
	void setYear(int x) { years = x; }
	int getYear() { return years; }
	void setFee(int x) { fee = x; }
	int getFee() { return fee; }
	void setRating(float x) { rating = x; }
	float getRating() { return rating/r; }
	void setSlot(int i) { slot[i] = !slot; }
	bool getSlot(int i) { return slot[i]; }
	void setR(int x) { r = x; }
	int getR() { return r; }

	
	bool operator==(Doctor x) {
		string a("");
		string b(cnic);
		string c(email);
		string bx(x.cnic);
		string cx(x.email);
		if (c == a) { if (b == bx) { return 1; } }
		else { if (c == cx) { return 1; } }
		return 0;
	}
	
	void display();
	void Register();
	void login();
	void menu();
	void submenu();
	void Update();
	void Delete();
	void book(Patient);
	void displayP(Patient);
	void setTime();
	void viewApp();
};
class Admin :public User {
public:
	Admin(string c = "", string b = "", string n = "") {
		strcpy_s(cnic, c.length() + 1, c.c_str());
		strcpy_s(name, n.length() + 1, n.c_str());
		strcpy_s(password, b.length() + 1, b.c_str());
	}

	void menu();
	void submenu();

	void set(Admin x) {
		setCnic(x.getCnic());
		setName(x.getName());
		setPassword(x.getPassword());
	}
	
	void PPatient();
	void VPatient();
	void PDoctor();
	void VDoctor();
	void viewApp();
};
class Oladoc {
	User* ptr;
public:
	Oladoc() {
		menu();
	}
	void menu();
};



class Feedback {
	char name[20];
	char doc[20];
	char f[100];
public:
	Feedback(){ }
	Feedback(string p, string d, string ff) {
		setPat(p);
		setDoc(d);
		setF(ff);
	}
	
	void setPat(string p) { strcpy_s(name, p.length() + 1, p.c_str()); }
	string getPat() { string p(name); return p; }
	void setDoc(string p) { strcpy_s(doc, p.length() + 1, p.c_str()); }
	string getDoc() { string p(doc); return p; }
	void setF(string p) { strcpy_s(f, p.length() + 1, p.c_str()); }
	string getF() { string p(f); return p; }
	
	void set(Feedback p) {
		setPat(p.getPat());
		setDoc(p.getDoc());
		setF(p.getF());
	}

};



class Appointment {
protected:
	int slot;
	char pc[20];
	char dc[20];
	
public:
	Appointment() { }
	Appointment(string p,string d,int i) {
		setPatient(p);
		setDoctor(d);
		slot = i;
	}



	void set(Appointment x) {
		setPatient(x.getPatient());
		setDoctor(x.getDoctor());
		slot = x.slot;
	}

	void setPatient(string c) { strcpy_s(pc, c.length() + 1, c.c_str()); }
	string getPatient() { string s(pc);  return s; }
	void setDoctor(string c) { strcpy_s(dc, c.length() + 1, c.c_str()); }
	string getDoctor() { string s(dc);  return s; }

	void setSlot(int p) { slot=p; }
	int getSlot() { return slot; }
	void Display(Patient,Doctor,Date,Time,Time,bool =1);
	void cancel(Patient, Doctor, Date, Time, Time);
	void take(Patient, Doctor, Date, Time, Time);
	void Update(Patient, Doctor, Date, Time, Date);
};



class Inperson :public Appointment {
public:
	Inperson() { }
	Inperson(Patient p, Doctor d, Date da, Time s, Time e) {
	}
};
class Online :public Appointment {
public:
	Online() { }
	Online(Patient p, Doctor d, Date da, Time s, Time e) {
	}
};








void write(string file, Patient obj) {
	ofstream out(file, ios::binary | ios::app);
	out.write((char*)&obj, sizeof(obj));
	out.close();
}
void Cread(string file) {

	if (file == "Doctor.dat") {
		Doctor obj;
		ifstream in(file, ios::binary);
		while (in.read((char*)&obj, sizeof(obj))) {
			obj.display();
		}
		in.close();
	}

	else if (file == "Patient.dat") {
		Patient obj;
		ifstream in(file, ios::binary);
		while (in.read((char*)&obj, sizeof(obj))) {
			obj.display();
		}
		in.close();
	}
}
void write(string file, Doctor obj) {
	ofstream out(file, ios::binary | ios::app);
	out.write((char*)&obj, sizeof(obj));
	out.close();
}
void write(string file, Admin obj) {
	ofstream out(file, ios::binary | ios::app);
	out.write((char*)&obj, sizeof(obj));
	out.close();
}



//void Update(Doctor);