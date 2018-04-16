#pragma once

//initialize��enter�֐��̗p�r��������	����
class Map :public Object
{
public:
	Map(ID _id) :Object(ID(_id)) {
		m_depth = -100;
		m_is_alive = true;
		m_p = Vec2(0.0, 0.0);
	};
	virtual ~Map() {};

	virtual void initialize()=0;
	virtual void finalize() =0;

	//Scene�̓������ۂɌĂяo�����
	virtual void enter() = 0;
	//���C���X�V
	virtual void update() = 0;
	virtual void draw() = 0;
	//Scene���o��ۂɌĂяo�����
	virtual void exit() = 0;

	virtual void debug_update() {};
	virtual void debug_draw() {};

	//�P��I�u�W�F�N�g���id�̓}�N���w��
	virtual void set_id() {};
protected:

};

#include"MapSub\MapSimple.cpp"