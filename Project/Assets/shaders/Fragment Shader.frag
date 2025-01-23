#version 330 core
in vec3 ourColor;  // Ricevuto dal Vertex Shader
out vec4 FragColor;

void main() {
    FragColor = vec4(ourColor, 1.0);  // Usa il colore ricevuto
}
