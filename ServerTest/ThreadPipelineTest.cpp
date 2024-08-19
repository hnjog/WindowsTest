#include <iostream>
#include<thread>
#include<vector>
#include<Windows.h>

using namespace std;

int x = 0;
int y = 0;
int r1 = 0;
int r2 = 0;
bool ready = false;

// volatile : 컴파일러의 최적화를 거부하는 키워드
// 멀티스레드 환경에서 고려

void Thread_1()
{
	while (ready == false)
	{
	}

	y = 1; // store y
	r1 = x; // Load x
}

void Thread_2()
{
	while (ready == false)
	{
	}

	x = 1; // store x
	r2 = y; // Load y
}

int main()
{
	int count = 0;
	while (true)
	{
		count++;

		x = y = r1 = r2 = 0;

		thread t1(Thread_1);
		thread t2(Thread_2);

		ready = true;

		t1.join();
		t2.join();

		// 원래라면 탈출 불가능
		// 그러나 컴파일러의 최적화에 따라
		// 탈출할 수 있음
		if (r1 == 0 && r2 == 0)
			break;
	}

	cout << count << endl;
}