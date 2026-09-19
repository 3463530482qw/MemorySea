#version 450

layout(push_constant) uniform PushConstants {
    mat4 mvp;
    vec4 minorColor;
    vec4 majorColor;
    vec4 gridParams;    // x = 小格边长, y = 每几格一条主线, z = 淡出距离, w = 四边形半径
    vec4 eyeGround;     // xy = 相机在地面上的投影
} pc;

layout(location = 0) in vec3 worldPosition;
layout(location = 0) out vec4 outColor;

// 世界坐标除以格距之后取到格子边界:交给 fwidth 把线条按屏幕像素定量,天然抗锯齿
float grid_line(vec2 coord) {
    vec2 grid = abs(fract(coord - 0.5) - 0.5) / fwidth(coord);
    return 1.0 - min(min(grid.x, grid.y), 1.0);
}

void main() {
    float gridSize = pc.gridParams.x;
    float majorEvery = pc.gridParams.y;
    float fadeDistance = pc.gridParams.z;

    float minor = grid_line(worldPosition.xz / gridSize);
    float major = grid_line(worldPosition.xz / (gridSize * majorEvery));

    // 离相机地面投影越远越淡:远处格线密到分不出格,让它自然消隐
    float distance = length(worldPosition.xz - pc.eyeGround.xy);
    float fade = 1.0 - smoothstep(fadeDistance * 0.3, fadeDistance, distance);
    if (fade <= 0.002) {
        discard;
    }

    bool majorOn = major > minor;
    vec3 rgb = majorOn ? pc.majorColor.rgb : pc.minorColor.rgb;
    float alpha = max(minor, major) * (majorOn ? pc.majorColor.a : pc.minorColor.a) * fade;
    if (alpha <= 0.002) {
        discard;   // 格线之间不写深度,后面的东西照旧看得见
    }
    outColor = vec4(rgb, alpha);
}
