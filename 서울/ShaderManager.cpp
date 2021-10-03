#include "DXUT.h"
#include "ShaderManager.h"

HRESULT ShaderManager::CreateEffect(std::string name, std::wstring filePath, DWORD flag)
{
#ifdef  _DEBUG
	flag |= D3DXSHADER_DEBUG;
#endif //  _DEBUG

	LPD3DXEFFECT pEffect;
	LPD3DXBUFFER pError;

	if (SUCCEEDED(D3DXCreateEffectFromFileW(Game::GetInstance().pDevice,
		filePath.c_str(),
		NULL,
		NULL,
		flag,
		NULL,
		&pEffect,
		&pError)))
	{
		auto ef = effects.find(name);

		if (ef != effects.end())
		{
			if (ef->second)
				SAFE_RELEASE(ef->second);
			effects.erase(name);
		}

		effects.insert(std::make_pair(name, pEffect));
		return S_OK;
	}
	else
	{
		if (pError)
		{
			std::cout << (char*)pError->GetBufferPointer() << std::endl;
			SAFE_RELEASE(pError);
		}

		return E_FAIL;
	}
}

LPD3DXEFFECT & ShaderManager::GetEffect(std::string name)
{
	return effects[name];
}
