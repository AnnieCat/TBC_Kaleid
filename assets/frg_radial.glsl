void main(void)
{
	vec2 uv = gl_FragCoord.xy / iResolution.xy;
    vec2 cHalf = vec2(0.5,0.5);
    vec2 cDist = cHalf - uv;
    cDist = normalize(cDist);
    vec2 cSample = uv+cDist*0.1;
    
	gl_FragColor = vec4(texture2D(iChannel0,cSample).rgb,1.0);
}