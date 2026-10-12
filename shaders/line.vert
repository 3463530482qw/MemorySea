#version 450

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec2 inUV;
layout(location = 2) in vec4 inColor;
layout(location = 3) in float inTexture;

layout(push_constant) uniform PushConstants {
    mat4 mvp;
    float screenW, screenH, snapPixel;
} pc;

layout(location = 0) out vec2 fragUV;
layout(location = 1) out vec4 fragColor;
layout(location = 2) out float fragTexture;

void main() {
    vec4 clip = pc.mvp * vec4(inPosition, 1.0);
    if (pc.snapPixel > 0.5) {
        vec2 ndc = clip.xy / clip.w;
        vec2 px = (ndc * 0.5 + 0.5) * vec2(pc.screenW, pc.screenH);
        px = floor(px + 0.5);
        ndc = px / vec2(pc.screenW, pc.screenH) * 2.0 - 1.0;
        clip.xy = ndc * clip.w;
    }
    gl_Position = clip;
    fragUV = inUV;   // uv 直接就是这一块面自己的 0~1(zb 每段每面一块贴图)
    fragColor = inColor;
    fragTexture = inTexture;
}
