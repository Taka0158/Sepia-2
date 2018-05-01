#pragma once

class SelectChar :public Scene
{
public:
	SelectChar();
	~SelectChar();

	void initialize();
	void finalize();

	void enter();
	void update();
	void draw();
	void debug_update();
	void debug_draw();
	void exit();

	void input()override;


private:
	//����L�[�ɂ�鏀�������̐؂�ւ����s��
	void toggle_ready();

	//�I�𒆂̃L�����N�^�\�����s��
	void draw_charcter();
	void draw_frame();

	//�L�����I���̌�����s��
	void decide_p1(CharType);
	void decide_p2(CharType);

	//�\�����̃L�����N�^�̉摜������Ă���
	Texture* get_tex(CharType);

	//�L�����N�^�̐������s��
	void chara_describe();

	//�����f�[�^�̓���
	void get_char_info(std::vector<String>& _container, CharType _type);

	//������������̌o�ߎ���
	int m_ready_timer;

	//������������̑҂�����
	static int m_ready_durtion;

	//�������ł������ǂ���
	bool m_is_ready_p1;
	bool m_is_ready_p2;
	//�\�����̃L�����^�C�v
	int m_index_p1;
	int m_index_p2;
};

int SelectChar::m_ready_durtion = 90;