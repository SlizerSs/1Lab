#include <iostream>
#include <fstream>
using namespace std;

struct List
{
	int number;
	List* next;
};

int isEmpty(List*);
void insert(List*&, int);
int del(List*&, int);
void printList(List*);
void sum_positive_elements(List*);
void search(List*, int);
void toFile(List*&);
void fromFile(List*&);


int choise;

int main()
{
	setlocale(LC_ALL, "ru");
	cout << "0 - сумма положительных элементов" << endl;
	cout << "1 - Добавление элемента в список" << endl;
	cout << "2 - удаление элемента из списка " << endl;
	cout << "3 - поиск элемента в списке" << endl;
	cout << "4 - вывод списка в консольное окно" << endl;
	cout << "5 - запись списка в файл" << endl;
	cout << "6 - считывание списка из файла" << endl;
	cout << "7 - выход" << endl;
	cout << "Введите: ";
	cin >> choise;

	List* first = NULL;
	int add_number_in_list;
	int delete_number_from_list;
	int find_number;

	while (choise != 7)
	{
		switch (choise)
		{
		case 0:
			cout << "___________________________________" << endl;
			sum_positive_elements(first);
			break;
		case 1:
			cout << "____________________________________" << endl;
			cout << "Введите число которое надо добавить: ";
			cin >> add_number_in_list;
			insert(first, add_number_in_list);
			break;
		case 2:
			cout << "_________________________________" << endl;
			if (!isEmpty(first))
			{
				cout << "Введите удаляемое число: ";
				cin >> delete_number_from_list;
				if (del(first, delete_number_from_list))
				{
					cout << "Удалено число( " << delete_number_from_list << " ) из списка" << endl;
				}
				else
				{
					cout << "Введенное вами число( " << delete_number_from_list << " ) не найдено" << endl;
				}
			}
			else
			{
				cout << "Список пуст!" << endl;
			}
			break;
		case 3:
			cout << "____________________________________" << endl;
			cout << "Введите число которое надо найти: ";
			cin >> find_number;
			search(first, find_number);
			break;
		case 4:
			cout << "___________________________________" << endl;
			printList(first);
			break;
		case 5:
			cout << "_________________________________" << endl;
			toFile(first);
			break;
		case 6:
			cout << "___________________________________" << endl;
			fromFile(first);
			break;
		default:
			cout << "Неправильный выбор!" << endl;
			break;
		}
		cout << endl << "Что дальше ? ";
		cin >> choise;
	}
	cout << "Конец" << endl;
	return 0;
}

void insert(List*& pointer, int add_number_in_list)
{
	List* new_pointer = new List;

	if (new_pointer != NULL)
	{
		new_pointer->number = add_number_in_list;
		new_pointer->next = pointer;
		pointer = new_pointer;
	}
	else
	{
		cout << "Невозможно добавить элемент!" << endl;
	}
}

void printList(List* pointer)
{
	if (pointer == NULL)
	{
		cout << "Список пуст!" << endl;
	}
	else
	{
		cout << "Ваш список:  ";
		while (pointer != NULL)
		{
			cout << pointer->number << " --> ";
			pointer = pointer->next;
		}
		cout << " --> NULL" << endl;
	}
}

int del(List*& pointer, int delete_number_from_list)
{
	List* previous_pointer, * current_pointer, * temporary_pointer;

	if (delete_number_from_list == pointer->number)
	{
		temporary_pointer = pointer;
		pointer = pointer->next;

		delete temporary_pointer;
		return delete_number_from_list;
	}
	else
	{
		previous_pointer = pointer;
		current_pointer = pointer->next;

		while (current_pointer != NULL && current_pointer->number != delete_number_from_list)
		{
			previous_pointer = current_pointer;
			current_pointer = current_pointer->next;
		}
		if (current_pointer != NULL)
		{
			temporary_pointer = current_pointer;
			previous_pointer->next = current_pointer->next;
			free(temporary_pointer);
			return delete_number_from_list;
		}
	}
	return 0;
}

int isEmpty(List* pointer)
{
	return pointer == NULL;
}

void sum_positive_elements(List* pointer)
{
	int sum = 0;

	if (pointer == NULL)
	{
		cout << "Список пуст!" << endl;
	}
	else
	{
		while (pointer != NULL)
		{
			if (pointer->number > 0)
			{
				sum = sum + (pointer->number);
			}
			pointer = pointer->next;
		}
		if (sum != 0)
		{
			cout << "Сумма положительных элементов: " << sum << endl;
		}
		else if (sum == 0)
		{
			cout << "Положительных элементов в спике нет!" << endl;
		}
	}
}

void search(List* pointer, int find_number)
{
	int check = 0;

	if (pointer == NULL)
	{
		cout << "Список пуст!" << endl;
	}
	else
	{
		while (pointer != NULL)
		{
			if (pointer->number == find_number)
			{
				cout << "Введенный вами элемент есть в спике!" << endl;
				check++;
			}
			pointer = pointer->next;
		}
		if (check == 0)
		{
			cout << "Введенного вами элемента в списке НЕТ!" << endl;
		}
	}
}

void toFile(List*& pointer)
{
	List* temporary = pointer;
	ofstream to_file("list_file.txt");

	if (to_file.fail())
	{
		cout << "Ошибка открытия файла!" << endl;
		exit(1);
	}
	while (temporary)
	{
		to_file << temporary->number << "  --> ";
		temporary = temporary->next;
	}
	to_file << " --> NULL";
	to_file.close();

	cout << "Список записан в файл list_file.txt" << endl;
}

void fromFile(List*& pointer)
{
	int temp;
	ifstream from_file("list_file_read.txt");

	if (from_file.fail())
	{
		cout << "Невозможно открыть файл!" << endl;
		exit(1);
	}

	for (int i = 0; i < 10; i++)
	{
		from_file >> temp;
		insert(pointer, temp);
	}
	from_file.close();
	cout << "Данные из файла list_file_read.txt успешно записаны в список!" << endl;
}