#version 440

struct Material{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	sampler2D diffuseTex;
	sampler2D specularTex;
};

in vec3 vs_position;
in vec3 vs_color;
in vec2 vs_texcoord;
in vec3 vs_normal;

out vec4 fs_color;

uniform Material material;

uniform vec3 lightPos0;
uniform vec3 cameraPos;

vec3 CalculateAmbient(Material material){
	return material.ambient;
}

vec3 CalculateDiffuse(Material material, vec3 vs_position, vec3 lightPos0, vec3 vs_normal){
	vec3 posToLightDirVec = normalize(lightPos0 - vs_position);
	vec3 diffuse = clamp(dot(posToLightDirVec, vs_normal) , 0 , 1) * material.diffuse;

	return diffuse;
}

vec3 CalculateSpecular(Material material, vec3 vs_position, vec3 lightPos0, vec3 vs_normal, vec3 cameraPos){
	vec3 lightToPosDirVec = normalize(vs_position -lightPos0);
	vec3 reflectDirVec = normalize(reflect(lightToPosDirVec, normalize(vs_normal)));
	vec3 posToViewDirVec = normalize(cameraPos - vs_position);
	float specularConstant = pow(max(dot(reflectDirVec, posToViewDirVec), 0) , 30);
	vec3 specular = material.specular * specularConstant ;
	//specular *= texture(material.specularTex, vs_texcoord).rgb;
	return specular;
}
void main(){
	//fs_color = vec4(vs_color, 1.f);
	
	//ambient light
	vec3 ambientLight = CalculateAmbient(material);

	//diffuse light
	vec3 diffuse = CalculateDiffuse(material, vs_position, lightPos0, vs_normal);

	//Specular light
	vec3 specular = CalculateSpecular(material, vs_position, lightPos0, vs_normal, cameraPos);
	//fs_color =  (vec4(ambientLight, 1.f) + vec4(diffuse, 1.f) + vec4(specular, 1.f));
	fs_color =  texture(material.diffuseTex, vs_texcoord) * (vec4(ambientLight, 1.f) + vec4(diffuse, 1.f) + vec4(specular, 1.f));
}