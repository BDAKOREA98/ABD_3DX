#include "Framework.h"
#include "StateManager.h"

StateManager::StateManager()
{
	CreateSamplerState();
}

StateManager::~StateManager()
{
	delete samplerstate;
}

void StateManager::CreateSamplerState()
{
	samplerstate = new SamplerState();

}
