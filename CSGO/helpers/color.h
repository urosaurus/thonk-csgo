#ifndef COLOR_H
#define COLOR_H
#ifdef _WIN32
#pragma once
#endif

class color
{
public:

	color()
	{
		*((int*)this) = 0;
	}

	color(int r, int g, int b)
	{
		set_color(r, g, b, 255);
	}

	color(int _r, int _g, int _b, int _a)
	{
		set_color(_r, _g, _b, _a);
	}

	// set the color
	// r - red component (0-255)
	// g - green component (0-255)
	// b - blue component (0-255)
	// a - alpha component, controls transparency (0 - transparent, 255 - opaque);
	void set_color(int r, int g, int b, int a = 255)
	{
		_color[0] = (unsigned char)r;
		_color[1] = (unsigned char)g;
		_color[2] = (unsigned char)b;
		_color[3] = (unsigned char)a;
	}

	void get_color(int& r, int& g, int& b, int& a) const
	{
		r = _color[0];
		g = _color[1];
		b = _color[2];
		a = _color[3];
	}

	void set_raw_color(int color32)
	{
		*((int*)this) = color32;
	}

	int get_raw_color() const
	{
		return *((int*)this);
	}

	inline int r() const { return _color[0]; }
	inline int g() const { return _color[1]; }
	inline int b() const { return _color[2]; }
	inline int a() const { return _color[3]; }

	unsigned char& operator[](int index)
	{
		return _color[index];
	}

	const unsigned char& operator[](int index) const
	{
		return _color[index];
	}

	bool operator==(const color& rhs) const
	{
		return (*((int *)this) == *((int*)&rhs));
	}

	bool operator!=(const color& rhs) const
	{
		return !(operator==(rhs));
	}

	color& operator=(const color& rhs)
	{
		set_raw_color(rhs.get_raw_color());
		return *this;
	}

	color rainbow(float freq, int alpha)
	{
		static uint32_t counter	= 0;

		color col = color(
			std::sin(freq * counter + 0) * 127 + 128,
			std::sin(freq * counter + 2) * 127 + 128,
			std::sin(freq * counter + 4) * 127 + 128,
			alpha);

		if (counter++ >= (uint32_t) - 1) counter = 0;

		return col;
	}

	static color white(int alpha = 255) { return color( 255, 255, 255, alpha ); }
	static color black(int alpha = 255) { return color( 0, 0, 0, alpha); }
	static color red(int alpha = 255) { return color( 255, 0, 0, alpha); }
	static color green(int alpha = 255) { return color( 0, 255, 0, alpha); }
	static color blue(int alpha = 255) { return color( 0, 0, 255, alpha); }

public:
	unsigned char _color[4];
};

#endif // !COLOR_H