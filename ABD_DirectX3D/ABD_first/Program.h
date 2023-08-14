#pragma once
class Program
{
public:
	Program();
	~Program();

	void Update();
	void Render();
	
	
private:
	// 내부적으로 구분 하기 위핢

	void Initialize();
	void Release();


private:

	Scene* scene = nullptr;

};

