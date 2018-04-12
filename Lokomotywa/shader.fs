#version 330 core

uniform sampler2D diffuse;
varying vec2 texture_position0;
varying vec3 normal0;

void main()
{
	gl_FragColor = texture2D(diffuse, texture_position0) * clamp(dot(-vec3(0,-1,-1), normal0), 0.2, 0.8);
}