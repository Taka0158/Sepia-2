#pragma once
class Object :public Entity
{
public:
	Object(ID _id) :Entity(ID(ID_MGR_OBJ) | _id) 
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
	Vec2 get_p()const { return m_p; };
	int get_depth()const { return m_depth; };
	void set_is_alive(bool _b) { m_is_alive = _b; };

	//ID��ݒ肷��
	virtual void set_id() = 0;

protected:
	//���b�Z�[�W�������s���֐�
	virtual bool on_message(const Telegram&) { return false; };

	//����ł��邩�����Ă��邩
	bool m_is_alive;

	//���g�̒��S���W
	Vec2 m_p;

	//�`��[�x�@�傫���قǌ�ɕ`��
	int m_depth = 5;
};

/*
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
*/