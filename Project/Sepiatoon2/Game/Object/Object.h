#pragma once
class Object :public CollidableObject
{
public:
	Object(ID _id) :CollidableObject(_id)
	{

	};
	virtual ~Object() {};

	virtual void initialize()=0;
	virtual void finalize()=0;
	virtual void update()=0;
	virtual void draw()=0;

	virtual void debug_update() {};
	virtual void debug_draw() {};

	bool get_is_alive()const { return m_is_alive; };
	int get_depth()const { return m_depth; };
	void set_depth(int _depth) { m_depth = _depth; };
	void set_init_depth(int _depth) { m_init_depth = _depth; };
	void init_depth(){ m_depth= m_init_depth; };
	int& get_depth_ref() { return m_depth; };
	void set_is_alive(bool _b) { m_is_alive = _b; };

	//���Ȃ苭���̌�t	�����K���Ɋ���
	virtual Color get_color() { return Palette::Black; }
	//virtual void destroy() { m_is_alive = false; }

	//ID��ݒ肷��
	virtual void set_id() = 0;

	//ID������������
	virtual void init_id() = 0;
	
	//�����l���̕`�撆�S���W
	Vec2 get_pos_height() { return Vec2(m_pos.x, m_pos.y - Max(m_height,0.0)); }
protected:
	//����ł��邩�����Ă��邩
	bool m_is_alive;

	//�`��[�x�@�傫���قǌ�ɕ`�� �n�ʂ�0
	int m_depth = 0;
	int m_init_depth = 0;

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
