#pragma once
class PixelShader : public Shader
{
public:
	PixelShader(wstring file);
	~PixelShader();

	// Shader��(��) ���� ��ӵ�
	virtual void SetShader() override;



private:

	ID3D11PixelShader* pixelShader;



};

