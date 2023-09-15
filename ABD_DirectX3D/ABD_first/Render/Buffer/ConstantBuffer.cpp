#include "Framework.h"
#include "ConstantBuffer.h"

ConstantBuffer::ConstantBuffer(void* data, UINT dataSize)
    : data(data), dataSize(dataSize)
{
    
       D3D11_BUFFER_DESC bufferDesc   = {};
       bufferDesc.ByteWidth           = dataSize;
       bufferDesc.Usage               = D3D11_USAGE_DYNAMIC;
       bufferDesc.BindFlags           = D3D11_BIND_CONSTANT_BUFFER;
       bufferDesc.CPUAccessFlags      = D3D11_CPU_ACCESS_WRITE;
       bufferDesc.MiscFlags           = 0;
       bufferDesc.StructureByteStride = 0;


       //D3D11_SUBRESOURCE_DATA data;               
       //data.pSysMem = vertices.data(); 
       // constant Buffer는 실시간으로 데이터를 받기에 initdata가 필요 없음
       DEVICE->CreateBuffer(&bufferDesc, nullptr, &constBuffer);
    
}

ConstantBuffer::~ConstantBuffer()
{
    constBuffer->Release();
}

void ConstantBuffer::SetVSBuffer(UINT slot)
{
    UpdateSubResource();
    DC->VSSetConstantBuffers(slot, 1, &constBuffer);
}

void ConstantBuffer::SetPSBuffer(UINT slot)
{
    UpdateSubResource();
    DC->PSSetConstantBuffers(slot, 1, &constBuffer);
}

void ConstantBuffer::SetCSBuffer(UINT slot)
{
    UpdateSubResource();
    DC->CSSetConstantBuffers(slot, 1, &constBuffer);
}

void ConstantBuffer::UpdateSubResource()
{
    // CPU가 데이터를 수정하는 과정
    DC->Map(constBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &subResource);

    memcpy(subResource.pData, data, dataSize);

    DC->Unmap(constBuffer, 0);

    
    //DC->UpdateSubresource(constBuffer, 0, nullptr, data, 0, 0);
    
}
