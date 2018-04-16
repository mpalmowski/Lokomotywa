#version 330 core

uniform sampler2D diffuse;
varying vec2 texture_position0;
varying vec3 normal0;
varying vec2 light0;

void main()
{
	gl_FragColor = texture2D(diffuse, texture_position0) * clamp(dot(-vec3(-0.3,-0.6,-1), normal0), light0.x, light0.y);
}