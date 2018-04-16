#pragma once

class MapSimple : public Map,public Singleton<MapSimple>
{
	friend class Singleton<MapSimple>;
public:
	MapSimple();
	~MapSimple();

	void initialize()override;
	void finalize() override;

	void enter()override;
	void update()override;
	void draw()override;
	void exit()override;

	void debug_update()override;
	void debug_draw()override;

	bool handle_message(const Telegram&)override;
	bool on_message(const Telegram&)override;

	void paint(Point,int=4);
private:
	//m_vertex_interval*i�Ԗځ@�̊i�q�_������
	//�S�Ă̒��_���Ԃ���
	void interpolation_vertex();

	//m_vertex_interval*i�Ԗڂ̊i�q�_
	//���v�Z����
	void calc_grid();

	//�S�Ă̒��_��ʂ�v�Z
	void calc_all_vertex();

	//�l�����_�̓����v�Z
	void calc_vertex(double&);


private:
	Texture m_background;
	int m_map_w = 1920;
	int m_map_h = 1080;

	// O(w*h)
	double m_vertex[1920][1080];
	//�v�Z���l�����钸�_�̃C���^�[�o��
	int m_vertex_interval = 16;

	//�C���N��Ԃ����t���鎞��ms
	int32 m_equilibrium = 1000;
	
	//�C���N����������ms
	int32 m_dry_dur = 500;

	//�C���N�������������l (0.0�`1.0)
	double m_threshold_dry = 0.10;
	//�C���N���h���ԂƂ݂Ȃ���邵�����l (0.0�`1.0)
	double m_threshold_wet = 0.80;
};

MapSimple* Singleton<MapSimple>::instance = nullptr;