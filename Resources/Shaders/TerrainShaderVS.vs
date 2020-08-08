uniform mat4 u_WVP;
uniform mat4 u_WV;

attribute vec3 a_posL;
attribute vec2 a_uv;

varying float v_distToCamera;
varying vec2 v_uv;

void main()
{
	vec4 posL = vec4(a_posL, 1.0);
	gl_Position = u_WVP * posL;
	v_uv = a_uv;

	vec4 posV = u_WV * posL;
	v_distToCamera = sqrt(posV.x * posV.x + posV.y * posV.y + posV.z * posV.z);
}