#ifndef __THREE__
#define __THREE__

class ThreeLayer
{
public:
	ThreeLayer();
	~ThreeLayer();
private:
};

class ThreeControl
{
public:
	ThreeControl();
	~ThreeControl();

private:
	void step();
	void display();
};

typedef std::unique_ptr<ThreeControl> ThreeControlRef;
#endif