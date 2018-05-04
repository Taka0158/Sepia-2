#include"ObjectManager.h"

//��a��include
#include"../Camera/SceneCamera.h"

ObjectManager::ObjectManager():Entity(ID(UID_MGR_OBJ))
{
	initialize();
}

ObjectManager::~ObjectManager()
{
	finalize();
}

void ObjectManager::initialize()
{
	finalize();

	SCENE_CAMERA->initialize();
	COLLIDE_TREE->initialize();

	m_timer = 0;
}

void ObjectManager::finalize()
{
	for (auto itr : m_objects)
	{
		if (itr != nullptr)
		{
			itr->init_id();
		}
	}

	destroy_all_object();
	check_alive();
	reset_object_id();
	destroy_map();

	//nullptr �̗v�f���폜����
	auto is_nullptr = [](Object* _obj)
	{
		return _obj==nullptr;
	};
	//�폜���ׂ��v�f���Ō����
	auto rmvIter = std::remove_if(m_objects.begin(), m_objects.end(), is_nullptr);
	//�폜���ׂ��ŏ��̗v�f����Ō�܂ł��폜����
	m_objects.erase(rmvIter, m_objects.end());

	while (!m_yet_objects.empty())
	{
		if (m_yet_objects.front() != nullptr)
		{
			delete m_yet_objects.front();
		}
		m_yet_objects.pop();
	}

	COLLIDE_TREE->finalize();
}

void ObjectManager::update()
{
	//���o�^�I�u�W�F�N�g��o�^����
	register_object();

	m_timer++;

	check_alive();
	
	check_collide();

	if (m_map != nullptr)m_map->update();

	for (unsigned int i = 0; i < m_objects.size(); i++)
	{
		if (m_objects[i] != nullptr)
		{
			if (m_objects[i]->get_is_alive() == false)continue;

			//���[�g��ԓ��ɔ[�߂�
			m_objects[i]->restrain_area();

			//�e�I�u�W�F�N�g�̃��[�g���ԍ����X�V����
			if(m_timer%m_morton_interval==0)m_objects[i]->update_morton_and_level();

			m_objects[i]->update();
		}
	}
}

void ObjectManager::draw()
{
	if (m_map != nullptr)m_map->draw();

	sort_objects();

	for (unsigned int i = 0; i < m_objects.size(); i++)
	{
		if (m_objects[i] != nullptr)
		{
			if (m_objects[i]->get_is_alive() == false)continue;
			m_objects[i]->draw();
		}
	}

	/*
	//�`��[�x���`�揇������
	if(m_timer%m_sort_duration==0)std::sort(m_objects_drawer.begin(), m_objects_drawer.end());


	//���I��m_depth��������̂͐����������ɂȂ�Ȃ�
	for (auto itr : m_objects_drawer)
	{
		if (itr.second != nullptr)
		{
			if (itr.second->get_is_alive() == false)continue;
			itr.second->draw();
		}
	}
	*/
}

void ObjectManager::debug_update()
{
	toggle_debug_draw();
	if (!m_is_debug_draw)return;
	
	if (m_map != nullptr)m_map->debug_update();

	for (unsigned int i = 0; i < m_objects.size(); i++)
	{
		if (m_objects[i] != nullptr)
		{
			if (m_objects[i]->get_is_alive() == false)continue;
			m_objects[i]->debug_update();
		}
	}
}

void ObjectManager::debug_draw()
{
	if (!m_is_debug_draw)return;

	if (m_map != nullptr)m_map->debug_draw();

	for (unsigned int i = 0; i < m_objects.size(); i++)
	{
		if (m_objects[i] != nullptr)
		{
			if (m_objects[i]->get_is_alive() == false)continue;

			//AABB�\��
			std::pair<Point, Point> p = collide::get_bounding_box(m_objects[i]->get_mask());
			Rect(p.first, p.second - p.first).draw(Color(Palette::Red, 100));
			//���[�g���ԍ��ƃ��x����\��
			FONT_DEBUG_16(m_objects[i]->get_morton_number(), L":", m_objects[i]->get_level()).drawCenter(m_objects[i]->get_p());

			m_objects[i]->debug_draw();
		}
	}
	COLLIDE_TREE->debug_draw();
	DEBUG->draw_collide_space();
	//�m�F�̂���
	//check_collide();

	/*
	for (auto itr : m_objects_drawer)
	{
		if (itr.second != nullptr)
		{
			if (itr.second->get_is_alive() == false)continue;
			itr.second->debug_draw();
		}
	}
	*/
	Println(L"���o�^�I�u�W�F�N�g��:", m_yet_objects.size());
	Println(L"�I�u�W�F�N�g��:", m_objects.size());
	//Println(L"�`��I�u�W�F�N�g��:", m_objects_drawer.size());

}

void ObjectManager::check_alive()
{
	if (m_objects.size() == 0)return;

	for (unsigned int i = 0; i < m_objects.size(); i++)
	{
		if (m_objects[i] != nullptr)
		{
			if (m_objects[i]->get_is_alive() == false)
			{
				//�`��I�u�W�F�N�g�o�^�̉���
				//reset_draw_object(m_objects[i]);

				//���l��delete����郁�b�Z�[�W�͍폜
				MSG_DIS->delete_direct_message(m_objects[i]); 

				//�Փ˔���؂����菜��
				m_objects[i]->remove_from_tree();

				delete m_objects[i];
				m_objects[i] = nullptr;
			}
		}
	}

	/*
	//������delete�ł��Ȃ�����

	auto isAlive = [](Object* obj)
	{
		return !obj->get_is_alive();
	};

	//�폜���ׂ��v�f���Ō����
	auto rmvIter = std::remove_if(m_objects.begin(), m_objects.end(), isAlive);

	//�`��I�u�W�F�N�g�o�^����
	for (auto itr = rmvIter; itr != m_objects.end(); itr++)
	{
		reset_draw_object(*itr);
	}

	//�폜���ׂ��ŏ��̗v�f����Ō�܂ł��폜����
	m_objects.erase(rmvIter, m_objects.end());
	*/
}

bool ObjectManager::handle_message(const Telegram& _msg)
{
	on_message(_msg);
	return true;
}

bool ObjectManager::on_message(const Telegram& _msg)
{
	bool ret = false;
	Paint p;
	InkballParm* ibp;

	switch (_msg.msg)
	{
	case msg::TYPE::OBJMGR_DESTROY_ALL_OBJECT:
		destroy_all_object();
		ret = true;
		break;
	case msg::TYPE::CREATE_INK_BALL:
		ibp=(InkballParm*)_msg.extraInfo;
		create_Inkball(ibp->pos, ibp->init_height, ibp->dir, ibp->fly_strength, ibp->color);
		ret = true;
		break;
	case msg::TYPE::ALL_WALL_PAINT:
		//�����I���̎��Ăяo�����z��
		//�ǉ��F�����ʂɉe�����Ȃ��悤�ɍ��F�ɂ���
		for (unsigned int i = 0; i < m_objects.size(); i++)
		{
			if (m_objects[i] != nullptr)
			{
				if (m_objects[i]->get_is_alive() == false)continue;
				if (is_same_class(m_objects[i]->get_id(), ID(ID_MAPGIMMCIK_WALL)))
				{
					p = Paint(Vec2_to_Point(m_objects[i]->get_p()), Palette::Black, 1.0, &ASSET_FAC->get_image(ImageType::WALL_BLACK), false);
					MSG_DIS->dispatch_message(0.0, this, m_map, msg::TYPE::MAP_PAINT, &p);
				}
			}
		}
		ret = true;
	}

	return ret;
}

Entity* ObjectManager::get_entity_from_id(ID _id)
{
	Entity* ret = nullptr;

	if (_id == ID(UID_OBJ_MAP))
	{
		return m_map;
	}

	//�œK�ȒT���A���S���Y���i�񕔒T���jTODO
	for (auto itr : m_objects)
	{
		if (itr == nullptr)continue;
		else if (itr->get_id() == _id)
		{
			return itr;
		}
	}
	return ret;
}

/*
void ObjectManager::create_TestObj(Vec2 _p)
{
	Object* new_obj = new TestObj(_p);

	regist_object(new_obj);
}
*/

void ObjectManager::create_Inkball(Vec2 _pos, double _init_height, Vec2 _dir, double _fly_strength, Color _color)
{
	if (m_map == nullptr)return;

	Inkball* new_obj = new Inkball(m_map, _pos, _init_height, _dir, _fly_strength, _color);

	m_yet_objects.push(new_obj);
}

void ObjectManager::create_Wall(Vec2 _pos)
{
	if (m_map == nullptr)return;

	Wall* new_obj = new Wall(m_map,_pos);

	m_yet_objects.push(new_obj);
}

void ObjectManager::create_Tire(Vec2 _pos)
{
	if (m_map == nullptr)return;

	Tire* new_obj = new Tire(m_map,_pos);

	m_yet_objects.push(new_obj);
}

void ObjectManager::create_Rumba(Vec2 _pos, Color _color)
{
	if (m_map == nullptr)return;

	Rumba* new_obj = new Rumba(m_map, _pos, _color);

	m_yet_objects.push(new_obj);
}

void ObjectManager::create_Ika(Vec2 _init_p,ControllerType _contoroller_type,Color _color,TeamType _team_type,CharType _char_type,SpecialType _special_type)
{
	if (m_map == nullptr)return;

	Ika* new_obj = new Ika(m_map,_contoroller_type,_init_p,_color,_team_type,_char_type,_special_type);
	
	m_yet_objects.push(new_obj);
}

void ObjectManager::create_Ika(int _index,Vec2 _pos)
{
	if (m_map == nullptr)return;
	Vec2 init_pos = _pos;
	ControllerType controller;
	TeamType team_type;
	Color color;
	CharType char_type;
	SpecialType special_type;

	Ika* new_obj;

	switch (_index)
	{
	case 1:
		controller = Setting::get_controller_1();
		team_type = Setting::get_ika_1_team();
		color = Setting::get_color(team_type);
		char_type = Setting::get_char_1();
		special_type = Setting::get_special_1();
		break;
	case 2:
		controller = Setting::get_controller_2();
		team_type = Setting::get_ika_2_team();
		color = Setting::get_color(team_type);
		char_type = Setting::get_char_2();
		special_type = Setting::get_special_2();
		break;
	case 3:
		controller = Setting::get_controller_3();
		team_type = Setting::get_ika_3_team();
		color = Setting::get_color(team_type);
		char_type = Setting::get_char_3();
		special_type = Setting::get_special_3();
		break;
	case 4:
		controller = Setting::get_controller_4();
		team_type = Setting::get_ika_4_team();
		color = Setting::get_color(team_type);
		char_type = Setting::get_char_4();
		special_type = Setting::get_special_4();
		break;
	}

	new_obj = new Ika(m_map, controller, init_pos, color, team_type, char_type, special_type);

	m_yet_objects.push(new_obj);

}

void ObjectManager::destroy_all_object()
{
	for (auto itr : m_objects)
	{
		if (itr == nullptr)continue;
		itr->set_is_alive(false);
	}
}

void ObjectManager::reset_object_id()
{
	TestObj::m_next_valid_id = 1;
}

/*
void ObjectManager::regist_draw_object(Object* _obj)
{
	Drawer d = Drawer(_obj->get_depth_ref(), _obj);

	m_objects_drawer.push_back(d);
}

void ObjectManager::reset_draw_object(Object* _obj)
{									 
	if (m_objects_drawer.size() == 0)return;

	std::vector<std::vector<Drawer>::iterator> delete_drawer;

	for (std::vector<Drawer>::iterator itr = m_objects_drawer.begin(); itr != m_objects_drawer.end(); itr++)
	{
		if (itr->second == _obj)
		{
			delete_drawer.push_back(itr);
		}
	}

	for (auto itr : delete_drawer)
	{
		m_objects_drawer.erase(itr);
	}
}

*/

void ObjectManager::regist_object(Object* _obj)
{
	//���`�T��
	for (unsigned int i = 0; i < m_objects.size(); i++)
	{
		if (m_objects[i] == nullptr)
		{
			m_objects[i] = _obj;
			//regist_draw_object(_obj);
			return;
		}
	}
	m_objects.push_back(_obj);
	//regist_draw_object(_obj);
}

void ObjectManager::set_map(MapType _type)
{
	if (m_map)return;

	switch (_type)
	{
	case MapType::SIMPLE:
		m_map = OBJ_MAP_SIMPLE;
		break;
	case MapType::SIMPLE_BIG:
		m_map = OBJ_MAP_SIMPLE_BIG;
		break;
	case MapType::CLASSIC:
		m_map = OBJ_MAP_CLASSIC;
		break;
	}

	m_map->enter();

}

void ObjectManager::destroy_map()
{
	if (!m_map)return;

	m_map->exit();
	m_map = nullptr;
}

void ObjectManager::change_map(Map* _map)
{
	if (!m_map)return;

	m_map->exit();

	m_map = _map;

	m_map->enter();
}

void ObjectManager::check_collide()
{
	if (m_objects.empty())return;

	//�Փ˖؍\���Ɋۓ���
	COLLIDE_TREE->collide();

	/*
	//�S�������S�T��
	for (int i = 0; i < m_objects.size(); i++)
	{
		//�R���W�������a��0�ɋ߂��Ɣ�����X�L�b�v
		if (m_objects[i] == nullptr)continue;
		if (m_objects[i]->get_mask_radius() < 0.1)continue;

		for (int j = i+1; j < m_objects.size(); j++)
		{
			if (m_objects[j] == nullptr)continue;
			if (m_objects[j]->get_mask_radius() < 0.1)continue;

			double distance = (m_objects[i]->get_p() - m_objects[j]->get_p()).length();

			//�Փ˔��菈��
			if (distance<=m_objects[i]->get_mask_radius()+ m_objects[j]->get_mask_radius())
			{
				double h1 = m_objects[i]->get_height();
				double h1_bottom = h1 - m_objects[i]->get_mask_height() / 2.0;
				double h1_top = h1 + m_objects[i]->get_mask_height() / 2.0;
				double h2 = m_objects[j]->get_height();
				double h2_bottom = h2 - m_objects[j]->get_mask_height() / 2.0;
				double h2_top = h2 + m_objects[j]->get_mask_height() / 2.0;
				double top_max = Max(h1_top, h2_top);
				double bottom_min = Min(h1_bottom, h2_bottom);
				//�����������Ȃ��
				if(top_max-bottom_min<m_objects[i]->get_mask_height()+ m_objects[j]->get_mask_height())
				{
					m_objects[i]->handle_collide(m_objects[j]);
					m_objects[j]->handle_collide(m_objects[i]);
				}
			}
		}
	}
	*/
	
	
}

void ObjectManager::register_object()
{
	if (m_yet_objects.empty() == true)return;

	while (!m_yet_objects.empty())
	{
		Object* new_obj = m_yet_objects.front();

		regist_object(new_obj);

		//�Փ˖؂ւ̓o�^
		new_obj->restrain_area();
		new_obj->init_morton_and_level();
		MSG_DIS->dispatch_message(0.0, m_id, UID_COLLIDE_TREE, msg::TYPE::REGISTER_TO_COLLIDE_TREE, new_obj);

		m_yet_objects.pop();
	}
}

void ObjectManager::sort_objects()
{
	if (m_objects.empty() == true)return;

	//���t���[���Ăяo������insertion sort�Ŏ���
	//m_depth�ɉ����ď����Ƀ\�[�g
	for (unsigned int i = 0; i < m_objects.size(); i++)
	{
		if (m_objects[i] == nullptr)continue;
		else if (m_objects[i]->get_is_alive() == false)continue;
		for (unsigned int j = i+1; j < m_objects.size();j++)
		{
			if (m_objects[j] == nullptr)continue;
			else if (m_objects[j]->get_is_alive() == false)continue;

			if (m_objects[i]->get_depth() > m_objects[j]->get_depth())
			{
				Object* tmp = m_objects[i];
				m_objects[i] = m_objects[j];
				m_objects[j] = tmp;
			}
		}
	}

}