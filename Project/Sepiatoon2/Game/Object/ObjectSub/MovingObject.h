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

	bool rotate_heading_to_face_position(Vec2);
	void set_heading(Vec2);

	//MovingObjectのパラメータを設定する
	virtual void set_moving_parm() = 0;
protected:

	Vec2 m_velocity =Vec2(0.0,0.0);

	Vec2 m_heading=Vec2(0.0,1.0);

	Vec2 m_side_heading=Vec2(1.0,0.0);

	double m_mass;

	double m_max_speed;

	double m_max_force;

	double m_max_turn_rate;
};

#include"MovingObjectSub\Ika.cpp"

bool MovingObject::rotate_heading_to_face_position(Vec2 _vec)
{
	Vec2 to_target = _vec.normalized();

	double angle = acos(m_heading.dot(to_target));

	if (angle < 0.000001)return true;

	if (angle < m_max_turn_rate)angle = m_max_turn_rate;

	Mat3x2 rotation_matrix;

	//clockwise
	//rotation_matrix.rotate(angle*m_heading.)
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
	//m_side_heading = ;

}