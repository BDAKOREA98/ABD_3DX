#pragma once
class Program
{
public:
	Program();
	~Program();

	void Update();
	void Render();
	
	
private:
	// ���������� ���� �ϱ� ����

	void Initialize();
	void Release();


private:

	Scene* scene = nullptr;

	bool isWireFrame = false;

};

