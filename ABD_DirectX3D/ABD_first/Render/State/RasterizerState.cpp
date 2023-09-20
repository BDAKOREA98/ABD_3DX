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

void RasterizerState::ChangeState(D3D11_FILL_MODE mode)
{

	if (desc.FillMode == mode)
	{
		return;
	}

	desc.FillMode = mode;

	if (rs != nullptr)
	{
		rs->Release();
	}
	

	DEVICE->CreateRasterizerState(&desc, &rs);
	DC->RSSetState(rs);

}
