#pragma once

enum class ImageType{
	MAP_SIMPLE = 0,
	INK_0_128,
	INK_1_128,
	INK_2_128,
	INK_3_128,
	INK_4_128,
	INK_5_128,
	INK_0_600,
	IKA_N_A,
	IKA_N_C,
	IKA_N_N,
	IKA_N_S
};

class AssetFactory :public Singleton<AssetFactory>
{
	friend class Singleton<AssetFactory>;
public:
	AssetFactory();
	~AssetFactory();

	void initialize();
	void finalize();

	//�e�ǂݍ��݉摜���폜���郁�\�b�h���Ȃ����ߓǂݍ��݂��ςȂ�

	//���I�ɉ摜�������s��Ȃ��ꍇ�̉摜�擾���\�b�h
	Image* get_image(ImageType);

	//���I�ɉ摜�������s���ꍇ�̉摜�������\�b�h
	Image get_image_copy(ImageType);

	//�e�N�X�`���擾���\�b�h
	Texture get_tex_copy(ImageType);

private:
	Image* m_map_simple_1920_1080 = nullptr;
	Image* m_ink_0_128=nullptr;
	Image* m_ink_1_128=nullptr;
	Image* m_ink_2_128=nullptr;
	Image* m_ink_3_128=nullptr;
	Image* m_ink_4_128=nullptr;
	Image* m_ink_5_128=nullptr;
	Image* m_ink_0_600=nullptr;
	Image* m_ika_n_n = nullptr;
	Image* m_ika_n_s = nullptr;
	Image* m_ika_n_c = nullptr;
	Image* m_ika_n_a = nullptr;

	std::vector<Image*> m_images;
};
AssetFactory* Singleton<AssetFactory>::instance = nullptr;