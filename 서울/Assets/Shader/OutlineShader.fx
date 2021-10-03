Texture2D spriteTexture;
float2 textureSize : VPOS;
float4 color;

sampler2D InputSampler = sampler_state
{
	Texture = <spriteTexture>;
};

struct ShaderInput
{
    float4 Color : COLOR0;
    float3 Position : SV_Position;
	float2 UV : TEXCOORD0;
};

float4 main(ShaderInput input) : COLOR
{
    float4 currentPixel = tex2D(InputSampler, input.UV) * input.Color;
    float4 output = currentPixel;
	
	if(currentPixel.a == 0.0f)
    {
        float2 uvPix = float2(4 / textureSize.x, 4 / textureSize.y);
		
        if (tex2D(InputSampler, float2(input.UV.x + uvPix.x, input.UV.y)).a > 0 ||
			tex2D(InputSampler, float2(input.UV.x, uvPix.y + input.UV.y)).a > 0 ||
			tex2D(InputSampler, float2(input.UV.x - uvPix.x, input.UV.y)).a > 0 ||
			tex2D(InputSampler, float2(input.UV.x, input.UV.y - uvPix.y)).a > 0)
        {
            output = color;
        }

    }
	
    return output;
}

technique Outline
{
	pass pass0
	{
		PixelShader = compile ps_2_0 main();
	}
}