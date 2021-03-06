/* Shader for approximating the way RMXP does bitmap
 * blending via DirectDraw */

uniform sampler2D source;
uniform sampler2D destination;

uniform vec4 subRect;

uniform float opacity;

varying vec2 v_texCoord;

void main()
{
	vec2 coor = v_texCoord;
	vec2 dstCoor = (coor - subRect.xy) * subRect.zw;

	vec4 srcFrag = texture2D(source, coor);
	vec4 dstFrag = texture2D(destination, dstCoor);

	vec4 resFrag;

	float ab = opacity;
	float as = srcFrag.a;
	float ad = dstFrag.a;

	float at = ab*as;
	resFrag.a = at + ad - ad*at;

	// Sigh...
	if (ad == 0.0)
		resFrag.rgb = srcFrag.rgb;
	else
		resFrag.rgb = as*srcFrag.rgb + (1.0-at) * ad * dstFrag.rgb;

	gl_FragColor = resFrag;
}
