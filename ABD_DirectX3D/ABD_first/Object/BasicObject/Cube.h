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

    // Shader�� meterial�� �������
    VertexShader*       vertexShader;
    PixelShader*        pixelShader;

    // Buffer�� mash�� �ٲܰ���
    VertexBuffer*       vertexBuffer;
    IndexBuffer*        indexBuffer;

    MatrixBuffer*       worldBuffer;

};

