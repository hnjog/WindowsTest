#pragma once
class Scene
{
public:
	Scene();
	virtual ~Scene();

	// ���� ���� �Լ�
	virtual void Init() abstract;
	virtual void Update() abstract;
	virtual void Render(HDC hdc) abstract;

protected:
	//vector<class Object*>
};

