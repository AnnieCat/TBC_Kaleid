#include "Three.h"
#include "cinder/Rand.h"


// ThreeLayer
ThreeLayer::ThreeLayer()
{
	mPlane = Rectf(-24, 36, 24, 0);
	AngVel = 2;
}

ThreeLayer::ThreeLayer(const gl::Texture &pTexture)
{
	mPlane = Rectf(-24, 36, 24, 0);
	AngVel = 2;
	mDepthFeed = pTexture;
}

ThreeLayer::~ThreeLayer()
{

}

void ThreeLayer::step()
{
}

void ThreeLayer::display()
{
	gl::pushMatrices();
	gl::color(ColorA(1, 1, 0, 1.f));
	gl::draw(mDepthFeed, mPlane);
	gl::rotate(90);
	gl::color(ColorA(1, 0, 1, 1.f));
	gl::draw(mDepthFeed, mPlane);
	gl::rotate(90);
	gl::color(ColorA(0, 1, 1, 1.f));
	gl::draw(mDepthFeed, mPlane);
	gl::rotate(90);
	gl::color(ColorA(1, 1, 1, 1.f));
	gl::draw(mDepthFeed, mPlane);
	gl::popMatrices();
}

// ThreeControl
ThreeControl::ThreeControl()
{
	mLayerNear = make_shared<ThreeLayer>();
	mLayerMid = make_shared<ThreeLayer>();
	mLayerFar = make_shared<ThreeLayer>();
	mAngle = 0.0f;
}

ThreeControl::ThreeControl(const gl::Texture &pTexture)
{
	mLayerNear = make_shared<ThreeLayer>(pTexture);
	mLayerMid = make_shared<ThreeLayer>(pTexture);
	mLayerFar = make_shared<ThreeLayer>(pTexture);
	mAngle = 0.0f;

}

ThreeControl::~ThreeControl()
{

}

void ThreeControl::step()
{
	mAngle+=0.5f;
	if (mAngle >= 360)
		mAngle = 0;
	mLayerNear->step();
	mLayerMid->step();
	mLayerFar->step();
}

void ThreeControl::display()
{
	gl::pushMatrices();
	gl::translate(0, 0, 200);
	gl::scale(3.5f, 3.5f);
	gl::rotate(mAngle*mLayerFar->AngVel*0.5f);
	mLayerFar->display();
	gl::popMatrices();

	gl::pushMatrices();
	gl::translate(0, 0, 400);
	gl::scale(5, 5);
	gl::rotate(-mAngle*mLayerMid->AngVel + 45.0f);
	mLayerMid->display();
	gl::popMatrices();

	gl::pushMatrices();
	gl::translate(0, 0, 600);
	gl::scale(5, 5);
	gl::rotate(mAngle*mLayerNear->AngVel);
	mLayerNear->display();
	gl::popMatrices();
	

}