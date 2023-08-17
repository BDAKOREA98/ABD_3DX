// ���� ��ǥ�踦 ����  4�������� �ѱ�

cbuffer World : register(b0)
{
    matrix world;   
};
cbuffer View : register(b1)
{
    matrix view;   
};
cbuffer Projection : register(b2)
{
    matrix projection;
};



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
    
    output.pos = mul(Input .pos,  world);
    output.pos = mul(output.pos, view);
    output.pos = mul(output.pos, projection);
    
    output.color = Input.color;
    
    
    return output;
}