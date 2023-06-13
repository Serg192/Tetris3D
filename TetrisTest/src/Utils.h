#ifndef Utils_h
#define Utils_h

#define MAX_COLORS 10

namespace GraphUtils
{
	enum Color {
		WHITE = 0,
		RED,
		GREEN,
		BLUE, 
		CRIMSON,
		MEDIUM_VIOLET_RED,
		ORANGE,
		ORCHID,
		STATE_BLUE,
		MEDIUM_SEA_GREEN
	};

	extern float colors[][4];

	void drawString(void* font, const unsigned char* text, float x, float y);
}

#endif