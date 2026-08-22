struct PixelInput {
    float4 position : SV_POSITION;
    float2 texCoord : TEXCOORD0;
    float4 color    : COLOR0;
};

float4 main(PixelInput input) : SV_Target {
    return input.color; 
}
