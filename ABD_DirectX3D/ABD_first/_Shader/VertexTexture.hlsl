// ���� ��ǥ�踦 ����  4�������� �ѱ�
#include "Header.hlsli"





struct VertexInput
{
    float4 pos : POSITION;
    float2 uv  : UV;
};


struct VertexOutput
{
    float4 pos : SV_POSITION;
    float2 uv  : UV;
};


VertexOutput main(VertexInput Input)
{
    
    VertexOutput output;
    
    output.pos = mul(Input.pos, world);
    output.pos = mul(output.pos, view);
    output.pos = mul(output.pos, projection);
    
    output.uv = Input.uv;
    
    
    return output;
}