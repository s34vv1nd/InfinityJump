precision mediump float;
uniform sampler2D u_texture0;
uniform sampler2D u_texture1;
uniform sampler2D u_texture2;
uniform sampler2D u_blendmap;

uniform vec4 u_fogColor;
uniform float u_fogMaxDist;
uniform float u_fogMinDist;

varying float v_distToCamera;
varying vec2 v_uv;

float computeLinearFogFactor()
{
	float factor;
	factor = (v_distToCamera - u_fogMaxDist) / (u_fogMaxDist - u_fogMinDist);
	factor = clamp(factor, 0.0, 1.0);
	return factor;
}

void main(void)
{
	vec4 tex0Color = texture2D(u_texture0, v_uv);
	vec4 tex1Color = texture2D(u_texture1, v_uv);
	vec4 tex2Color = texture2D(u_texture2, v_uv);
	vec4 blend = texture2D(u_blendmap, v_uv);
	blend = blend / (blend.r + blend.g + blend.b);
	vec4 baseColor = blend.r * tex0Color + blend.g * tex1Color + blend.b * tex2Color;

	float fogFactor = computeLinearFogFactor();
	gl_FragColor = fogFactor * u_fogColor + (1.0 - fogFactor) * baseColor;
}