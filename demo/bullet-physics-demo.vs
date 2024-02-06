#version 330

layout (location = 0) in vec3 Position;

uniform mat4 gTransformation;
uniform vec3 gColor;

out vec3 Color;

void main()
{
    gl_Position = gTransformation * vec4(Position, 1.0);
    Color = gColor;
}
