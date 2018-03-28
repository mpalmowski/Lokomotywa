#version 330 core

uniform sampler2D diffuse;
varying vec2 texture_position0;

void main()
{
	gl_FragColor = texture2D(diffuse, texture_position0);
}