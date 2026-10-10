#pragma once


static const char* DEFAULT_VERT_SHADER =
    "struct VSInput { float3 pos : POSITION; float2 uv : TEXCOORD; };\n"
    "struct VSOutput { float4 pos : SV_POSITION; float2 uv : TEXCOORD; };\n"
    "VSOutput VSMain(VSInput input) {\n"
    "    VSOutput output;\n"
    "    output.pos = float4(input.pos, 1.0);\n"
    "    output.uv = input.uv;\n"
    "    return output;\n"
    "}\n";

static const char* DEFAULT_FRAG_SHADER =
    "struct FSInput { float2 uv : TEXCOORD; };\n"
    "float4 FSMain(FSInput input) : SV_TARGET {\n"
    "    return float4(1.0, 0.0, 1.0, 1.0);\n"
    "}\n";
