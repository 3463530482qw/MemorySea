#version 450

layout(location = 0) in vec2 fragUV;
layout(location = 1) in vec4 fragColor;

layout(set = 0, binding = 0) uniform sampler2D texSampler;

layout(location = 0) out vec4 outColor;

void main() {
    // 图集是 R8 格式,字形数据在红色通道
    // 乘以顶点颜色可以染色文字并设置最终透明度
    float alpha = texture(texSampler, fragUV).r;
    outColor = vec4(fragColor.rgb, fragColor.a * alpha);
}