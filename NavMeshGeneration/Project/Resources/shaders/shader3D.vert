#version 450

layout(binding = 0) uniform UniformBufferObject 
{
    mat4 model;
    mat4 view;
    mat4 proj;

    int useNormalMap;
    vec3 cameraPos;

} ubo;

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec2 inTexCoord;
layout(location = 2) in vec3 inNormal;
layout(location = 3) in vec3 inTangent;
layout(location = 4) in vec3 inBitangent;


layout(location = 0) out vec2 fragTexCoord;
layout(location = 1) out vec3 fragNormal;
layout(location = 2) out vec3 fragTangent;
layout(location = 3) out vec3 fragBitangent;
layout(location = 4) out vec3 fragPos;

layout(location = 5) out vec3 fragCameraPos;

layout(location = 6) out int fragUseNormalMap;

void main() 
{
    gl_Position = ubo.proj * ubo.view * ubo.model * vec4(inPosition, 1.0);

    fragNormal = (ubo.model * vec4(inNormal, 0)).rgb;
    fragTexCoord = inTexCoord;
    fragTangent = (ubo.model * vec4(inTangent, 0)).rgb;
    fragBitangent = (ubo.model * vec4(inBitangent, 0)).rgb;
    fragPos = inPosition;
    fragCameraPos = ubo.cameraPos;

    // Extract the camera position from the view matrix
    mat3 viewRotMat = mat3(ubo.view);        // Extract rotation part of view matrix
    vec3 viewTrans = vec3(ubo.view[3]);      // Extract translation part of view matrix


    fragUseNormalMap = ubo.useNormalMap;
}