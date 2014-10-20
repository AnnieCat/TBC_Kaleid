void main(void)
{
	vec2 uv = gl_FragCoord.xy / iResolution.xy;
	vec2 cHalf = vec2(0.5,0.5);
    vec2 cTheta = cHalf-uv;
    float d = length(cTheta)*2.0;

	float s = sin(d-iGlobalTime)*2.0;
    uv.y += cTheta.y*s;
    gl_FragColor = vec4(texture2D(iChannel1,uv).rgb,1.0);
}