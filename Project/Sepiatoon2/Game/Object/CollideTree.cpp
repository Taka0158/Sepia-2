#include"CollideTree.h"

CollideTree::CollideTree():Entity(ID(UID_COLLIDE_TREE))
{
	for (int i = 0; i < COLLIDE_MAX_INDEX_SIZE; i++)
	{
		m_collidable_objects[i] = nullptr;
		m_list_last_objects[i] = nullptr;
	}
	initialize();
}

CollideTree::~CollideTree()
{
	finalize();
}

void CollideTree::initialize()
{
	finalize();

	for (int i = 0; i < COLLIDE_MAX_INDEX_SIZE; i++)
	{
		//�ԕ��̐���
		m_collidable_objects[i] = new CollidableObject();
		m_list_last_objects[i] = m_collidable_objects[i];
	}
}

void CollideTree::finalize()
{
	//�ԕ��̍폜
	for (int i = 0; i < COLLIDE_MAX_INDEX_SIZE; i++)
	{
		if (m_collidable_objects[i] != nullptr)
		{
			delete m_collidable_objects[i];
			m_collidable_objects[i] = nullptr;
		}
	}
}

void CollideTree::register_object(CollidableObject* _obj)
{
	//�܂��Ȃɂ��i�[����Ă��Ȃ����(�ԕ������݂���͂������j
	if (m_list_last_objects[_obj->get_ary_index()] == nullptr)
	{
		ASSERT(L"�ԕ������܂���");
		m_list_last_objects[_obj->get_ary_index()] = _obj;
		m_collidable_objects[_obj->get_ary_index()] = _obj;
	}
	else
	{
		//���Ɋi�[����Ă���I�u�W�F�N�g�̎��|�C���^�ɓo�^
		m_list_last_objects[_obj->get_ary_index()]->set_next_object(_obj);
		_obj->set_previous_object(m_list_last_objects[_obj->get_ary_index()]);
		//�Ō����object���X�V
		m_list_last_objects[_obj->get_ary_index()] = _obj;
	}
}

void CollideTree::collide()
{
	//�Փ˃I�u�W�F�N�g���X�g
	std::stack<CollidableObject*> stk;

	collide_same_space(0, stk);

	collide_sub(0, stk,0);

}

void CollideTree::collide_sub(int _parent_index, std::stack<CollidableObject*>& _stk,int _count)
{
	if (_parent_index * 4 + 4 >= COLLIDE_MAX_INDEX_SIZE)
	{
		return;
	}
	std::stack<CollidableObject*> stk = _stk;

	for (int i = 1; i <= 4; i++)
	{
		int push_count = 0;

		int index = _parent_index * 4 + i;

		//����ԓ��ƏՓ˔���
		push_count += collide_same_space(index, _stk);

		//���X�g���̃I�u�W�F�N�g�ƏՓ˔���
		collide_stacklist(index, stk);

		//���ʃ��x���ֈړ�
		collide_sub(index, _stk,push_count);
	}

	for (int i = 0; i < _count; i++)
	{
		_stk.pop();
	}
}

int CollideTree::collide_same_space(int _index, std::stack<CollidableObject*>& _stk)
{
	if (_index >= COLLIDE_MAX_INDEX_SIZE)return 0;
	int ret = 0;
	//�ԕ��͖���
	CollidableObject* obj1 = m_collidable_objects[_index]->get_next_object();
	//�����Ɠ�����ԓ��ő�������
	while (obj1 != nullptr)
	{
		CollidableObject* obj2 = obj1->get_next_object();
		//�}�X�N���a��0�Ȃ��
		if (obj1->get_mask_radius() < MASK_RADIUS_NULL)
		{
			obj1 = obj1->get_next_object();
		}
		else
		{
			while (obj2 != nullptr)
			{
				//�}�X�N���a��0�Ȃ��
				if (obj2->get_mask_radius() < MASK_RADIUS_NULL)
				{
					obj2 = obj2->get_next_object();
				}
				else
				{
					//�f�o�O�p�\��
					//debug_draw_collide(obj1, obj2);

					//double distance = (obj1->get_p() - obj2->get_p()).length();

					//�Փ˔��菈��
					if (obj1->get_mask().intersects(obj2->get_mask()))
					{
						double h1 = obj1->get_height();
						double h1_bottom = h1 - obj1->get_mask_height() / 2.0;
						double h1_top = h1 + obj1->get_mask_height() / 2.0;
						double h2 = obj2->get_height();
						double h2_bottom = h2 - obj2->get_mask_height() / 2.0;
						double h2_top = h2 + obj2->get_mask_height() / 2.0;
						double top_max = Max(h1_top, h2_top);
						double bottom_min = Min(h1_bottom, h2_bottom);
						//�����������Ȃ��
						if (top_max - bottom_min<obj1->get_mask_height() + obj2->get_mask_height())
						{
							obj1->handle_collide(obj2);
							obj2->handle_collide(obj1);
						}
					}
					obj2 = obj2->get_next_object();
				}
			}
			_stk.push(obj1);
			ret++;
			obj1 = obj1->get_next_object();
			//obj1 = obj2;
		}
	}
	return ret;
}

void CollideTree::collide_stacklist(int _index, std::stack<CollidableObject*>& _stk)
{
	if (_index >= COLLIDE_MAX_INDEX_SIZE)return;

	//�ԕ��͖���
	CollidableObject* obj1 = m_collidable_objects[_index]->get_next_object();

	//�����Ɠ�����ԓ��̃I�u�W�F�N�g��stacklist���̃I�u�W�F�N�g�ƏՓ˔���
	while (obj1 != nullptr)
	{
		//�}�X�N���a��0�Ȃ��
		if (obj1->get_mask_radius() < MASK_RADIUS_NULL)
		{
			obj1 = obj1->get_next_object();
		}
		else
		{
			std::stack<CollidableObject*> stk = _stk;
			while (!stk.empty())
			{
				CollidableObject* obj2 = stk.top();

				//�f�o�O�p�\��
				//debug_draw_collide(obj1, obj2);

				//double distance = (obj1->get_p() - obj2->get_p()).length();
				//�Փ˔��菈��
				if (obj1->get_mask().intersects(obj2->get_mask()))
				{
					double h1 = obj1->get_height();
					double h1_bottom = h1 - obj1->get_mask_height() / 2.0;
					double h1_top = h1 + obj1->get_mask_height() / 2.0;
					double h2 = obj2->get_height();
					double h2_bottom = h2 - obj2->get_mask_height() / 2.0;
					double h2_top = h2 + obj2->get_mask_height() / 2.0;
					double top_max = Max(h1_top, h2_top);
					double bottom_min = Min(h1_bottom, h2_bottom);
					//�����������Ȃ��
					if (top_max - bottom_min<obj1->get_mask_height() + obj2->get_mask_height())
					{
						obj1->handle_collide(obj2);
						obj2->handle_collide(obj1);
					}
				}
				stk.pop();
			}
			obj1 = obj1->get_next_object();
		}
	}
}

void CollideTree::debug_draw()
{
	for (int index=0;index<COLLIDE_MAX_INDEX_SIZE;index++)
	{
		int count = 0;
		//�ŏ��͔ԕ��̂��ߏȂ�
		CollidableObject* obj = m_collidable_objects[index]->get_next_object();
		while (obj != nullptr)
		{
			CollidableObject* next_obj = obj->get_next_object();
			
			count++;

			if (next_obj == nullptr)break;

			Line(obj->get_p(), next_obj->get_p()).drawArrow(3.0,Vec2(5.0,5.0),Palette::Black);

			obj = next_obj;
		}
		m_count[index] = count;
	}

	/*
	for (int index = 0; index < COLLIDE_MAX_INDEX_SIZE; index++)
	{
		Println(L"index(", index, L")=", m_count[index]);
	}
	*/

	Println(L"COLLIDE_TREE:�o�^�I�u�W�F�N�g�̐�", m_count);
}

bool CollideTree::handle_message(const Telegram& _msg)
{
	on_message(_msg);
	return true;
}

bool CollideTree::on_message(const Telegram& _msg)
{
	bool ret = false;

	switch (_msg.msg)
	{
	case msg::TYPE::REMOVE_FROM_COLLIDE_TREE :
		remove_object((CollidableObject*)_msg.extraInfo);
		ret = true;
		break;
	case msg::TYPE::REGISTER_TO_COLLIDE_TREE:
		register_object((CollidableObject*)_msg.extraInfo);
		ret = true;
		break;
	}

	return ret;
}

void CollideTree::remove_object(CollidableObject* _obj)
{								  
	if (m_list_last_objects[_obj->get_ary_index()] == _obj)
	{
		//�Ō����object���X�V����
		m_list_last_objects[_obj->get_ary_index()] = _obj->get_previous_object();
	}
}

void CollideTree::debug_draw_collide(CollidableObject* _o1, CollidableObject* _o2)
{
	Line(_o1->get_p(), _o2->get_p()).draw(5.0,Palette::Red);
}

