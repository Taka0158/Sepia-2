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
	IKA_N_S,
	SCENESWITCH_1,
	SCENESWITCH_1_BG,
	SCENESWITCH_IKA,
};

enum class MovieType
{
	//CUTIN_IKA
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
	Image& get_image(ImageType);

	//���I�ɉ摜�������s���ꍇ�̉摜�������\�b�h
	Image get_image_copy(ImageType);

	//�e�N�X�`���擾���\�b�h
	Texture get_tex_copy(ImageType);

	//�e�N�X�`���擾���\�b�h�i�����R�X�g�Ȃ�
	Texture& get_tex(ImageType);

	VideoPlayer& get_video(MovieType);

private:
	Image* m_im_map_simple_1920_1080 = nullptr;
	Image* m_im_ink_0_128=nullptr;
	Image* m_im_ink_1_128=nullptr;
	Image* m_im_ink_2_128=nullptr;
	Image* m_im_ink_3_128=nullptr;
	Image* m_im_ink_4_128=nullptr;
	Image* m_im_ink_5_128=nullptr;
	Image* m_im_ink_0_600=nullptr;
	Image* m_im_ika_n_n = nullptr;
	Image* m_im_ika_n_s = nullptr;
	Image* m_im_ika_n_c = nullptr;
	Image* m_im_ika_n_a = nullptr;
	Image* m_im_scene_switch_1 = nullptr;
	Image* m_im_scene_switch_ika = nullptr;
	Image* m_im_scene_switch_1_bg = nullptr;

	Texture* m_tex_map_simple_1920_1080 = nullptr;
	Texture* m_tex_ink_0_128 = nullptr;
	Texture* m_tex_ink_1_128 = nullptr;
	Texture* m_tex_ink_2_128 = nullptr;
	Texture* m_tex_ink_3_128 = nullptr;
	Texture* m_tex_ink_4_128 = nullptr;
	Texture* m_tex_ink_5_128 = nullptr;
	Texture* m_tex_ink_0_600 = nullptr;
	Texture* m_tex_ika_n_n = nullptr;
	Texture* m_tex_ika_n_s = nullptr;
	Texture* m_tex_ika_n_c = nullptr;
	Texture* m_tex_ika_n_a = nullptr;
	Texture* m_tex_scene_switch_1 = nullptr;
	Texture* m_tex_scene_switch_ika = nullptr;
	Texture* m_tex_scene_switch_1_bg = nullptr;

	std::vector<Image*> m_images;

	//VideoPlayer* m_cutin_ika= nullptr;
};
AssetFactory* Singleton<AssetFactory>::instance = nullptr;