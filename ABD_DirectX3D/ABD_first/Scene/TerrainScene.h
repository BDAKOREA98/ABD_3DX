#pragma once
class TerrainScene : public Scene
{
public:

	TerrainScene();
	~TerrainScene();


	// Scene��(��) ���� ��ӵ�
	virtual void Update() override;
	virtual void PreRender() override;
	virtual void Render() override;
	virtual void PostRender() override;



		
private:

	Terrain* terrain;
	Sphere_Color* sphere;
	Robot* robot;


};

