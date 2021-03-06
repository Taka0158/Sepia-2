#include"AssetFactory.h"

AssetFactory::AssetFactory()
{
	initialize();
}

AssetFactory::~AssetFactory()
{
	finalize();
}

void AssetFactory::initialize()
{
	finalize();
}

void AssetFactory::finalize()
{

}

Image& AssetFactory::get_image(ImageType _type, int _index)
{
	Image* ret = nullptr;
	switch (_type)
	{
	default:
		ASSERT(L"AssetFactory::get_image():予期していないImageTypeです");
		break;
	case ImageType::IKA_N_A:
		ret = (m_im_ika_n_a != nullptr) ? m_im_ika_n_a : m_im_ika_n_a = new Image(PASS_IKA_N_A);
		break;
	case ImageType::IKA_N_C:
		ret = (m_im_ika_n_c != nullptr) ? m_im_ika_n_c : m_im_ika_n_c = new Image(PASS_IKA_N_C);
		break;
	case ImageType::IKA_N_N:
		ret = (m_im_ika_n_n != nullptr) ? m_im_ika_n_n : m_im_ika_n_n = new Image(PASS_IKA_N_N);
		break;
	case ImageType::IKA_N_S:
		ret = (m_im_ika_n_s != nullptr) ? m_im_ika_n_s : m_im_ika_n_s = new Image(PASS_IKA_N_S);
		break;
	case ImageType::INK_0_128:
		ret = (m_im_ink_0_128 != nullptr) ? m_im_ink_0_128 : m_im_ink_0_128 = new Image(PASS_INK_0_128);
		break;
	case ImageType::INK_1_128:
		ret = (m_im_ink_1_128 != nullptr) ? m_im_ink_1_128 : m_im_ink_1_128 = new Image(PASS_INK_1_128);
		break;
	case ImageType::INK_2_128:
		ret = (m_im_ink_2_128 != nullptr) ? m_im_ink_2_128 : m_im_ink_2_128 = new Image(PASS_INK_2_128);
		break;
	case ImageType::INK_3_128:
		ret = (m_im_ink_3_128 != nullptr) ? m_im_ink_3_128 : m_im_ink_3_128 = new Image(PASS_INK_3_128);
		break;
	case ImageType::INK_4_128:
		ret = (m_im_ink_4_128 != nullptr) ? m_im_ink_4_128 : m_im_ink_4_128 = new Image(PASS_INK_4_128);
		break;
	case ImageType::INK_5_128:
		ret = (m_im_ink_5_128 != nullptr) ? m_im_ink_5_128 : m_im_ink_5_128 = new Image(PASS_INK_5_128);
		break;
	case ImageType::INK_0_600:
		ret = (m_im_ink_0_600 != nullptr) ? m_im_ink_0_600 : m_im_ink_0_600 = new Image(PASS_INK_0_600);
		break;
	case ImageType::MAP_SIMPLE:
		ret = (m_im_map_simple_1920_1080 != nullptr) ? m_im_map_simple_1920_1080 : m_im_map_simple_1920_1080 = new Image(PASS_MAP_SIMPLE);
		break;
	case ImageType::SCENESWITCH_1:
		ret = (m_im_scene_switch_1 != nullptr) ? m_im_scene_switch_1 : m_im_scene_switch_1 = new Image(PASS_SCENESWITCH_1);
		break;
	case ImageType::SCENESWITCH_1_BG:
		ret = (m_im_scene_switch_1_bg != nullptr) ? m_im_scene_switch_1_bg : m_im_scene_switch_1_bg = new Image(PASS_SCENESWITCH_1_BG);
		break;
	case ImageType::SCENESWITCH_IKA:
		ret = (m_im_scene_switch_ika != nullptr) ? m_im_scene_switch_ika : m_im_scene_switch_ika = new Image(PASS_SCENESWITCH_1_BG);
		break;
	case ImageType::IKA_CUTIN:
		ret = (m_im_ika_cutin != nullptr) ? m_im_ika_cutin : m_im_ika_cutin = new Image(PASS_IKA_CUTIN);
		break;
	case ImageType::SHADOW_64:
		ret = (m_im_shadow_64 != nullptr) ? m_im_shadow_64 : m_im_shadow_64 = new Image(PASS_SHADOW_64);
		break;
	case ImageType::TIRE_64:
		ret = (m_im_tire_64 != nullptr) ? m_im_tire_64 : m_im_tire_64 = new Image(PASS_TIRE_64);
		break;
	case ImageType::ANIM_TYPHOON:
		ret = (m_im_typhoon[_index] != nullptr) ? m_im_typhoon[_index] : m_im_typhoon[_index] = new Image(PASS_TYPHOON(_index));
		break;
	case ImageType::RUMBA:
		ret = (m_im_rumba != nullptr) ? m_im_rumba  : m_im_rumba = new Image(PASS_RUMBA);
		break;
	case ImageType::INKBALL:
		ret = (m_im_inkball != nullptr) ? m_im_inkball : m_im_inkball = new Image(PASS_INKBALL);
		break;
	case ImageType::ANIM_EXPLOSION_READY:
		ret = (m_im_explosion_ready[_index] != nullptr) ? m_im_explosion_ready[_index] : m_im_explosion_ready[_index] = new Image(PASS_EXPLOSION_READY(_index));
		break;
	case ImageType::ANIM_EXPLOSION:
		ret = (m_im_explosion[_index] != nullptr) ? m_im_explosion[_index] : m_im_explosion[_index] = new Image(PASS_EXPLOSION(_index));
		break;
	}
	return *ret;
}

Image AssetFactory::get_image_copy(ImageType _type)
{
	Image ret;
	switch (_type)
	{
	default:
		ASSERT(L"AssetFactory::get_image_copy():予期していないImageTypeです");
		break;
	case ImageType::IKA_N_A:
	case ImageType::IKA_N_C:
	case ImageType::IKA_N_N:
	case ImageType::IKA_N_S:
	case ImageType::INK_0_128:
	case ImageType::INK_1_128:
	case ImageType::INK_2_128:
	case ImageType::INK_3_128:
	case ImageType::INK_4_128:
	case ImageType::INK_5_128:
	case ImageType::INK_0_600:
	case ImageType::MAP_SIMPLE:
	case ImageType::SCENESWITCH_1:
	case ImageType::SCENESWITCH_1_BG:
	case ImageType::SCENESWITCH_IKA:
	case ImageType::IKA_CUTIN:
	case ImageType::SHADOW_64:
	case ImageType::TIRE_64:
	case ImageType::RUMBA:
	case ImageType::INKBALL:
		ret=get_image(_type).clone();
		break;
	}
	return ret;
}

Texture AssetFactory::get_tex_copy(ImageType _type)
{
	Texture ret;
	switch (_type)
	{
	default:
		ASSERT(L"AssetFactory::get_tex_copy():予期していないImageTypeです");
		break;
	case ImageType::IKA_N_A:
	case ImageType::IKA_N_C:
	case ImageType::IKA_N_N:
	case ImageType::IKA_N_S:
	case ImageType::INK_0_128:
	case ImageType::INK_1_128:
	case ImageType::INK_2_128:
	case ImageType::INK_3_128:
	case ImageType::INK_4_128:
	case ImageType::INK_5_128:
	case ImageType::INK_0_600:
	case ImageType::MAP_SIMPLE:
	case ImageType::SCENESWITCH_1:
	case ImageType::SCENESWITCH_1_BG:
	case ImageType::SCENESWITCH_IKA:
	case ImageType::IKA_CUTIN:
	case ImageType::SHADOW_64:
	case ImageType::TIRE_64:
	case ImageType::RUMBA:
	case ImageType::INKBALL:
		ret = Texture(get_tex(_type));
		break;
	}
	return ret;
}

Texture& AssetFactory::get_tex(ImageType _type,int _index)
{
	Texture* ret = nullptr;
	switch (_type)
	{
	default:
		ASSERT(L"AssetFactory::get_image():予期していないImageTypeです");
		break;
	case ImageType::IKA_N_A:
		ret = (m_tex_ika_n_a != nullptr) ? m_tex_ika_n_a : m_tex_ika_n_a = new Texture(get_image(_type));
		break;
	case ImageType::IKA_N_C:
		ret = (m_tex_ika_n_c != nullptr) ? m_tex_ika_n_c : m_tex_ika_n_c = new Texture(get_image(_type));
		break;
	case ImageType::IKA_N_N:
		ret = (m_tex_ika_n_n != nullptr) ? m_tex_ika_n_n : m_tex_ika_n_n = new Texture(get_image(_type));
		break;
	case ImageType::IKA_N_S:
		ret = (m_tex_ika_n_s != nullptr) ? m_tex_ika_n_s : m_tex_ika_n_s = new Texture(get_image(_type));
		break;
	case ImageType::INK_0_128:
		ret = (m_tex_ink_0_128 != nullptr) ? m_tex_ink_0_128 : m_tex_ink_0_128 = new Texture(get_image(_type));
		break;
	case ImageType::INK_1_128:
		ret = (m_tex_ink_1_128 != nullptr) ? m_tex_ink_1_128 : m_tex_ink_1_128 = new Texture(get_image(_type));
		break;
	case ImageType::INK_2_128:
		ret = (m_tex_ink_2_128 != nullptr) ? m_tex_ink_2_128 : m_tex_ink_2_128 = new Texture(get_image(_type));
		break;
	case ImageType::INK_3_128:
		ret = (m_tex_ink_3_128 != nullptr) ? m_tex_ink_3_128 : m_tex_ink_3_128 = new Texture(get_image(_type));
		break;
	case ImageType::INK_4_128:
		ret = (m_tex_ink_4_128 != nullptr) ? m_tex_ink_4_128 : m_tex_ink_4_128 = new Texture(get_image(_type));
		break;
	case ImageType::INK_5_128:
		ret = (m_tex_ink_5_128 != nullptr) ? m_tex_ink_5_128 : m_tex_ink_5_128 = new Texture(get_image(_type));
		break;
	case ImageType::INK_0_600:
		ret = (m_tex_ink_0_600 != nullptr) ? m_tex_ink_0_600 : m_tex_ink_0_600 = new Texture(get_image(_type));
		break;
	case ImageType::MAP_SIMPLE:
		ret = (m_tex_map_simple_1920_1080 != nullptr) ? m_tex_map_simple_1920_1080 : m_tex_map_simple_1920_1080 = new Texture(get_image(_type));
		break;
	case ImageType::SCENESWITCH_1:
		ret = (m_tex_scene_switch_1 != nullptr) ? m_tex_scene_switch_1 : m_tex_scene_switch_1 = new Texture(get_image(_type));
		break;
	case ImageType::SCENESWITCH_1_BG:
		ret = (m_tex_scene_switch_1_bg != nullptr) ? m_tex_scene_switch_1_bg : m_tex_scene_switch_1_bg = new Texture(get_image(_type));
		break;
	case ImageType::SCENESWITCH_IKA:
		ret = (m_tex_scene_switch_ika != nullptr) ? m_tex_scene_switch_ika : m_tex_scene_switch_ika = new Texture(get_image(_type));
		break;
	case ImageType::IKA_CUTIN:
		ret = (m_tex_ika_cutin != nullptr) ? m_tex_ika_cutin : m_tex_ika_cutin = new Texture(get_image(_type));
		break;
	case ImageType::SHADOW_64:
		ret = (m_tex_shadow_64 != nullptr) ? m_tex_shadow_64 : m_tex_shadow_64 = new Texture(get_image(_type));
		break;
	case ImageType::TIRE_64:
		ret = (m_tex_tire_64 != nullptr) ? m_tex_tire_64 : m_tex_tire_64 = new Texture(get_image(_type));
		break;
	case ImageType::ANIM_TYPHOON:
		ret = (m_tex_typhoon[_index] != nullptr) ? m_tex_typhoon[_index] : new Texture(get_image(_type,_index));
		break;
	case ImageType::RUMBA:
		ret = (m_tex_rumba != nullptr) ? m_tex_rumba: m_tex_rumba = new Texture(get_image(_type));
		break;
	case ImageType::INKBALL:
		ret = (m_tex_inkball != nullptr) ? m_tex_inkball : m_tex_inkball = new Texture(get_image(_type));
		break;
	case ImageType::ANIM_EXPLOSION_READY:
		ret = (m_tex_explosion_ready[_index] != nullptr) ? m_tex_explosion_ready[_index] : new Texture(get_image(_type, _index));
		break;
	case ImageType::ANIM_EXPLOSION:
		ret = (m_tex_explosion[_index] != nullptr) ? m_tex_explosion[_index] : new Texture(get_image(_type, _index));
		break;
	}

	return *ret;
}



/*
VideoPlayer& AssetFactory::get_video(MovieType _type)
{
	VideoPlayer* ret = nullptr;
	switch (_type)
	{
	case MovieType::CUTIN_IKA:
		ret = (m_cutin_ika!= nullptr) ? m_cutin_ika: m_cutin_ika = new VideoPlayer(PASS_CUTIN_MOVIE);
		break;
	}
	return *ret;
}
*/