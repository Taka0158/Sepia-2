#include"ObjectManager.h"



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
}

void ObjectManager::finalize()
{
	destroy_all_object();
	check_alive();
	reset_object_id();
	destroy_map();
}

void ObjectManager::update()
{
	check_alive();
	
	check_collide();

	if (m_map != nullptr)m_map->update();


	for (unsigned int i = 0; i < m_objects.size(); i++)
	{
		if (m_objects[i] != nullptr)
		{
			if (m_objects[i]->get_is_alive() == false)continue;
			m_objects[i]->update();
		}
	}
}

void ObjectManager::draw()
{
	/*
	for (unsigned int i = 0; i < m_objects.size(); i++)
	{
		if (m_objects[i] != nullptr)
		{
			if (m_objects[i]->get_is_alive() == false)continue;
			m_objects[i]->draw();
		}
	}
	*/
	if (m_map != nullptr)m_map->draw();

	//レイヤ有り
	for (auto itr : m_objects_drawer)
	{
		if (itr.second != nullptr)
		{
			if (itr.second->get_is_alive() == false)continue;
			itr.second->draw();
		}
	}
}

void ObjectManager::debug_update()
{
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
	if (m_map != nullptr)m_map->debug_draw();

	for (unsigned int i = 0; i < m_objects.size(); i++)
	{
		if (m_objects[i] != nullptr)
		{
			if (m_objects[i]->get_is_alive() == false)continue;
			m_objects[i]->debug_draw();
		}
	}
	Println(L"オブジェクト数:", m_objects.size());
	Println(L"描画オブジェクト数:", m_objects_drawer.size());

}

void ObjectManager::check_alive()
{
	if (m_objects.size() == 0)return;

	auto isAlive = [](Object* obj)
	{
		return !obj->get_is_alive();
	};

	//削除すべき要素を最後尾へ
	auto rmvIter = std::remove_if(m_objects.begin(), m_objects.end(), isAlive);

	//描画オブジェクト登録解除
	for (auto itr = rmvIter; itr != m_objects.end(); itr++)
	{
		reset_draw_object(*itr);
	}

	//削除すべき最初の要素から最後までを削除する
	m_objects.erase(rmvIter, m_objects.end());
}

bool ObjectManager::handle_message(const Telegram& _msg)
{
	on_message(_msg);
	return true;
}

bool ObjectManager::on_message(const Telegram& _msg)
{
	bool ret = false;

	switch (_msg.msg)
	{
	case msg::TYPE::OBJMGR_DESTROY_ALL_OBJECT:
		destroy_all_object();
		ret = true;
		break;
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

	//最適な探索アルゴリズム（二部探索）TODO
	for (auto itr : m_objects)
	{
		if (itr->get_id() == _id)
		{
			return itr;
		}
	}

	return ret;
}

void ObjectManager::create_TestObj(Vec2 _p)
{
	Object* new_obj = new TestObj(_p);

	regist_object(new_obj);
}

void ObjectManager::create_Ika(Vec2 _init_p,ControllerType _contoroller_type,Color _color,TeamType _team_type,CharType _char_type,SpecialType _special_type)
{
	if (m_map == nullptr)return;

	Ika* new_obj = new Ika(m_map,_contoroller_type,_init_p,_color,_team_type,_char_type,_special_type);
	
	regist_object(new_obj);
}

void ObjectManager::destroy_all_object()
{
	for (auto itr : m_objects)
	{
		itr->set_is_alive(false);
	}
}

void ObjectManager::reset_object_id()
{
	TestObj::m_next_valid_id = 1;
}

void ObjectManager::regist_draw_object(Object* _obj)
{
	Drawer d = Drawer(_obj->get_depth(), _obj);

	m_objects_drawer.insert(d);
}

void ObjectManager::reset_draw_object(Object* _obj)
{									 
	Drawer d = Drawer(_obj->get_depth(), _obj);
	
	if (_obj == nullptr)
	{
		ASSERT(L"regist_draw_object() : 削除済みのオブジェクトをresetしました");
	}

	int temp = m_objects_drawer.erase(d);

	if (temp == 0)
	{
		ASSERT(L"regist_draw_object() : resetに失敗しました");
	}
}

void ObjectManager::regist_object(Object* _obj)
{
	m_objects.push_back(_obj);
	regist_draw_object(_obj);
}

void ObjectManager::set_map(MapType _type)
{
	if (m_map)return;

	switch (_type)
	{
	case MapType::SIMPLE:
		m_map = OBJ_MAP_SIMPLE;
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

	//ゴリ押し全探索
	for (int i = 0; i < m_objects.size(); i++)
	{
		//コリジョン半径が0に近いと判定をスキップ
		if (m_objects[i]->get_mask_radius() < 0.1)continue;

		for (int j = i+1; j < m_objects.size(); j++)
		{
			if (m_objects[j]->get_mask_radius() < 0.1)continue;

			//衝突しているなら
			if (m_objects[i]->get_mask().intersects(m_objects[j]->get_mask()))
			{
				//高さが同じならば
				if(Abs(m_objects[i]->get_height()-m_objects[j]->get_height())<=HEIGHT_THRESHOLD)
				{
					m_objects[i]->handle_collide(m_objects[j]);
					m_objects[j]->handle_collide(m_objects[i]);
				}
			}
		}
	}
}