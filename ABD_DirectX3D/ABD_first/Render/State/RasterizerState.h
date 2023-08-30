#pragma once
class RasterizerState
{
public:

	RasterizerState();
	~RasterizerState();

	void SetState();

private:

	
	ID3D11RasterizerState* rs = nullptr;
	D3D11_RASTERIZER_DESC desc = {};


};

