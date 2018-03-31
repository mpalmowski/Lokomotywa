#version 330 core

attribute vec3 position;
attribute vec2 texture_position;
attribute vec3 normal;

varying vec2 texture_position0;
varying vec3 normal0;

uniform mat4 transform;

void main()
{
	gl_Position  = transform * vec4(position, 1.0);
	texture_position0 = texture_position;
	normal0 = (transform * vec4(normal, 0.0)).xyz;
}