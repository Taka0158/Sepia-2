#include"IkaCutin.h"

IkaCutin::IkaCutin() :CutScene(Setting::get_ms(), 4000)
{
}

IkaCutin::~IkaCutin()
{

}

void IkaCutin::enter(Scene* _owner)
{
	OPEN_MOVIE_IKA_CUTIN;
	PLAY_MOVIE_IKA_CUTIN(m_region);
}

void IkaCutin::exit(Scene* _owner)
{
	if (ISPLAYING_MOVIE_IKA_CUTIN)STOP_MOVIE_IKA_CUTIN;
}

void IkaCutin::update_sub(Scene* _owner)
{
	//âEÇ©ÇÁç∂Ç÷
	int easing = EaseInOut(m_start_pos, -m_start_pos, Easing::Quad, m_ratio);
	m_region.x = easing;
}

void IkaCutin::draw_sub(Scene* _owner)
{
	Println(L"cutin");
}