#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class TBC_KaleidApp : public AppNative {
  public:
	void setup();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();
};

void TBC_KaleidApp::setup()
{
}

void TBC_KaleidApp::mouseDown( MouseEvent event )
{
}

void TBC_KaleidApp::update()
{
}

void TBC_KaleidApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) ); 
}

CINDER_APP_NATIVE( TBC_KaleidApp, RendererGl )
