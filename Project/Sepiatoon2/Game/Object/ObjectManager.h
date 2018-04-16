#pragma once

#include"Object.h"

class Map;

enum class MapType {
	SIMPLE
};

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

	//Create�֐�
	//�e�X�g�p
	void create_TestObj(Vec2 _p);

	//���b�Z�[�W�̎󂯎��֐�
	bool handle_message(const Telegram& _msg)override;
	//���b�Z�[�W�̎d�������s���֐�
	//�����Ń��b�Z�[�W�ɑΉ����鏈�����Ăяo��
	bool on_message(const Telegram& _msg);

	//�Ǘ��I�u�W�F�N�g��ID�ɂ��T��
	Entity* get_entity_from_id(ID _id)override;

	//--------MAP�֐�-----
	void set_map(MapType);
	void destroy_map();
	//�g���\��͂Ȃ�
	//�A���o�g���I�ȃ��[�h������Ύg�p����H
	//Map�T�u�N���X����Ăяo��
	void change_map(Map*);
private:

	//Object������ł�����폜����
	void check_alive();
	
	//�o�^�ς�object��is_alive��false�ɂ���
	void destroy_all_object();

	//�e�N���X��id�����Z�b�g����
	void reset_object_id();

	//�`�揇���t���s��
	void regist_draw_object(Object*);

	//�`�揇���t������������
	void reset_draw_object(Object*);

	//create�֐���object�̃C���X�^���X�����ꍇ
	//���̊֐��ɓn��
	void regist_object(Object*);


private:
	//�I�u�W�F�N�g�̃C���X�^���X�i�̃|�C���^�j���i�[����
	std::vector<Object*> m_objects;

	//<����Object��depth	,	����Object�̃|�C���^>
	typedef std::pair<int, Object*> Drawer;

	//object.m_depth��ŕ��ёւ���
	std::set<Drawer> m_objects_drawer;

	//map�C���X�^���X
	Map* m_map = nullptr;

};						 

ObjectManager* Singleton<ObjectManager>::instance = nullptr;
