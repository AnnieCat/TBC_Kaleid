#include "Zoom.h"
#include "cinder/app/AppNative.h"

using namespace ci::app;
//class ZoomPlate
ZoomPlate::ZoomPlate() : CurrentDepth(1000), mStartDepth(1000), IsDead(false), mUpper(Rectf(-24, 36, 24, 0)), mLower(Rectf(-24, 0, 24, -36))
{
}

ZoomPlate::ZoomPlate(const float &pStartDepth) : CurrentDepth(pStartDepth), mStartDepth(pStartDepth), IsDead(false), mUpper(Rectf(-36, 64, 36, 0)), mLower(Rectf(-36, 0, 36, -64))
{
}

ZoomPlate::~ZoomPlate()
{

}

void ZoomPlate::step()
{
	CurrentDepth -= 10;
	if (CurrentDepth <= 0)
		IsDead = true;
}

void ZoomPlate::display()
{
	gl::pushMatrices();
	gl::translate(0, 0, CurrentDepth);
	//PlateShader.bind();
	gl::color(ColorA(0, 1, 0, CurrentDepth / mStartDepth));
	gl::drawSolidRect(mUpper);
	gl::color(ColorA(0, 0, 1, CurrentDepth / mStartDepth));
	gl::drawSolidRect(mLower);
	gl::popMatrices();
	//PlateShader.unbind();
}

//class ZoomControl
ZoomControl::ZoomControl() : TriggerDepth(200), NumPlates(3)
{
	mPlates.push_back(ZoomPlate());
}

ZoomControl::ZoomControl(const float &pTriggerDepth, const int &pNumPlates) : TriggerDepth(pTriggerDepth), NumPlates(pNumPlates)
{
	mPlates.push_back(ZoomPlate());	
}

ZoomControl::~ZoomControl()
{

}

void ZoomControl::step()
{
	bool cAddPlate = false;

	for (vector<ZoomPlate>::iterator pit = mPlates.begin(); pit != mPlates.end();)
	{
		if (pit->IsDead)
		{
			pit = mPlates.erase(pit);
		}
		else
		{
			pit->step();
			if (pit->CurrentDepth == TriggerDepth)
				cAddPlate = true;

			++pit;
		}
	}

	console() << "Num Plates: " << mPlates.size() << endl;
	if (cAddPlate&&mPlates.size() < NumPlates)
		mPlates.push_back(ZoomPlate());

}

void ZoomControl::display()
{
	std::for_each(mPlates.begin(), mPlates.end(), [](ZoomPlate &cZ){ cZ.display(); });
}