#version 130

varying vec2 texCoord0;
varying vec3 normal0;
varying vec3 color0;
varying vec3 weight0;
varying vec3 position0;

uniform sampler2D sampler;
uniform vec3 [2]lightDirection;
uniform vec3 [2]lightColor;
uniform vec4 ambient;
uniform vec4 diffuse;
uniform vec4 specular;

uniform int bonus;
uniform int index;
uniform vec3 eye;
vec3 CalcDiffuse(vec3 L){

	vec3 kd = diffuse.xyz;//vec3(0.8f,0.4f,0.5f);
	vec3 diffuse2 = kd*max(dot(normal0,normalize(-L)),0);
	return diffuse2;
}

vec3 calcSpecular(vec3 L){
	vec3 Ks =specular.xyz;
	vec3 u = normalize(L);
	//vec3 R = normalize(u - 2*normal0*dot(u,normal0));
	vec3 R= reflect(u,normalize(normal0));
	vec3 V = normalize(eye-position0);
	vec3 specular = Ks*max(pow(dot(V, R),50), 0);
	specular = clamp(specular, vec3(0.0,0.0,0.0),vec3(1.0,1.0,1.0));
	return specular;
}

void main()
{
	
  //  vec3 tmp = dot(-lightDirection[0], normal0) * color0 ;
//	if(index >4)
	{
	//gl_FragColor = clamp((texture2D(sampler, texCoord0) *clamp(vec4(tmp,1.0), 0.0, 1.0) +  vec4(CalcDiffuse(L),1.0) + vec4(calcSpecular(L),1.0)+ ambient),0.0,0.85);
	//gl_FragColor=texture2D(sampler,texCoord0);
	}
	//else
	//	gl_FragColor = clamp((texture2D(sampler, texCoord0) *clamp(vec4(tmp,1.0), 0.0, 1.0) ),0.0,0.85);

	vec3 ia=vec3(1,1,1);
	vec3 ambint=vec3(ambient.xyz)*ia;
	vec3 L = vec3(0.0f,0.5f,-1.0f);
	vec3 L1=normalize(-L);
	vec3 i1dif=vec3(0.8,0.7,1);
	vec3 dif=CalcDiffuse(L);//vec3(diffuse.xyz)*(dot(normal0,L1))*i1dif;
	vec3 i1spec=vec3(0.6,0.7,0.3);
	int alpha=10;
	vec3 v=eye-position0;
	if(v!=vec3(0,0,0))
	{v=normalize(v);}
	vec3 spec=calcSpecular(L);//vec3(specular.xyz)*max(0,pow(dot(v,reflect(L1,normalize(normal0))),alpha))*i1spec;

	//vec3 color=clamp(ambint,0,1)+clamp(dif,0,1)+clamp(spec,0,1);
	vec3 color1=clamp(ambint,0,1);
	color1+=clamp(dif,0,1);
	color1+=clamp(spec,0,1);
	gl_FragColor=clamp(vec4(clamp(color1,0,1).xyz,1)*texture2D(sampler,texCoord0),0,1);
	
	if(bonus==1)
	{
	float dist= length(eye-position0);
	float p= (80 - dist)/(80 - 20);

    p= clamp( p, 0.0, 1.0 );
 
   //if you inverse color in glsl mix function you have to
   //put 1.0 - fogFactor
   gl_FragColor = mix(vec4(1,0,0,1), gl_FragColor, 1-0.2);
		}

	//gl_FragColor = clamp(vec4(color0,1),0.0,1.0);
	//gl_FragColor = vec4(normal0,1.0);+

}








