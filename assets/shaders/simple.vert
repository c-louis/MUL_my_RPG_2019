#version 130

void main()
{
        gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;	
        gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;
        gl_FrontColor = vec4(1,0,0,1);
}
