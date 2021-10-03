#include "DXUT.h"
#include "ShaderManager.h"

ShaderManager::~ShaderManager()
{
    for (auto& effect : effects)
        SAFE_RELEASE(effect.second);
}

HRESULT ShaderManager::Create(std::string name, std::wstring path, DWORD flag)
{
#ifdef _DEBUG
    flag |= D3DXSHADER_DEBUG;
#endif
    LPD3DXEFFECT pEffect;
    LPD3DXBUFFER pError;

    if (SUCCEEDED(D3DXCreateEffectFromFileW(Game::GetInstance().pDevice,
        path.c_str(),
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

LPD3DXEFFECT& ShaderManager::GetEffect(std::string name)
{
    return effects[name];
}
