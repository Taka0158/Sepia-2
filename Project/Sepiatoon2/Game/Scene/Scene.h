#pragma once

class SceneManager;
class CutScene;



class Scene
{
public:
	virtual void initialize() = 0;
	virtual void  finalize() = 0;

	//Sceneの入った際に呼び出される
	virtual void enter() = 0;
	//メイン更新
	virtual void update() = 0;
	virtual void draw() = 0;
	//Sceneを出る際に呼び出される
	virtual void exit() = 0;

	virtual void debug_update() = 0;
	virtual void debug_draw() = 0;

	//使用するStateでオーバーライド
	virtual void set_cut_scene(CutInType,Color = Palette::White) {};

	virtual void delete_cut_scene() 
	{
		if (m_cut_scene!=nullptr)
		{
			m_cut_scene.reset();
			m_cut_scene = nullptr;
		}
	};

	virtual ~Scene() {};

	String get_scene_name() { return scene_name; };
	UIManager* get_ui() { return m_ui; };


	//背景を描画する準備をする
	void init_background();
	//背景を描画する
	void draw_background();
	//背景イカを描画する
	void draw_ika();
	//イカ座標の更新
	void update_ika_pos();

	//入力によるindexの変化
	virtual void input();
	//コマンドの表示
	virtual void draw_command(int _init_y=0, int _font_size=64);
	

protected:
	String scene_name;

	//コマンド選択のindex
	int m_index;
	
	//シーンごとに別のUIにすべき？
	//規模が小さいので単一のUIで済ます
	//UIが存在しないSceneは　nullptr
	//		  する			 UIManager
	UIManager* m_ui = nullptr;

	std::unique_ptr<CutScene> m_cut_scene = nullptr;

	int m_timer = 0;
	//最も後ろにある背景
	Image m_bg;
	Texture m_tex_bg;

	//背景イカの数
	const static int m_num_ika;

	//背景イカの描画座標
	std::vector<Vec2> m_ika_pos;

	//背景イカのスピード
	std::vector<double> m_ika_speed;

	//イカ出現の上下インターバル
	int m_interval = 600;

	//インデックス遷移のインターバル
	int m_input_timer = 0;
	const static int m_input_interval;

	//サブSceneが利用するコマンド
	std::vector<SceneCommand*> m_commands;
};

const int Scene::m_num_ika = 16;
const int Scene::m_input_interval = 10;


void Scene::draw_background()
{
	m_tex_bg.draw();

	draw_ika();

	//画像の数
	int num_bg = 8;

	for (int i = 0; i < num_bg; i++)
	{
		Color ca = Setting::get_color(TeamType::TEAM_A);
		Color cb = Setting::get_color(TeamType::TEAM_B);
		double r = double(i + 1) / double(num_bg);
		double sin = Sin(m_timer*0.02) + Sin(m_timer*0.01)*Pi*(i - num_bg / 2);
		double cos = Cos(m_timer*0.02) + Cos(m_timer*0.01)*Pi*(i - num_bg / 2);
		Vec2 center_pos = Setting::get_sc() / 2.0;
		double horizontal_interval = 400;
		double x = center_pos.x + horizontal_interval*(i - num_bg / 2) + cos;
		ASSET_FAC->get_tex(ImageType::TITLE_BG).scale(Setting::get_sc_scale()).drawAt(x + 15, center_pos.y + sin + 15, blend_color(ca, cb, r));
		ASSET_FAC->get_tex(ImageType::TITLE_BG).scale(Setting::get_sc_scale()).drawAt(x, center_pos.y - sin, blend_color(ca, cb, r));
	}
}

void Scene::draw_ika()
{
	for (unsigned int i = 0; i < m_num_ika; i++)
	{
		ASSET_FAC->get_tex(ImageType::TITLE_IKA_BG).scale(0.5*m_ika_speed[i] * Setting::get_sc_scale()).drawAt(m_ika_pos[i]);
	}
}

void Scene::update_ika_pos()
{
	int max_x = Setting::get_sc().x;
	int max_y = Setting::get_sc().y;


	for (unsigned int i = 0; i < m_num_ika; i++)
	{
		//上まで行き着いたら
		if (m_ika_pos[i].y < 0 - m_interval)
		{
			m_ika_pos[i] = Vec2(Random(0, max_x), Random(max_y + m_interval / 2, max_y + m_interval));
		}
		else
		{
			m_ika_pos[i].y -= 1.5*m_ika_speed[i];
		}
	}
}

void Scene::init_background()
{
	m_timer = 0;
	m_bg = Image(Setting::full_sc_w, Setting::full_sc_h, Palette::White);

	//背景画像の塗りつぶし
	for (int32 y = 0; y < m_bg.height; ++y)
	{
		for (int32 x = 0; x < m_bg.width; ++x)
		{
			m_bg[y][x] = Color(double(y) / Setting::full_sc_h * 255, double(x) / Setting::full_sc_w * 255, 255);
		}
	}
	m_tex_bg = Texture(m_bg);


	int max_x = Setting::get_sc().x;
	int max_y = Setting::get_sc().y;

	//初期座標を決定する
	for (unsigned int i = 0; i < m_num_ika; i++)
	{
		m_ika_pos.push_back(Vec2(Random(-m_interval, max_x + m_interval), Random(-m_interval, max_y + m_interval)));
		m_ika_speed.push_back(Random(0.75, 1.25));
	}
}

void Scene::input()
{
	if (m_input_timer > m_input_interval)
	{
		if (Setting::is_pressed_key_up_p1() || Setting::is_pressed_key_up_p2())
		{
			m_index--;
			m_input_timer = 0;
		}
		else if (Setting::is_pressed_key_down_p1() || Setting::is_pressed_key_down_p2())
		{
			m_index++;
			m_input_timer = 0;
		}
	}
	else
	{
		m_input_timer++;
	}

	m_index = clamp(m_index, 0, int(m_commands.size())-1);

	if (Setting::is_clicked_key_decide_p1() || Setting::is_clicked_key_decide_p2())
	{
		m_commands[m_index]->execute(this);
	}
}
void Scene::draw_command(int _init_y,int _font_size)
{
	int temp = int(m_commands.size()) / 2;
	int interval = _font_size+ _font_size/2;
	//偶数
	if (int(m_commands.size()) % 2 == 0)
	{
		Point C(Setting::get_sc().x / 2, Setting::get_sc().y / 2);
		for (int i = -temp; i < temp; i++)
		{
			//選択中
			if (i + temp == m_index)
			{
				FONT_IKA_KANA(_font_size)(m_commands[i + temp]->get_name()).drawCenter(C.x, C.y+_init_y + i*interval, Palette::Black);
			}
			//それ以外
			else
			{
				FONT_IKA_KANA(_font_size)(m_commands[i + temp]->get_name()).drawCenter(C.x, C.y + _init_y + i*interval, Palette::White);
			}
		}
	}
	//奇数
	else
	{
		Point C(Setting::get_sc().x / 2, Setting::get_sc().y / 2);
		for (int i = -temp; i <= temp; i++)
		{
			//選択中
			if (i + temp == m_index)
			{
				FONT_IKA_KANA(_font_size)(m_commands[i + temp]->get_name()).drawCenter(C.x, C.y + _init_y + i*interval, Palette::Black);
			}
			//それ以外
			else
			{
				FONT_IKA_KANA(_font_size)(m_commands[i + temp]->get_name()).drawCenter(C.x, C.y + _init_y + i*interval, Palette::White);
			}
		}
	}
}


#include"CutScene\CutScene.cpp"


