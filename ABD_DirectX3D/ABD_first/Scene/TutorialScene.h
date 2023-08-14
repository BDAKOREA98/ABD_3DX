#pragma once

struct Vertex
{
    Vertex(float x, float y, float z)
    {
        pos = XMFLOAT3(x, y, z);
    }
    XMFLOAT3 pos;
};
struct VertexColor
{
    VertexColor(XMFLOAT3 pos, XMFLOAT4 color)
        : pos(pos), color(color)
    {
    }
    XMFLOAT3 pos;
    XMFLOAT4 color;
};

struct WVP
{
    XMMATRIX world;
    XMMATRIX view;
    XMMATRIX projection;
};



class TutorialScene : public Scene
{
	
public:
	
	TutorialScene();
	~TutorialScene();

	
	virtual void Update() override;

	virtual void PreRender() override;

	virtual void Render() override;

	virtual void PostRender() override;


private:
	
    WVP wvp;


    vector<VertexColor> vertices;
    vector<UINT> indices;




    ID3D11Device* device;
    ID3D11DeviceContext* deviceContext;

    IDXGISwapChain* swapchain;
    ID3D11RenderTargetView* renderTargetView;
    ////////////////////////////////////////////////////////////

    ID3D11VertexShader* vertexShader;
    ID3D11PixelShader* pixelShader;

    ID3D11InputLayout* inputLayout;


    ID3D11Buffer* vertexBuffer;
    ID3D11Buffer* IndexBuffer;
    ID3D11Buffer* constBuffer;


    UINT stride = 0;
    UINT offset = 0;


};

