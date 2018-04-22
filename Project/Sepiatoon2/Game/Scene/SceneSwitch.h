#pragma once

//シーン切り替えの時に表示する装飾
//Strategyで実装する
//自己完結型（ただし削除メソッドはSceneManagerクラスが持つ)
class SceneSwitch
{	
public:
	//_start ミリ秒で開始時間を受け取る
	//_duration サブクラスで継続時間(ミリ秒)を決定する 
	SceneSwitch(int32 _start,int32 _duration)
	{
		m_start_ms = _start;
		m_switch_ms = _start + _duration / 2;
		m_end_ms = _start + _duration;
		m_dur_ms = _duration;
	}
	virtual ~SceneSwitch() {};

	//切り替え時	SWITCH
	//動作完了時	END
	//				を渡す
	SwitchType update()
	{
		int32 current_time = Setting::get_ms();
		//前半
		if (current_time < m_switch_ms)
		{
			m_1st_r = double(current_time - m_start_ms) / double(m_switch_ms - m_start_ms);
			m_1st_r = Max(0.01, Min(m_1st_r, 1.0));
			m_2nd_r = 1;
			update_sub();
			m_current_state = SwitchType::FIRST;
		}
		//後半
		else if(m_switch_ms<=current_time && current_time < m_end_ms)
		{
			m_2nd_r = double(current_time - m_switch_ms) / double(m_end_ms - m_switch_ms);
			m_2nd_r = Max(0.01, Min(m_2nd_r, 1.0));
			m_1st_r = 1;
			update_sub();
			if (m_current_state == SwitchType::FIRST)m_current_state = SwitchType::SWITCH;
			else m_current_state = SwitchType::SECOND;
		}
		//終了
		else if( m_end_ms <=current_time)
		{
			m_current_state = SwitchType::END;
		}
		return m_current_state;
	}

	//純粋仮想関数だとSceneManager::change_scene()でエラー
	virtual void update_sub() {};

	//描画はサブクラスに委任
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

	//使用しない前提
	virtual void initialize() {};		 
	virtual void finalize() {};

	SwitchType get_state()const { return m_current_state; };
protected:
	//前半・後半の時間比率
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