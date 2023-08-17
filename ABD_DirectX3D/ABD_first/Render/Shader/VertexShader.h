#pragma once
class VertexShader : public Shader
{
	friend class Shader;
private:

	VertexShader(wstring file);
	~VertexShader();
	// Shader을(를) 통해 상속됨
	void CreateInputLayout();	

public:
	virtual void SetShader() override;

private:

	ID3D11InputLayout*  inputLayout;
	ID3D11VertexShader* vertexShader;

};

