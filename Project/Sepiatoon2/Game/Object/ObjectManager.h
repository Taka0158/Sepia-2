#pragma once

#include"CollidableObject.h"
#include"CollideTree.cpp"
#include"Object.h"

class Map;

// GameMain
class ObjectManager : public Singleton<ObjectManager>,public Entity,public ManagerEntity
{
	friend class Singleton<ObjectManager>;
	ObjectManager();
	~ObjectManager();
public:

	void update();
	void debug_update();
	void draw();
	void debug_draw();

	void initialize();
	void finalize();


	//-----------------------------------------------Create�֐�--------------------------------------------------------------------------
	//�e�X�g�p
	//void create_TestObj(Vec2 _p);

	void create_Ika(Vec2 _init_p=Vec2(240.0,240.0),
		ControllerType _contoroller_type=ControllerType::PLAYER_1,
		Color _color=Setting::get_color(Setting::get_ika_1_team()),
		TeamType _team_type=Setting::get_ika_1_team(),
		CharType _char_type=Setting::get_char_1(),
		SpecialType _special_type=Setting::get_special_1());
	Ika* create_Ika(int _index,Vec2 _pos);

	void create_Tire(Vec2 _pos);

	void create_Rumba(Vec2 _pos, Color _color);

	void create_Inkball(Vec2 _pos, double _init_height, Vec2 _dir, double _fly_strength, Color _color,double _paint_scale);

	void create_Wall(Vec2 _pos);

	void create_Missile(Vec2 _pos, double _init_height, Color _color,MissileType _type=MissileType::NORMAL);

	void create_SpecialOrb(Vec2 _pos, double _init_height, Vec2 _dir, double _fly_strength, OrbType _type=OrbType::NORMAL);

	void create_IkaBalloon(Vec2 _pos,IkaBalloonType _type);

	void create_Trampoline(Vec2 _pos);

	void create_RespawnPoint(Vec2 _pos, TeamType _type);

	//-----------------------------------------------Create�֐�--------------------------------------------------------------------------

	//���b�Z�[�W�̎󂯎��֐�
	bool handle_message(const Telegram& _msg)override;
	//���b�Z�[�W�̎d�������s���֐�


	//�Ǘ��I�u�W�F�N�g��ID�ɂ��T��
	Entity* get_entity_from_id(ID _id)override;

	//--------MAP�֐�-----
	void set_map(MapType);
	void destroy_map();
	//�g���\��͂Ȃ�
	//�A���o�g���I�ȃ��[�h������Ύg�p����H
	//Map�T�u�N���X����Ăяo��
	void change_map(Map*);

	Map* get_map() { return m_map; };
private:
	void toggle_debug_draw()
	{
		m_is_debug_draw = (Input::KeyYen.clicked) ? !m_is_debug_draw : m_is_debug_draw;
	}

	//�����Ń��b�Z�[�W�ɑΉ����鏈�����Ăяo��
	bool on_message(const Telegram& _msg);

	//�Փ˔���֐�
	void check_collide();

	//Object������ł�����폜����
	void check_alive();
	
	//�o�^�ς�object��is_alive��false�ɂ���
	void destroy_all_object();

	//�e�N���X��id�����Z�b�g����
	void reset_object_id();

	//�`�揇���t���s��
	//void regist_draw_object(Object*);

	//�`�揇���t������������
	//void reset_draw_object(Object*);

	//create�֐���object�̃C���X�^���X�����ꍇ
	//���̊֐��ɓn��
	void regist_object(Object*);

	//update�֐��n�߂ŃI�u�W�F�N�g�̓o�^���s��
	void register_object();

	//�`��[�x�ɍ��킹��m_objects���\�[�g����
	void sort_objects();

	//�~�T�C���̃^�[�Q�b�g��T��
	Object* find_missile_target(Missile*);
private:
	//���o�^�I�u�W�F�N�g���i�[����
	//register_objcet()�œo�^�����
	std::queue<Object*> m_yet_objects;

	//�I�u�W�F�N�g�̃C���X�^���X�i�̃|�C���^�j���i�[����
	std::vector<Object*> m_objects;

	//<����Object��depth	,	����Object�̃|�C���^>
	//���I�ɕω�������͕̂��ёւ����Ȃ�
	typedef std::pair<int&, Object*> Drawer;

	//object.m_depth��ŕ��ёւ���
	//�l���傫���قǎ�O�ɕ`�悳���
	//std::vector<Drawer> m_objects_drawer;

	bool m_is_debug_draw = false;
	
	//map�C���X�^���X
	Map* m_map = nullptr;

	int m_timer = 0;

	//�`�揇�̃\�[�g�Ԋu(�t���[��)
	int m_sort_duration = 1;

	//���[�g���ԍ����X�V����p�x
	static int m_morton_interval;
};						 

ObjectManager* Singleton<ObjectManager>::instance = nullptr;
int ObjectManager::m_morton_interval = 5;