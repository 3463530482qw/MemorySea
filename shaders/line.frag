#version 450

layout(location = 0) in vec2 fragUV;
layout(location = 1) in vec4 fragColor;
layout(location = 2) in float fragTexture;

layout(set = 0, binding = 0) uniform sampler2D lineTexture;

layout(location = 0) out vec4 outColor;

void main() {
    outColor = fragTexture > 0.5 ? texture(lineTexture, fragUV) : fragColor;
}
