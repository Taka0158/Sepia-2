#pragma once
class Object :public Entity
{
public:
	Object(ID _id) :Entity(ID(UID_MGR_OBJ) | _id) 
	{

	};
	virtual ~Object() {};

	virtual void initialize()=0;
	virtual void finalize()=0;
	virtual void update()=0;
	virtual void draw()=0;

	virtual void debug_update() {};
	virtual void debug_draw() {};
	virtual void mask_update() {};

	bool get_is_alive()const { return m_is_alive; };
	Vec2 get_p()const { return m_pos; };
	int get_depth()const { return m_depth; };
	int& get_depth_ref() { return m_depth; };
	void set_is_alive(bool _b) { m_is_alive = _b; };
	Circle& get_mask() { return m_mask; };
	double get_mask_radius() { return m_mask_radius; };
	double get_height() { return m_height; }
	void set_height(double _s) { m_height = _s; }
	double get_mask_height() { return m_mask_height; };

	//ID��ݒ肷��
	virtual void set_id() = 0;

	//ID������������
	virtual void init_id() = 0;
	
	//�Փ˔���̎󂯎����s��
	virtual bool handle_collide(Object*  _obj) { return false; };

	//�����l���̕`�撆�S���W
	Vec2 get_pos_height() { return Vec2(m_pos.x, m_pos.y - m_height); }


protected:
	//���b�Z�[�W�������s���֐�
	virtual bool on_message(const Telegram&) { return false; };

	//�Փˏ������s��
	virtual bool on_collide(Object* _obj) { return false; };

	//����ł��邩�����Ă��邩
	bool m_is_alive;

	//���g�̒��S���W
	Vec2 m_pos;

	//�`��[�x�@�傫���قǌ�ɕ`�� �n�ʂ�0
	int m_depth = 0;

	//�n�ʂ���̍���
	double m_height = 0.0;

	int m_init_depth = 0;

	//�R���W�����}�X�N
	Circle m_mask = Circle(0, 0, 0);

	//�R���W�����}�X�N�̑傫��
	double m_mask_radius=1.0;

	//�R���W�����}�X�N�̍���
	double m_mask_height = 2.0;

};


#include"ObjectSub\Map.cpp"
#include"ObjectSub\TestObj.cpp"
#include"ObjectSub\MovingObject.h"

//��r���Z�q�̃I�[�o�[���[�h
//�`�揇���̒�`
inline bool operator==(const Object& _o1, const Object& _o2)
{
	return (_o1.get_depth() == _o2.get_depth());
}
inline bool operator<(const Object& _o1, const Object& _o2)
{
	if (_o1 == _o2)
	{
		return false;
	}
	else
	{
		return (_o1.get_depth() < _o2.get_depth());
	}
}
