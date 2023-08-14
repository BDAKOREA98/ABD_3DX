#pragma once
// Scene�� InterFace�� �̰͸����δ� ���� �� �ִ°� ����



class Scene
{
public:			 
		
	virtual ~Scene() = default;

	virtual void Update() = 0;


	// Render���� ó���� �͵� ex) Render Target, mini map���
	virtual void PreRender() = 0;
	// main ���� �׷��� ģ����
	virtual void Render() = 0;
	// main���� �׷��� ���Ŀ� �׷��� �͵� ex) UI���
	virtual void PostRender() = 0;
	




};