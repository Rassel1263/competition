#include "DXUT.h"
#include "ColorShader.h"

ColorShader::ColorShader()
{
    shader = ShaderManager::GetInstance().GetEffect("Color");
}

ColorShader::~ColorShader()
{
    SAFE_RELEASE(shader);
}

HRESULT ColorShader::Prepare()
{
    return shader->SetTechnique(shader->GetTechniqueByName("Color"));
}

HRESULT ColorShader::Begin()
{
    if (FAILED(shader->Begin(0, NULL))) return E_FAIL;

    return shader->BeginPass(0);
}

HRESULT ColorShader::End()
{
    return shader->End();
}

HRESULT ColorShader::SetTexture(const Texture* texture)
{
    return shader->SetTexture(shader->GetParameterByName(0, "spriteTexture"), texture->src);
}

HRESULT ColorShader::SetColor(D3DXVECTOR4 color, bool plus)
{
    if (FAILED(shader->SetBool(shader->GetParameterByName(0, "plus"), plus)))
        return E_FAIL;

    return shader->SetVector(shader->GetParameterByName(0, "color"), &color);
}

void ColorShader::Render(ColorShader* shader, Sprite& spr, RenderInfo& ri, D3DXVECTOR4 color, bool plus)
{
    shader->Prepare();
    shader->SetTexture(spr.GetNowScene());
    shader->SetColor(color, plus);
    shader->Begin();
    spr.Render(ri);
    shader->End();
}
