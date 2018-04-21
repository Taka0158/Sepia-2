#pragma once

class Map;
class IkaState;

class Ika :public MovingObject
{
public:
	Ika(Map* _map,Vec2 _p,Color _color,TeamType _team_type,CharType _char_type,SpecialType _special_type);
	~Ika();

	void initialize();
	void finalize();
	void update();
	void draw();
	void mask_update();

	void debug_update();
	void debug_draw();

	void set_id();
	
	void set_moving_parm();

	//State変更
	void change_state(IkaState*);

	//ノーマル状態
	Texture& get_tex_n() { return m_tex_n; }
	//泣き状態
	Texture& get_tex_c() { return m_tex_c; }
	//泳ぎ状態
	Texture& get_tex_s() { return m_tex_s; }
	//怒り状態
	Texture& get_tex_a() { return m_tex_a; }

	Color get_color() { return m_color; }
	TeamType get_team_type(){ return m_team_type; }
	CharType get_char_type() { return m_char_type; }
	SpecialType get_special_type() { return m_special_type; }
	Vec2 get_init_pos() { return m_init_pos; }
	Map* get_map() { return m_map; }

	void set_init_pos(Vec2 _p) { m_init_pos = _p; }


private:
	//画像の登録
	void regist_texture(CharType);
private:
	//イカの状態を表す
	std::unique_ptr<IkaState> m_ika_state;

	//開始座標
	Vec2 m_init_pos;

	//MAP情報
	Map* m_map;

	//各種パラメータ
	Color m_color;
	TeamType m_team_type;
	CharType m_char_type;
	SpecialType m_special_type;

	//画像データ
	Texture m_tex_n;
	Texture m_tex_c;
	Texture m_tex_s;
	Texture m_tex_a;
	

	static int m_next_valid_id;

};

int Ika::m_next_valid_id = 0;

#include"IkaState\IkaState.h"