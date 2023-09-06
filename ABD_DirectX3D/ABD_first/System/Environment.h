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

private:

	
	MatrixBuffer* projBuffer;
	
	LightBuffer* lightBuffer;
	LightBuffer* lightBuffer2;
};

