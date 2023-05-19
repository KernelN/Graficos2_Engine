#version 330 core
layout(location = 0) in vec4 aPos;   // the position variable has attribute position 0
layout(location = 1) in vec4 aColor; // the color variable has attribute position 1

out vec4 ourColor; // output a color to the fragment shader

uniform mat4 mvp;

void main()
{
    gl_Position = mvp * aPos;
    ourColor = aColor; // set ourColor to the input color we got from the vertex data
}