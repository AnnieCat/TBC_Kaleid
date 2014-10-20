#ifdef _DEBUG
#pragma comment(lib, "DSAPI32.dbg.lib")
#else
#pragma comment(lib, "DSAPI32.lib")
#endif
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
#include "Globe.h"
#include "Wavey.h"
#include "DSAPI.h"
#include "DSAPIUtil.h"

using namespace ci;
using namespace ci::app;
using namespace std;

typedef std::unique_ptr<CameraPersp> CameraPtr;

class TBC_KaleidApp : public AppNative {
public:
	void prepareSettings(Settings *pSettings);
	void initDS4();
	void setup();
	void mouseDown( MouseEvent event );
	void keyDown(KeyEvent pEvent);
	void update();
	
	void draw();

	enum KaleidMode
	{
		KM_ZOOM,
		KM_THREE,
		KM_GLOBE,
		KM_WAVE
	};

private:
	gl::Texture DepthFeed;
	KaleidMode mMode;
	CameraPtr mCamera;
	ZoomControlPtr mZoomControl;
	ThreeControlPtr mThreeControl;

	DSAPI *mDS4;
	uint16_t *mDepth;
};

void TBC_KaleidApp::prepareSettings(Settings *pSettings)
{
	pSettings->setWindowSize(720, 1280);
	pSettings->setWindowPos(Vec2i(20,20));
	pSettings->setFrameRate(30.0f);
}

void TBC_KaleidApp::initDS4()
{
	mDS4 = DSCreate(DS_DS4_PLATFORM);
    DSHardware *mHardware = mDS4->accessHardware();

	if (!mDS4->probeConfiguration())
	{
		console() << "Unable to access DS4 Config" << endl;
		quit();
	}

    if (!mDS4->isCalibrationValid())
    {
        console() << "Calibration data on camera is invalid" << endl;
		quit();
    }

	if (mDS4->enableZ(true))
	{
		if (!mDS4->setLRZResolutionMode(true, 480, 360, 60, DS_LUMINANCE8))
		{
			console() << "Unable to set desired depth resolution" << endl;
			quit();
		}
		mDS4->enableLRCrop(true);

	}
	else
	{
		console() << "Unable to start depth streaming" << endl;
		quit();
	}

	if (!mDS4->startCapture())
	{
		console() << "Unable to start DS4, exiting" << endl;
		quit();
	}
}

void TBC_KaleidApp::setup()
{
	//DepthFeed = gl::Texture(loadImage(loadAsset("capture.png")));
	DepthFeed = gl::Texture(480, 360);
	mMode = KM_THREE;
	mCamera = make_unique<CameraPersp>();
	mCamera->setPerspective(60.f, getWindowAspectRatio(), 0.1f, 1000.0f);
	mCamera->lookAt(Vec3f::zero(), Vec3f(0, 0, 1000));

	mZoomControl = make_unique<ZoomControl>(200.0f,3,DepthFeed);
	mThreeControl = make_unique<ThreeControl>(DepthFeed);

	initDS4();
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
		case KaleidMode::KM_WAVE:
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


	switch (mMode)
	{
		case KaleidMode::KM_ZOOM:
		{
			gl::setMatrices(*mCamera);
			mZoomControl->display();
			break;
		}
		case KaleidMode::KM_THREE:
		{
			gl::setMatrices(*mCamera);
			mThreeControl->display();
			break;
		}
		case KaleidMode::KM_GLOBE:
		{
			gl::setMatrices(*mCamera);
			gl::color(Color::white());
			gl::drawSphere(Vec3f(0,0,300), 10);
			break;
		}
		case KaleidMode::KM_WAVE:
		{
			gl::setMatricesWindow(getWindowSize());
			break;
		}
	}
	gl::disableAlphaBlending();
}

CINDER_APP_NATIVE( TBC_KaleidApp, RendererGl )

