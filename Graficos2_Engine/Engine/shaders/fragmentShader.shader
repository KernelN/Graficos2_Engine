#version 330 core
out vec4 fragColor;
in vec4 ourColor;

void main()
{
    fragColor = ourColor;
}