#include "Framework.h"
#include "RasterizerState.h"



RasterizerState::RasterizerState()
{
	desc.CullMode = D3D11_CULL_BACK;
	desc.FillMode = D3D11_FILL_SOLID;

	DEVICE->CreateRasterizerState(&desc, &rs);


}

RasterizerState::~RasterizerState()
{
	rs->Release();
}

void RasterizerState::SetState()
{
	DC->RSSetState(rs);
}
