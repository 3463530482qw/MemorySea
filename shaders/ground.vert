#version 450

layout(push_constant) uniform PushConstants {
    mat4 mvp;
    vec4 minorColor;
    vec4 majorColor;
    vec4 gridParams;    // x = 小格边长, y = 每几格一条主线, z = 淡出距离, w = 四边形半径
    vec4 eyeGround;     // xy = 相机在地面上的投影
} pc;

layout(location = 0) out vec3 worldPosition;

const vec2 corners[6] = vec2[6](
    vec2(-1.0, -1.0), vec2(1.0, -1.0), vec2(1.0, 1.0),
    vec2(-1.0, -1.0), vec2(1.0, 1.0), vec2(-1.0, 1.0)
);

void main() {
    // 六个顶点按 gl_VertexIndex 展开:以相机地面投影为中心的正方形(y 恒 0 = 地面),
    // 半径由推常量给,所以这块面片跟着相机走 —— 走到哪都有地面,看不到边界
    vec2 offset = corners[gl_VertexIndex] * pc.gridParams.w;
    worldPosition = vec3(pc.eyeGround.x + offset.x, 0.0, pc.eyeGround.y + offset.y);
    gl_Position = pc.mvp * vec4(worldPosition, 1.0);
}
