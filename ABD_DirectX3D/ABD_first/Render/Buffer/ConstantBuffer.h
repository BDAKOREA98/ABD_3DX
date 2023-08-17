#pragma once
class ConstantBuffer
{
public:

	ConstantBuffer(void* data, UINT dataSize);
	virtual ~ConstantBuffer();

	void SetVSBuffer(UINT slot);
	void SetPSBuffer(UINT slot);

	void UpdateSubResource();


private:

	void* data;
	UINT dataSize;

	ID3D11Buffer* constBuffer;
};

