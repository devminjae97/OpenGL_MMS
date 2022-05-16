#version 330 core

out vec4 FragColour;

in vec3 myColour;
in vec2 texCoord;

uniform sampler2D myTexture;

void main()
{
//  FragColour = vec4(myColour, 1.0f);
    vec4 texColour = texture(myTexture, texCoord);

    if(texColour.a < 0.1f)
        discard;                 // make transparency if colour.a value < 0.1f

   FragColour = texColour;
}