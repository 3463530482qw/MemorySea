#version 450

layout(location = 0) in vec2 fragUV;
layout(location = 1) in vec4 fragColor;
layout(location = 2) in vec2 fragEffects;        // x=描边宽,y=抗锯齿带宽(SDF d 值)
layout(location = 3) in vec4 fragOutlineColor;

layout(set = 0, binding = 0) uniform sampler2D texSampler;

layout(location = 0) out vec4 outColor;

void main() {
    // 图集是 R8 的 SDF:0.5 是轮廓,大于 0.5 在字形内;
    // 烘焙时 128 个灰度值铺满留白 pad,故 d=0/1 恰在留白边界,界外零填充与边界连续
    float d = texture(texSampler, fragUV).r;
    float ow = fragEffects.x;
    float aa = max(fragEffects.y, 0.01);

    float body = smoothstep(0.5 - aa, 0.5 + aa, d);

    // 描边:轮廓外 [0.5-ow, 0.5] 的带(被正文盖住的部分自然消隐,封闭笔画内部不误填)
    float outline = 0.0;
    if (ow > 0.0) {
        outline = (1.0 - body) * smoothstep(0.5 - ow - aa, 0.5 - ow + aa, d);
    }

    vec4 col = vec4(fragColor.rgb, fragColor.a * body);
    col = mix(col, vec4(fragOutlineColor.rgb, fragOutlineColor.a * outline), outline);
    outColor = col;
}
