/*
	I am using CircularLinkedList (my own) with iterators and some helping functions to solve this problem.
	First of all I read data (names of people) from file in CircularLinkedList. (I used names instead of numbers to show people).
	Then ask user for starting name. 
	Then ask user for how many person not to kill. (I suppose that in number of perople not to kill, the current person is also included).
	Then call Game function.
	Algorithm to solve this problem:
		- store staring perosn (iterator) in an other variable.
		- jump to next person by skiping  PersonsNotToKill number of people by adding that number (PersonsNotToKill) to iterator StaringPerson. (+ operator is overloaded in iterator class which will jump N times) ::N = value added to iterator i.e itertor + value;
		- Print who is killing whome
		- store the next iterator in an onther variable.
		- decrement in current iterator (which is at that time next) to come back to current node.
		- Delete the current iterator by using delete function. (CircularLinkedList::Delete(iterator) is a function implemented in Circular linked list class which takes iterator as parameter and delete that node)
		- Store next of iterator to current iterator.
		- repeat these steps untill the size of circular linked list become one (1);
		-That one person is winner.


*/
#include<iostream>
#include<string>
#include<fstream>
#include"CircularLinkedList.h"

using namespace std;

bool CompareStrings(string a, string b) //Compare two strings and return true if equal
{
	if (a.size() != b.size())
		return false;
	for (int i = 0; i < a.size(); i++)
	{
		if (a[i] != b[i])
			return false;
	}
	return true;
} 

struct Pair // To store a booleon value and and iterator of circular linked list
{
	bool isFind;
	CircularLinkedList<string>::iterator<string> it;
	Pair()
	{

	}
	void operator = (const Pair &P)
	{
		isFind = P.isFind;
		it = P.it;
	}
};

bool ReadFile(CircularLinkedList<string> &Names, string FileName, unsigned int NamesToRead) //Reads data (names of people from file) Make sure that file contains atleast NamesToRead number of people. 
{
	ifstream fin(FileName);
	string tmp;
	while (getline(fin, tmp) && NamesToRead > 0)
	{
		Names.InsertAtTail(tmp);
		NamesToRead--;
	}
	if (NamesToRead > 0)
		return false;
	else
		return true;
	fin.close();
}

template<typename T>
Pair isPresentInList(CircularLinkedList<T> &L, const T Element) //Check that is ap particular element present in list and return it's position (iterator)
{
	Pair Output;
	Output.isFind = false;
	auto li = L.begin();
	string name;
	for (int i = 0; i < L.SIZE(); i++,li++)
	{
		name = *li;
		if (CompareStrings(Element, name))
		{
			Output.it = li;
			Output.isFind = true;
			break;
		}
	}
	return Output;
}

void Game(unsigned int NoOfPeoples, CircularLinkedList<string>::iterator<string> StartingPerson, unsigned int PersonNotToKilled, CircularLinkedList<string> &People)
{
	cout << endl;
	while (People.SIZE() != 1)
	{
		auto killer = StartingPerson;
		StartingPerson = StartingPerson + (PersonNotToKilled);
		cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << endl;
		cout <<"\t\t"<< *killer << " killed " << *StartingPerson << endl;
		auto next = ++StartingPerson;
		StartingPerson--;
		People.Delete(StartingPerson);
		StartingPerson = next;
	}
	cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << endl << endl;

	cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
	cout << "\t\tWinner: " << *StartingPerson << endl;
	cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
}

void Play(string FileName)
{
	CircularLinkedList<string> People;
	unsigned int NoOfPeoples = { 0 };
	string StartingPerson = { '\0' };
	unsigned int PersonNotToKilled = { 0 };

	cout << "--------------------------------------------------------" << endl;
	cout << "  The number of people standing in the circle are : ";    //Make sure that file contains atleast NoOfPeoples number of people name in file. 
	cin >> NoOfPeoples;
	ReadFile(People, FileName, NoOfPeoples);
	Pair IsFind;
	do
	{
		cout << "--------------------------------------------------------" << endl;
		cout << "\t    The starting person is: ";
		cin >> StartingPerson;
		cout << "--------------------------------------------------------" << endl;
		IsFind = isPresentInList(People, StartingPerson);
	} while (!IsFind.isFind);

	cout << "  How many persons are NOT to be killed starting from \n \t\t the initial person: ";
	cin >> PersonNotToKilled;
	cout << "--------------------------------------------------------" << endl;
	Game(NoOfPeoples, IsFind.it, PersonNotToKilled, People);
}

void menu()
{
	unsigned int key;
	string FileName;
	bool x = true;
	do
	{
		cout << "########################################################" << endl;
		cout << "\t\tPress 1 to Start the Game" << endl;
		cout << "\t\tPress 2 to Exit the Game" << endl;
		cout << "########################################################" << endl;
		cout << "\t\t      Press Key: ";
		cin >> key;
		switch (key)
		{
		case 1:
			cout << "\t\t Enter File Name: ";
			cin >> FileName;
			cout << endl;
			Play("Data.txt");
			break;
		case 2:
			x = false;
		default:
			break;
		}
	} while (x);
}
int main()
{
	menu();
	return 0;
}