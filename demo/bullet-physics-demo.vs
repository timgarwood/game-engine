#version 330

layout (location = 0) in vec3 Position;

uniform mat4 gTransformation;
uniform mat4 gStartOffset;
uniform mat4 gRotation;
uniform mat4 gView;
uniform vec3 gColor;

out vec3 Color;

void main()
{
    gl_Position = gView * gTransformation * vec4(Position, 1.0);
    Color = gColor;
}
