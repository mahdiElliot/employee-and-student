// Tamrine_1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>

using namespace std;

class Pair
{
public:
	int CourseId = 0;
	int Grade = 0;

	Pair(int courseId, int grade)
	{
		CourseId = courseId;
		Grade = grade;
	}
};

class MyDateTime
{
private:
	int year;
	int month;
	int day;

public:
	MyDateTime() : MyDateTime(0000, 00, 00)
	{}

	MyDateTime(int year, int month, int day)
	{
		this->year = year;
		this->month = month;
		this->day = day;
	}

	string ToString()
	{
		return "" + to_string(year) + "-" + to_string(month) + "-" + to_string(day);
	}

	~MyDateTime() {}
};

class Person
{
protected:
	string name;
	string workId;
	string fatherName;
	string melliId;
	MyDateTime birthDate;

public:
	Person() : Person(string(""), string(""), string(""), string(""), MyDateTime()) {}

	Person(string name) : Person(name, string(""), string(""), string(""), MyDateTime()) {}

	Person(string name, string workId, string fatherName, string melliId, MyDateTime birthDate)
	{
		SetName(name);
		SetId(workId);
		SetFatherName(fatherName);
		SetMelliId(melliId);
		SetBirthDate(birthDate);
	}

	string GetName()
	{
		return name;
	}

	void SetName(string _name)
	{
		name = _name;
	}

	string GetId()
	{
		return workId;
	}

	void SetId(string _workId)
	{
		int size = _workId.length();
		if (size == 10)
			workId = _workId;
	}

	string GetFatherName()
	{
		return fatherName;
	}

	void SetFatherName(string _fatherName)
	{
		fatherName = _fatherName;
	}

	string GetMelliId()
	{
		return melliId;
	}

	void SetMelliId(string _melliId)
	{
		melliId = _melliId;
	}

	MyDateTime GetBirthDate()
	{
		return birthDate;
	}

	void SetBirthDate(MyDateTime _birthDate)
	{
		birthDate = _birthDate;
	}

	virtual void Print()
	{
		cout << "\n\nName: " << name << endl
			<< "Work ID: " << workId << endl
			<< "Father Name: " << fatherName << endl
			<< "Melli ID: " << melliId << endl
			<< "Birth Date: " << birthDate.ToString() << endl;
	}

	~Person() {}
};

class Employee : public Person
{
protected:
	long salary = 0;
	Employee* boss;
	int workingYears = 0;
	string preamble = string("");
	bool isInitialized = false;
	bool hasBoss = false;

public:
	Employee() : Employee(string(""), string(""), string(""), string(""), MyDateTime(), nullptr, 0, string("")) {}

	Employee(string name, string workId, string fatherName, string melliId, MyDateTime birthDate, Employee* _boss, int _workingYears, string _preamble)
		: Person(name, workId, fatherName, melliId, birthDate)
	{
		SetBoss(_boss);
		workingYears = _workingYears;
		preamble = _preamble;
	}

	void CalcSalary(long baseSalary, float tax)
	{
		long gain = workingYears * baseSalary * 0.12;
		salary = baseSalary + gain - tax;
	}

	void SetBoss(Employee* _boss)
	{
		boss = _boss;
		isInitialized = true;

		hasBoss = (_boss == nullptr) ? false : true;
	}

	virtual void Print()
	{
		if (isInitialized)
		{
			Person::Print();
			cout << fixed << "Salary: " << salary << endl;

			if (hasBoss)
				cout << "Boss's Name: " << boss->name << endl;

			cout << "Working Years: " << workingYears << endl
				<< "Preamble: " << preamble << endl << endl;
		}
		else
			cout << "* You have to initialize this employee's [boss] first. *" << endl << endl;
	}

	~Employee() {}
};

class HourlyEmployee : public Employee
{
private:
	int teachingHours = 0;
	float tuitionPerHour = 0;

public:
	HourlyEmployee(string _name, string _workId, string _fatherName, string _melliId, MyDateTime _birthDate, int _teachingHours, float _tuitionPerHour)
	{
		name = _name;
		workId = _workId;
		fatherName = _fatherName;
		melliId = _melliId;
		birthDate = _birthDate;

		salary = 0;
		teachingHours = _teachingHours;
		tuitionPerHour = _tuitionPerHour;
	}

	void CalcSalary(float tax)
	{
		salary = teachingHours * tuitionPerHour - tax;
	}

	void Print()
	{
		if (isInitialized)
		{
			Employee::Print();
			cout << "[ HaqoTadrisi ast. ]" << endl << endl;
		}
		else
			cout << "* You have to initialize this employee's [boss] first. *" << endl << endl;
	}

	~HourlyEmployee() {}
};

class Student : public Person
{
private:
	int coursesCount = 0;
	float totalGrade = 0;
	int* passed;

public:
	Student() : Student(string(""), string(""), string(""), string(""), MyDateTime(), 0) {}

	Student(string name, string workId, string fatherName, string melliId, MyDateTime birthDate, int _coursesCount)
		: Person(name, workId, fatherName, melliId, birthDate)
	{
		coursesCount = _coursesCount;
		passed = new int[_coursesCount];
	}

	void AddGrade(int courseId, int grade)
	{
		if (grade >= 0 && grade <= 20)
			if (courseId < coursesCount)
				passed[courseId] = grade;

		totalGrade = 0;
		for (int i = 0; i < coursesCount; i++)
			totalGrade += passed[i];
		totalGrade /= coursesCount;
	}

	int GetPass()
	{
		cout << "Passed Courses Count of [" << name << "]: " << coursesCount << endl << endl;
		return coursesCount;
	}

	float GetTotalGrade()
	{
		return totalGrade;
	}

	void operator + (Pair pair)
	{
		AddGrade(pair.CourseId, pair.Grade);
	}

	~Student()
	{
		delete passed;
	}
};

int main()
{
	MyDateTime anishtaynBD(1879, 3, 14);
	Student anishtayn("Anishtayn", "9931200030", "Albert", "0011223344", anishtaynBD, 10);
	Pair mathScore(10, 20);
	anishtayn + mathScore;

	MyDateTime niotonBD(1643, 1, 4);
	Student nioton("Nioton", "9931200057", "Peter", "5566778899", niotonBD, 20);
	Pair physicsScore(0, 19);
	nioton + physicsScore;

	MyDateTime aziziBD(1360, 1, 1);
	Employee Azizi("Azizi", "0003120030", "Gholam", "0111223344", aziziBD, nullptr, 25, "Raees ast");
	Azizi.CalcSalary(5000000, 500000);

	MyDateTime bahramiBD(1367, 11, 12);
	Employee Bahrami("Bahrami", "0003121030", "Abbas", "1011223344", bahramiBD, &Azizi, 15, "Moaven ast");
	Bahrami.CalcSalary(4000000, 400000);

	MyDateTime abbasiBD(1372, 5, 31);
	Employee Abbasi("Abbasi", "0003120036", "Mohsen", "0511223344", abbasiBD, &Bahrami, 8, "Karmand ast");
	Abbasi.CalcSalary(3000000, 300000);

	anishtayn.Print();
	anishtayn.GetPass();
	nioton.Print();
	nioton.GetPass();

	Azizi.Print();
	Bahrami.Print();
	Abbasi.Print();
}