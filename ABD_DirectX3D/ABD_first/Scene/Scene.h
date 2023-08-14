#pragma once
// Scene은 InterFace임 이것만으로는 만들 수 있는게 없음



class Scene
{
public:			 
		
	virtual ~Scene() = default;

	virtual void Update() = 0;


	// Render전에 처리할 것들 ex) Render Target, mini map등등
	virtual void PreRender() = 0;
	// main 으로 그려질 친구들
	virtual void Render() = 0;
	// main으로 그려진 이후에 그려질 것들 ex) UI등등
	virtual void PostRender() = 0;
	




};