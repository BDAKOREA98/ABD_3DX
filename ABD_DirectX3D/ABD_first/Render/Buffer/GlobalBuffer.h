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
		data.padding = 0.0f;
		data.ambientLight = Vector4(0.1f, 0.1f, 0.1f, 1.0f);
	}

	

	struct Data
	{
		Vector3 LightDirection ;
		float padding ;
		Vector4 ambientLight;
	} data;

};

class ViewBuffer : public ConstantBuffer
{
public:
	ViewBuffer()
		:ConstantBuffer(&data, sizeof(data))
	{
		data.view = XMMatrixIdentity();
		data.invView = XMMatrixIdentity();
	}

	void SetData(Matrix view, Matrix invView)
	{
		data.view = XMMatrixTranspose(view);
		data.invView = XMMatrixTranspose(invView);
	}

private:

	struct Data
	{
		Matrix view;
		Matrix invView;
	} data;

};

class MaterialBuffer : public ConstantBuffer
{
public:
	MaterialBuffer()
		:ConstantBuffer(&data, sizeof(data))
	{
		
	}



	struct Data
	{
		Vector4 Mdiffuse	= Vector4( 1,1,1,1 );
		Vector4 Mspecular	= Vector4( 1,1,1,1 );
		Vector4 Mambient	= Vector4( 1,1,1,1 );
		Vector4 emissive	= Vector4(0, 0, 0, 1);

		int hasDiffuseMap	= 0;
		int hasSpecularMap	= 0;
		int hasNormalMap	= 0;
		int hasAlphaMap		= 0;

		float shininess		= 24.0f;

		Vector3 padding		= {};


	} data;

};


class RayBuffer : public ConstantBuffer
{
public:
	RayBuffer()
		:ConstantBuffer(&data, sizeof(data))
	{

		

	}



	struct Data
	{

		Vector3 origin		= {};
		float	outputSize	= 0;

		Vector3 direction	= {};
		float	padding		= 0;

	} data;

};


class BrushBuffer : public ConstantBuffer
{
public:
	BrushBuffer()
		:ConstantBuffer(&data, sizeof(data))
	{



	}

	struct Data
	{

		int type = 0;
		Vector3 location = {};

		float range = 10.0f;
		Vector3 color = {0.0f,0.5f,0.0f};
		

	} data;

};