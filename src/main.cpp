#include "engine/engine.hpp"
#include <cstdlib>
#include <ctime>

int main(int argc, char* argv[])
{
	std::srand(std::time(nullptr));
	Engine engine;

	engine.start();

	return 0;
}