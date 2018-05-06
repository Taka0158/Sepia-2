#include"IkaSpecialDash.h"

IkaSpecialDash::IkaSpecialDash() :IkaState(IkaStateType::IKA_SPECIAL_DASH)
{

}

IkaSpecialDash::~IkaSpecialDash()
{

}

void IkaSpecialDash::input(Ika* _owner)
{
	if (_owner->get_controller()->get_key_swim().pressed)
	{
		m_timer++;
		m_max_speed += 0.005;
	}
	else
	{

	}
}
void IkaSpecialDash::enter(Ika* _owner)
{
	m_owner = _owner;

	//開始パラメータ(倍率)
	m_max_speed = 1.2;

	_owner->set_special_gauge_rate(0.0);
	_owner->set_moving_parm(m_state_type);

}
void IkaSpecialDash::update(Ika* _owner)
{
	m_timer++;

	input(_owner);

	_owner->set_max_speed(m_max_speed);

	//下位Stateでも同じく呼ばれることに注意
	_owner->regene_hp();

	m_is_tex_loop = (m_timer > m_duration) ? false : true;
	m_tex_index = get_tex_loop_index(m_tex_index, NUM_OF_ANIM_ORB - 1, 9, 29, m_is_tex_loop);

	//通常のstateの振る舞いをする
	_owner->get_ika_fsm()->get_current_state()->update(_owner);

	//アニメーションが最後まで再生されれば終了メッセージを送る
	if (m_tex_index >= NUM_OF_ANIM_ORB - 1)
	{
		MSG_DIS->dispatch_message(0.0, _owner, _owner, msg::TYPE::DELETE_IKA_GLOBAL_STATE);
	}
}
void IkaSpecialDash::draw(Ika* _owner)
{
	Println(L"max_speed", _owner->get_max_speed());
	Println(L"m_max_speed", m_max_speed);
	double scale = _owner->get_tex_scale();
	_owner->get_ika_fsm()->get_current_state()->draw(_owner);
	ASSET_FAC->get_tex(ImageType::ANIM_ORB, m_tex_index).scale(1.0).drawAt(_owner->get_p(), Color(_owner->get_color(),150));

}

void IkaSpecialDash::exit(Ika* _owner)
{
	_owner->fly(5.0);
	_owner->init_max_speed();
	_owner->init_special_gauge_rate();
}

IkaStateType IkaSpecialDash::get_state_type()
{
	//override不要か？
	return m_state_type;
}

bool IkaSpecialDash::on_collide(Ika* _owner, CollidableObject* _obj)
{
	bool ret = false;

	if (Ika* other = dynamic_cast<Ika*>(_obj))
	{
		//敵なら
		if (other->get_color() != _owner->get_color())
		{
			//他のスペシャルに打ち勝つ
			IkaStateType other_state = other->get_ika_fsm()->get_now_state();
			if (other_state == IkaStateType::IKA_SPECIAL_TYPHOON || other_state == IkaStateType::IKA_SPECIAL_SUPERNOVA)
			{
				double value = IKA_DASH_DAMAGE;
				MSG_DIS->dispatch_message(0.0, _owner, other, msg::TYPE::DEFINITE_DAMAGE_OTHER, &value);
			}
		}
	}

	ret = _owner->get_ika_fsm()->get_current_state()->on_collide(_owner, _obj);

	return ret;
}
