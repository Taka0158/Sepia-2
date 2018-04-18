#pragma once

//OBJ_MGRとEFFECT_MGRがカメラの影響を受ける

class SceneCamera :public ham::Camera2D,public Singleton<SceneCamera>,public Entity
{
	friend class Singleton<SceneCamera>;
public:		
	SceneCamera();
	~SceneCamera();

	void initialize();
	void finalize();

	void debug_draw();
	bool handle_message(const Telegram& _msg)override;

	//Objectの座標をカメラの中心にする
	void set_center(Object*,bool);
	//カメラ中心を引数にあわせる
	void set_center(Vec2,bool);

	Vec2 get_center_pos()const { return m_pos; };

	//カメラ移動に応じたマウス位置を返す
	//ただし、Scale 1　以外の場合　正常に機能しない
	static Vec2 get_mouse_pos()
	{
		Vec2 temp = Vec2(SCENE_CAMERA->getCameraArea().pos);
		return Mouse::PosF() + temp;
	}
	static Point get_mouse_posP()
	{
		Point temp = Vec2_to_Point(SCENE_CAMERA->getCameraArea().pos);
		return Mouse::Pos() + temp;
	}
private:
	bool on_message(const Telegram&);
};

SceneCamera* Singleton<SceneCamera>::instance = nullptr;


