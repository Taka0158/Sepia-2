#pragma once



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
	Image& get_image(ImageType,int =0);

	//���I�ɉ摜�������s���ꍇ�̉摜�������\�b�h
	Image get_image_copy(ImageType);

	//�e�N�X�`���擾���\�b�h
	Texture get_tex_copy(ImageType);

	//�e�N�X�`���擾���\�b�h�i�����R�X�g�Ȃ�
	Texture& get_tex(ImageType, int = 0);

	//VideoPlayer& get_video(MovieType);

	//�f�o�b�O�p
	void load_all_image();

	void delete_all_image();

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
	Image* m_im_ika_cutin = nullptr;
	Image* m_im_shadow_64 = nullptr;
	Image* m_im_tire_64 = nullptr;
	Image* m_im_typhoon[NUM_OF_ANIM_TYPHOON] = { nullptr };
	Image* m_im_rumba = nullptr;
	Image* m_im_inkball = nullptr;
	Image* m_im_explosion[NUM_OF_ANIM_EXPLOSION] = { nullptr };
	Image* m_im_explosion_ready[NUM_OF_ANIM_EXPLOSION_READY] = { nullptr };
	Image* m_im_title_bg = nullptr;
	Image* m_im_title_ika_bg = nullptr;
	Image* m_im_title_logo = nullptr;

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
	Texture* m_tex_ika_cutin = nullptr;
	Texture* m_tex_shadow_64 = nullptr;
	Texture* m_tex_tire_64 = nullptr;
	Texture* m_tex_typhoon[NUM_OF_ANIM_TYPHOON] = { nullptr };
	Texture* m_tex_rumba = nullptr;
	Texture* m_tex_inkball = nullptr;
	Texture* m_tex_explosion[NUM_OF_ANIM_EXPLOSION] = { nullptr };
	Texture* m_tex_explosion_ready[NUM_OF_ANIM_EXPLOSION_READY] = { nullptr };
	Texture* m_tex_title_bg = nullptr;
	Texture* m_tex_title_ika_bg = nullptr;
	Texture* m_tex_title_logo = nullptr;

	std::vector<Image*> m_images;

	//VideoPlayer* m_cutin_ika= nullptr;
};
AssetFactory* Singleton<AssetFactory>::instance = nullptr;