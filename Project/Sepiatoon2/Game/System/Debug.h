#pragma once

//-----------------------------------debug---------------------------------
class DebugText
{
public:
	DebugText(double _time, String _info)
	{
		time = Setting::stopwatch.s() + _time;
		info = _info;
	}
	//�\���p������
	double time;
	//�t�����
	String info;
};
bool operator==(const DebugText& t1, const DebugText& t2)
{
	return (t1.time - t2.time < 0.0001);
}
bool operator<(const DebugText&t1, const DebugText&t2)
{
	if (t1 == t2)return false;
	else return (t1.time < t2.time);
}

class Debug :public Singleton<Debug>
{
	friend class Singleton<Debug>;
public:
	void update()
	{
		show_mouse_pos();

		//�t���X�N���[���؂�ւ�
		if (Input::KeyF4.clicked)
		{
			Setting::toggle_fullscreen();
		}
		//fps�\��
		Println(Profiler::FPS(), L"FPS");

		check();
	}
	void show()
	{
		if (texts.empty())return;
		for (auto itr : texts)
		{
			Println(itr.info);
		}
	}
	void regist(DebugText _text)
	{
		texts.push_back(_text);
	}
	//�Փˋ�Ԃ̕`��
	void draw_collide_space();
private:
	//�S������Ԃ�`��
	//_pos : ������W�ƉE�����W
	//_level : �Ăяo�����̕������x��
	void draw_area(std::pair<Point,Point> _pos ,int _level=0 );

	//�����؂�̃f�o�b�O�e�L�X�g���폜
	void check()
	{
		if (texts.empty())return;

		auto isInvalid = [](DebugText& text)
		{
			return text.time <= Setting::stopwatch.s();
		};

		auto rmvIter = std::remove_if(texts.begin(), texts.end(), isInvalid);

		texts.erase(rmvIter, texts.end());
	}
	//�}�E�X�̍��W��\��
	void show_mouse_pos()
	{
		Println(L"�}�E�X���W:",Mouse::Pos() );
	}
private:
	static std::vector<DebugText> texts;
};
std::vector<DebugText> Debug::texts = std::vector<DebugText>();
Debug* Singleton<Debug>::instance = nullptr;


void Debug::draw_collide_space()
{
	Rect root = Rect(COLLIDE_ROOT_SPACE_LT, Size(COLLIDE_SPACE_WIDTH, COLLIDE_SPACE_HEIGHT));
	
	//�A���t�@�l
	int a = 100;
	Color c = Color(Palette::Cyan);

	//���[�g��Ԃ̕\��
	root.draw(Color(c,a));

	draw_area(std::make_pair(COLLIDE_ROOT_SPACE_LT, COLLIDE_ROOT_SPACE_LT+ Size(COLLIDE_SPACE_WIDTH, COLLIDE_SPACE_HEIGHT)), 0);

}

void Debug::draw_area(std::pair<Point, Point> _pos, int _level)
{
	if (_level >= COLLIDE_SPACE_MAX_PARTITION_LEVEL)return;

	std::queue<std::pair<Point, Point>> q;

	Point lt = _pos.first;
	Point rb = _pos.second;
	int w = rb.x - lt.x;
	int h = rb.y - lt.y;

	Color c;
	if (_level == 0)c = Color(Palette::Red);
	else if (_level == 1)c = Color(Palette::Orange);
	else if (_level == 2)c = Color(Palette::Green);
	else if (_level == 3)c = Color(Palette::Gray);
	else if (_level == 4)c = Color(Palette::Black);

	for (int x = 0; x < 2; x++)
	{
		for (int y = 0; y < 2; y++)
		{
			Point p = lt + Point(w/2*x, h/2*y);
			Rect(p + Point(1, 1), Size(w/2-1, h/2-1)).drawFrame(COLLIDE_SPACE_MAX_PARTITION_LEVEL-_level+1,0.0,c);
			q.push(std::make_pair(p, p + Point(w / 2, h / 2)));
		}
	}

	while (q.empty() == false)
	{
		draw_area(q.front(), _level + 1);
		q.pop();
	}
}

//-----------------------------------debug---------------------------------