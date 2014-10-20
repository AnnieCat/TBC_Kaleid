#include "cinder/app/AppNative.h"
#include "cinder/audio/Context.h"
#include "cinder/Camera.h"
#include "cinder/CinderMath.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Texture.h"
#include "cinder/gl/GlslProg.h"
#include "cinder/ImageIo.h"

#include "Zoom.h"
#include "Three.h"
using namespace ci;
using namespace ci::app;
using namespace std;

typedef std::unique_ptr<CameraPersp> CameraPtr;

class TBC_KaleidApp : public AppNative {
public:
	void prepareSettings(Settings *pSettings);
	void setup();
	void mouseDown( MouseEvent event );
	void keyDown(KeyEvent pEvent);
	void update();
	
	void draw();

	enum KaleidMode
	{
		KM_ZOOM, KM_THREE, KM_GLOBE
	};

private:
	gl::Texture DepthFeed;
	KaleidMode mMode;
	CameraPtr mCamera;
	ZoomControlPtr mZoomControl;
	ThreeControlPtr mThreeControl;

};

void TBC_KaleidApp::prepareSettings(Settings *pSettings)
{
	pSettings->setWindowSize(720, 1280);
	pSettings->setWindowPos(Vec2i(20,20));
	pSettings->setFrameRate(30.0f);
}

void TBC_KaleidApp::setup()
{
	DepthFeed = gl::Texture(loadImage(loadAsset("capture.png")));

	mMode = KM_THREE;
	mCamera = make_unique<CameraPersp>();
	mCamera->setPerspective(60.f, getWindowAspectRatio(), 0.1f, 1000.0f);
	mCamera->lookAt(Vec3f::zero(), Vec3f(0, 0, 1000));

	mZoomControl = make_unique<ZoomControl>(200.0f,3,DepthFeed);
	mThreeControl = make_unique<ThreeControl>(DepthFeed);

}

void TBC_KaleidApp::keyDown(KeyEvent pEvent)
{
	char cChar = pEvent.getChar();
	switch (cChar)
	{
		case 'q':
		{
			quit();
			break;
		}
		case '3':
		{
			//go back
			int cMode = (int)mMode;
			cMode--;
			if (cMode < 0)
				cMode = 2;
			mMode = (KaleidMode)cMode;
			break;
		}
		case '5':
		{
			//go forward
			int cMode = (int)mMode;
			cMode++;
			if (cMode > 2)
				cMode = 0;
			mMode = (KaleidMode)cMode;
			break;
		}
	}
}

void TBC_KaleidApp::mouseDown( MouseEvent event )
{
}

void TBC_KaleidApp::update()
{
	switch (mMode)
	{
		case KaleidMode::KM_ZOOM:
		{
			mZoomControl->step();
			break;
		}
		case KaleidMode::KM_THREE:
		{
			mThreeControl->step();
			break;
		}
		case KaleidMode::KM_GLOBE:
		{
			break;
		}
	}
}

void TBC_KaleidApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) ); 
	gl::enableAlphaBlending();
	gl::setMatrices(*mCamera);

	switch (mMode)
	{
		case KaleidMode::KM_ZOOM:
		{
			mZoomControl->display();
			break;
		}
		case KaleidMode::KM_THREE:
		{
			mThreeControl->display();
			break;
		}
		case KaleidMode::KM_GLOBE:
		{
			gl::color(Color::white());
			gl::drawSphere(Vec3f(0,0,300), 10);
			break;
		}
	}
	gl::disableAlphaBlending();
}

CINDER_APP_NATIVE( TBC_KaleidApp, RendererGl )

