#shader vertex
#version 330 core

layout(location = 0) in vec4 a_Position;
layout(location = 1) in vec4 a_Color;

// output to fragment shaders
out vec4 frag_Color;

void main()
{
	gl_Position =  a_Position;

    frag_Color = a_Color;

}

#shader fragment
#version 330 core

uniform float H;
uniform float W;

layout(location = 0) out vec4 color;
in vec4 gl_FragCoord;

in vec4 frag_Color;

void main() {
	if(round(mod(gl_FragCoord.x, 13.0f)) == 0.0f || round(mod(gl_FragCoord.y, 13.0f)) == 0.0f)
        color = vec4(0.4f, 0.4f, 0.4f, 1.0f);
    else
        color = vec4(0.0f, 0.0f, 0.0f, 1.0f);
}


