#ifndef __GLOBE__
#define __GLOBE__

#include <vector>
#include "cinder/gl/gl.h"
#include "cinder/gl/GlslProg.h"
#include "cinder/gl/Texture.h"
#include "cinder/Rect.h"

using namespace std;
using namespace ci;

class GlobeManager
{
public:
	GlobeManager();
	~GlobeManager();

private:
	vector<Rectf> mPlanes;

};

typedef std::unique_ptr<GlobeManager> GlobeManagerPtr;
#endif