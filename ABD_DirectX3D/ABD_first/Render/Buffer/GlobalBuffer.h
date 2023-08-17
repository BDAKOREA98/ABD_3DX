#pragma once
class MatrixBuffer : public ConstantBuffer
{
public:

	MatrixBuffer()
		:ConstantBuffer(&data, sizeof(data))
	{
		data.matrix = XMMatrixIdentity();
	}

	void SetData(XMMATRIX value)
	{
		data.matrix = XMMatrixTranspose(value);
	}


	
	
private:

	struct Data
	{
		XMMATRIX matrix;
	} data;

	
	

};