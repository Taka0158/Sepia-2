#include"TestObj.h"

TestObj::TestObj(Vec2 _p):Object(ID_OBJ_TEST)
{
	set_id();
	initialize();
	m_p = _p;
}

TestObj::~TestObj()
{
	finalize();
}

void TestObj::initialize()
{
	m_is_alive = true;
	m_p = Vec2(0.0, 0.0);
	radius = 8.0;
}

void TestObj::finalize()
{

}

void TestObj::update()
{

}

void TestObj::draw()
{
	Circle(m_p, radius).draw();
}

void TestObj::debug_update()
{
	//OBJ_MGRの最後に格納されたTestObjが最終的に適応される
	if (Input::KeySpace.clicked)
	{
		MSG_DIS->dispatch_message(0, m_id, UID_SCENE_CAMERA, msg::TYPE::SCENE_SET_CENTER, this);
	}


}

void TestObj::debug_draw()
{
	FontAsset(L"font_debug_8")(m_p).drawCenter(m_p, Palette::Black);
	FontAsset(L"font_debug_8")(to_hex(m_id)).drawCenter(m_p+Vec2(0.0,10.0), Palette::Black);
}

bool TestObj::handle_message(const Telegram& _msg)
{
	on_message(_msg);
	return true;
}

bool TestObj::on_message(const Telegram& _msg)
{
	bool ret = false;

	//処理

	return ret;
}

void TestObj::set_id()
{
	if (m_next_valid_id < 0xFFFF)
	{
		m_id |= m_next_valid_id;
		m_next_valid_id++;
	}
	else
	{
		ASSERT(L"オブジェクトのID割り当てが上限を超えました");
	}
}