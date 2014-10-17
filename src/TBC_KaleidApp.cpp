#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Texture.h"
#include "cinder/gl/GlslProg.h"
#include "cinder/audio/Context.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class TBC_KaleidApp : public AppNative {
public:
	void setup();
	void mouseDown( MouseEvent event );	
	void update();
	void updateZoom();
	void updateThree();
	void updateGlobe();
	
	void draw();
	void drawZoom();
	void drawThree();
	void drawGlobe();

	enum KaleidMode
	{
		KM_ZOOM, KM_THREE, KM_GLOBE
	};
};

void TBC_KaleidApp::setup()
{
}

void TBC_KaleidApp::mouseDown( MouseEvent event )
{
}

void TBC_KaleidApp::updateZoom()
{

}

void TBC_KaleidApp::updateThree()
{

}

void TBC_KaleidApp::updateGlobe()
{

}

void TBC_KaleidApp::update()
{
}

void TBC_KaleidApp::drawZoom()
{

}

void TBC_KaleidApp::drawThree()
{

}

void TBC_KaleidApp::drawGlobe()
{

}

void TBC_KaleidApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) ); 
}

CINDER_APP_NATIVE( TBC_KaleidApp, RendererGl )
