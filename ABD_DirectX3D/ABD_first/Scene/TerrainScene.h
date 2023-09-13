#pragma once
class TerrainScene : public Scene
{
public:

	TerrainScene();
	~TerrainScene();


	// Scene을(를) 통해 상속됨
	virtual void Update() override;
	virtual void PreRender() override;
	virtual void Render() override;
	virtual void PostRender() override;
	
	void RawData();


		
private:

	Terrain* terrain;
	Sphere_Color* sphere;
	Robot* robot;
	Vector3 pickerPos;

};

