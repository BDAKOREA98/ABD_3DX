#pragma once

struct Ray
{
	Vector3 origin;
	Vector3 direction;

};

class Camera : public Singleton<Camera>
{
	friend class Singleton;

private:

	Camera();
	~Camera();


public:

	void Update();
	void PostRender();

	Transform* GetTransform() { return transform; }

	Ray ScreenPointToRay(Vector3 screenPos);

private:

	void FreeMode();
	void TargetMode();
	
	void SetView();

	void Save();
	void Load();


private:

	Transform* transform = nullptr;

	float moveSpeed		= 20.0f;
	float rotationSpeed	= 5.0f;
	

	ViewBuffer*	viewBuffer;
	Matrix			viewmatrix = {};

	Vector3			oldPos;


	
	

};

