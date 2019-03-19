#include <stdio.h>
#include <iostream>
#include <vector>
#include <cmath>
#include "numbers.dat"

using namespace std;

void SearchArray(int head, int tail, vector<int> &simple);
void Seive(vector<int> &simple);

const int Max = 100000;

int main(int argc, char* argv[])
{
	if (argc % 2 == 0 || argc == 1) //Проверяем корректность ввода
	{
		return -1;//Возврат ошибки
	}

	vector<int> simple; //Найденные простые числа

	Seive(simple);

	int head, tail; //Значения начала и конца подмассива поиска, -1 если неизвестны.
	head = tail = -1;

	for (int i = 1; i < argc; ++i) //Получаем аргументы
	{
		if (head == -1) //Проверяем наличие начала подмассива
		{
			head = std::atoi(argv[i]); //При отсутствии полученный элемент - голова
		}
		else
		{
			tail = std::atoi(argv[i]); //Иначе это хвост

			if (head <= tail)//Проверка начало <=конец
			{
				SearchArray(head, tail, simple);
			}
			else
			{
				cout << 0;
			}

			head = tail = -1; //Возвращение значений по умолчанию
		}
	}

	return 0;
}

void SearchArray(int head, int tail, vector<int> &simple)
{
	int count = 0; //Количество найденных простых чисел
	bool flag = false; //Флаг нахождения внутри подмассива

	for (int i = 0, j = 0; i < Size; i++)
	{
		while (Data[i] > simple[j] && j < simple.size() - 1) //Получаем >= простое число.
		{
			j++;
		}
		if (Data[i] < head) //Не дошли до начала подмассива
		{
			continue;
		}
		else if (Data[i] == head) //Проверяем элементы совпадающие с начальным
		{
			flag = true;
			if (Data[i] == simple[j])
			{
				count++;
			}
		}
		else if (Data[i] == tail && flag)//Проверяем элементы совпадающие с конечным
		{
			if (Data[i] == simple[j])
			{
				count++;
			}
		}
		else if (Data[i] > tail && flag) //Закрываем флаг с концом подмассива
		{
			flag = false;
		}
		else if (flag) //Проверяем элементы внутри подмассива
		{
			if (Data[i] == simple[j])
			{
				count++;
			}
		}
		else //Отбрасываем элементы после конечного или при отсутствии элементов
		{
			if (flag) //Если прошли подмассив и флаг не закрыт, то конечного элемента нет
			{
				count = 0;
			}
			flag = false;
			break;
		}
	}
	cout << count << "\n"; //Вывод количества простых чисел в подмассиве
};

void Seive(vector<int> &simple)
{
	int div[Max + 1]; //Минимальные простые делители
	memset(div, 0, (Max + 1) * sizeof(int));
	for (int i = 2; i <= Max; ++i) //Строим решето Эратосфена за линейное время
	{
		if (div[i] == 0)
		{
			div[i] = i;
			simple.push_back(i);
		}
		for (int j = 0; j < (int)simple.size() && simple[j] <= div[i] && i * simple[j] <= Max; ++j)
		{
			div[i*simple[j]] = simple[j];
		}
	}
};

