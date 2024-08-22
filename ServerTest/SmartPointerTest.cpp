#include <iostream>
#include<thread>
#include<vector>
#include<Windows.h>
#include<atomic>
#include<mutex>
#include<map>
#include<queue>

using namespace std;


class Knight : enable_shared_from_this<Knight>
{
public:
	void Test()
	{
		// 일반 포인터를 shared_ptr로 만듦
		// 주의점
		// 이건 자기 자신을 가리키는 공유 포인터 이며,
		// ref가 0이 되는 순간 this를 '지우게 됨'
		// 
		// 아~주 위험하니 이런식으로 사용하지 말자
		// 
		//Move(shared_ptr<Knight>(this));

		// weak를 건네주는 방식은 조금 더 안전한 방식
		//Move(shared_ptr<Knight>(_wptr));

		// 공유 포인터를 사용할 것이라면 이게 안전한 방식
		Move(shared_from_this());
	}

	void Move(shared_ptr<Knight> k)
	{

	}

private:
	//weak_ptr<Knight> _wptr;
};

int main()
{
	Knight* ptr = new Knight();
	{
		// Test 함수 내부에서 별도의 공유 포인터가 하나 '생성' 됨
		// 그렇기에 ref Block이 2개로 나뉘며
		// '2'번 지우려고 시도하기에 터지게 된다
		//
		shared_ptr<Knight> k(ptr);
		k->Test(); // Crash
	}
}