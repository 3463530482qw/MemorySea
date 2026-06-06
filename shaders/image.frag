#version 450

layout(location = 0) in vec2 fragUV;
layout(location = 1) in vec4 fragColor;

layout(set = 0, binding = 0) uniform sampler2D texSampler;

layout(location = 0) out vec4 outColor;

void main() {
    vec4 texColor = texture(texSampler, fragUV);
    // 预乘 alpha：消除直通 alpha 格式图片的白色/彩色描边
    texColor.rgb *= texColor.a;
    outColor = texColor * fragColor;
}
