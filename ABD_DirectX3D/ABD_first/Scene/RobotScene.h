#pragma once
class RobotScene : public Scene
{
public:
	RobotScene();
	virtual ~RobotScene();
	virtual void Update() override;
	virtual void PreRender() override;
	virtual void Render() override;
	virtual void PostRender() override;

	void inputKey();

	bool active = true;
	bool active_L = false;
	bool active2 = false;
	bool active2_L = true;
	


private:

	Cube* head	;
	Cube* bodytrans;
	Cube* bodytrans2;

	float key = 0.0f;
	float key2 = 0.0f;


	Cube* body	;
	Cube* arm_L	;
	Cube* arm_R	;
	Cube* leg_L	;
	Cube* leg_R	;




};

