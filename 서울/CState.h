#pragma once
template <typename T>
class CState
{
public:
	virtual void EnterState(T* obj) = 0;
	virtual void UpdateState(T* obj, float deltaTime) = 0;
	virtual void ExitState(T* obj) = 0;
};
