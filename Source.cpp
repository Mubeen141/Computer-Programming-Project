#include <iostream>
#include <conio.h>
#include <fstream>
#include <iomanip>
using namespace std;

void intro();                //Function for intro
void menu();                 // Main menu
void studrecmenu();          // Menu for records
void newrecord();
void resultmenu();
void showalldata();
void showdata();
void search();
void resultcard();
void gpa(int);
void grade(int);
int const size = 30;

struct result    // data for result
{
	int enrol, sem;
	char name[30];
	int ICT, CP, PHY, ENG, MATH;
	void getdata();
	double gpa;
	char grade;
	void updaterecord();  ///additional functions
	void deleterecord();
	void classsummary();
} student;
void intro()
{

	cout << setw(60) << "********************************************************" << endl;
	cout << setw(60) << "      1st Semester Computer Programming Project" << endl;
	cout << setw(60) << "            STUDENT MANAGEMENT SYSTEM" << endl;
	cout << setw(60) << " Developed by: \nUmair Ilyas (01-134182-108) \nMubeen Ahmed Jawad (01-134182-081) " << endl;
	cout << setw(60) << "********************************************************" << endl;
	_getch();
	system("cls");
	cout << endl;
} //introduction

void menu()
{
	int ch;
	system("cls");
	cout << setw(60) << "WELCOME" << endl;
	cout << setw(60) << "Student Result Management System" << endl;
	cout << "\t Press the following keys for navigation" << endl;
	cout << "\t 1. Student Records" << endl;
	cout << "\t 2. Result Management" << endl;
	cout << "\t 3. Exit Program" << endl;
	cin >> ch;
	while (ch > 3 || ch <= 0)
	{
		cout << "Invalid key. Please select again";
		cin >> ch;
	}
	switch (ch)
	{
	case 1:
	{	studrecmenu();
	break;
	}
	case 2:
	{	resultmenu();
	break;
	}
	case 3:
	{	system("cls");
	cout << "\n\n\t\t\tHAVE A NICE DAY" << endl;
	}
	}
}        // Navigation Menu created

void studrecmenu()
{
	result student;
	int enrol;
	int ch;
	system("cls");
	cout << endl << "Please select an option" << endl;
	cout << "\t1. Create a Record" << endl;
	cout << "\t2. Search a Record" << endl;
	cout << "\t3. Delete a Record" << endl;
	cout << "\t4. Update a Record" << endl;
	cout << "\t5. View all Records" << endl;
	cout << "\t6. Main Menu" << endl;
	cin >> ch;
	switch (ch)
	{
	case 1: { newrecord(); break; }
	case 2:
	{ system("cls");
	search();
	break;
	}
	case 3: { student.deleterecord(); break;  }
	case 4: { student.updaterecord(); break; }
	case 5:
	{
		showalldata();
		break;
	}
	case 6: { menu(); }
	}
}
void newrecord()
{
	char ch;

	fstream datafile("newrecords.dat", ios::app | ios::binary | ios::out);
	do
	{
		student.getdata();
		datafile.write((char *)&student, sizeof(result));
		cout << "Want to Enter another Record ? (Y/N) ";
		cin >> ch;
	} while (ch == 'y' || ch == 'Y');
	datafile.close();
	studrecmenu();
}
void search()
{
	char ch;
	int c = 0;
	int roll;
	system("cls");
	cout << "\n\t\t\tEnter Enrollment Number :";
	cin >> roll;
	ifstream datafile;
	datafile.open("newrecords.dat", ios::out | ios::binary);
	datafile.read((char *)&student, sizeof(student));
	while (!datafile.eof())
	{
		if (student.enrol == roll)
		{
			showdata();
			cout << "*******************************************" << endl;
			c++;
		}
		datafile.read((char *)&student, sizeof(student));
	}
	if (c == 0)
	{
		cout << "Record Not Found !" << endl;
	}
	cout << "\n\tWant to search another Record ? (Y/N)";
	cin >> ch;
	datafile.close();
	if (ch == 'y' || ch == 'Y')
	{
		search();
	}
	else
	{
		studrecmenu();
	}
}
void result::getdata()
{
	double sum = 0.0;
	double per = 0.0; // percentage
	system("cls");
	cout << "\nEnter Information of Student :" << endl;
	cin.ignore();
	cout << "\t\t\tName: ";
	cin.getline(name, 30);
	cout << "\t\t\tEnrollment: ";
	cin >> enrol;
	cout << "\t\t\tSemester: ";
	cin >> sem;
	cout << "\nEnter Marks of Subjects: " << endl;
	cout << "\t\t\tComputer Programming: ";
	cin >> CP;
	cout << "\t\t\tApplied Physic:";
	cin >> PHY;
	cout << "\t\t\tIntro to Computer & Tech: ";
	cin >> ICT;
	cout << "\t\t\tEnglish: ";
	cin >> ENG;
	cout << "\t\t\tCalculus: ";
	cin >> MATH;
	sum = CP + PHY + ICT + ENG + MATH;
	per = (sum / 500) * 100;
	if (per >= 80.0)
	{
		grade = 'A';
		gpa = 4.0;
	}
	else if (per >= 70.0 && per <= 79.0)
	{
		grade = 'B';
		gpa = 3.5;
	}
	else if (per >= 60.0 && per <= 69.0)
	{
		grade = 'C';
		gpa = 2.5;
	}
	else if (per >= 50.0 && per <= 59.0)
	{
		grade = 'D';
		gpa = 1.5;
	}
	else if (per < 50.0)
	{
		grade = 'F';
		gpa = 0.0;
	}
}
void showalldata()
{
	result student;
	fstream datafile;
	datafile.open("newrecords.dat", ios::in | ios::binary);
	datafile.read(reinterpret_cast<char *>(&student), sizeof(student));
	system("cls");
	while (!datafile.eof())
	{
		cout << "\nInformation of Student :" << endl;
		cout << "\t\t\tName: " << student.name << endl;
		cout << "\t\t\tEnrollment: " << student.enrol << endl;
		cout << "\t\t\tSemester: " << student.sem << endl;
		cout << "\nMarks of Subjects: " << endl;
		cout << "\t\t\tComputer Programming: " << student.CP << endl;
		cout << "\t\t\tApplied Physics: " << student.PHY << endl;
		cout << "\t\t\tIntro to Computer & Tech: " << student.ICT << endl;
		cout << "\t\t\tEnglish: " << student.ENG << endl;
		cout << "\t\t\tCalculus: " << student.MATH << endl;
		datafile.read(reinterpret_cast<char *>(&student), sizeof(student));
		cout << "_________________________________________________________________" << endl;
		cout << "\t\tPress Any Key to See Next Record !" << endl;
		_getch();
	}
	cout << "\n\t\tRecords Ended" << endl;
	system("pause");
	datafile.close();
	studrecmenu();
}
void showdata()
{
	cout << "\nInformation of Student :" << endl;
	cout << "\t\t\tName: " << student.name << endl;
	cout << "\t\t\tEnrollment: " << student.enrol << endl;
	cout << "\t\t\tSemester: " << student.sem << endl;
	cout << "\nMarks of Subjects: " << endl;
	cout << "\t\t\tComputer Programming: " << student.CP << endl;
	cout << "\t\t\tApplied Physics: " << student.PHY << endl;
	cout << "\t\t\tIntro to Computer & Tech: " << student.ICT << endl;
	cout << "\t\t\tEnglish: " << student.ENG << endl;
	cout << "\t\t\tCalculus: " << student.MATH << endl;
}
void grade(int sub)
{
	if (sub >= 80)
	{
		cout << "A";
	}
	else if (sub >= 70 && sub <= 79)
	{
		cout << "B";
	}
	else if (sub >= 60 && sub <= 69)
	{
		cout << "C";
	}
	else if (sub >= 50 && sub <= 59)
	{
		cout << "D";
	}
	else if (sub < 50)
	{
		cout << "F";
	}
}
void gpa(int sub)
{
	if (sub >= 80)
	{
		cout << 4.0;
	}
	else if (sub >= 70 && sub <= 79)
	{
		cout << 3.5;
	}
	else if (sub >= 60 && sub <= 69)
	{
		cout << 2.5;
	}
	else if (sub >= 50 && sub <= 59)
	{
		cout << 1.5;
	}
	else if (sub < 50)
	{
		cout << 0;
	}
}
void result::deleterecord()
{
	char ch;
	int c = 0;
	int roll;
	fstream datafile("newrecords.dat", ios::in | ios::out | ios::binary);
	fstream tempfile("Text.dat", ios::in | ios::out | ios::binary | ios::app);
	do
	{
		system("cls");
		cout << "\n\t\t\tEnter Enrollment Number to Delete Record :";
		cin >> roll;
		datafile.read((char *)&student, sizeof(student));
		while (!datafile.eof())
		{
			if (student.enrol != roll)
			{
				tempfile.write((char *)&student, sizeof(student));
			}
			datafile.read((char *)&student, sizeof(student));
		}
		if (c != 0)
			cout << "Record Not Found !" << endl;
		else
			cout << "Record Has been Deleted !" << endl << endl;
		cout << "\n\tWant to Delete another Record ? (Y/N)";
		cin >> ch;
	} while (ch == 'Y' || ch == 'y');
	datafile.close();
	tempfile.close();
	remove("newrecords.dat");
	rename("Text.dat", "newrecords.dat");
	studrecmenu();
}

void result::updaterecord()
{
	char ch;
	int c = 0;
	int roll;
	do
	{
		fstream tempfile("Text.dat", ios::in | ios::binary | ios::app);
		fstream datafile("newrecords.dat", ios::in | ios::out | ios::binary | ios::app);
		system("cls");
		cout << "\n\t\t\tEnter Enrollment Number to Update Record :";
		cin >> roll;
		datafile.read((char *)&student, sizeof(student));
		while (!datafile.eof())
		{
			if (student.enrol != roll)
			{
				tempfile.write((char *)&student, sizeof(student));
			}
			else
			{
				c++;
			}
			datafile.read((char *)&student, sizeof(student));
		}
		student.getdata();
		tempfile.write((char *)&student, sizeof(result));
		datafile.close();
		tempfile.close();
		if (c == 0)
			cout << "Record Not Found !" << endl;
		else
			cout << "Record Has been Updadted !" << endl << endl;
		remove("newrecords.dat");
		rename("Text.txt", "newrecords.dat");
		cout << "\n\tWant to Update another Record ? (Y/N)";
		cin >> ch;
	} while (ch == 'Y' || ch == 'y');
	studrecmenu();
}
void resultmenu()
{
	int ch;
	system("cls");
	cout << endl << "\t1. Overall Class Summary";
	cout << endl << "\t2. Generate Report Card";
	cout << endl << "\t3. Back to Main Menu" << endl;
	cout << endl << "\n\tSelect from list (1-3): ";
	cin >> ch;
	switch (ch)
	{
	case 1: { student.classsummary(); menu(); break; }
	case 2: { resultcard(); resultmenu(); break; }
	case 3: { menu(); break; }
	}
}
void result::classsummary()
{
	int p = 0, f = 0;
	fstream datafile("newrecords.dat", ios::in | ios::out | ios::binary);
	datafile.read((char *)&student, sizeof(student));
	system("cls");
	while (!datafile.eof())
	{
		if (grade != 'F')
		{
			cout << "\t\t\t\tPassed Students: " << endl;
			p++;
			showdata();
			cout << "==========================================" << endl;
		}
		else
		{
			cout << "\t\t\t\tFailed Students: " << endl;
			f++;
			showdata();
			cout << "==========================================" << endl;
		}
		datafile.read((char *)&student, sizeof(student));
	}
	cout << "Total Numbers of Passed Students: " << p << endl;
	cout << "Total Numbers of Failed Students: " << f << endl;
	datafile.close();
	system("pause");
	studrecmenu();
}
void resultcard()
{
	int c = 0;
	char ch;
	int roll;
	do
	{
		cout << "\n\t\t\tEnter Enrollment Number :";
		cin >> roll;
		ifstream datafile;
		datafile.open("newrecords.dat", ios::out | ios::binary);
		datafile.read((char *)&student, sizeof(student));
		while (!datafile.eof())
		{
			if (student.enrol == roll)
			{
				system("cls");
				cout << endl;
				cout << setw(70) << "Bahria University Islamabad" << endl << endl;
				cout << setw(70) << "   Result Card    " << endl << endl;;
				cout << setw(20) << "Name : " << student.name << setw(65) << "Enrollment: " << student.enrol << endl;
				cout << setw(20) << "             Dept of Computer Science" << setw(62) << "Class: BSCS-1A" << endl;
				cout << setw(20) << "------------------------------------------------------------------------------------------------------------------------" << endl;
				cout << setw(20) << "|Course Title|" << setw(30) << "|Maximum Marks|" << setw(20) << "|Obtained Marks|" << setw(14) << "|CGPA|" << setw(15) << "|Grade|" << endl;
				cout << setw(20) << "Computer Programming" << setw(29) << "100" << setw(19) << student.CP << setw(14) << setprecision(2); gpa(student.CP); cout << "\t\t "; grade(student.CP); cout << endl;
				cout << setw(20) << "Intro to Comp & Tech" << setw(29) << "100" << setw(19) << student.ICT << setw(14) << setprecision(2); gpa(student.ICT); cout << "\t\t "; grade(student.ICT); cout << endl;
				cout << setw(20) << "  Physics " << setw(29) << "100" << setw(19) << student.PHY << setw(14) << setprecision(2); gpa(student.PHY); cout << "\t\t "; grade(student.PHY); cout << endl;
				cout << setw(20) << "      Calculus      " << setw(29) << "100" << setw(19) << student.MATH << setw(14) << setprecision(2); gpa(student.MATH); cout << "\t\t "; grade(student.MATH); cout << endl;
				cout << setw(20) << "       English      " << setw(29) << "100" << setw(19) << student.ENG << setw(14) << setprecision(2); gpa(student.ENG); cout << "\t\t "; grade(student.ENG); cout << endl;
				cout << setw(20) << "------------------------------------------------------------------------------------------------------------------------" << endl;
				cout << endl << endl << "\tCGPA :" << student.gpa << endl;
				cout << endl << "\tGrade :" << student.grade << endl;
				c++;
			}
			datafile.read((char *)&student, sizeof(student));
		}
		if (c == 0)
		{
			cout << "Record Not Found !" << endl;
		}
		cout << endl << "\tDo you want to optain another Result Card? (Y/N)";
		cin >> ch;
	} while (ch == 'Y' || ch == 'y');
	system("cls");
}