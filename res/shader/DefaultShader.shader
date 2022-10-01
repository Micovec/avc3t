#shader vertex
#version 330 core

//layout(location = 0) out vec4 color;
//
////in vec2 v_TexCoord;
//
//uniform vec4 u_Color;
////uniform sampler2D u_Texture;
//
//void main()
//{
//	//vec4 texColor = texture(u_Texture, v_TexCoord);
//	color = u_Color;
//};

in vec3 i_Position;
in vec3 i_Normal;
in vec2 i_Uv;

uniform mat4 u_MVP;
uniform mat4 u_ViewMatrix;
uniform mat4 u_NormalMatrix;

smooth out vec2 v_uv;
out vec3 v_Normal;

void main()
{
	gl_Position = u_MVP * vec4(i_Position, 1);

	v_uv = i_Uv;
	v_Normal = normalize((u_ViewMatrix * u_NormalMatrix * vec4(i_Normal, 0)).xyz);	// Normal in eye coords
}

#shader fragment
#version 330 core

struct Material
{
	vec3 ambient;
	vec3 diffuse;

	// Texture
	sampler2D diffuseSampler;
};

struct Light
{
	// Color changing variables
	vec3 ambient;
	vec3 diffuse;

	// Transform
	vec3 direction;
};

uniform Material u_Material;
uniform mat4 u_ViewMatrix;

// Lights
uniform Light u_DirectionalLight;

smooth in vec2 v_uv;		// Texture position
in vec3 v_Normal;	// Eye space coord

out vec4 o_Color;

// Method definition
vec4 calculateLight(vec3 lightVector, vec3 vertexNormal, Material material, Light light);
vec4 directionalLight(vec3 vertexNormal, Material material, Light light);

void main()
{
	vec4 finalColor = directionalLight(v_Normal, u_Material, u_DirectionalLight);

	o_Color = finalColor;
}

vec4 calculateLight(vec3 lightVector, vec3 vertexNormal, Material material, Light light)
{
	vec4 materialDiffuseTex = texture(material.diffuseSampler, v_uv);

	// Ambient
	vec4 ambient = vec4(light.ambient * material.ambient.rgb, 1);

	// Diffuse
	vec3 normal = normalize(vertexNormal);
	//vec3 normal = normalize(vec3(1,1,0));

	float diff = max(dot(normal, lightVector), 0.0);
	vec4 diffuse = vec4(light.diffuse * material.diffuse.rgb, 1) * diff;

	return (ambient + diffuse) * materialDiffuseTex;
}

vec4 directionalLight(vec3 vertexNormal, Material material, Light light)
{
	vec3 lightDirection = normalize(mat3(u_ViewMatrix) * light.direction);
	return calculateLight(lightDirection, vertexNormal, material, light);
}

// -----------------------------------------------------
