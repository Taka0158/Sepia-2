#pragma once

class Telegram;

//ID�����N���X�͕K���p������
//�Ǘ��N���X���܂�
class Entity
{
public:
	Entity(ID _id)
	{
		m_id=_id;
	}
	virtual ~Entity() {};
	
	//���b�Z�[�W���󂯎��֐�
	virtual bool handle_message(const Telegram& msg) = 0;

	ID get_id()const { return m_id; }
protected:
	ID m_id;
};

//�Ǘ��N���X�͌p������
//�Ǘ�����N���X���Ȃ����Entity���p������
class ManagerEntity
{
public:
	//ID����Entity�̃C���X�^���X��T��
	virtual Entity* get_entity_from_id(ID _id) = 0;
};