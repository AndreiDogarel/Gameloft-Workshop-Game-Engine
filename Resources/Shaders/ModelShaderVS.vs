attribute vec3 a_posL;
uniform mat4 u_mvp;
attribute vec2 a_uv;
varying vec2 v_uv;

void main()
{
	gl_Position = u_mvp * vec4(a_posL, 1.0);
	v_uv = a_uv;
}
   