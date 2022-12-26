// ChyrunSofialab11.3.2.cpp : This file contains the 'main' function. Program execution begins and ends there.
// Lab_11_3.cpp
// < Чирун Софія >
// Лабораторна робота № 11.3.2
//Впорядкування та бінарний пошук у бінарному файлі 
// Варіант 18

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <Windows.h> 
using namespace std;
enum Student { IT, KN, ME, TN, FI };
string studentStr[] = { "Інформатика" ,"Комп’ютерні науки",  "Матем. та екон.", "Трудове навчання", "Фізика та інформ." };
struct Specialist
{
	string prizv;
	int course;
	Student student;
	double fizyk;
	double matem;
	union
	{
		double progr;
		double numbm;
		double pedag;
	};
	double serbl;
};

void Create(Specialist* p, const int N);
void Print(Specialist* p, const int N);
void Serbal(Specialist* p, const int N);
double MinSerbal(Specialist* p, const int N);
int Dobre(Specialist* p, int j, const int N, int d);
int* IndexSort(Specialist* p, const int N);
void PrintIndexSorted(char* fname, Specialist* p, int* I, const int N);
int BinSearch(Specialist* p, const int N, const string iprizv, const Student student, const int icourse);
void Sort(Specialist* p, const int N);
void CreateBIN(char* fname, Specialist* p, const int N) 
{
	ofstream fout(fname, ios::binary); 
	string s; 
	fout << "===============================================================================================================================" << endl;
	fout << "| № | Прізвище | Курс |   Спеціальність   | Фізика | Математика | Програмування | Чисельні методи | Педагогіка | Середній бал |" << endl;
	fout << "-------------------------------------------------------------------------------------------------------------------------------" << endl;
	for (int i = 0; i < N; i++)
	{
		fout << "|" << setw(2) << right << i + 1 << " ";
		fout << "| " << setw(9) << left << p[i].prizv
			<< "| " << setw(4) << right << p[i].course << " "
			<< "| " << setw(17) << left << studentStr[p[i].student] << " "
			<< "| " << setw(6) << setprecision(2) << fixed << right << p[i].fizyk << " "
			<< "| " << setw(10) << setprecision(2) << fixed << right << p[i].matem << " ";
		switch (p[i].student)
		{
		   case KN:
			  fout << "| " << setw(13) << setprecision(2) << fixed << right << p[i].progr << " |" << setw(18) << right << "|" << setw(14) << right << "| ";
			  break;
		   case IT:
			  fout << "| " << setw(15) << " |" << setw(16) << setprecision(2) << fixed << right << p[i].numbm << " |" << setw(14) << right << "| ";
			  break;
		   case ME:
			  fout << "| " << setw(15) << right << "|" << " " << setw(17) << right << "|" << " " << setw(10) << right << p[i].pedag << " | ";
			  break;
		   case FI:
			  fout << "| " << setw(15) << right << "|" << " " << setw(17) << right << "|" << " " << setw(10) << right << p[i].pedag << " | ";
			  break;
		   case TN:
			  fout << "| " << setw(15) << right << "|" << " " << setw(17) << right << "|" << " " << setw(10) << right << p[i].pedag << " | ";
			  break;
		}
		fout << setw(12) << setprecision(2) << fixed << right << p[i].serbl << " | " << endl;
	}
	fout << "===============================================================================================================================" << endl;
	fout << endl;
    fout << endl;
}

void CreateBIN1(char* fname, Specialist* p, const int N) 
{
	ofstream fout(fname, ios::binary); 
	string s; 
	fout << endl << "Кількість оцінок добре: ";
	fout << endl << "Фізика: " << Dobre(p, 1, N, 0);
	fout << endl << "Математика: " << Dobre(p, 2, N, 0);
	fout << endl << "Програмування: " << Dobre(p, 3, N, 0);
	fout << endl << "Чисельні методи: " << Dobre(p, 4, N, 0);
	fout << endl << "Педагогіка: " << Dobre(p, 5, N, 0);
	fout << endl << endl;
}

void PrintBIN(char* fname)
{
	ifstream fin(fname, ios::binary); 
	char c; 
	while (fin.read((char*)&c, sizeof(c))) 
	{
		cout << c; 
	}
	cout << endl;
}

int main()
{ 
	SetConsoleCP(1251); 
	SetConsoleOutputCP(1251); 
	int N, istudent, found, icourse;
	cout << "Введіть N: "; cin >> N;
	Student student;
	string iprizv;
	Specialist* p = new Specialist[N];
	Create(p, N);
	Serbal(p, N);
	Print(p, N);
	char fname[100]; 
	cout << "enter file name 1: "; cin >> fname;
	cout << endl << "Мінімaльний середній бал: " << MinSerbal(p, N) << endl;
	CreateBIN(fname, p, N); 
	cout << "\nВивід результату з файлу 1: " << endl;
	PrintBIN(fname); 
	char gname[100]; 
	cout << "enter file name 2: "; cin >> gname;
	CreateBIN1(gname, p, N);
	cout << "\nВивід результату з файлу 2: " << endl;
	PrintBIN(gname);
	char f2name[100]; 
	cout << "enter file name 3: "; cin >> f2name;
	cout << "індексне впорядкування та вивід даних" << endl;
	cout << "\nВивід результату з файлу 3: " << endl;
	PrintIndexSorted(f2name, p, IndexSort(p, N), N);
    cout << "фізичне впорядкування даних та вивід даних" << endl;
	Sort(p, N);
	Print(p, N);
	cout << "Введіть ключі пошуку:" << endl;
	cout << " спеціальність (0 - Інформатика, 1 - Комп’ютерні науки, 2 - Математика та економіка, 3 - Трудове навчання, 4 - Фізика та інформатика ): ";
	cin >> istudent;
	student = (Student)istudent;
	cin.get(); 
	cin.sync(); 
	cout << " курс: "; cin >> icourse;
	cout << " прізвище: "; cin >> iprizv;
	if ((found = BinSearch(p, N, iprizv, student, icourse)) != -1)
	   cout << "Знайдено працівника в позиції " << found + 1 << endl;
	else
	   cout << "Шуканого працівника не знайдено" << endl;
	return 0;
}

void Create(Specialist* p, const int N)
{
	int student;
	for (int i = 0; i < N; i++)
	{
		cout << "Студент № " << i + 1 << ":" << endl;
		cin.get(); 
		cin.sync(); 
		cout << " прізвище: "; getline(cin, p[i].prizv);
		cout << " курс: "; cin >> p[i].course;
		cout << " спеціальність (0 - Інформатика,1 - Комп’ютерні науки,  2 - Математика та економіка, 3 - Трудове навчання, 4 - Фізика та інформатика ): ";
		cin >> student;
		p[i].student = (Student)student;
		cout << " фізика: "; cin >> p[i].fizyk;
		cout << " математика: "; cin >> p[i].matem;
		switch (p[i].student)
		{
		   case KN:
			  cout << " програмування : "; cin >> p[i].progr; 
			  break;
		   case IT:
			  cout << " чисельні методи : "; cin >> p[i].numbm; 
			  break;
		   case ME:
			  cout << " педагогіка : "; cin >> p[i].pedag; 
			  break;
		   case FI:
			  cout << " педагогіка : "; cin >> p[i].pedag; 
			  break;
		   case TN:
			  cout << " педагогіка : "; cin >> p[i].pedag; 
			  break;
		}
		cout << endl;
	}
}

void Serbal(Specialist* p, const int N)

{
	double s = 0;
	for (int i = 0; i < N; i++)
	{
		s = p[i].fizyk + p[i].matem;
		switch (p[i].student)
		{
		   case KN:
			  s += p[i].progr;
			  break;
		   case IT:
			  s += p[i].numbm;
			  break;
		   case ME:
			  s += p[i].pedag;
			  break;
		   case FI:
			  s += p[i].pedag;
			  break;
		   case TN:
			  s += p[i].pedag;
			  break;
		}
		p[i].serbl = s / 3;
		s = 0;
	}
}

double MinSerbal(Specialist* p, const int N)
{
	double s = 1000;
	for (int i = 0; i < N; i++)
	{
		if (p[i].serbl < s)
		   s = p[i].serbl;
	}
	return s;
}

int Dobre(Specialist* p, int j, const int N, int d)
{
	double s = 4;
	for (int i = 0; i < N; i++)
		switch (j)
		{
		   case 1:
			  if (p[i].fizyk == s)
				 d++;
			  break;
		   case 2:
			  if (p[i].matem == s)
				 d++;
			  break;
		   case 3:
			  if (p[i].progr == s)
				 d++; 
			  break;
		   case 4:
			  if (p[i].numbm == s)
				 d++; 
			  break;
		   case 5:
			  if (p[i].pedag == s)
				 d++; 
			  break;
		}
	return d;
}

void Print(Specialist* p, const int N)
{
	cout << "===============================================================================================================================" << endl;
	cout << "| № | Прізвище | Курс |   Спеціальність   | Фізика | Математика | Програмування | Чисельні методи | Педагогіка | Середній бал |" << endl;
	cout << "-------------------------------------------------------------------------------------------------------------------------------" << endl;
	for (int i = 0; i < N; i++)
	{
		cout << "|" << setw(2) << right << i + 1 << " ";
		cout << "| " << setw(9) << left << p[i].prizv
			<< "| " << setw(4) << right << p[i].course << " "
			<< "| " << setw(17) << left << studentStr[p[i].student] << " "
			<< "| " << setw(6) << setprecision(2) << fixed << right << p[i].fizyk << " "
			<< "| " << setw(10) << setprecision(2) << fixed << right << p[i].matem << " ";
		switch (p[i].student)
		{
		   case KN:
			  cout << "| " << setw(13) << setprecision(2) << fixed << right << p[i].progr << " |" << setw(18) << right << "|" << setw(14) << right << "| ";
			  break;
		   case IT:
			  cout << "| " << setw(15) << " |" << setw(16) << setprecision(2) << fixed << right << p[i].numbm << " |" << setw(14) << right << "| ";
			  break;
		   case ME:
			  cout << "| " << setw(15) << right << "|" << " " << setw(17) << right << "|" << " " << setw(10) << right << p[i].pedag << " | ";
			  break;
		   case FI:
			  cout << "| " << setw(15) << right << "|" << " " << setw(17) << right << "|" << " " << setw(10) << right << p[i].pedag << " | ";
			  break;
		   case TN:
			  cout << "| " << setw(15) << right << "|" << " " << setw(17) << right << "|" << " " << setw(10) << right << p[i].pedag << " | ";
			  break;
		}
		cout << setw(12) << setprecision(2) << fixed << right << p[i].serbl << " | " << endl;
	}
	cout << "===============================================================================================================================" << endl;
	cout << endl;
}

int* IndexSort(Specialist* p, const int N)
{ 
	int* I = new int[N]; 
	for (int i = 0; i < N; i++)
		I[i] = i; 
	int i, j, value; 
	for (i = 1; i < N; i++)
	{
		value = I[i];
		for (j = i - 1;
			j >= 0 && ((p[I[j]].student > p[value].student) ||
				(p[I[j]].student == p[value].student &&
				 p[I[j]].prizv < p[value].prizv) ||
				(p[I[j]].student == p[value].student &&
				 p[I[j]].prizv == p[value].prizv &&
				 p[I[j]].course > p[value].course)); j--)
		{
			I[j + 1] = I[j];
		}
		I[j + 1] = value;
	}
	return I;
}

void PrintIndexSorted(char* fname, Specialist* p, int* I, const int N)
{
	ofstream fout(fname, ios::binary);
	fout << "===============================================================================================================================" << endl;
	fout << "| № | Прізвище | Курс |   Спеціальність   | Фізика | Математика | Програмування | Чисельні методи | Педагогіка | Середній бал |" << endl;
	fout << "-------------------------------------------------------------------------------------------------------------------------------" << endl;
	for (int i = 0; i < N; i++)
	{
		fout << "|" << setw(2) << right << i + 1 << " ";
		fout << "| " << setw(9) << left << p[I[i]].prizv
			<< "| " << setw(4) << right << p[I[i]].course << " "
			<< "| " << setw(17) << left << studentStr[p[I[i]].student] << " "
			<< "| " << setw(6) << setprecision(2) << fixed << right << p[I[i]].fizyk << " "
			<< "| " << setw(10) << setprecision(2) << fixed << right << p[I[i]].matem << " ";
		switch (p[I[i]].student)
		{
		   case KN:
			  fout << "| " << setw(13) << setprecision(2) << fixed << right << p[I[i]].progr << " |" << setw(18) << right << "|" << setw(14) << right << "| ";
			  break;
		   case IT:
			  fout << "| " << setw(15) << " |" << setw(16) << setprecision(2) << fixed << right << p[I[i]].numbm << " |" << setw(14) << right << "| ";
			  break;
		   case ME:
			  fout << "| " << setw(15) << right << "|" << " " << setw(17) << right << "|" << " " << setw(10) << right << p[I[i]].pedag << " | ";
			  break;
		   case FI:
			  fout << "| " << setw(15) << right << "|" << " " << setw(17) << right << "|" << " " << setw(10) << right << p[I[i]].pedag << " | ";
			  break;
		   case TN:
			  fout << "| " << setw(15) << right << "|" << " " << setw(17) << right << "|" << " " << setw(10) << right << p[I[i]].pedag << " | ";
			  break;
		}
		fout << setw(12) << setprecision(2) << fixed << right << p[I[i]].serbl << " | " << endl;
	}
	fout << "===============================================================================================================================" << endl;
	fout << endl;
}

int BinSearch(Specialist* p, const int N, const string iprizv, const Student student, const int icourse) {
	
	int L = 0, R = N - 1, m;
	do 
	{
		m = (L + R) / 2;
		if (p[m].prizv == iprizv && p[m].student == student && p[m].course == icourse)
		   return m;
		if ((p[m].student < student) ||
			(p[m].student == student &&
			 p[m].prizv > iprizv) ||
			(p[m].student == student &&
			 p[m].prizv == iprizv &&
			 p[m].course < icourse))
		{
		   L = m + 1;
		}
		else
		{
		   R = m - 1;
		}
	} while (L <= R);
	return -1;
}

void Sort(Specialist* p, const int N)
{
	Specialist tmp;
	for (int i0 = 0; i0 < N - 1; i0++) 
		for (int i1 = 0; i1 < N - i0 - 1; i1++)
			if ((p[i1].student > p[i1 + 1].student) ||
				(p[i1].student == p[i1 + 1].student &&
				 p[i1].prizv > p[i1 + 1].prizv) ||
				(p[i1].student == p[i1 + 1].student &&
				 p[i1].prizv == p[i1 + 1].prizv &&
				 p[i1].course > p[i1 + 1].course))
			{
			   tmp = p[i1];
			   p[i1] = p[i1 + 1];
			   p[i1 + 1] = tmp;
			}
}