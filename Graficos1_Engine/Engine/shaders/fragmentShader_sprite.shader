#version 330 core
in vec2 v_SpriteCoord;

uniform sampler2D u_Sprite;

void main()
{
   vec4 texColor = texture(u_Sprite, v_SpriteCoord);
}