#version 450

layout(location = 0) in vec2 fragUV;
layout(location = 1) in vec4 fragColor;

layout(set = 0, binding = 0) uniform sampler2D texSampler;

layout(location = 0) out vec4 outColor;

void main() {
    // 图集纹理的 alpha 通道包含字形数据，RGB 为白色
    // 乘以顶点颜色可以染色文字并设置最终透明度
    vec4 texColor = texture(texSampler, fragUV);
    outColor = vec4(fragColor.rgb, fragColor.a * texColor.a);
}