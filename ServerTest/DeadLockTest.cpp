#include <iostream>
#include<thread>
#include<vector>
#include<Windows.h>
#include<atomic>
#include<mutex>
#include<map>

using namespace std;

class User
{

};

class UserManager
{
public:
	User* GetUser(int id)
	{
		unique_lock<mutex> guard(_lock);

		if (_users.find(id) == _users.end())
		{
			return nullptr;
		}

		return _users[ id ];
	}

private:
	map<int , User*> _users;
	mutex _lock;
};

mutex m1;
mutex m2;

// DeadLock
// 기본적으론
// '락'을 가져간 후, '언락'을 하지 않아 발생하는 문제
// 
// wrapper 클래스를 사용함으로서 기본적인 휴먼 에러 등은 예방할 수 있음
//

void Thread_1()
{
	for (int i = 0; i < 10000; i++)
	{
		lock_guard<mutex> lockGuard1(m1); // scope를 이용하여 범위를 지정해줄 수도 있음 {} 
		lock_guard<mutex> lockGuard2(m2);
	}
}

void Thread_2()
{
	// 1 과는 다르게 lock을 얻는 순서가 반대임
	// m1을 다른 스레드가 가져가고
	// m2를 이 스레드가 가져간 상황이라면
	// 서로 다른 lock을 얻을때까지 무한정 대기함
	// 
	for (int i = 0; i < 10000; i++)
	{
		/*lock_guard<mutex> lockGuard2(m2);
		lock_guard<mutex> lockGuard1(m1);*/

		// 다시 순서를 바꿔주면 정상 실행
		// lock이 많아질 수록 버그가 발생할 가능성도 높아짐

		// 특정한 lock을 특정 주체가 잡도록 하도록 '설계'할 수 있으나
		// 결국 lock이 많아질 수록 관리가 힘듦
		// 데드락은 '예방'이 힘듦
		// 적은 케이스 에서는 문제가 없다가 라이브에 올라와서 문제가 발생하는 경우도 존재

		// 어찌보면 '그래프' 알고리즘과 비슷하다
		// 데드락을 '사이클'로 볼 수 있으므로
		//
		lock_guard<mutex> lockGuard1(m1);
		lock_guard<mutex> lockGuard2(m2);
	}
}

int main()
{
	thread t1(Thread_1);
	thread t2(Thread_2);

	t1.join();
	t2.join();

	cout << "Jobs Done";
}