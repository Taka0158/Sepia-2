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
		//番兵の生成
		m_collidable_objects[i] = new CollidableObject();
		m_list_last_objects[i] = m_collidable_objects[i];
	}
}

void CollideTree::finalize()
{
	//番兵の削除
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
	//まだなにも格納されていなければ(番兵が存在するはずだが）
	if (m_list_last_objects[_obj->get_ary_index()] == nullptr)
	{
		ASSERT(L"番兵がいません");
		m_list_last_objects[_obj->get_ary_index()] = _obj;
		m_collidable_objects[_obj->get_ary_index()] = _obj;
	}
	else
	{
		//既に格納されているオブジェクトの次ポインタに登録
		m_list_last_objects[_obj->get_ary_index()]->set_next_object(_obj);
		_obj->set_previous_object(m_list_last_objects[_obj->get_ary_index()]);
		//最後尾のobjectを更新
		m_list_last_objects[_obj->get_ary_index()] = _obj;
	}
}

void CollideTree::collide()
{
	//衝突オブジェクトリスト
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

		//同空間内と衝突判定
		push_count += collide_same_space(index, _stk);

		//リスト内のオブジェクトと衝突判定
		collide_stacklist(index, stk);

		//下位レベルへ移動
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
	//番兵は無視
	CollidableObject* obj1 = m_collidable_objects[_index]->get_next_object();
	//自分と同じ空間内で総当たり
	while (obj1 != nullptr)
	{
		CollidableObject* obj2 = obj1->get_next_object();
		//マスク半径が0ならば
		if (obj1->get_mask_radius() < MASK_RADIUS_NULL)
		{
			obj1 = obj1->get_next_object();
		}
		else
		{
			while (obj2 != nullptr)
			{
				//マスク半径が0ならば
				if (obj2->get_mask_radius() < MASK_RADIUS_NULL)
				{
					obj2 = obj2->get_next_object();
				}
				else
				{
					//デバグ用表示
					//debug_draw_collide(obj1, obj2);

					//double distance = (obj1->get_p() - obj2->get_p()).length();

					//衝突判定処理
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
						//高さが同じならば
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

	//番兵は無視
	CollidableObject* obj1 = m_collidable_objects[_index]->get_next_object();

	//自分と同じ空間内のオブジェクトとstacklist内のオブジェクトと衝突判定
	while (obj1 != nullptr)
	{
		//マスク半径が0ならば
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

				//デバグ用表示
				//debug_draw_collide(obj1, obj2);

				//double distance = (obj1->get_p() - obj2->get_p()).length();
				//衝突判定処理
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
					//高さが同じならば
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
		//最初は番兵のため省く
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

	Println(L"COLLIDE_TREE:登録オブジェクトの数", m_count);
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
		//最後尾のobjectを更新する
		m_list_last_objects[_obj->get_ary_index()] = _obj->get_previous_object();
	}
}

void CollideTree::debug_draw_collide(CollidableObject* _o1, CollidableObject* _o2)
{
	Line(_o1->get_p(), _o2->get_p()).draw(5.0,Palette::Red);
}

