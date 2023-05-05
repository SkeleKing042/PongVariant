#include "Ball.h"
#include "raylib.h"

using namespace std;

Ball::Ball(double givenSpeed, double givenSize, vector<double> givenMomentum)
{
	speed = givenSpeed;
	size = givenSize;
	position.push_back(GetScreenWidth() / 2);
	position.push_back(GetScreenHeight() / 2);
	momentum.push_back(givenMomentum[0] * speed);
	momentum.push_back(givenMomentum[1] * speed);
}

Ball::~Ball()
{

}

void Ball::MoveBall()
{
	// Moves the ball based on its momentum
	position[0] += momentum[0];
	position[1] += momentum[1];

	// Screen edge detection
	// Scales with ball size
	if (position[0] <= 0 + size || position[0] >= GetScreenWidth() - size)
	{
		momentum[0] *= -1;
	}
	if (position[1] <= 0 + size || position[1] >= GetScreenHeight() - size)
	{
		momentum[1] *= -1;
	}

}