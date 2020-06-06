struct v2f
{
    float4 pos : POSITION;
    float4 color : COLOR;
};

v2f mat_vp(float4 pos : POSITION,
    float4 color : COLOR,
    uniform float4x4 transMatrix
    )
{
    v2f result;
    result.pos = mul(transMatrix, float4(tPos, 1));
    result.color = color;
    return result;
}

float4 mat_fp(v2f data) : COLOR
{
    return data.color;
}