#pragma once

//�Փˉ\�I�u�W�F�N�g
class CollidableObject :public Entity
{
public:
	//�ԕ��p�R���X�g���N�^
	CollidableObject() :Entity(UID_UNKNOWN) {};

	CollidableObject(ID _id) :Entity(ID(UID_MGR_OBJ) | _id){};

	virtual ~CollidableObject() {};	  

	//�����`�̃}�X�N���g���ꍇ��override
	virtual void mask_update() { m_mask.setPos(m_pos).setSize(m_mask_radius); };

	virtual bool handle_message(const Telegram& msg) { return false; };


	Vec2 get_p()const { return m_pos; };
	Circle& get_mask() { return m_mask; };
	double get_mask_radius() { return m_mask_radius; };
	double set_mask_radius(double _s) { m_mask_radius=_s; };
	double get_height() { return m_height; }
	void set_height(double _s) { m_height = _s; }
	double get_mask_height() { return m_mask_height; };

	//�Փ˔���̎󂯎����s��
	virtual bool handle_collide(CollidableObject*  _obj) { return false; };


	//�Փ˔���4���؂���o�^���O��
	void remove_from_tree();

	//���[�g���ԍ��Ə�����ԃ��x�����X�V����
	void update_morton_and_level();

	//���[�g���ԍ���level�̏��������s��
	void init_morton_and_level();

	//m_pos�����[�g��ԓ��Ɏ��߂�
	void restrain_area();

	int get_morton_number() { return m_morton_number; }
	int get_level() { return m_level; }
	int get_ary_index() { return m_ary_index; }
	CollidableObject* get_previous_object() { return m_previous_object; }
	CollidableObject* get_next_object() { return m_next_object; }
	void set_previous_object(CollidableObject* _obj) { m_previous_object = _obj; }
	void set_next_object(CollidableObject* _obj) { m_next_object= _obj; }



protected:
	//���b�Z�[�W�������s���֐�
	virtual bool on_message(const Telegram&) { return false; };

	//�Փˏ������s��
	virtual bool on_collide(CollidableObject* _obj) { return false; };

	//���g�̒��S���W
	Vec2 m_pos;

	//�n�ʂ���̍���
	double m_height = 0.0;

	//�R���W�����}�X�N
	Circle m_mask = Circle(0, 0, 0);

	//�R���W�����}�X�N�̑傫��
	double m_mask_radius = 1.0;

	//�R���W�����}�X�N�̍���
	double m_mask_height = 2.0;

	//�����ؔz��ɑ����Ă��鎟�̃I�u�W�F�N�g���w������
	CollidableObject* m_next_object = nullptr;
	//�O�̃I�u�W�F�N�g���w��
	CollidableObject* m_previous_object = nullptr;

	//������Ԃ̃��[�g���ԍ�
	int m_morton_number=0;

	//������Ԃ̃��x��
	int m_level=0;

	//�؍\���z��ɂ����index
	int m_ary_index=0;


};

void CollidableObject::init_morton_and_level()
{
	Point p = collide::get_bounding_box(m_mask).second;
	//���[�g��ʊO�ɂ̓C�J�Ȃ��悤�ɂ���
	m_morton_number = collide::get_morton_order_from_index(p);

	m_level = collide::get_level_from_mask(m_mask);

	m_ary_index = collide::get_index_form_morton_num_and_level(m_morton_number, m_level);

}


void CollidableObject::update_morton_and_level()
{

	Point p = Vec2_to_Point(m_pos);
	//���[�g��ʊO�ɂ̓C�J�Ȃ��悤�ɂ���
	int new_morton = collide::get_morton_order_from_index(p);

	if (m_morton_number == new_morton)return;

	m_morton_number = new_morton;

	m_level = collide::get_level_from_mask(m_mask);

	int new_ary_index = collide::get_index_form_morton_num_and_level(m_morton_number, m_level);

	//�z��index�ɕύX�������
	if (new_ary_index != m_ary_index)
	{
		//�؂̕ύX���s��
		remove_from_tree();
		m_ary_index = new_ary_index;
		MSG_DIS->dispatch_message(0.0, UID_UNKNOWN, UID_COLLIDE_TREE, msg::TYPE::REGISTER_TO_COLLIDE_TREE, this, false);
	}
	else
	{

	}

}

void CollidableObject::remove_from_tree()
{
	//���̃I�u�W�F�N�g�����Ȃ����
	if (m_next_object == nullptr)
	{
		//�؂ɍŌ�������E���邱�Ƃ�`����
		MSG_DIS->dispatch_message(0.0, UID_UNKNOWN, UID_COLLIDE_TREE, msg::TYPE::REMOVE_FROM_COLLIDE_TREE, this,false);
		m_previous_object->set_next_object(nullptr);
		m_previous_object = nullptr;

	}
	else
	{
		//�O��̂�����
		m_previous_object->set_next_object(m_next_object);
		m_next_object->set_previous_object(m_previous_object);
		m_next_object = nullptr;
		m_previous_object = nullptr;
	}
}

void CollidableObject::restrain_area()
{
	m_pos = clamp(m_pos, Vec2(0.1, 0.1), Vec2(COLLIDE_SPACE_WIDTH - 1, COLLIDE_SPACE_HEIGHT - 1));
}