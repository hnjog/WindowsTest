#pragma once

class Object;

class ObjectManager
{
	DECLARE_SINGLE(ObjectManager)

	~ObjectManager();

	void Add(Object* object);
	void Remove(Object* object);
	void Clear();

	const vector<Object*>& GetObjects() { return _objects; }

	template<typename T>
	T* CreateObject()
	{
		// type trait
		// T*가 Object* 로 변환이 되지 않으면
		// 컴파일 시간에 error를 내뱉기 위함
		static_assert(std::is_convertible_v<T*, Object*>);

		T* object = new T();
		object->Init();
		// 문제 있으면 컴파일 시점에서 에러 발생
		// 템플릿은 해당 타입을 넣어서 함수를 타이핑해주는 방식이기에


		return object;
	}

private:
	vector<class Object*> _objects;

};

