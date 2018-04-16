#include"SceneCamera.h"

SceneCamera::SceneCamera():Entity(ID_SCENE_CAMERA)
{
	initialize();
}

SceneCamera::~SceneCamera()
{
	finalize();
}

void SceneCamera::initialize()
{
	finalize();

	using namespace Input; {
		std::array<Key,6> key = { KeyNum8,KeyNum4,KeyNum5,KeyNum6,KeyNum1,KeyNum2};
		setKeyConfig(key);
	}

	//¶ãÀ•W‚ª0,0‚Æ‚È‚é
	setPos(Vec2(Setting::sc_w/2, Setting::sc_h / 2));
	setTargetPos(Vec2(Setting::sc_w / 2, Setting::sc_h / 2));
	setScale(1);
	setTargetScale(1);

}

void SceneCamera::finalize()
{

}

void SceneCamera::debug_draw()
{
	String str = L"Camera: ";
	Println(str, L"m_pos", m_pos);
	Println(str, L"m_targetPos", m_targetPos);
	Println(str, L"m_grabPos", m_grabPos);
	Println(str, L"CameraArea", getCameraArea());

}

void SceneCamera::set_center(Object* _obj, bool _is_ease=true)
{
	if (_obj == nullptr)return;

	setTargetPos(_obj->get_p());

	if (_is_ease == false)
	{
		setPos(_obj->get_p());
	}
}

void SceneCamera::set_center(Vec2 _p, bool _is_ease = true)
{
	setTargetPos(_p);

	if (_is_ease == false)
	{
		setPos(_p);
	}
}


bool SceneCamera::handle_message(const Telegram& _msg)
{
	on_message(_msg);
	return true;
}

bool SceneCamera::on_message(const Telegram& _msg)
{
	bool ret = false;
	switch (_msg.msg)
	{
	case msg::TYPE::SCENE_SET_CENTER:
		set_center((TestObj*)_msg.extraInfo );
		ret = true;
		break;
	}
	return ret;
}