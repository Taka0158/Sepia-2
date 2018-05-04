#pragma once

class CollideTree :public Singleton<CollideTree>, public Entity
{
	friend class Singleton<CollideTree>;
	CollideTree();
	virtual ~CollideTree();
public:

	void initialize();
	void finalize();

	//�؂ɓo�^
	void register_object(CollidableObject* _obj);

	//�o�^�I�u�W�F�N�g���痣�E�͂����󂯎��
	void remove_object(CollidableObject*);

	//�Փ˔�����s��
	void collide();

	void debug_draw();

	bool handle_message(const Telegram& _msg)override;
	bool on_message(const Telegram& _msg);
private:
	//�f�o�O�\���p
	void debug_draw_collide(CollidableObject*, CollidableObject*);
	//�����Ɠ����Y���i��ԁj���ŏՓ˔�����s�� �Ԃ�l��push������
	int collide_same_space(int _index, std::stack<CollidableObject*>& _stk);
	//�q��ԂƂ̏Փ˔�����s��
	void collide_sub(int _parent_index, std::stack<CollidableObject*>&,int);
	//stack�̒��̏Փ˃I�u�W�F�N�g�ƏՓ˔�����s��
	void collide_stacklist(int _index, std::stack<CollidableObject*>& _stk);

	//�o�^�I�u�W�F�N�g�̐�
	int m_count[COLLIDE_MAX_INDEX_SIZE] = {0};

	//4���ؔz��
	//���g��Object*�̑o�������X�g�\��
	std::array<CollidableObject*, COLLIDE_MAX_INDEX_SIZE> m_collidable_objects;

	//�Ō����CollidableObject���i�[
	std::array<CollidableObject*,COLLIDE_MAX_INDEX_SIZE> m_list_last_objects;


};

CollideTree* Singleton<CollideTree>::instance = nullptr;