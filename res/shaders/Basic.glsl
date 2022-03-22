#shader vertex
#version 330 core

layout(location = 0) in vec4 a_Position;

// output to fragment shaders
void main()
{
	gl_Position =  a_Position;


}

#shader fragment
#version 330 core

uniform float H;
uniform float W;

layout(location = 0) out vec4 color;
in vec4 gl_FragCoord;

void main() {
	color = vec4(0.25f, 0.5f, 1.0f, 1.0f);
}


