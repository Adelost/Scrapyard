#include "Simulation.h"

//#include <Engine/Engine.h>
#include <Components/Test.h>
#include <Utils/Console.h>
#include <Components/Input.h>
//#include <Utils/Array.h>
//#include <vector>

Simulation::Simulation()
{
	////Component::Graphic::initClass();
	//Component::Apple::initClass();
	//Component::Banana::initClass();
	//Component::Citrus::initClass();

	/*Entity* e;
	e = Entity::create();
	auto cApple = Component::Apple::create(e);
	int size = sizeof(Component::Apple);
	Component::Banana::create(e);
	Component::Citrus::create(e);

	e = Entity::create();
	Component::Banana::create(e);
	Component::Citrus::create(e);

	Component::Input input;
	input.button("Forward");*/

	//sys::TimeSystem::Time.start();
}

void Simulation::update()
{
	// Calculate delta time
	sys::Time.update();

	//sys::Time.delta();
	//sys::Time.delta();
	//sys::Time.delta();

	Array<int> foo;


	
	//System::GL.draw();
	//System::GUI.
	//System::Input.setButton();
	//Component::Input input;

	//Component::Input;
	//System::Input.delta();


	//ecs::_Time.tick();
	//ecs::Time time;



	//Component::Alpha a(1);


	////System::input

	//for (auto cApple : Component::Apple::iterator)
	//{
	//	int id = cApple->entityId();
	//	int size = sizeof(cApple);

	//	auto cBanana = Component::Banana::get(id);
	//	if (!cBanana)
	//		continue;
	//	auto cCitrus = Component::Citrus::get(id);
	//	if (!cCitrus)
	//		continue;
	//}

	//for (auto cGraphic : Component::Graphic::iterator)
	//{
	//	Component::Transform* cTransform = cGraphic->cTransform.get();
	//	//int id = cGraphic->entityId();
	//}
}


//System::Input;
//System::Camera
//System::Translation;
//System::Offset;
//System::Lookat;
//System::Animation;

//System::Sound;
//System::Graphic;



