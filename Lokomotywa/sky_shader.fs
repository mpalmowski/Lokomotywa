#version 330 core

uniform sampler2D diffuse;
varying vec2 texture_position0;
varying vec3 normal0;
varying vec2 light0;

void main()
{
	gl_FragColor = texture2D(diffuse, texture_position0) * light0.y;
}