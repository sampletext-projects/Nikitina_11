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


void gen_files(string& directory, int n)
{
	_mkdir(directory.c_str());
	for (int i = 0; i < n; i++)
	{
		ofstream f(directory + "n" + to_string(i + 1) + ".txt");
		for (int j = 0; j < 24; j++)
		{
			//генерация давления от 0.3 до 6 бар
			f << rand() % 57 / 10. + 0.3 << " ";
		}
		cout << "Сгенерирован " << i + 1 << "/" << n << " файлов\n";
		f.close();
	}
}


double** read_datas(string& directory, int n)
{
	double** datas = new double*[n];

	for (int i = 0; i < n; i++)
	{
		ifstream f(directory + "n" + to_string(i + 1) + ".txt");
		f.peek();
		if (!f.good())
		{
			return nullptr;
		}
		double* data = new double[24];
		for (int j = 0; j < 24; ++j)
		{
			f >> data[j];
		}
		f.close();
		datas[i] = data;

		cout << "Считано " << i + 1 << "/" << n << " файлов\n";
		f.close();
	}
	return datas;
}

int main()
{
	setlocale(LC_ALL, "russian");
	cout << "Автор: Никитина Дарья Сергеевна\n";

	string directory = "data/";

	int n;
	cout << "Введите количество датчиков: ";
	cin >> n;

	int k;
	cout << "Введите команду (1 - генерация, 2 анализ): ";
	cin >> k;

	if (k == 1)
	{
		gen_files(directory, n);
	}
	else if (k == 2)
	{
		double** datas = read_datas(directory, n);
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
