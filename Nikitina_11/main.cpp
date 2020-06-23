#include <iostream>//для cin cout
#include <fstream>//для ifstream/ofstream
#include <direct.h>
#include <iomanip>
#include <string>

using namespace std;

void write_mas(double* m, int size)
{
	for (int i = 0; i < size; i++)
	{
		cout << setw(4) << setprecision(2) << m[i] << " ";
	}
	cout << "\n";
}

double* remove_inaccuracy(double* data)
{
	double* fix = new double[24]{0};
	fix[0] = (data[23] + data[0] + data[1]) / 3;
	fix[23] = (data[22] + data[23] + data[0]) / 3;

	for (int i = 1; i < 23; ++i)
	{
		fix[i] = (data[i - 1] + data[i] + data[i + 1]) / 3;
	}
	return fix;
}


void gen_datas(string& file, int n)
{
	ofstream f(file);
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < 24; j++)
		{
			//генерация давления от 0.3 до 6 бар
			f << rand() % 57 / 10. + 0.3 << " ";
		}
		f << "\n";
		cout << "Сгенерировано " << i + 1 << "/" << n << " данных\n";
	}
	f.close();
}


double** read_datas(string& file, int n)
{
	ifstream f(file);
	f.peek();
	if (!f.good())
	{
		return nullptr;
	}

	double** datas = new double*[n];

	for (int i = 0; i < n; i++)
	{
		double* data = new double[24];
		for (int j = 0; j < 24; ++j)
		{
			f >> data[j];
		}
		datas[i] = data;

		cout << "Считано " << i + 1 << "/" << n << " данных\n";
	}
	f.close();
	return datas;
}

int main()
{
	setlocale(LC_ALL, "russian");
	cout << "Автор: Никитина Дарья Сергеевна\n";

	string file_name = "file.txt";

	int n;
	cout << "Введите количество датчиков: ";
	cin >> n;

	int k;
	cout << "Введите команду (1 - генерация, 2 анализ): ";
	cin >> k;

	if (k == 1)
	{
		gen_datas(file_name, n);
	}
	else if (k == 2)
	{
		double** datas = read_datas(file_name, n);
		if (datas == nullptr)
		{
			cout << "Возникла ошибка при считывании файлов!\nПроверьте их наличие и количество!\n";
		}
		else
		{
			for (int i = 0; i < n; ++i)
			{
				write_mas(datas[i], 24);
			}
			cout << "!Сглаживание!\n";
			for (int i = 0; i < n; ++i)
			{
				double* fixed = remove_inaccuracy(datas[i]);
				write_mas(fixed, 24);
				delete[] fixed;
			}
		}
	}
	else
	{
		cout << "Команда не распознана!\n";
	}

	system("pause");
	return 0;
}
