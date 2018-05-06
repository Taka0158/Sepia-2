#include"ObjectManager.h"

//苦渋のinclude
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

	//nullptr の要素を削除する
	auto is_nullptr = [](Object* _obj)
	{
		return _obj==nullptr;
	};
	//削除すべき要素を最後尾へ
	auto rmvIter = std::remove_if(m_objects.begin(), m_objects.end(), is_nullptr);
	//削除すべき最初の要素から最後までを削除する
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
	//未登録オブジェクトを登録する
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

			//ルート空間内に納める
			m_objects[i]->restrain_area();

			//各オブジェクトのモートン番号を更新する
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
	//描画深度より描画順序整列
	if(m_timer%m_sort_duration==0)std::sort(m_objects_drawer.begin(), m_objects_drawer.end());


	//動的にm_depthが代わるものは正しい順序にならない
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

			//AABB表示
			std::pair<Point, Point> p = collide::get_bounding_box(m_objects[i]->get_mask());
			Rect(p.first, p.second - p.first).draw(Color(Palette::Red, 100));
			//モートン番号とレベルを表示
			FONT_DEBUG_16(m_objects[i]->get_morton_number(), L":", m_objects[i]->get_level()).drawCenter(m_objects[i]->get_p());

			m_objects[i]->debug_draw();
		}
	}
	COLLIDE_TREE->debug_draw();
	DEBUG->draw_collide_space();
	//確認のため
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
	Println(L"未登録オブジェクト数:", m_yet_objects.size());
	Println(L"オブジェクト数:", m_objects.size());
	//Println(L"描画オブジェクト数:", m_objects_drawer.size());

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
				//描画オブジェクト登録の解除
				//reset_draw_object(m_objects[i]);

				//受取人がdeleteされるメッセージは削除
				MSG_DIS->delete_direct_message(m_objects[i]); 

				//衝突判定木から取り除く
				m_objects[i]->remove_from_tree();

				delete m_objects[i];
				m_objects[i] = nullptr;
			}
		}
	}

	/*
	//正しくdeleteできなかった

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
	//switch文を使うことの見通しの悪さ
	std::pair<int, Vec2>* pair;
	IkaStateType s;
	Paint p;
	InkballParm* ip;
	OrbParm* op;
	IkaBalloonParm* ibp;
	MissileParm* mp;
	RumbaParm* rp;
	Ika* ika;

	switch (_msg.msg)
	{
	case msg::TYPE::OBJMGR_DESTROY_ALL_OBJECT:
		destroy_all_object();
		ret = true;
		break;
	case msg::TYPE::CREATE_INK_BALL:
		ip=(InkballParm*)_msg.extraInfo;
		create_Inkball(ip->pos, ip->init_height, ip->dir, ip->fly_strength, ip->color,ip->paint_scale);
		ret = true;
		break;
	case msg::TYPE::ALL_WALL_PAINT:
		//試合終了の時呼び出される想定
		//壁下色を結果に影響しないように黒色にする
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
				else if (is_same_class(m_objects[i]->get_id(), ID(ID_MAPGIMMCIK_RESPAWN_POINT)))
				{
					p = Paint(Vec2_to_Point(m_objects[i]->get_p()), Palette::Black, 1.0, &ASSET_FAC->get_image(ImageType::WALL_BLACK_CIRCLE), false);
					MSG_DIS->dispatch_message(0.0, this, m_map, msg::TYPE::MAP_PAINT, &p);
				}

			}
		}
		ret = true;
		break;
	case msg::TYPE::GET_MISSILE_TARGET:
		MSG_DIS->dispatch_message(0.0, m_id, _msg.sender_id, msg::TYPE::GIVE_MISSILE_TARGET, find_missile_target((Missile*)_msg.extraInfo));
		ret = true;
		break;
	case msg::TYPE::CREATE_ORB:
		op = (OrbParm*)_msg.extraInfo;
		create_SpecialOrb(op->pos, op->init_height, op->dir, op->fly_strength, op->type);
		ret = true;
		break;
	case msg::TYPE::CREATE_IKABALLOON:
		ibp = (IkaBalloonParm*)_msg.extraInfo;
		create_IkaBalloon(ibp->pos, ibp->type);
		ret = true;
		break;
	case msg::TYPE::CREATE_MISSILE:
		mp = (MissileParm*)_msg.extraInfo;
		create_Missile(mp->pos,mp->init_height,mp->color,mp->type);
		ret = true;
		break;
	case msg::TYPE::CREATE_RUMBA:
		rp = (RumbaParm*)_msg.extraInfo;
		create_Rumba(rp->pos,rp->color);
		ret = true;
		break;
	case msg::TYPE::CREATE_IKA:
		pair = (std::pair<int, Vec2>*)_msg.extraInfo;
		ika = create_Ika(pair->first, pair->second);
		//もしリスポーンオブジェクトから呼び出されていたらIkaを返す
		if (is_same_class(_msg.sender_id, ID(ID_MAPGIMMCIK_RESPAWN_POINT)))
		{
			MSG_DIS->dispatch_message(0.0, m_id, ID(_msg.sender_id), msg::TYPE::GIVE_CREATED_IKA, ika);
		}
		break;
	case msg::TYPE::ALL_IKA_STATE_RESPAWN:
		for (unsigned int i = 0; i < m_objects.size(); i++)
		{
			if (m_objects[i] != nullptr)
			{
				if (m_objects[i]->get_is_alive() == false)continue;
				if (is_same_class(m_objects[i]->get_id(), ID(ID_OBJ_IKA)))
				{
					s = IkaStateType::IKA_RESPAWN;
					MSG_DIS->dispatch_message(0.0, this, m_objects[i], msg::TYPE::DELETE_IKA_GLOBAL_STATE);
					MSG_DIS->dispatch_message(0.0, this, m_objects[i], msg::TYPE::SET_IKA_GLOBAL_STATE,&s);
				}
			}
		}
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

void ObjectManager::create_Inkball(Vec2 _pos, double _init_height, Vec2 _dir, double _fly_strength, Color _color, double _paint_scale)
{
	if (m_map == nullptr)return;

	Inkball* new_obj = new Inkball(m_map, _pos, _init_height, _dir, _fly_strength, _color,_paint_scale);

	m_yet_objects.push(new_obj);
}

void ObjectManager::create_SpecialOrb(Vec2 _pos, double _init_height, Vec2 _dir, double _fly_strength, OrbType _type)
{
	if (m_map == nullptr)return;

	SpecialOrb* new_obj = new SpecialOrb(m_map, _pos, _init_height, _dir, _fly_strength, _type);

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

Ika* ObjectManager::create_Ika(int _index,Vec2 _pos)
{
	if (m_map == nullptr)return nullptr;
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

	return new_obj;

}

void ObjectManager::create_Missile(Vec2 _pos, double _init_height, Color _color, MissileType _type)
{
	if (m_map == nullptr)return;

	Missile *new_obj = new Missile(m_map, _pos, _init_height, _color,_type);

	m_yet_objects.push(new_obj);
}

void ObjectManager::create_IkaBalloon(Vec2 _pos, IkaBalloonType _type)
{
	if (m_map == nullptr)return;

	IkaBalloon* new_obj = new IkaBalloon(m_map, _pos,_type);

	m_yet_objects.push(new_obj);
}

void ObjectManager::create_Trampoline(Vec2 _pos)
{
	if (m_map == nullptr)return;

	Trampoline* new_obj = new Trampoline(m_map, _pos);

	m_yet_objects.push(new_obj);
}

void ObjectManager::create_RespawnPoint(Vec2 _pos,TeamType _type)
{
	if (m_map == nullptr)return;

	RespawnPoint* new_obj = new RespawnPoint(m_map, _pos,Setting::get_color(_type));

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
	//線形探索
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

	//衝突木構造に丸投げ
	COLLIDE_TREE->collide();

	/*
	//ゴリ押し全探索
	for (int i = 0; i < m_objects.size(); i++)
	{
		//コリジョン半径が0に近いと判定をスキップ
		if (m_objects[i] == nullptr)continue;
		if (m_objects[i]->get_mask_radius() < 0.1)continue;

		for (int j = i+1; j < m_objects.size(); j++)
		{
			if (m_objects[j] == nullptr)continue;
			if (m_objects[j]->get_mask_radius() < 0.1)continue;

			double distance = (m_objects[i]->get_p() - m_objects[j]->get_p()).length();

			//衝突判定処理
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
				//高さが同じならば
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

		//衝突木への登録
		new_obj->restrain_area();
		new_obj->init_morton_and_level();
		MSG_DIS->dispatch_message(0.0, m_id, UID_COLLIDE_TREE, msg::TYPE::REGISTER_TO_COLLIDE_TREE, new_obj);

		m_yet_objects.pop();
	}
}

void ObjectManager::sort_objects()
{
	if (m_objects.empty() == true)return;

	//毎フレーム呼び出すためinsertion sortで実装
	//m_depthに応じて昇順にソート
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

Object* ObjectManager::find_missile_target(Missile* _missile)
{
	Object* ret = nullptr;

	Color missile_color = _missile->get_color();

	//候補を格納
	std::list<Object*> rumba_targets;

	for(unsigned int i=0;i<m_objects.size();i++)
	{
		if (m_objects[i] != nullptr)
		{
			if (m_objects[i]->get_is_alive() == false)continue;
			if (is_same_class(m_objects[i]->get_id(),ID(ID_OBJ_IKA)))
			{
				if (m_objects[i]->get_color() != missile_color)
				{
					//Ikaが見つかれば即座に終了
					return m_objects[i];
				}
			}
			else if (is_same_class(m_objects[i]->get_id(), ID(ID_OBJ_RUMBA)))
			{
				if (m_objects[i]->get_color() != missile_color)
				{
					//Rumbaが見つかれば候補に格納
					rumba_targets.push_back(m_objects[i]);
				}
			}
		}
	}

	//ルンバがいればそれに向かう
	if (rumba_targets.empty() == false)ret = rumba_targets.front();
	return ret;
}