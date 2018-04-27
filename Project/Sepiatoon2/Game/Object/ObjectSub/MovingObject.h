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
			m_depth = m_init_depth+int(m_height);
		}
		else
		{
			//描画深度を高さに応じて変化させる
			m_depth = m_init_depth;
		
			m_height = 0.0;
			m_gravity_force = 0.0;
		}
	}

	void burst(Vec2 _power)
	{
		m_velocity = _power;
	}

	//浮かせる
	void fly(double _strength=20.0)
	{
		m_height += 0.2;
		m_gravity_force -= _strength;
	}

	void enable_gravity()
	{
		m_gravity = 0.98;
	}

	void unable_gravity()
	{
		m_gravity = 0.0;
	}

	virtual void init_moving_param()
	{
		m_mass = 1.0;
		m_max_speed = 10.0;
		m_max_force = 10.0;
		m_max_turn_rate = 0.01;
		m_friction = 0.05;
	}

	//影を描画する
	void draw_shadow(double _size = 1.0)
	{
		if (m_height > 3.0)
		{
			ASSET_FAC->get_tex(ImageType::SHADOW_64).scale(_size).drawAt(m_pos);
		}
	}

	void calc_angle(double& _angle)
	{
		//前作からのコピペ
		//角度計算
		if (m_velocity.length() <= m_max_speed*0.2)return;
		double angletemp = Atan2(m_velocity.y, m_velocity.x);
		//回転角の小さい方をdiffとする（この部分）
		double anglediff1 = (abs(angletemp - _angle)<Pi) ? angletemp - _angle : 2 * Pi - abs(angletemp - _angle);
		double angle_add = Pi / 180 * 3;
		double temp = Sign(anglediff1)*angle_add;
		_angle += temp;
		if (_angle > 2 * Pi)_angle -= 2 * Pi;
		else if (_angle < -Pi + 1)_angle += 2 * Pi;
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
	double m_gravity = 0.98;

	//重力による力
	double m_gravity_force = 0.0;

};

#include"MovingObjectSub\Ika.cpp"
#include"MovingObjectSub\MapGimmick.h"
#include"MovingObjectSub\Item.h"

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