#include <iostream>
#include<thread>
#include<vector>
#include<Windows.h>
#include<atomic>
#include<mutex>

using namespace std;

// 상호베타적
mutex m;

vector<int> v;

// RAII (Resource Acquisition Is Initalization)

// 일종의 간단한 래핑 클래스
template<typename T>
class LockGuard
{
public:
	LockGuard(T& m)
		:_mutex(m)
	{
		_mutex.lock();
	}

	~LockGuard()
	{
		_mutex.unlock();
	}

private:
	T& _mutex;
};

void Push()
{
	for (int i = 0; i < 10000; i++)
	{
		// 누군가 사용중이면 대기
		// 상호 베타적인 공간을 만들어줌
		
		// 중간에 break 당해도 빠트리지 않도록
		//LockGuard<mutex> LockGuard(m);

		// 표준
		//std::lock_guard<mutex> lockGuard(m);

		// 비슷하지만 추가적인 기능
		// 바로 잠그지 않고 lock을 호출하도록 옵션 줄 수 있음
		std::unique_lock<mutex> uniqueLock(m, std::defer_lock);

		// 이때 잠금
		uniqueLock.lock();

		v.push_back(i);

		if (i == 5000)
			break;
	}
}

int main()
{
	// atomic은 특정한 '변수'하나만을 멀티스레드 환경에서 '보장'하는 방식
	// 모든 변수에 atomic을 사용하는 것은...
	// 그렇기에 세마포어와 mutex 같은 동기화 기법을 이용하여
	// 임계영역(critical section)을 구현한다
	//

	// vector는 동적 배열이기에
	// heap에서 관리함
	// size 넘어버리면 새로운 공간을 찾아 할당하기에
	// thread가 잘못된 위치를 접근할 가능성이 있음
	// (reserve 를 사용하면 크래시가 안나올 가능성은 있음)
	// 
	// 그래도 하나의 주소에 동시에 접근하여 값을 쓰려고 하니
	// 정상적으로 적용되지 않고 '덮어쓸' 가능성이 존재함
	// 
	// STL 컨테이너들은 멀티스레드에서 비슷한 위험을 가진다
	// 
	//

	v.reserve(100000);

	thread t1(Push);
	thread t2(Push);
	thread t3(Push);

	t1.join();
	t2.join();
	t3.join();

	
	cout << v.size() << endl;

}