attribute vec4 a_pos;

varying vec2 v_uv;

void main() {
	gl_Position = vec4(a_pos.xy, -0.5, 1.0);
	v_uv = a_pos.zw;
}