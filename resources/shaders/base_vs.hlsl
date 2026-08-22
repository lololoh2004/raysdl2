struct VertexInput {
    float3 position : POSITION;
    float2 texCoord : TEXCOORD0;
    float4 color    : COLOR0;
};

struct VertexOutput {
    float4 position : SV_POSITION;
    float2 texCoord : TEXCOORD0;
    float4 color    : COLOR0;
};

VertexOutput main(VertexInput input) {
    VertexOutput output;
    output.position = float4(input.position, 1.0f); 
    output.texCoord = input.texCoord;
    output.color = input.color;
    return output;
}
