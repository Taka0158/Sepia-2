#pragma once

class Map;
class IkaState;
class IkaController;

class Ika :public MovingObject
{
	//friend class IkaState;
	//friend class IkaController;
public:
	Ika(Map* _map,ControllerType _controller_type,Vec2 _p,Color _color,TeamType _team_type,CharType _char_type,SpecialType _special_type);
	~Ika();

	void initialize();
	void finalize();
	void update();
	void draw();
	void mask_update();

	void debug_update();
	void debug_draw();

	void set_id();
	
	//Charに応じてのMovingObjectのパラメータ設定
	void set_moving_parm();

	//物理挙動処理
	void behavior_update();

	//Mapにインクをぶちまける関数
	void paint();

	//State変更
	void change_state(IkaState*);

	//座標の制限
	void restrain();

	//テクスチャの倍率
	double get_tex_scale() { return 0.25; };

	//同名クラス以下で呼び出されるパラメータの補正
	void set_moving_parm(double _mass, double _max_speed, double _max_force, double _max_turn_rate, double _friction);

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
	ControllerType get_controller_type() { return m_controller_type; }
	Vec2 get_init_pos() { return m_init_pos; }
	Vec2 get_target_pos() { return m_target_pos; }
	Map* get_map() { return m_map; }
	Color get_rival_color() { return m_rival_color; }

	void set_init_pos(Vec2 _p) { m_init_pos = _p; }

	bool handle_message(const Telegram&)override;
	bool on_message(const Telegram&);

private:
	//画像の登録
	void regist_texture(CharType);
	//コントロールクラスの割り当て
	void regist_controller(ControllerType);
	//相手の色を設定する
	void set_rival_color();
protected:
	Vec2 m_target_pos;

private:
	//イカの状態を表す
	std::unique_ptr<IkaState> m_ika_state;

	//イカのコントロールクラス
	std::unique_ptr<IkaController> m_controller;
	
	//開始座標
	Vec2 m_init_pos;

	//MAP情報
	Map* m_map;

	//各種パラメータ
	Color m_color;
	Color m_rival_color;
	TeamType m_team_type;
	CharType m_char_type;
	SpecialType m_special_type;
	ControllerType m_controller_type;

	//画像データ
	Texture m_tex_n;
	Texture m_tex_c;
	Texture m_tex_s;
	Texture m_tex_a;

	static int m_next_valid_id;

};

int Ika::m_next_valid_id = 0;

#include"IkaState\IkaState.h"
#include"IkaController\IkaController.h"