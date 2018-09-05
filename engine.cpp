#include "engine.hpp"

#include <ctime>
#include <chrono>
#include <scenes/gamescene.hpp>
#include <memory>

Engine::Engine() : sceneMng(this)
{
	window.create(sf::VideoMode(800, 600), "randballs");
}


Engine::~Engine() = default;

void Engine::stop() { isRunning = false; }

void Engine::start()
{
	sceneMng.addScene(std::make_unique<GameScene>());

	using clock = std::chrono::high_resolution_clock;
	constexpr std::chrono::nanoseconds timestep(TIMESTEP_N);

	std::chrono::nanoseconds acc(0);
	auto time_start = clock::now();

	while (isRunning)
	{
		auto scene = sceneMng.getCurrent();

		auto delta_time = clock::now() - time_start;
		time_start = clock::now();
		acc += std::chrono::duration_cast<std::chrono::nanoseconds>(delta_time);

		scene->update();
		while (acc >= timestep)
		{
			acc -= timestep;
			scene->fixedupdate(TIMESTEP_S);
		}

		const auto alpha = (float)acc.count() / timestep.count();
		scene->render(alpha);
	}
}

int main(int argc, char* argv[])
{
	std::srand(std::time(nullptr));
	Engine engine;

	engine.start();

	return 0;
}