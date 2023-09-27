#pragma once
class ModelExportScene : public Scene
{
public:
	ModelExportScene();
	virtual ~ModelExportScene();
	
	// Scene��(��) ���� ��ӵ�

	virtual void Update() override;
	virtual void PreRender() override;
	virtual void Render() override;
	virtual void PostRender() override;


private:

	ModelExporter* exporter;


};

