#include "DXUT.h"
#include "OutlineShader.h"

OutlineShader::OutlineShader()
{
    shader = ShaderManager::GetInstance().GetEffect("Outline");
}

OutlineShader::~OutlineShader()
{
    SAFE_RELEASE(shader);
}

HRESULT OutlineShader::PrePare()
{
    return shader->SetTechnique(shader->GetTechniqueByName("Outline"));
}

HRESULT OutlineShader::Begin()
{
    if (FAILED(shader->Begin(0, NULL))) return E_FAIL;
    return shader->BeginPass(0);
}

HRESULT OutlineShader::End()
{
    return shader->End();
}

HRESULT OutlineShader::SetTexture(const Texture* texture)
{
    if (FAILED(shader->SetTexture(shader->GetParameterByName(0, "spriteTexture"), texture->src)))
        return E_FAIL;

    float textureSize[2] = { texture->info.Width, texture->info.Height };
    return shader->SetFloatArray(shader->GetParameterByName(0, "textureSize"), textureSize, 2);
}

HRESULT OutlineShader::SetColor(D3DXVECTOR4 color)
{
    if (FAILED(shader->SetVector(shader->GetParameterByName(0, "color"), &color)))
        return E_FAIL;
}

void OutlineShader::Render(OutlineShader* shader, Sprite& spr, RenderInfo& ri, D3DXVECTOR4 color)
{
    shader->PrePare();
    shader->SetTexture(spr.GetNowScene());
    shader->SetColor(color);
    shader->Begin();
    spr.Render(ri);
    shader->End();
}
