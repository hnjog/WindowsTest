#include <iostream>
#include<thread>
#include<vector>
#include<Windows.h>
#include<atomic>
#include<mutex>
#include<map>
#include<queue>

using namespace std;

class RefCountable
{
public:
	RefCountable() {}
	virtual ~RefCountable() {}

	int GetRefCount() { return _refCount; }
	int AddRef() { return ++_refCount; }
	int ReleaseRef()
	{
		int refCount = --_refCount;
		if (refCount == 0)
		{
			delete this;
		}

		return refCount;
	}

	// 멀티스레드 환경에서 위험할 순 있음
protected:
	atomic<int> _refCount = 1;
};

template<typename T>
class TSharedPtr
{
public:
	TSharedPtr() {}
	TSharedPtr(T* ptr) { Set(ptr); }

	//복사
	TSharedPtr(const TSharedPtr& other) { Set(other._ptr); }

	// 이동
	TSharedPtr(TSharedPtr&& other) { _ptr = other._ptr; other._ptr = nullptr; }

private:
	void Set(T* ptr)
	{
		_ptr = ptr;
		if (ptr)
			ptr->AddRef();
	}

	void Release()
	{
		if (_ptr != nullptr)
		{
			_ptr->ReleaseRef();
			_ptr = nullptr;
		}
	}

private:
	T* _ptr = nullptr;
};

class Knight : public RefCountable
{

};

map<int , Knight*> _knights;

void Test(Knight* knight)
{
	_knights[ 100 ] = knight;
	// 이게 '나뉘어' 있기에 멀티 스레드 환경에서 문제가 발생할 여지가 있음
	// 멀티 스레드 환경에서 '수동'으로 관리를 하는 것은 매우 피곤한 일
	knight->AddRef();
}

int main()
{
	Knight* knight = new Knight();

	thread t(Test , knight);
	
	t.join();
}