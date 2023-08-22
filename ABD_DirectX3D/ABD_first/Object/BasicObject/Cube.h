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

    void CreateMesh();

    void Debug();

private:


    vector<VertexColor> vertices;
    vector<UINT>        indices;

    
    // Shader는 meterial로 만들거임
    Material* material;
    // Buffer는 mash로 바꿀거임
    Mesh*     mesh;

  

    MatrixBuffer*       worldBuffer;

    //SRT
    XMFLOAT3 scale          = {1.0f, 1.0f, 1.0f};
    XMFLOAT3 rotation       = {0.0f, 0.0f, 0.0f};
    XMFLOAT3 translation    = {0.0f, 0.0f, 0.0f};

    XMMATRIX s;
    XMMATRIX r;
    XMMATRIX t;
    
    XMMATRIX world;


};

