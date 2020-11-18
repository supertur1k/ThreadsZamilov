#include <iostream>
#include <list>
#include <thread>
#include <mutex>
#include <algorithm>

using namespace std;

/*
*   Замилов Артур Рафаэлович БПИ193
*	
*   Вычислить прямое произведение множеств А1, А2, А3, А4. Входные
*   данные: множества чисел А1, А2, А3, А4, мощности множеств могут быть не
*   равны между собой и мощность каждого множества больше или равна 1.
*   Количество потоков является входным параметром.
*
*/

// Мощности множеств
int setLength1, setLength2, setLength3, setLength4;

// Множества
int *A1, *A2, *A3, *A4;

// Основной метод вычисления декартового произведения
void DoWork(int begin, int end, list<int*>& multiply)
{
	for (int i = begin; i < end; i++)
	{
		for (int j = 0; j < setLength2; j++)
		{
			for (int k = 0; k < setLength3; k++)
			{
				for (int m = 0; m < setLength4; m++)
				{
					int* multiplyFoo = new int[4];
					multiplyFoo[0] = A1[i];
					multiplyFoo[1] = A2[j];
					multiplyFoo[2] = A3[k];
					multiplyFoo[3] = A4[m];
					multiply.push_back(multiplyFoo);
				}
			}
		}
	}
}

mutex mtx;

int main()
{
	// Для русского языка
	setlocale(LC_ALL, "ru");
	// Кол-во потоков
	int threadsCounter;
	cout << "Введите кол-во потоков: " << endl;
	cin >> threadsCounter;
	if (threadsCounter < 1)
	{
		cout << "Некорректный ввод." << endl;
		return 0;
	}

	// Ввод мощностей 4 множеств
	cout << "Введите количество элементов первого множества: " << endl;
	cin >> setLength1;
	if (setLength1 < 1)
	{
		cout << "Некорректный ввод." << endl;
		return 0;
	}
	cout << "Введите количество элементов второго множества: " << endl;
	cin >> setLength2;
	if (setLength2 < 1)
	{
		cout << "Некорректный ввод." << endl;
		return 0;
	}
	cout << "Введите количество элементов третьего множества: " << endl;
	cin >> setLength3;
	if (setLength3 < 1)
	{
		cout << "Некорректный ввод." << endl;
		return 0;
	}
	cout << "Введите количество элементов четвертого множества: " << endl;
	cin >> setLength4;
	if (setLength4 < 1)
	{
		cout << "Некорректный ввод." << endl;
		return 0;
	}

	// Инициализация множеств
	A1 = new int[setLength1];
	A2 = new int[setLength2];
	A3 = new int[setLength3];
	A4 = new int[setLength4];
	for (size_t i = 0; i < setLength1; i++)
	{
		A1[i] = i;
	}
	for (size_t i = 0; i < setLength2; i++)
	{
		A2[i] = i;
	}
	for (size_t i = 0; i < setLength3; i++)
	{
		A3[i] = i;
	}
	for (size_t i = 0; i < setLength4; i++)
	{
		A4[i] = i;
	}

	// По скольку разбиваем по первому множеству, число потоков не может приувеличивать его мощность
	if (setLength1 < threadsCounter) threadsCounter = setLength1;
	int period = setLength1 / threadsCounter;

	// Разбиваем умножения по кол-ву потоков
	list<int*> *multiply = new list<int*>[threadsCounter];
	thread* threads = new thread[threadsCounter];

	int begin = 0;
	int end;

	for (int i = 0; i < threadsCounter; i++)
	{
		if (i == threadsCounter - 1)
		{
			end = setLength1;
		}

		else
		{
			end = begin + period;
		}

		multiply[i] = list<int*>();

		mtx.lock();
		threads[i] = thread(DoWork, begin, end, ref(multiply[i]));
		mtx.unlock();

		begin = end;
	}

	// Дожидаемся выполнения всех потоков
	for (int i = 0; i < threadsCounter; i++)
	{
		threads[i].join();
	}

	// Собираем перемножения распределенные среди первого множества по потокам во едино.
	list<int*> multiplyFinal;
	for (int i = 0; i < threadsCounter; i++)
	{
		multiplyFinal.insert(multiplyFinal.end(), multiply[i].begin(), multiply[i].end());
	}

	for (auto i = multiplyFinal.begin(); i != multiplyFinal.end(); i++)
	{
		cout << (*i)[0] << "\t" << (*i)[1] << "\t" << (*i)[2] << "\t" << (*i)[3] << endl;
	}

	delete[] A1;
	delete[] A2;
	delete[] A3;
	delete[] A4;
	delete[] multiply;
	delete[] threads;
}



/*
#include <iostream>
// Библиотека для работы с потоками
#include <thread>
// Библиотека для работы со временем
#include <chrono>
// Библиотека для защиты потоков
#include <mutex>
#include <list>
#include <map>
#include <set>
#include <vector>

using namespace std;

/*
*   Замилов Артур Рафаэлович БПИ193
*
*   Вычислить прямое произведение множеств А1, А2, А3, А4. Входные
*   данные: множества чисел А1, А2, А3, А4, мощности множеств могут быть не
*   равны между собой и мощность каждого множества больше или равна 1.
*   Количество потоков является входным параметром.
*
/

void DoWork()
{
    for (int i = 0; i < 10; i++)
    {
        cout << "ID: " << this_thread::get_id() << " DoWork " << i << endl;
        this_thread::sleep_for(chrono::milliseconds(1000));
    }
}

void getMultiply(multiset<int> A1, multiset<int> A2, multiset<int> A3, multiset<int> A4) {
    for (int i = 0; i < A1.size; i++) {
        for (int j = 0;)
    }
}
int main()
{
    setlocale(LC_ALL, "ru");

    // Кол-во потоков
    int threadsCounter;
    cout << "Введите кол-во потоков: " << endl;
    cin >> threadsCounter;

    // Словарь пар прямого произведения
    map <int, int> numbers;
    
    multiset<int> A1;
    multiset<int> A2;
    multiset<int> A3;
    multiset<int> A4;
    
    int n, a;
    cout << "Введите мощность первого множества: " << endl;
    cin >> n;
    cout << "Введите первое множество: " << endl;
    for (int i = 0;  i < n;  i++)
    {
        cin >> a;
        A1.insert(a);
    }

    cout << "Введите мощность второго множества: " << endl;
    cin >> n;
    cout << "Введите второе множество: " << endl;
    for (int i = 0; i < n; i++)
    {
        cin >> a;
        A1.insert(a);
    }

    cout << "Введите мощность третьего множества: " << endl;
    cin >> n;
    cout << "Введите третье множество: " << endl;
    for (int i = 0; i < n; i++)
    {
        cin >> a;
        A1.insert(a);
    }

    cout << "Введите мощность четвертого множества: " << endl;
    cin >> n;
    cout << "Введите четвертое множество: " << endl;
    for (int i = 0; i < n; i++)
    {
        cin >> a;
        A1.insert(a);
    }
    vector<std::thread> tv;
    for (int i = 1; i <= threadsCounter; ++i) {
        tv.push_back(std::thread(stream, i));
    }
    thread th(DoWork);
    
    for (int i = 0; i < 10; i++)
    {
        cout << "ID: " << this_thread::get_id() << " main " << i << endl;
        this_thread::sleep_for(chrono::milliseconds(500));
    }
    th.join();
    return 0;
}
*/