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


private:

	MatrixBuffer* viewBuffer;
	MatrixBuffer* projBuffer;
};
