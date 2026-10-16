#version 450

layout(location = 0) in vec2 fragUV;
layout(location = 1) in vec4 fragColor;
layout(location = 2) in float fragTexture;

layout(set = 0, binding = 0) uniform sampler2D lineTexture;

layout(location = 0) out vec4 outColor;

void main() {
    // 0 = 纯顶点色;1 = 贴图色乘顶点色(线/图);2 = 取贴图 alpha 乘顶点色(字体图集:字形覆盖率在 alpha 里)
    if (fragTexture > 1.5) {
        outColor = vec4(fragColor.rgb, fragColor.a * texture(lineTexture, fragUV).a);
        return;
    }
    outColor = fragColor * (fragTexture > 0.5 ? texture(lineTexture, fragUV) : vec4(1.0));
}
