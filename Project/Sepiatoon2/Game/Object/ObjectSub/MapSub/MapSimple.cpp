#include"MapSimple.h"

MapSimple::MapSimple() :Map(UID_OBJ_MAP_SIMPLE)
{
	set_id();
	initialize();
}

MapSimple::~MapSimple()
{
	finalize();
}

void MapSimple::initialize()
{
	finalize();

}

void MapSimple::finalize()
{

}

void MapSimple::enter()
{
	initialize();
}

void MapSimple::exit()
{
	finalize();
}

void MapSimple::update()
{

}

void MapSimple::draw()
{

}

void MapSimple::debug_update()
{

}

void MapSimple::debug_draw()
{
	Println(L"***MAP_SIMPLE***");
}

bool MapSimple::handle_message(const Telegram& _msg)
{
	on_message(_msg);
	return true;
}

bool MapSimple::on_message(const Telegram& _msg)
{
	bool ret = false;

	return ret;
}