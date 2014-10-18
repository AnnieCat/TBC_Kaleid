#ifndef __ZOOM__
#define __ZOOM__

#include <vector>
#include "cinder/gl/gl.h"
#include "cinder/gl/GlslProg.h"
#include "cinder/gl/Texture.h"
#include "cinder/Rect.h"

using namespace ci;
using namespace std;

class ZoomPlate
{
public:
	ZoomPlate();
	ZoomPlate(const float &pStartDepth);
	~ZoomPlate();

	void step();
	void display();

	bool IsDead;
	float CurrentDepth;
	gl::GlslProg PlateShader;
	gl::Texture PlateTexture;

private:
	Rectf mUpper;
	Rectf mLower;

	float mStartDepth;
};

class ZoomControl
{
public:
	ZoomControl();
	ZoomControl(const float &pTriggerDepth, const int &pNumPlates);
	~ZoomControl();

	void step();
	void display();

	float TriggerDepth;
	int NumPlates;
private:
	vector<ZoomPlate> mPlates;
};

typedef std::unique_ptr<ZoomControl> ZoomControlRef;
#endif