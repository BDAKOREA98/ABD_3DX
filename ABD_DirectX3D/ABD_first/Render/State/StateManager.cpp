#include "Framework.h"
#include "StateManager.h"

StateManager::StateManager()
{
	CreateSamplerState();
	CreateRaterizerState();
}

StateManager::~StateManager()
{
	delete samplerstate;
	delete rasterizerstate;
}

void StateManager::CreateSamplerState()
{
	samplerstate = new SamplerState();

}

void StateManager::CreateRaterizerState()
{
	rasterizerstate = new RasterizerState();
	rasterizerstate->SetState();
}
