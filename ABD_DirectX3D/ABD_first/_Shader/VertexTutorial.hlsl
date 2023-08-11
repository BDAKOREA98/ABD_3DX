// 동차 좌표계를 위해  4차원으로 넘김

cbuffer WVP : register(b0)
{
    matrix world;
    matrix view;
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
    
    output.pos = mul(Input.pos, world);
    output.pos = mul(output.pos, view);
    output.pos = mul(output.pos, projection);
    
    output.color = Input.color;
    
    
    return output;
}