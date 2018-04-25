#pragma once

//移動するクラス

class MovingObject :public Object
{
public:
	MovingObject(ID _id):Object(_id) {};
	~MovingObject() {};

	Vec2 get_velocity() { return m_velocity; }
	Vec2 get_heading() { return m_heading; }
	Vec2 get_side_heading() { return m_side_heading; }

	double get_mass() { return m_mass; };
	double get_max_speed() { return m_max_speed; }
	double get_max_force() { return m_max_force; }
	double get_max_turn_rate() { return m_max_turn_rate; }

	//目標の座標へ正面ベクトルが向くようにする
	//ただしベクトル回転の更新はm_max_turn_rateによって制限される
	//目標の座標へ向くとtrueを返す
	bool rotate_heading_to_face_position(Vec2);

	//新しく方向ベクトルm_heading（vec_side)を設定
	void set_heading(Vec2);

	//MovingObjectのパラメータを設定する
	virtual void set_moving_parm() = 0;

	//重力を適応する
	void gravity()
	{
		if (m_height >= 0.1)
		{
			m_gravity_force += m_gravity;
			m_height -= m_gravity_force;
			
			//描画深度を高さに応じて変化させる
			m_depth -= int(m_height);
		}
		else
		{
			//描画深度を高さに応じて変化させる
			m_depth = m_init_depth;
		
			m_height = 0.0;
			m_gravity_force = 0.0;
		}
	}

	//浮かせる
	void fly(double _strength=20.0)
	{
		m_height = 0.2;
		m_gravity_force -= _strength;
	}

	//影を描画する
	void draw_shadow(double _size = 1.0)
	{
		if (m_height > 3.0)
		{
			ASSET_FAC->get_tex(ImageType::SHADOW_64).scale(_size).drawAt(m_pos);
		}
	}
protected:

	Vec2 m_velocity =Vec2(0.0,0.0);

	Vec2 m_heading=Vec2(0.0,1.0);

	Vec2 m_side_heading=Vec2(1.0,0.0);

	double m_friction;

	double m_mass;

	double m_max_speed;

	double m_max_force;

	double m_max_turn_rate;

	//重力加速度
	static double m_gravity;

	//重力による力
	double m_gravity_force = 0.0;

};

double MovingObject::m_gravity = 0.98;

#include"MovingObjectSub\Ika.cpp"

bool MovingObject::rotate_heading_to_face_position(Vec2 _vec)
{
	Vec2 to_target = _vec.normalized();

	double angle = acos(m_heading.dot(to_target));

	if (angle < 0.000001)return true;

	if (angle < m_max_turn_rate)angle = m_max_turn_rate;

	Mat3x2 rotation_matrix;

	//clockwise
	rotation_matrix.rotate(angle*Sign(m_heading.cross(to_target)));
	rotation_matrix.transform(m_heading);
	rotation_matrix.transform(m_velocity);

	//垂直ベクトル
	m_side_heading = m_heading;
	return false;
}

void MovingObject::set_heading(Vec2 _vec)
{
	assert((new_heading.LengthSq() - 1.0) < 0.00001);

	m_heading = _vec;

	//垂直
	m_side_heading = perp(m_heading);

}