#include <iostream>
#include<thread>
#include<vector>
#include<Windows.h>

using namespace std;

int buffer[10000][10000];

int main()
{
	memset(buffer, 0, sizeof(buffer));

	{
		auto start = GetTickCount64();

		_int64 sum = 0;

		for (int i = 0; i < 10000; i++)
			for (int j = 0; j < 10000; j++)
				sum += buffer[i][j];

		auto end = GetTickCount64();

		cout << "Elapsed Tick : " << (end - start) << endl;
	}

	{
		auto start = GetTickCount64();

		_int64 sum = 0;

		// 이 방식은 기존 인덱스 접근과는 다르고
		// 띄엄띄엄 위치를 찾기에
		// 캐시 친화적이지 않은 인덱스 접근임
		for (int i = 0; i < 10000; i++)
			for (int j = 0; j < 10000; j++)
				sum += buffer[j][i]; 

		auto end = GetTickCount64();

		cout << "Elapsed Tick : " << (end - start) << endl;
	}
}