#pragma once
class Game
{
public:
	Game();
	~Game();

public:
	void Init(HWND hwnd);
	void Update();
	void Render();

private:
	HWND _hwnd = {}; // Window Handle
	HDC _hdc = {};	 // Device Context Handle

private:
	// Double Buffering
	RECT _rect;
	HDC _hdcBack = {};
	HBITMAP _bmpBack = {};

};

/*
	Handle : � ü�� ���� ���ҽ� ���� �����ϱ� ���� ������ pointer Ȥ�� �ε��� �� ����� ����

	���α׷��� Ư���� ���ҽ��� '�ʿ�'�� ������,
	���� �ٷ�⿡�� ������ ��� (������, ex : �ϵ����)
	OS�� ������ ���� �ش� �ڿ��� ���� �����ϰ� �ٷ�� ����
	(OS�� '�߻�ȭ' �׸��� '��ȣ' ��ɰ� ����)

	HWND : ������(â)�� ����
	HDC : �׷��Ƚ� ��ü �ĺ�, ��� ��ġ(������, ����� ��)�� ���� �׸��� ����� �����ϴµ� ���

*/