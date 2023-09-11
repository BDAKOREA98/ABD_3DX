#pragma once
class Environment : public Singleton<Environment>

{
	friend class Singleton;
private:
	Environment();
	~Environment();

	void CreateViewPort();
	void CreatePerspective();







public:

	void SetEnvironment();
	void PostRender();

	Matrix GetPorjMatrix() { return projMatrix; }



private:

	
	MatrixBuffer*	projBuffer;
	Matrix			projMatrix;


	LightBuffer* lightBuffer;
	LightBuffer* lightBuffer2;
};

