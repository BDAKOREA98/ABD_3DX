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


	Cube* trans;

private:



private:

	bool active = false;

	Cube* L_eye;
	Cube* R_eye;
	Cube* mouse;

	Cube* Head;
	Cube* body;


	Cube* L_Arm1;
	Cube* L_Arm2;
	Cube* L_Arm3;

	Cube* R_Arm1;
	Cube* R_Arm2;
	Cube* R_Arm3;

	Cube* L_Leg1;
	Cube* L_Leg2;
	Cube* L_Leg3;
	Cube* L_Leg4;

	Cube* R_Leg1;
	Cube* R_Leg2;
	Cube* R_Leg3;
	Cube* R_Leg4;





};

