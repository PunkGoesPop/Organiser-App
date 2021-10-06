
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

//Проверка на существование элемента в списке дел
bool isFound (vector<vector<string>>& vec, int& day, string& duty)
{
	bool found = false;
	for (auto& i : vec[day - 1])
	{
		if (duty == i)
			found = true;
	}
	return found;
}

int main()
{
	vector <int> days_in_months = { 31, 28, 31, 30, 31, 30 ,31, 31, 30, 31, 30, 31 };
	vector <vector<string>> tasks (31);

	int q = 0;
	cin >> q;
	int month = 0;

	for (int i = 0; i < q; i++)
	{
		string operation;
		cin >> operation;
		int day = 0;
		
		if (operation == "ADD")
		{
			string duty;
			cin >> day >> duty;
			//Если день пуст на дела
			if (tasks[day - 1].size() == 0)
			{
				tasks[day - 1].push_back(duty);
			}
			else
			{
				//Проверка на уже существующие дело в списке
				bool is_found = isFound(tasks, day, duty);

				if(!(is_found))
					tasks[day - 1].push_back(duty);		
			}
		}
		if (operation == "DUMP")
		{
			cin >> day;
			cout << tasks[day - 1].size();
			for (auto& i : tasks[day - 1])
			{
				cout << " " << i;
			}
			cout<<endl;
		}
		if (operation == "NEXT")
		{
			++month;
			if (month == 12)
				month = 0;
			//Февраль
			if (!(days_in_months[month] % 2) && month == 1 && month != 12)
			{
				vector<string> temp;
				temp.insert(temp.end(), tasks[days_in_months[month]].begin(), tasks[days_in_months[month]].end());
				temp.insert(temp.end(), tasks[days_in_months[month] + 1].begin(), tasks[days_in_months[month] + 1].end());
				temp.insert(temp.end(), tasks[days_in_months[month] + 2].begin(), tasks[days_in_months[month] + 2].end());
				tasks.resize(days_in_months[month]);

				for (auto& i : temp)
				{
					bool is_found = isFound(tasks, days_in_months[month], i);

					if (!(is_found))
						tasks[days_in_months[month] - 1].push_back(i);
				}	
				/*cout << days_in_months[month] << ": days, month is " << month + 1 << " VEC SIZE: " << tasks.size() << endl;*/
			}
			//30 дней в месяце
			else if (!(days_in_months[month] % 2) && month != 12)
			{
				vector<string> temp;
				temp.insert(temp.end(), tasks[days_in_months[month]].begin(), tasks[days_in_months[month]].end());
				tasks.resize(days_in_months[month]);

				for (auto& i : temp)
				{
					bool is_found = isFound(tasks, days_in_months[month], i);

					if (!(is_found))
						tasks[days_in_months[month] - 1].push_back(i);
				}
				
			}
			//31 дней в месяце
			else if (days_in_months[month] % 2 && month != 12)
			{
				tasks.resize(days_in_months[month]);
				
			}
		}
	}
}




