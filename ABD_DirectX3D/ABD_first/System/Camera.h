#pragma once
class Camera : public Singleton<Camera>
{
	friend class Singleton;

private:

	Camera();
	~Camera();

public:

	void Update();
	void PostRender();


private:

	void FreeMode();
	void TargetMode();

	void SetView();


private:

	Transform* transform = nullptr;

	float moveSpeed		= 20.0f;
	float rotationSpeed	= 5.0f;
	

	MatrixBuffer*	viewBuffer;
	Matrix			viewmatrix;

	Vector3			oldPos;


	
	

};

