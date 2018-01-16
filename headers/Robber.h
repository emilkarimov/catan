/// \file
/// Robber.h
/// Robber class
///
#ifndef ROBBER_H
#define ROBBER_H

#include <string> // C++ standard string class
#include <array>

/// Robber class
///
/// More detailed text.
class Robber {
public:
	/// constructor
	/// \param x x-coordinate of the robber
	/// \param y y-coordinate of the robber
	Robber(int x, int y);
	/// destructor
	~Robber() = default;

	/// draw function
	void draw() const;

	/// textual info
	std::string toString() const;

	/// getter location
	const std::array<int, 2>& getLoc() const;

	/// setter location
	void setLoc(int x, int y);

private:
	/// location of the robber
	std::array<int, 2> loc;
};

#endif // ROBBER_H




