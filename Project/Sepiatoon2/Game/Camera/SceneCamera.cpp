#include"SceneCamera.h"

SceneCamera::SceneCamera():Entity(UID_SCENE_CAMERA)
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

	//左上座標が0,0となる
	setPos(Vec2(Setting::sc_w/2, Setting::sc_h / 2));
	setTargetPos(Vec2(Setting::sc_w / 2, Setting::sc_h / 2));
	setScale(1);
	setTargetScale(1);
}

void SceneCamera::finalize()
{
	m_subjects.clear();
}

void SceneCamera::debug_draw()
{
	//SS用
	if (Input::KeyNum9.clicked)
	{
		if (OBJ_MGR->get_map() != nullptr)
		{
			Size s=OBJ_MGR->get_map()->get_map_size();
			set_center(s/2, true);
		}
	}
	if (Input::KeyNum3.clicked)
	{
		setTargetScale(1.0);
	}
	String str = L"Camera: ";
	Println(str, L"m_pos", m_pos);
	Println(str, L"m_targetPos", m_targetPos);
	Println(str, L"m_scale", m_scale);
	Println(str, L"CameraArea", getCameraArea());
	Println(str, L"被写体の数", m_subjects.size());
	for (auto itr : m_subjects)
	{
		Println(L"被写体のID:",to_hex(itr->get_id()));
	}

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
	case msg::TYPE::REGIST_CAMERA_SUBJECT:
		regist_subject((MovingObject*)_msg.extraInfo);
		ret = true;
		break;
	case msg::TYPE::RESET_CAMERA_SUBJECT:
		reset_subject((MovingObject*)_msg.extraInfo);
		ret = true;
		break;
	case msg::TYPE::SHAKE_CAMERA:
		Vec2 direction = (*((Vec2*)_msg.extraInfo))*2;
		shake_screen(direction);
		ret = true;
		break;
	}
	return ret;
}

void SceneCamera::update_sub()
{
	m_shake_direction.x -= m_shake_direction.x*m_friction;
	m_shake_direction.y -= m_shake_direction.y*m_friction;

	//被写体がいないなら終了
	if (m_subjects.empty())return;

	Vec2 desired_camera_center = Vec2(0.0,0.0);

	for (auto itr : m_subjects)
	{
		desired_camera_center += itr->get_p() + itr->get_velocity()*5;
	}

	desired_camera_center /= double(m_subjects.size());

	setTargetPos(desired_camera_center+m_shake_direction);

	set_scale();
}


void SceneCamera::regist_subject(MovingObject* _obj)
{
	m_subjects.push_back(_obj);
}

void SceneCamera::reset_subject(MovingObject* _obj)
{
	auto is_same = [&](MovingObject* obj)
	{
		return _obj->get_id() == obj->get_id();
	};
	m_subjects.erase(remove_if(m_subjects.begin(), m_subjects.end(), is_same), m_subjects.end());
}

void SceneCamera::shake_screen(Vec2 _vec)
{
	m_shake_direction = _vec;
}

void SceneCamera::set_scale()
{
	Vec2 current_pos = getPos();

	//カメラ中心座標から一番遠いオブジェクトの位置を記録
	Vec2 far_pos=Vec2(0.0,0.0);
	double far_length = 0.0;
	for (auto itr : m_subjects)
	{
		double dif = (current_pos - (itr->get_p()+itr->get_velocity() * 5)).length();
		if (far_length <= dif)
		{
			far_pos = itr->get_p();
			far_length = dif;
		}
	}
	//半径 r　以内に　被写体が映るようにする
	double r = (Setting::get_sc().y/2-250 );
	double desired_scale = r/far_length;

	desired_scale = clamp(desired_scale, CAMERA_MIN_SCALE, CAMERA_MAX_SCALE);

	setTargetScale(desired_scale);
}