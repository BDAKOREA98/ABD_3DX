#include "Framework.h"
#include "StructuredBuffer.h"

StructuredBuffer::StructuredBuffer(void* inputData, UINT inputStride, UINT inputCount, UINT outputStride, UINT outputCount)
	: 
	inputData	(inputData),
	inputStride	(inputStride),
	inputCount	(inputCount),
	outputStride(outputStride),
	outputCount	(outputCount)
{
	 CreateInput();
	 CreateSRV();
	 CreateOutput();
	 CreateUAV();
	 CreateResult();
}

StructuredBuffer::~StructuredBuffer()
{
	result->Release();
	uav->Release();
	output->Release();
	srv->Release();
	input->Release();
}

void StructuredBuffer::Copy(void* data, UINT size)
{
	DC->CopyResource(result, output);

	D3D11_MAPPED_SUBRESOURCE subResource;

	DC->Map(result, 0, D3D11_MAP_READ, 0, &subResource);
	memcpy(data, subResource.pData, size);

	DC->Unmap(result, 0);

}
void StructuredBuffer::SetSRV()
{
	DC->CSSetShaderResources(0, 1, &srv);

}
void StructuredBuffer::SetUAV()
{
	DC->CSSetUnorderedAccessViews(0, 1, &uav, nullptr);

}
void StructuredBuffer::CreateOutput()
{
	ID3D11Buffer* buffer;
	D3D11_BUFFER_DESC desc = {};
	// stride 변수형 크기, count 그것이 몇개있는가 ?
	desc.Usage		= D3D11_USAGE_DEFAULT;
	desc.ByteWidth	= outputStride * outputCount;
	desc.BindFlags	= D3D11_BIND_UNORDERED_ACCESS;
	desc.MiscFlags	= D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;
	desc.StructureByteStride = outputStride;

	DEVICE->CreateBuffer(&desc, nullptr, &buffer);

	// Resource란 변수형이 버퍼를 바로 못 받아와서 위 과정을 통해 형변환 후 output에 넣음
	output = (ID3D11Resource*)buffer;
}

void StructuredBuffer::CreateUAV()
{
	ID3D11Buffer* buffer = (ID3D11Buffer*)output;

	D3D11_BUFFER_DESC desc = {};
	buffer->GetDesc(&desc);

	D3D11_UNORDERED_ACCESS_VIEW_DESC uavdesc = {};
	uavdesc.Format				= DXGI_FORMAT_UNKNOWN;
	uavdesc.ViewDimension		= D3D11_UAV_DIMENSION_BUFFER;
	uavdesc.Buffer.FirstElement = 0;
	uavdesc.Buffer.Flags		= 0;
	uavdesc.Buffer.NumElements	= outputCount;

	DEVICE->CreateUnorderedAccessView(buffer, &uavdesc, &uav);
}



void StructuredBuffer::CreateResult()
{
	ID3D11Buffer* buffer;
	D3D11_BUFFER_DESC desc = {};
	((ID3D11Buffer*)output)->GetDesc(&desc);

	desc.Usage			= D3D11_USAGE_STAGING;
	desc.BindFlags		= 0;
	desc.MiscFlags		= 0;
	desc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;

	DEVICE->CreateBuffer(&desc, nullptr, &buffer);

	result = (ID3D11Resource*)buffer;
}

void StructuredBuffer::CreateInput()
{
	ID3D11Buffer* buffer;
	D3D11_BUFFER_DESC desc = {};
	// stride 변수형 크기, count 그것이 몇개있는가 ?
	desc.Usage		= D3D11_USAGE_DEFAULT;
	desc.ByteWidth	= inputStride * inputCount;
	desc.BindFlags	= D3D11_BIND_SHADER_RESOURCE;
	desc.MiscFlags	= D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;
	desc.StructureByteStride = inputStride;


	D3D11_SUBRESOURCE_DATA initData = {};
	initData.pSysMem = inputData;


	DEVICE->CreateBuffer(&desc, &initData, &buffer);

	// Resource란 변수형이 버퍼를 바로 못 받아와서 위 과정을 통해 형변환 후 output에 넣음
	input = (ID3D11Resource*)buffer;
}

void StructuredBuffer::CreateSRV()
{
	ID3D11Buffer* buffer = (ID3D11Buffer*)input;
	D3D11_BUFFER_DESC desc = {};
	buffer->GetDesc(&desc);

	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
	srvDesc.Format = DXGI_FORMAT_UNKNOWN;
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_BUFFER;
	srvDesc.Buffer.FirstElement = 0;
	srvDesc.Buffer.NumElements = inputCount;

	DEVICE->CreateShaderResourceView(buffer, &srvDesc, &srv);


}
