#pragma once



class Map;
class IkaState;
class IkaController;
class IkaStateMachine;

class Ika :public MovingObject,public Indicatable
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
	void init_id()override;

	//Charに応じてのMovingObjectのパラメータ設定
	void set_moving_parm();

	//物理挙動処理
	void behavior_update();

	//Mapにインクをぶちまける関数
	void paint();

	//座標の制限
	void restrain();

	//テクスチャの倍率
	double get_tex_scale() { return 0.25; };

	//Stateによる補正
	void set_moving_parm(IkaStateType);

	//ノーマル状態
	Texture& get_tex_n() { return m_tex_n; }
	//泣き状態
	Texture& get_tex_c() { return m_tex_c; }
	//泳ぎ状態
	Texture& get_tex_s() { return m_tex_s; }
	//怒り状態
	Texture& get_tex_a() { return m_tex_a; }

#pragma region get_function
	Color get_color() { return m_color; }
	TeamType get_team_type(){ return m_team_type; }
	CharType get_char_type() { return m_char_type; }
	SpecialType get_special_type() { return m_special_type; }
	ControllerType get_controller_type() { return m_controller_type; }
	IkaController* get_controller() { return m_controller.get(); }
	IkaStateMachine* get_ika_fsm() { return m_ika_fsm.get(); }

	double get_hp() { return m_hp; }
	double get_init_hp() { return m_init_hp; }
	double get_special_gauge() { return m_special_gauge; }
	double get_init_special_gauge() { return m_init_special_gauge; }
	double get_paint_scale() { return m_paint_scale; }
	double get_swim_jump() { return m_swim_jump; }

	Vec2 get_init_pos() { return m_init_pos; }
	Vec2 get_target_pos() { return m_target_pos; }
	Map* get_map() { return m_map; }
	Color get_rival_color() { return m_rival_color; }
	//0.5*Piは素材の向きによるもの
	double get_angle() { return m_angle + 0.5*Pi; }
#pragma endregion

	//倍率変動
	void set_special_gauge(double _s) { m_special_gauge = m_init_special_gauge*_s; }
	void init_special_gauge() { m_special_gauge = m_init_special_gauge; }

	//倍率変動
	void set_special_gauge_rate(double _s) { m_gauge_rate = m_init_gauge_rate*_s; }
	void init_special_gauge_rate() { m_gauge_rate = m_init_gauge_rate; }
	//倍率変動
	void set_paint_scale(double _s) { m_paint_scale = m_init_paint_scale*_s; }
	void init_paint_scale() { m_paint_scale = m_init_paint_scale; }	 

	//倍率変動
	void set_mask_radius(double _s) { m_mask_radius = m_init_mask_radius*_s; }
	void init_mask_radius() { m_mask_radius = m_init_mask_radius; }

	//倍率変動
	void set_mask_height(double _s) { m_mask_height = m_init_mask_height*_s; }
	void init_mask_height() { m_mask_height= m_init_mask_height; }

	//倍率変動
	void set_max_speed(double _s) { m_max_speed = m_init_max_speed*_s; }
	void init_max_speed() { m_max_speed= m_init_max_speed; }

	//倍率変動
	void set_hp_regene_rate(double _s) { m_hp_regene_rate = m_init_hp_regene_rate*_s; }
	void init_hp_regene_rate() { m_hp_regene_rate = m_init_hp_regene_rate; }
	
	//倍率変動
	void set_swim_jump(double _s) { m_swim_jump = m_init_swim_jump *_s; }
	void init_swim_jump() { m_swim_jump = m_init_swim_jump; }

	void set_init_pos(Vec2 _p) { m_init_pos = _p; }

	bool handle_message(const Telegram&)override;
	bool handle_collide(CollidableObject* _obj)override;

	void show_ui()override;

	//ダメージを受けた時呼ぶ
	void damaged(double);
	//例外なくダメージを受ける
	void damaged_definitely(double _damage);
	//相手のキャラタイプに応じてダメージ量変動
	void damaged(CharType);
	//HPが0の時呼び出す
	void destroy();
	//パラメータの初期化
	void init_param();

	//スペシャルゲージの上昇
	void increase_special_gauge(double _value);
	//hpの自動回復
	void regene_hp();
	//Sink状態の継続ダメージ
	void sink_damage();

	//スペシャルの発動
	void execute_special();

	bool is_enable_execute_special() { return m_special_gauge >= m_max_special_gauge; }
private:
	bool on_message(const Telegram&)override;
	bool on_collide(CollidableObject* _obj)override;
	//画像の登録
	void regist_texture(CharType);
	//コントロールクラスの割り当て
	void regist_controller(ControllerType);
	//相手の色を設定する
	void set_rival_color();
	//パラメータ変更
	void set_moving_parm(double _mass, double _max_speed, double _max_force, double _max_turn_rate, double _friction);
	//Stateのセット
	void set_state(IkaStateType);
	void set_global_state(IkaStateType);
	void overwrite_global_state(IkaStateType);

	//キャラごとのパラーメタを設定
	void set_char_param(CharType _type);
	//スペシャルゲージの表示
	void show_special_gauge();
	//体力ゲージの表示
	void show_hp();

protected:
	Vec2 m_target_pos;
private:
	//イカのコントロールクラス
	std::unique_ptr<IkaController> m_controller;

	//イカ状態のFSM
	std::unique_ptr<IkaStateMachine> m_ika_fsm;
	
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

	//Charによる初期パラメータ保存
	double m_init_mass;
	double m_init_max_speed;
	double m_init_max_force;
	double m_init_max_turn_rate;
	double m_init_friction;

	//画像データ
	Texture m_tex_n;
	Texture m_tex_c;
	Texture m_tex_s;
	Texture m_tex_a;

	//描画角度
	double m_angle;

	static int m_next_valid_id;

	//------------------GAME内で利用するパラメータ
	double m_init_hp;
	double m_hp;
	double m_init_special_gauge;
	double m_special_gauge;

	//paintの半径の倍率
	double m_init_paint_scale;
	double m_paint_scale;

	//hpの自動回復量
	double m_hp_regene_rate;
	double m_init_hp_regene_rate;

	//special gauge のたまりやすさ
	double m_init_gauge_rate;
	double m_gauge_rate;

	//コリジョン判定
	double m_init_mask_radius;

	//コリジョンマスクの高さ
	double m_init_mask_height;

	//スペシャルゲージのMAX値
	static double m_max_special_gauge;

	//泳ぎ状態から跳ねる高さ
	double m_swim_jump;
	double m_init_swim_jump;
};

int Ika::m_next_valid_id = 1;
double Ika::m_max_special_gauge= 100.0;

#include"IkaController\IkaController.h"
#include"IkaStateMachine.cpp"
