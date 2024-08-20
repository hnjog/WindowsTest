#include <iostream>
#include<thread>
#include<vector>
#include<Windows.h>
#include<atomic>
#include<mutex>

using namespace std;

class Lock
{
public:
	void lock()
	{
		// 이게 결국 2개로 나뉘기에
		// 동시에 2개의 thread로 나뉠 수 있음
		// 이 방식으로는 lock 걸기 힘듦
		//while (_flag)
		//{
		//	// 누가 lock 가져갔네?
		//}

		//_flag = true;

		bool expected = false;
		bool desired = true;

		/*if (_flag == expected)
		{
			_flag = desired;
			return true;
		}
		else
		{
			expected = _flag;
			return false;
		}*/

		// CAS(Compare-And-Swap)
		// 위의 의사코드를 어셈블리어로 한번에 해주는 함수
		while (_flag.compare_exchange_strong(expected , desired) == false)
		{
			// expected가 OUT되서 값이 바뀌기에
			// 다시 대입
			expected = false;
		}

		// SpinLock?
		// 임계영역에 진입하지 못했을 때,
		// 다른 스레드가 하는 행동??
		// - 무한루프를 돌며 기다린다...
		// 
		//

	}

	void unlock()
	{
		_flag = false;
	}

private:
	atomic<bool> _flag = false;
};

// 상호베타적
Lock m;

vector<int> v;

void Push()
{
	for (int i = 0; i < 10000; i++)
	{
		std::lock_guard<Lock> lockGuard(m);

		v.push_back(i);
	}
}

int main()
{
	v.reserve(100000);

	thread t1(Push);
	thread t2(Push);

	t1.join();
	t2.join();

	cout << v.size() << endl;
}