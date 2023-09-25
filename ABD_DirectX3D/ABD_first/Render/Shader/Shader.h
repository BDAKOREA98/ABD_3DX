#pragma once
class Shader
{
	

protected:
	
	
	virtual ~Shader();

public:

	static class VertexShader* GetVS(wstring file);
	static class PixelShader*  GetPS(wstring file);
	static class ComputeShader*  GetCS(wstring file);

	static  void Delete();
	virtual void SetShader() = 0;

	wstring GetPath() {return path;	}
protected:

	ID3DBlob* blob;

	
	static map<wstring, Shader*> shaders;
	// singleton과 비슷하다고 생각하면 됨 있으면 리턴 없으면 생성
	//

	wstring path;

};

