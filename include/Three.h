#ifndef __THREE__
#define __THREE__

#include <vector>
#include "cinder/gl/gl.h"
#include "cinder/gl/GlslProg.h"
#include "cinder/gl/Texture.h"
#include "cinder/Rect.h"

using namespace std;
using namespace ci;

class ThreeLayer
{
public:
	ThreeLayer();
	ThreeLayer(const gl::Texture &pTexture);
	~ThreeLayer();

	void step();
	void display();
	
	float AngVel;
private:
	float mDepth;
	Rectf mPlane;
	gl::Texture mDepthFeed;
};
typedef std::shared_ptr<ThreeLayer> ThreeLayerRef;

class ThreeControl
{
public:
	ThreeControl();
	ThreeControl(const gl::Texture &pTexture);
	~ThreeControl();

	void step();
	void display();

private:
	float mAngle;
	ThreeLayerRef mLayerNear;
	ThreeLayerRef mLayerMid;
	ThreeLayerRef mLayerFar;
};

typedef std::unique_ptr<ThreeControl> ThreeControlPtr;
#endif