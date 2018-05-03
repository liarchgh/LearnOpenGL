#version 330 core
uniform sampler2D ourTexture0;
uniform sampler2D ourTexture1;
uniform float mixPara;
in vec4 ourColor;
in vec2 TexCoord;
out vec4 FragColor;
void main() {
 /* FragColor = mix(mix(texture(ourTexture0, TexCoord), texture(ourTexture1, TexCoord), 0.5), ourColor, 0.2); */
 FragColor = mix(texture(ourTexture0, TexCoord), texture(ourTexture1, vec2(1.0 - TexCoord.x, TexCoord.y)), mixPara);
}
