// 동차 좌표계를 위해  4차원으로 넘김

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