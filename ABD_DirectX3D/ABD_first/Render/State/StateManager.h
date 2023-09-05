#pragma once
class StateManager : public Singleton<StateManager>
{
	friend class Singleton;
public:

	StateManager();
	~StateManager();

	void CreateSamplerState();
	void CreateRaterizerState();
	
	RasterizerState* GetRS() { return rasterizerstate; }


private:
	SamplerState* samplerstate = nullptr;
	RasterizerState* rasterizerstate = nullptr;
};

