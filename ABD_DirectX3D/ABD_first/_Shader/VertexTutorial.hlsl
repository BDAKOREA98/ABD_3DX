// ���� ��ǥ�踦 ����  4�������� �ѱ�
#include "Header.hlsli"




struct VertexInput
{
    float4 pos     : POSITION;
    float4 color   : COLOR;
};


struct VertexOutput
{
    float4 pos : SV_POSITION;
    float4 color : COLOR;
};


VertexOutput main(VertexInput Input) 
{
    
    VertexOutput output;
    
    output.pos = mul(Input .pos, world)     ;
    output.pos = mul(output.pos, view)      ;
    output.pos = mul(output.pos, projection);
    
    output.color = Input.color;
    
    
    return output;
}