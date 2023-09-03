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

	


private:


	Robot* robot;




};

