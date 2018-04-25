#include"IkaCutin.h"

IkaCutin::IkaCutin(Color _color) :CutScene(Setting::get_ms(), 1000)
{
	m_using_texture = ASSET_FAC->get_tex(ImageType::IKA_CUTIN);
	m_color = _color;
}

IkaCutin::~IkaCutin()
{

}

void IkaCutin::enter(Scene* _owner)
{
}

void IkaCutin::exit(Scene* _owner)
{
}

void IkaCutin::update_sub(Scene* _owner)
{
}

void IkaCutin::draw_sub(Scene* _owner)
{
	//âEÇ©ÇÁç∂Ç÷
	Println(L"cutin");
	double scale = Setting::get_sc_scale();
	int easing = EaseInOut(m_start_pos, -m_start_pos, Easing::Quad, m_ratio);
	Vec2 pos = Vec2(m_using_texture.width*scale / 2 + easing, m_using_texture.height*scale / 2 );
	m_using_texture.scale(scale).drawAt(pos, m_color);
}