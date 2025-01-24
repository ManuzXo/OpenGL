#version 330 core
in vec4 ourColor;  // Ricevuto dal Vertex Shader
out vec4 FragColor;

void main() {
    FragColor = ourColor;
}
