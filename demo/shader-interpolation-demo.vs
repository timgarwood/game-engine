#version 330

layout (location = 0) in vec3 Position;

out vec4 Color;

vec4 colors[3] = vec4[3]( vec4(1,0,0,1),
                          vec4(0,1,0,1),
                          vec4(0,0,1,1) );

void main()
{
    gl_Position = vec4(Position, 1.0);
    Color = colors[gl_VertexID];
}
