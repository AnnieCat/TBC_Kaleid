#include "Zoom.h"

//class ZoomPlate
ZoomPlate::ZoomPlate() : CurrentDepth(1000), IsDead(false), mUpper(Rectf(-36, 64, 36, 0)), mLower(Rectf(-36, 0, 36, -64))
{
}

ZoomPlate::ZoomPlate(const float &pStartDepth) : CurrentDepth(pStartDepth), IsDead(false), mUpper(Rectf(-36, 64, 36, 0)), mLower(Rectf(-36, 0, 36, -64))
{
}

ZoomPlate::~ZoomPlate()
{

}

void ZoomPlate::step()
{
	--CurrentDepth;
	if (CurrentDepth <= 0)
		IsDead = true;
}

void ZoomPlate::display()
{
	gl::pushMatrices();
	gl::translate(0, 0, CurrentDepth);
	//PlateShader.bind();
	gl::color(ColorA(0, 1, 0, 0.5f));
	gl::drawSolidRect(mUpper);
	gl::color(ColorA(0, 0, 1, 0.5f));
	gl::drawSolidRect(mLower);
	gl::popMatrices();
	//PlateShader.unbind();
}

//class ZoomControl
ZoomControl::ZoomControl() : TriggerDepth(500), NumPlates(2)
{
	for (size_t i = 0; i < NumPlates; ++i)
	{
		mPlates.push_back(ZoomPlate());
	}
}

ZoomControl::ZoomControl(const float &pTriggerDepth, const int &pNumPlates) : TriggerDepth(pTriggerDepth), NumPlates(pNumPlates)
{
	for (size_t i = 0; i < NumPlates; ++i)
	{
		mPlates.push_back(ZoomPlate());
	}
}

ZoomControl::~ZoomControl()
{

}

void ZoomControl::step()
{
	std::for_each(mPlates.begin(), mPlates.end(), [](ZoomPlate &cZ){ cZ.step(); });
	std::remove_if(mPlates.begin(), mPlates.end(), [](ZoomPlate &cZ){ return cZ.IsDead; });
	for (const ZoomPlate &cPlate : mPlates)
	{
		if (cPlate.CurrentDepth == TriggerDepth)
		{
			if (mPlates.size() < NumPlates)
				mPlates.push_back(ZoomPlate());
		}
	}
}

void ZoomControl::display()
{
	std::for_each(mPlates.begin(), mPlates.end(), [](ZoomPlate &cZ){ cZ.display(); });
}