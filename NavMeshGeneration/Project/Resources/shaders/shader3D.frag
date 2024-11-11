#version 450


layout(binding = 1) uniform sampler2D textures[4];


layout(location = 0) in vec2 fragTexCoord;
layout(location = 1) in vec3 fragNormal;
layout(location = 2) in vec3 fragTangent;
layout(location = 3) in vec3 fragBitangent;
layout(location = 4) in vec3 fragPos;

layout(location = 5) in vec3 cameraPos;

layout(location = 6) flat in int useNormalMap;


layout(location = 0) out vec4 outColor;

vec3 G_SunLightDirection = normalize(vec3(0.577, 0.577, 0.557));
//vec3 G_SunLightColor = vec3(1.0, 0.9, 0.7);
vec3 G_SunLightColor = vec3(1.0, 1.0, 1.0);
float G_SunLightIntensity = 1;

float G_AmbientIntensity = 0.03;

const float PI = 3.14159265358979323846;

vec3 GetNormal()
{
    vec3 normal;

    if (useNormalMap == 1) 
    {
        vec3 T = normalize(fragTangent);
        vec3 B = normalize(fragBitangent);
        vec3 N = normalize(fragNormal);
        mat3 TBN = mat3(T, B, N);

        vec3 sampledNormal = texture(textures[3], fragTexCoord).rgb;
        sampledNormal = normalize(sampledNormal * 2.0 - 1.0);

        normal = normalize(TBN * sampledNormal);
    } 
    else 
    {
        normal = normalize(fragNormal);
    }

    return normal;
}

vec3 GetRadiance(vec3 lightColor, float lightIntensity)
{
    return lightColor * lightIntensity;
}

vec3 FresnelFunction_Schlick(vec3 halfVector, vec3 viewDir, vec3 f0)
{
	float powerExpression = 1 - (dot(halfVector, viewDir));

	return f0 + (1 - f0) * powerExpression * powerExpression * powerExpression * powerExpression * powerExpression;

}
float NormalDistribution_GGX(vec3 normal, vec3 halfVector, float roughness)
{
    const float alphaSq = (roughness * roughness) * (roughness * roughness);
	const float dot = dot(normal, halfVector);
	const float expression = dot * dot * (alphaSq - 1) + 1;

	return alphaSq / (PI * expression * expression);
}
float GeometryFunction_SchlickGGX(vec3 normal, vec3 viewDir, float roughness)
{
    const float alpha = roughness * roughness;
	const float k = (alpha + 1) * (alpha + 1) / 8.f;
	const float dot = dot(normal, -viewDir);
	if (dot < 0) return 0;

	return dot / (dot * (1 - k) + k);
}
float GeometryFunction_Smith(vec3 normal, vec3 viewDir, vec3 lightDir, float roughness)
{
    return GeometryFunction_SchlickGGX(normal, viewDir, roughness) * GeometryFunction_SchlickGGX(normal, lightDir, roughness);
}

vec3 GetBRDF(vec3 normal, vec3 lightDir, vec3 viewDir, vec3 albedo, float metallic, float roughness)
{
    vec3 halfVector = normalize(lightDir + viewDir);
	vec3 f0 = (metallic < 0.0001) ? vec3( 0.04, 0.04, 0.04) : albedo;

	vec3 fresnel = FresnelFunction_Schlick(halfVector, viewDir, f0);
	float normalDistribution = NormalDistribution_GGX(normal, halfVector, roughness);
	float geometryTerm = GeometryFunction_Smith(normal, viewDir, lightDir, roughness);

	float reverseDenominator = 1 / (4 * dot(viewDir , normal) * dot(lightDir , normal));

	vec3 cookTorrence = normalDistribution * (fresnel * (geometryTerm * reverseDenominator));


	vec3 kd = (metallic < 0.0001) ? vec3(1.0, 1.0, 1.0) - fresnel : vec3(0, 0, 0);
	vec3 diffuseLambert = kd * albedo / PI;

	return diffuseLambert + cookTorrence;
}

void main() 
{
    vec4 albedo = texture(textures[0], fragTexCoord);
    float metallic = texture(textures[1], fragTexCoord).r;
    float roughness = texture(textures[2], fragTexCoord).r;
    
    vec3 normal = GetNormal();

    vec3 ambient = G_AmbientIntensity * albedo.rgb;
    float cosineLaw = max(dot(normal, G_SunLightDirection), 0);
    vec3 viewDir = normalize(fragPos - cameraPos); // Camera direction

    vec3 radiance = GetRadiance(G_SunLightColor, G_SunLightIntensity);
    vec3 brdf = GetBRDF(normal, -G_SunLightDirection, viewDir, albedo.rgb, metallic, roughness);

    vec3 finalColor = ambient + cosineLaw * radiance * brdf;
    outColor = vec4(finalColor, albedo.a);
}