#include "Zoom.h"

//class ZoomPlate
ZoomPlate::ZoomPlate() : CurrentDepth(1000), mStartDepth(1000), IsDead(false), mUpper(Rectf(-24, 36, 24, 0)), mLower(Rectf(-24, 0, 24, -36))
{
}

ZoomPlate::ZoomPlate(const float &pStartDepth, const gl::Texture &pTexture) : CurrentDepth(pStartDepth), mStartDepth(pStartDepth), IsDead(false), mUpper(Rectf(-36, 64, 36, 0)), mLower(Rectf(-36, 0, 36, -64)), DepthFeed(pTexture)
{
}

ZoomPlate::~ZoomPlate()
{

}

void ZoomPlate::step()
{
	CurrentDepth -= 5;
	if (CurrentDepth <= 0)
		IsDead = true;
}

void ZoomPlate::display()
{
	gl::pushMatrices();
	gl::translate(0, 0, CurrentDepth);
	//PlateShader.bind();
	gl::color(ColorA(0, 1, 0, CurrentDepth / mStartDepth));
	//gl::drawSolidRect(mUpper);
	gl::draw(DepthFeed, mUpper);
	gl::translate(0.0f, mLower.getHeight(), 0.0f);
	gl::scale(1.0f, -1.0f, 1.0f);
	gl::color(ColorA(0, 0, 1, CurrentDepth / mStartDepth));
	//gl::drawSolidRect(mLower);
	gl::draw(DepthFeed, mLower);
	gl::popMatrices();
	//PlateShader.unbind();
}

//class ZoomControl
ZoomControl::ZoomControl() : TriggerDepth(200), NumPlates(3)
{
	mPlates.push_back(ZoomPlate());
}

ZoomControl::ZoomControl(const float &pTriggerDepth, const int &pNumPlates, const gl::Texture &pTexture) : TriggerDepth(pTriggerDepth), NumPlates(pNumPlates), mDepthFeed(pTexture)
{
	mPlates.push_back(ZoomPlate(400,mDepthFeed));	
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

	if (cAddPlate&&mPlates.size() < NumPlates)
		mPlates.push_back(ZoomPlate(400, mDepthFeed));

}

void ZoomControl::display()
{
	std::for_each(mPlates.begin(), mPlates.end(), [](ZoomPlate &cZ){ cZ.display(); });
}