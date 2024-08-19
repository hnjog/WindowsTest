#include <iostream>
#include<thread>
#include<vector>

using namespace std;

void HelloThread(int i)
{
	cout << "Hello Thread" << i << endl;
}

int main()
{
	vector<thread> threads;
	
	// 스레드를 무작정 늘려도 코어가 부족하면
	// 영 애매... 
	// 스레드 끼리 문맥교환이 발생하기에 마냥 좋아지지 않는다는 점을 확인
	// 어지간하면 하드웨어 개수를 고려하여 스레드를 사용해야 함
	// 스레드는 각각의 stack 영역을 지니고
	// 프로세스의 Heap과 Data 영역을 공유한다
	// 
	// Heap의 영역을 공유한다는 점이 굉장히 큰 이슈로 번질 수 있음
	//
	for (int i = 0; i < 10; i++)
	{
		threads.push_back(thread(HelloThread, i));
	}

	cout << "Hello main" << endl;

	// 신경 안쓸테니 독립하여 살아라... 는 느낌이지만
	// 보통은 쓰일일 없음
	// t.detach();

	// t thread가 일을 끝낼때까지 대기하기
	for (int i = 0; i < 10; i++)
	{
		threads[i].get_id();
		// 스레드 실행시킬 cpu 코어 갯수
		// 서버용 컴퓨터에 몇개있는지 확인하고 해야 함
		int a = threads[i].hardware_concurrency();

		threads[i].join();
	}

}
