#ifndef LATCH_H_
#define LATCH_H_

class Latch
{
private:
	bool previous, current;

public:
	Latch() : previous(false), current(false) {}

	bool UpdateLatch(bool pressed)
	{
		if (pressed && !previous)
			current = !current;
		else
			current = false;

		previous = pressed;

		return current;
	}
};

#endif

