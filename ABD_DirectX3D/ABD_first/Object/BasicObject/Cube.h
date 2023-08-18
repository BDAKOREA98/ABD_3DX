#pragma once
class Cube
{
public:

	Cube();
	~Cube();


    void Update() ;

    void PreRender() ;

    void Render() ;

    void PostRender();



private:


    vector<VertexColor> vertices;
    vector<UINT>        indices;

    // Shader는 meterial로 만들거임
    VertexShader*       vertexShader;
    PixelShader*        pixelShader;

    // Buffer는 mash로 바꿀거임
    VertexBuffer*       vertexBuffer;
    IndexBuffer*        indexBuffer;

    MatrixBuffer*       worldBuffer;

};

