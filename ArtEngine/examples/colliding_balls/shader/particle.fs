#version 460 core

in vec2 pos;
flat in int index;
out vec4 fragColor;

layout (std430, binding = 2) buffer velocity
{
    vec4 v[];
};

uniform float R;

void main()
{
    if (length(pos) > R) discard;
    else
    {
        vec3 color = vec3(1.0-0.005 * length(v[index].xyz));
        fragColor = vec4(color, 1.0f);
    }
}
