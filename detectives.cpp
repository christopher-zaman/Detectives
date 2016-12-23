#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class Detective
{
public:
	string Name;
	string Specialty;
	int Experience;
};

void AddNewRecord(Detective detectives[], int &count)
{
	string name;
	cout << "Enter Detective Name: ";
	cin >> name;

	for (int i = 0; i < count; i++)
	{
		if (detectives[i].Name == name)
		{
			cout << "There is already a detective with this name!" << endl;
			return;
		}
	}

	string specialty;
	cout << "Enter Detective Specialy: ";
	cin >> specialty;

	int expr;
	cout << "Enter Detective Experience: ";
	cin >> expr;

	detectives[count].Name = name;
	detectives[count].Specialty = specialty;
	detectives[count].Experience = expr;

	count++;
}

void Search(Detective detectives[], int &count)
{
	string specialty;
	cout << "Enter Detective Specialy: ";
	cin >> specialty;

	int expr;
	cout << "Enter Detective Experience: ";
	cin >> expr;

	int index = -1;

	// go through each detective in the array
	for (int i = 0; i < count; i++)
	{
		// if the detective's specilty and experience matches the criteria
		if (detectives[i].Specialty == specialty && detectives[i].Experience >= expr)
		{
			// see if this is the first detective matching the criteria
			// notice that index is initialized to -1 above
			if (index == -1)
				index = i;
			// if this is not the first detective
			// then check if the experience of this dective is 
			// more than the dectective we had found earlier
			else if (detectives[i].Experience > detectives[index].Experience)
				index = i; // if so, take this detective as the pivot
		}
	}

	// once all searching is over. 
	// lets see the value of index
	// if the value of index stayed as -1,
	// that means we could not find any dective.
	// if it is not -1, that means 
	// it points to the detective we found
	if (index == -1)
		cout << "Could not find any detective!" << endl;
	else
		cout << "Here is the detective: " << detectives[index].Name << endl;
}

void LoadData(Detective detectives[], int &count)
{
	ifstream input("C:\\Users\\christopherzaman\\Desktop\\detectives.txt");

	count = 0;

	while (!input.eof())
	{
		input >> detectives[count].Name;
		input >> detectives[count].Specialty;
		input >> detectives[count].Experience;
		count++;
	}
}

void SaveData(Detective detectives[], int count)
{
	ofstream output("data.txt");

	for (int i = 0; i < count; i++)
	{
		output << detectives[i].Name << " ";
		output << detectives[i].Specialty << " ";
		output << detectives[i].Experience;
		if (i != count - 1)
			output << endl;
	}
}

void ReportBySpecialty(Detective detectives[], int &count, string specialty)
{
	cout << endl;
	cout << specialty << endl;
	cout << "===========================" << endl;

	for (int i = 0; i < count; i++)
	{
		if (detectives[i].Specialty == specialty)
		{
			cout << detectives[i].Name << " ";
			cout << detectives[i].Specialty << " ";
			cout << detectives[i].Experience << endl;
		}
	}
	cout << endl;
}

void Report(Detective detectives[], int &count)
{
	ReportBySpecialty(detectives, count, "Homicide");
	ReportBySpecialty(detectives, count, "Fraud");
	ReportBySpecialty(detectives, count, "Theft");
	ReportBySpecialty(detectives, count, "Gangs");
	ReportBySpecialty(detectives, count, "Traffic");
}

int main()
{
	Detective detectives[1000];
	int count;

	LoadData(detectives, count);

	while (true)
	{
		cout << "1- Add New Record" << endl;
		cout << "2- Search" << endl;
		cout << "3- Report" << endl;
		cout << "0- Exit" << endl;
		int choice;
		cout << "What now?" << endl;
		cin >> choice;

		if (choice == 3)
			Report(detectives, count);

		if (choice == 2)
			Search(detectives, count);

		if (choice == 1)
			AddNewRecord(detectives, count);

		if (choice == 0)
			break;
	}

	SaveData(detectives, count);

	system("PAUSE");
	return 0;
}