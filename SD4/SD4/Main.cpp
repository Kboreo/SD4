// Project 4.cpp : Defines the entry point for the console application.
//
//
#include "stdafx.h"

#include"iostream"
using namespace std;
class consumer;
class ATM // ATM class
{
public:
	ATM(consumer& cn) :cnsm(cn)
	{
		j = true;
	}
	void welcome(); // Login interface
	bool check_passwd(char n[], char pwd[]);// Check password
	bool loss();//lost
	void change_passwd(); // change password
	void fetchmoney(); // withdrawal
	void transfer();//transfer
	void information(); // check user information
	void exitATM();
	void functionshow(); // show the ATM functions
	void lock();//when you input the wrong password for 3 times it will locked

private:
	bool j;
	int times; // The times of user input the passwod
	consumer& cnsm;
};

class consumer// user class
{
public:
	friend class ATM;
	consumer(char Name[], char Num[], char Id[20], float Money, char Password[]);
protected:
	char* get_name(); // get the name of the user
	char* get_num(); // get card number
	char* get_id();//get personal id
	char* get_passwd();// get password 
	float get_money(); // get balance of deposits
	void set_passwd(char pwd[]);// set the password
	void set_money(float m);// withdrawal
private:
	char passwd[8];// user's password
	char name[20]; // user name 
	char id[20];//user id
	char num[20];//
	float money;//
};


consumer::consumer(char Name[], char Num[], char Id[20], float Money, char Password[])
{
	strcpy_s(name, Name);
	strcpy_s(num, Num);
	strcpy_s(id, Id);
	money = Money;
	strcpy_s(passwd, Password);
}
float consumer::get_money()
{
	return money;
}
char* consumer::get_name()
{
	return name;
}
char* consumer::get_num()
{
	return num;
}
char* consumer::get_id()
{
	return id;
}
char* consumer::get_passwd()
{
	return passwd;
}
void consumer::set_money(float m)
{
	money -= m;
}
void consumer::set_passwd(char pwd[])
{
	strcpy_s(passwd, pwd);
}

void ATM::welcome()
{
	times = 0;
	cout << "Welcome to bank ATM " << endl;
	char pwd[8], num1[20], ch;
	int i = 0;
	do
	{
		i = 0;
		cout << endl << "Pls input you card numer:";
		do
		{
			cin.get(ch);
			num1[i++] = ch;
		} while (ch != '\n');
		num1[i - 1] = '\0';

		i = 0;
		cout << "Pls input your password:";
		do
		{
			cin.get(ch);
			pwd[i++] = ch;
		} while (ch != '\n');
		pwd[i - 1] = '\0';

		if (!check_passwd(num1, pwd))
		{
			cout << "You password is incorrect, please re-enter" << endl;
			times++;
		}
		else
		{
			functionshow();
		}

	} while (times<3);
	lock();
}

bool ATM::check_passwd(char num[], char pwd[])
{
	if (strcmp(num, cnsm.get_num()) == 0 && strcmp(pwd, cnsm.get_passwd()) == 0)
		return true;
	else
		return false;
}

void ATM::functionshow()
{
	int n;
	do
	{
		cout << "This machine can handle the following function:" << endl;
		cout << "**********************************************" << endl;
		cout << "                    " << endl;
		cout << "1>Report the Loss" << "    " << "  2>Change the password" << endl;
		cout << "                    " << endl;
		cout << "3>Withdraw" << "    " << "         4>Transfer" << endl;
		cout << "                    " << endl;
		cout << "5>Check the balance" << "    " << "6>Exit" << endl;
		cout << "                    " << endl;
		cout << "**********************************************" << endl;
		cout << endl << "Please enter the corresponding operation sequence number to operate：" << endl;
		cin >> n;
		while (n<1 || n>6)
		{
			cout << "Please enter the correct operation number!" << endl;
			cin >> n;
		}
		switch (n)
		{
		case 1: loss(); break;
		case 2: change_passwd(); break;
		case 3: fetchmoney(); break;
		case 4: transfer(); break;
		case 5: information(); break;
		case 6: exitATM(); break;
		}
	} while (true);
}

bool ATM::loss()
{
	char a;
	do
	{
		cout << "Are you sure to report the loss:(y/n)" << endl;
		cin >> a;
		if (a == 'y')
		{
			cout << "Report lost success!" << endl;
			exit(2);
		}
		else
		{
			cout << "Exit!" << endl;
		}

	} while (a == 'y');
	return j = true;
}

void ATM::change_passwd()
{
	char pwd[8], repwd[8];
	times = 0;
	do
	{
		cout << endl << "Pls input your old password：";
		cin >> pwd;
		if (!check_passwd(cnsm.get_num(), pwd))
			times++;
		else
			break;
	} while (times<3);
	if (times == 3)
		lock();
	int t = 1;
	do
	{
		cout << "Pls input you new password：";
		cin >> pwd;
		cout << "ls input you new password again：";
		cin >> repwd;
		t = strcmp(pwd, repwd);
		if (t != 0)
			cout << "The two passwords you entered are not the same. Please re-enter the password.!" << endl;
	} while (t != 0);
	cnsm.set_passwd(pwd);
	cout << "Password modification success, please keep in mind!" << endl;
}

void ATM::fetchmoney()
{
	float m;
	char ch;
	do
	{
		cout << endl << "How much money do you want:" << endl;
		cin >> m;
		while (m <= 0)
		{
			cout << "Pls input the correct number!" << endl;
			cin >> m;
		}
		if (cnsm.get_money() - m<0)
		{
			cout << "Sorry, your balance is not enough.!" << endl;
		}
		else
		{
			cout << endl << "Successful, please get the money!" << endl;
			cnsm.set_money(m);
		}
		cout << "Do you want to continue to withdraw money:(y/n) " << endl;
		cin >> ch;
	} while (ch == 'y' || ch == 'Y');
}

void ATM::transfer()
{
	char z[20];
	float num;
	cout << "Please enter the account number you transfer:" << endl;
	cin >> z;
	cout << "How much money do you want to transfer:" << endl;
	cin >> num;
	cnsm.money -= num;
	if (cnsm.money>0)
		cout << "Success!" << "Your balance:" << cnsm.money << endl;
	else
		cout << "Your balance is not enough！" << endl;
}

void ATM::information()
{
	cout << "**********************************" << endl;
	cout << "* User_Name: " << cnsm.get_name() << endl;
	cout << "* User_ID: " << cnsm.get_id() << endl;
	cout << "* Account number: " << cnsm.get_num() << endl;
	cout << "* Your balance: " << cnsm.get_money() << endl;
	cout << "**********************************" << endl;
}

void ATM::lock()
{
	cout << endl << "Sorry, your card has been confiscated! " << endl;
	exit(1);
}

void ATM::exitATM()
{
	cout << endl << "Thank you. Welcome to our next visit.!" << endl;
	cout << "Pls take the card……" << endl;
	exit(0);
}

void main()
{
	consumer c1("Dake", "323401020056078", "S123456789", 450.8, "123456");
	/*consumer c2("ABCe", "323401020056079", "S123456780", 1450.8, "123456");
	consumer c3("ABCa", "323401020056074", "S123456788", 2450.8, "123456");
	consumer c4("ABCw", "323401020056077", "S123456787", 23450.8, "123456");
	consumer c5("ABCc", "323401020056075", "S123456786", 4450.8, "123456");
	consumer c6("ABCd", "323401020056076", "S123456785", 50.8, "123456");
	consumer c7("ABCs", "323401020056072", "S123456784", 233450.8, "123456");
	consumer c8("ABCq", "323401020056073", "S123456783", 4503.8, "123456");
	consumer c9("ABCz", "323401020056071", "S123456782", 45031.18, "123456");
	consumer c10("ABCb", "323401020056069", "S123456781", 45230.8, "123456");*/
	ATM atm(c1);
	/*ATM atm(c2);
	ATM atm(c3);
	ATM atm(c4);
	ATM atm(c5);
	ATM atm(c6);
	ATM atm(c7);
	ATM atm(c8);
	ATM atm(c9);
	ATM atm(c10);*/
	atm.welcome();
}
