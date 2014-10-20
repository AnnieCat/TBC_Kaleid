#version 150

uniform vec2 mUV;
uniform sampler2D mDepth;
 
void main(void)
{
	vec2 cUV = vec2(mUV);
    vec2 cHalf = gl_FragCoord.xy*vec2(0.5,0.5);
    vec2 cTheta = gl_FragCoord.xy-cHalf;
    cUV.y*=sin(cTheta.y*0.01);
    cUV.x*=1.5*cos(cTheta.x*0.01)+2.0;
    gl_FragColor = vec4(texture2D(mDepth,cUV).rgb,1.0);
}