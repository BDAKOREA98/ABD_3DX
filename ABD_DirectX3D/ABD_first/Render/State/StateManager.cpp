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
	delete raterizerstate;
}

void StateManager::CreateSamplerState()
{
	samplerstate = new SamplerState();

}

void StateManager::CreateRaterizerState()
{
	raterizerstate = new RasterizerState();
	raterizerstate->SetState();
}
