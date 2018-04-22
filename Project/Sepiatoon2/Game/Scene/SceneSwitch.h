#pragma once

//�V�[���؂�ւ��̎��ɕ\�����鑕��
//Strategy�Ŏ�������
//���Ȋ����^�i�������폜���\�b�h��SceneManager�N���X������)
class SceneSwitch
{	
public:
	//_start �~���b�ŊJ�n���Ԃ��󂯎��
	//_duration �T�u�N���X�Ōp������(�~���b)�����肷�� 
	SceneSwitch(int32 _start,int32 _duration)
	{
		m_start_ms = _start;
		m_switch_ms = _start + _duration / 2;
		m_end_ms = _start + _duration;
		m_dur_ms = _duration;
	}
	virtual ~SceneSwitch() {};

	//�؂�ւ���	SWITCH
	//���슮����	END
	//				��n��
	SwitchType update()
	{
		int32 current_time = Setting::get_ms();
		//�O��
		if (current_time < m_switch_ms)
		{
			m_1st_r = double(current_time - m_start_ms) / double(m_switch_ms - m_start_ms);
			m_1st_r = Max(0.01, Min(m_1st_r, 1.0));
			m_2nd_r = 1;
			update_sub();
			m_current_state = SwitchType::FIRST;
		}
		//�㔼
		else if(m_switch_ms<=current_time && current_time < m_end_ms)
		{
			m_2nd_r = double(current_time - m_switch_ms) / double(m_end_ms - m_switch_ms);
			m_2nd_r = Max(0.01, Min(m_2nd_r, 1.0));
			m_1st_r = 1;
			update_sub();
			if (m_current_state == SwitchType::FIRST)m_current_state = SwitchType::SWITCH;
			else m_current_state = SwitchType::SECOND;
		}
		//�I��
		else if( m_end_ms <=current_time)
		{
			m_current_state = SwitchType::END;
		}
		return m_current_state;
	}

	//�������z�֐�����SceneManager::change_scene()�ŃG���[
	virtual void update_sub() {};

	//�`��̓T�u�N���X�ɈϔC
	virtual void draw() {};
	virtual void debug_draw()
	{
		Println(L"Switch:1st ", m_1st_r);
		Println(L"Switch:2nd ", m_2nd_r);
		Println(L"Switch:str ", m_start_ms);
		Println(L"Switch:swi ", m_switch_ms);
		Println(L"Switch:end ", m_end_ms);
		Println(L"Switch:dur ", m_dur_ms);
	}

	//�g�p���Ȃ��O��
	virtual void initialize() {};		 
	virtual void finalize() {};

	SwitchType get_state()const { return m_current_state; };
protected:
	//�O���E�㔼�̎��Ԕ䗦
	double m_1st_r = 0.01;
	double m_2nd_r = 0.01;
	
	SwitchType m_current_state = SwitchType::FIRST;

	int32 m_start_ms = 0;
	int32 m_switch_ms = 0;
	int32 m_end_ms = 0;

	int32 m_dur_ms = 0;

};

#include"SceneSwitchSub\FadeInOut.cpp"
#include"SceneSwitchSub\IkaSwitch.cpp"
#include"SceneSwitchSub\IkaIkaSwitch.cpp"

/*

T::T():SceneSwitch(Setting::get_ms(), 800)
{

}

T::~T()
{

}

void T::update_sub()
{
if (m_current_state == SwitchType::FIRST)
{
double easing = EaseIn(0.01, 1.0, Easing::Sine, m_1st_r);

}
else
{
double easing = EaseIn(1.00, 0.01, Easing::Sine, m_2nd_r);
}

}

void T::draw()
{

}


*/