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

Image* AssetFactory::get_image(ImageType _type)
{
	Image* ret = nullptr;
	switch (_type)
	{
	default:
		ASSERT(L"AssetFactory::get_image():—\Šú‚µ‚Ä‚¢‚È‚¢ImageType‚Å‚·");
		break;
	case ImageType::IKA_N_A:
		ret = (m_ika_n_a != nullptr) ? m_ika_n_a : m_ika_n_a = new Image(PASS_IKA_N_A);
		break;
	case ImageType::IKA_N_C:
		ret = (m_ika_n_c != nullptr) ? m_ika_n_c : m_ika_n_c = new Image(PASS_IKA_N_C);
		break;
	case ImageType::IKA_N_N:
		ret = (m_ika_n_n != nullptr) ? m_ika_n_n : m_ika_n_n = new Image(PASS_IKA_N_N);
		break;
	case ImageType::IKA_N_S:
		ret = (m_ika_n_s != nullptr) ? m_ika_n_s : m_ika_n_s = new Image(PASS_IKA_N_S);
		break;
	case ImageType::INK_0_128:
		ret = (m_ink_0_128 != nullptr) ? m_ink_0_128 : m_ink_0_128 = new Image(PASS_INK_0_128);
		break;
	case ImageType::INK_1_128:
		ret = (m_ink_1_128 != nullptr) ? m_ink_1_128 : m_ink_1_128 = new Image(PASS_INK_1_128);
		break;
	case ImageType::INK_2_128:
		ret = (m_ink_2_128 != nullptr) ? m_ink_2_128 : m_ink_2_128 = new Image(PASS_INK_2_128);
		break;
	case ImageType::INK_3_128:
		ret = (m_ink_3_128 != nullptr) ? m_ink_3_128 : m_ink_3_128 = new Image(PASS_INK_3_128);
		break;
	case ImageType::INK_4_128:
		ret = (m_ink_4_128 != nullptr) ? m_ink_4_128 : m_ink_4_128 = new Image(PASS_INK_4_128);
		break;
	case ImageType::INK_5_128:
		ret = (m_ink_5_128 != nullptr) ? m_ink_5_128 : m_ink_5_128 = new Image(PASS_INK_5_128);
		break;
	case ImageType::INK_0_600:
		ret = (m_ink_0_600 != nullptr) ? m_ink_0_600 : m_ink_0_600 = new Image(PASS_INK_0_600);
		break;
	case ImageType::MAP_SIMPLE:
		ret = (m_map_simple_1920_1080 != nullptr) ? m_map_simple_1920_1080 : m_map_simple_1920_1080 = new Image(PASS_MAP_SIMPLE);
		break;
	}
	return ret;
}

Image AssetFactory::get_image_copy(ImageType _type)
{
	Image ret;
	switch (_type)
	{
	default:
		ASSERT(L"AssetFactory::get_image_copy():—\Šú‚µ‚Ä‚¢‚È‚¢ImageType‚Å‚·");
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
		ret=get_image(_type)->clone();
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
		ASSERT(L"AssetFactory::get_tex_copy():—\Šú‚µ‚Ä‚¢‚È‚¢ImageType‚Å‚·");
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
		Image im = get_image_copy(_type);
		ret = Texture(im);
		break;
	}
	return ret;
}
