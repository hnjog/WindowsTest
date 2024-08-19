#include <iostream>
#include<thread>
#include<vector>
#include<Windows.h>
#include<atomic>

using namespace std;

// 템플릿 클래스 atomic
// 일단 템플릿이긴 하지만,
// 아주 무거운 구조체 같은 것을 넣으면 더욱 느려질 수 있음
atomic<int> sum = 0;

// Quiz
// 이 함수를 멀티 스레드 환경에서 돌린다고 하였을 때
// 문제가 있을까?
// - 내 의견 
// : 없지 않을까...?
// i와 p 모두 일단 '지역 변수'이다
// 따라서 stack 에 저장된다
// 
// - 정답
// : 아님
// heap 영역을 '활용'하지만
// 주소값은 지역변수(스택)에 저장됨
// 
// heap 영역이 '공유' 될때 문제인 것
// 외부에서 '주소'를 넘겨주는 방식이라면 당연히 문제가 될 수 있음
//
void Test()
{
	
	for (int i = 0; i < 10000; i++)
	{
		int* p = new int();

		*p = 100;

		delete p;
	}
	
}

void Add()
{
	for (int i = 0; i < 100'0000; i++)
	{
		sum++;
		// 어셈블리어로 본다면
		// 멀리 있는 sum을 직접 대입하는게 아니라
		// temp 용 으로 계산 후 넣어주기에
		// 
		// int eax = sum;
		// eax = eax + 1;
		// sum = eax;
		// -> 중간에 '끼어들만한 요소' 존재
		// 
		// 해당 과정을 문제 없이 진행하려면
		// 'atomic' 클래스 사용
		// 
		// -> 다른 어셈블리어를 사용
		// 
		// 결과적으로 All or Nothing 으로
		// 실행하거나 안되거나 의 결과만을 낳음
		// 
		// 대신 '기다려야' 함
		// 또한 매우 무거운 클래스이기에 성능 이슈가 발생할 수 있음(일반 자료형보다 10배)
		// 


	}
}

void Sub()
{
	for (int i = 0; i < 100'0000; i++)
	{
		sum--;
	}
}

int main()
{
	// temp에 sum의 대입 이전에 값을 집어 넣은 것은 맞지만
	// 다른 thread가 '건드릴' 수 있기에 확신은 못한다 (멀티스레드 환경...)

	// 2개로 나뉘기에 atomic 하지 않음
	int temp = sum.load(); // temp = sum;
	sum.store(10); // sum = 10;

	// 대입하며 이전 값 temp2 에 넣음
	int temp2 = sum.exchange(10);

	// 더하면서 이전 값 temp3 에 넣음
	int temp3 = sum.fetch_add(10);

	// 함수를 하나 사용하는 방식이 'atomic'하게 동작

	// 현재 sum을 사용할 수 있는가?
	// 관련 조작이 너무 무겁다면 lock으로 인해 sum 사용 불가 상태
	bool isLock = sum.is_lock_free();

	thread t1(Add);
	thread t2(Sub);

	t1.join();
	t2.join();

	// sum 은 과연 0일까?
	// 중간에 값을 덮어씌우는 과정이 발생
	// '전역 변수'는 Data 영역이기에 멀티 스레드의 위험범위 안에 존재한다
	// (근데 어차피 heap도 마찬가지)
	// 
	// 
	cout << sum << endl;
}