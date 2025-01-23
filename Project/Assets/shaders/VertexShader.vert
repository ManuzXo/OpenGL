#version 330 core
layout(location = 0) in vec3 aPos;  // Posizione (associata al VBO)
layout(location = 1) in vec3 aColor; // Colore (associato al VBO)

out vec3 ourColor;  // Passaggio al Fragment Shader

void main() {
    gl_Position = vec4(aPos, 1.0);  // Trasformazione del vertice
    ourColor = aColor;             // Trasmetti il colore
}
