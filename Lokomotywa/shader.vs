#version 330 core

attribute vec3 position;
attribute vec2 texture_position;

varying vec2 texture_position0;

uniform mat4 transform;

void main()
{
	gl_Position  = transform * vec4(position, 1.0);
	texture_position0 = texture_position;
}