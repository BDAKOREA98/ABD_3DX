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

class LightBuffer : public ConstantBuffer
{
public:
	LightBuffer()
		:ConstantBuffer(&data, sizeof(data))
	{
		data.LightDirection = V_DOWN;
	}

	void SetData(Vector3 direction)
	{
		data.LightDirection = direction;
	}

private:

	struct Data
	{
		Vector3 LightDirection;
		float padding = 0;
	} data;

};