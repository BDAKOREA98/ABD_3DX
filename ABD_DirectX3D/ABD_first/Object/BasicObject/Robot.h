#pragma once
class Robot : public Transform
{
public:

	Robot();
	~Robot();

	void Update();
	void Render();

	void InputKey();
	void PostRender();


	DiffuseCube* trans;

private:



private:

	bool active = false;

	DiffuseCube* L_eye;
	DiffuseCube* R_eye;
	DiffuseCube* mouse;

	DiffuseCube* Head;
	DiffuseCube* body;


	DiffuseCube* L_Arm1;
	DiffuseCube* L_Arm2;
	DiffuseCube* L_Arm3;

	DiffuseCube* R_Arm1;
	DiffuseCube* R_Arm2;
	DiffuseCube* R_Arm3;

	DiffuseCube* L_Leg1;
	DiffuseCube* L_Leg2;
	DiffuseCube* L_Leg3;
	DiffuseCube* L_Leg4;

	DiffuseCube* R_Leg1;
	DiffuseCube* R_Leg2;
	DiffuseCube* R_Leg3;
	DiffuseCube* R_Leg4;





};

