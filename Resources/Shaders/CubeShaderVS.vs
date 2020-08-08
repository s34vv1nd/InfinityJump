attribute vec3 a_posL;
uniform mat4 u_WVP;
varying vec4 v_pos;

void main(void)
{
	v_pos = vec4(a_posL, 1.0);
	gl_Position = u_WVP * v_pos;
}