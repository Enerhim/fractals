#version 330 core
out vec4 FragColor;

in vec2 uv;
uniform vec2 center;
uniform float zoom;
uniform int maxIter;

uniform int width;
uniform int height;

void main() {
    vec2 z = vec2(0, 0);
    vec2 c = center + vec2(-2.5f + (float(uv.x)) * 3.5f, -1.0f + (float(uv.y)) * 2.0f) * zoom;
    
    int iter = 0;
    for (int i = 0; i < maxIter; i++) {
        z = vec2(z.x*z.x - z.y*z.y + c.x, 2*z.x*z.y + c.y);
    
        if (dot(z,z) > 4) {
            break;
        }
        iter++;

    }
    vec3 color = vec3(float(iter) / float(maxIter));
    FragColor = vec4(color, 1.0f);
}
