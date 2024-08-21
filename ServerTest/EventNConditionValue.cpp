#include <iostream>
#include<thread>
#include<vector>
#include<Windows.h>
#include<atomic>
#include<mutex>
#include<map>
#include<queue>

using namespace std;

mutex m;
queue<int> q;
// 운영체제가 관리하는 특별한 정수값
// 커널 쪽의 특정한 리소스나 하드웨어를 가리키는 용도로 사용

// Event를 모든 컨텐츠에서 사용하는 것은 비용 문제를 발생할 수 있음
// '다른 프로그램'에서도 사용할 수 있는 자원이므로
// 반드시 사용하는 요소는 아님
// 여러 Thread에서 사용하기에 그렇게 적합한 구조가 아닐 수 있음
// (User Level에서 고려된 것은 아니므로)
HANDLE hEvent;

// 조건 변수
// 커널 오브젝트는 아님 User 레벨
condition_variable cv;

// 생산자 - 소비자 모델
// 멀티 스레드를 잘 활용할 수 있는 모델 - '분업화'
void Producer()
{
	while (true)
	{
		// CV 사용시
		// 1. LOCK 잡기
		// 2. 공유 변수 값 수정
		// 3. LOCK 풀기
		// 4. CV를 통한 공지
		//
		{
			unique_lock<mutex> lock(m);
			q.push(100);
			// cv를 아예 lock을 잡은 순간에 조정할 순 있으나
			// lock을 굳이 더 오래잡을 필요가 있을지는 고민
		}

		// Signal 상태로 변환
		//::SetEvent(hEvent);

		// 대기 중인 녀석이 있다면 '하나' 꺠운다
		cv.notify_one();

		// sleep 이랑 비슷한 함수
		// '기다림'을 통하여 '잠시' m에 대한 lock을 얻으려 하지 않도록 한다
		this_thread::sleep_for(100ms);
	}
}

void Consumer()
{
	while (true)
	{
		// SIGNAL이 될때까지 대기하기
		// 공회전 돌지 않도록 처리함
		//::WaitForSingleObject(hEvent , INFINITE);

		// 신호 리셋처리할지 여부
		//::ResetEvent(hEvent);

		unique_lock<mutex> lock(m);

		// 특정 함수를 넣어 원하는 조건에서 일어날 수 있음
		cv.wait(lock , []() {return q.empty() == false; });
		// 1. lock을 잡으려고 시도한다 (이미 lock을 잡았다면 skip)
		// 2. 조건 확인
		// -> 조건 만족 시, 바로 빠져나와 이어서 코드 진행
		// -> 조건 만족 x 시, lock을 풀고 대기 상태로 전환
		// 
		// 조건 변수를 사용하기 위하여
		// '유니크 락'을 사용
		// (중간에 풀어줄 수 있기에)
		//


		//if (q.empty() == false)
		{
			int data = q.front();
			q.pop();
			cout << data << endl;
		}

		this_thread::sleep_for(100ms);
	}
}


int main()
{
	// 커널 오브젝트
	// - Usage Count (사용되고 있는 개수)
	// - Signal / Non-Signal (사용 가능 상태)

	//hEvent = ::CreateEvent(NULL/*보안속성*/ , FALSE/*AUTO 인지 MANUAL인지*/ , FALSE/*초기상태*/ , NULL);

	thread t1(Producer);
	thread t2(Consumer);

	t1.join();
	t2.join();

	//::CloseHandle(hEvent);
}