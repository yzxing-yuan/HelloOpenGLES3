#version 300 es

layout(location = 0) in vec4 a_position;
layout(location = 1) in vec3 a_color;
out vec3 v_color;

void main()
{
   gl_Position = a_position;
   v_color = a_color;
}
