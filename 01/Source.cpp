#include <stdio.h>
#include <iostream>
#include <vector>
#include <cmath>
#include "numbers.dat"


using namespace std;

const int Simple317[66] =
{ 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73,
79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163,
167, 173, 179, 181, 191, 193, 197, 199, 211, 223, 227, 229, 233, 239, 241, 251,
257, 263, 269, 271, 277, 281, 283, 293, 307, 311, 313, 317}; 
//Ускорение работы за счет прегенерации простых чисел [0, sqrt(100000)] 
//Используется для перебора делителей, ускорение работы за счет отброса составных делителей.

void SearchArray(int head, int tail); //Поиск подмассива в массиве по значениям [head, tail]
bool CheckSimple(int n); //Проверка простоты числа (метод перебора простых делителей до sqrt[n])
int GetUpperSimple(int n); //Получение индекса максимального простого делителя n из Simple317

int main(int argc, char* argv[])
{
	if (argc % 2 == 0||argc==1) //Проверяем корректность ввода
	{
		return -1;//Возврат ошибки
	}

	int head, tail; //Значения начала и конца подмассива поиска, -1 если неизвестны.
	head = tail = -1;

	for (int i = 1; i < argc; ++i) //Получаем аргументы
	{
		if (head == -1) //Проверяем наличие начала подмассива
		{
			head= std::atoi(argv[i]); //При отсутствии полученный элемент - голова
		}
		else
		{
			tail = std::atoi(argv[i]); //Иначе это хвост

			if (head <= tail)//Проверка начало <=конец
			{
				SearchArray(head, tail);
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

void SearchArray(int head, int tail)
{
	int count = 0; //Количество найденных простых чисел
	bool flag = false; //Флаг нахождения внутри подмассива

	for (int i = 0; i < Size; i++)
	{
		if (Data[i] < head) //Не дошли до начала подмассива
		{
			continue;
		}
		else if (Data[i] == head) //Проверяем элементы совпадающие с начальным
		{
			flag = true;
			if (CheckSimple(Data[i]))
			{
				count++;
			}
		}
		else if (Data[i] == tail && flag)//Проверяем элементы совпадающие с конечным
		{
			if (CheckSimple(Data[i]))
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
			if (CheckSimple(Data[i]))
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
	cout << count <<"\n"; //Вывод количества простых чисел в подмассиве
};

bool CheckSimple(int n)
{
	if (n == 2) //алгоритм не захватывает 2
	{
		return true;
	}
	int upperSimple = GetUpperSimple(n); //Получаем индекс из массива простых
	for (int i = 0; i <= upperSimple; i++)
	{
		if (n%Simple317[i] == 0||n==1) //Проверяем делимость на простые числа, избавляемся от 1
		{
			return false; //Если делится - число не простое
		}
	}
	return true; //Иначе - простое
}

int GetUpperSimple(int n)
{
	for (int i = 0; i < 66; i++)
	{
		if (Simple317[i] > sqrt(n))
		{
			return i;
		}
	}
	return 65;
}