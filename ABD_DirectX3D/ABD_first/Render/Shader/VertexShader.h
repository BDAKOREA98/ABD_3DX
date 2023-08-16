#pragma once
class VertexShader : public Shader
{
public:
	VertexShader(wstring file);
	~VertexShader();
	// Shader을(를) 통해 상속됨
	virtual void SetShader() override;

private:

	void CreateInputLayout();	

private:

	ID3D11InputLayout*  inputLayout;
	ID3D11VertexShader* vertexShader;

};

