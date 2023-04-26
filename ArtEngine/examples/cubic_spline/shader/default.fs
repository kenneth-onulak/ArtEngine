#version 330

in vec4 ex_Color;
in vec3 ex_Normal;

in vec3 ex_Model;//Model Space
in vec4 ex_Frag;

out vec4 fragColor;

uniform vec3 camera;
uniform vec3 color;
uniform float alpha;

void main(void)
{
    fragColor = vec4(color, alpha);
}
