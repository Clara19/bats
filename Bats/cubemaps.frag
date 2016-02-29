in vec3 textureDir; // Direction vector representing a 3D texture coordinate
uniform samplerCube cubemap;  // Cubemap texture sampler

void main()
{             
    color = texture(cubemap, textureDir);
}  