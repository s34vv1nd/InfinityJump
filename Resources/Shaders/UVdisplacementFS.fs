precision mediump float;
uniform sampler2D u_texture;
uniform sampler2D u_dispTexture;
uniform sampler2D u_maskTexture;
uniform vec2 u_dispMax;
uniform float u_time;

varying vec2 v_uv;

void main()
{
	vec2 disp = texture2D(u_dispTexture, vec2(v_uv.x, v_uv.y + u_time)).rg;
	vec2 offset = (2.0 * disp - 1.0) * u_dispMax;
	vec4 color = texture2D(u_texture, v_uv + offset);
	vec4 alphaValue = texture2D(u_maskTexture, v_uv);
	gl_FragColor = color * vec4(1.0, 1.0, 1.0, alphaValue.r);
}