#pragma once

class Scene;

class SceneCommand 
{
public:
	SceneCommand() {};
	virtual ~SceneCommand() {};

	virtual void execute(Scene*) =0;

	String get_name() { return m_name; }
protected:
	//表示する名前
	String m_name;
};

class GoToTitleCommand :public SceneCommand
{
public:
	GoToTitleCommand() { m_name = L"タイトルへもどる"; }
	void execute(Scene*)override;
};

class GoToOptionCommand :public SceneCommand
{
public:
	GoToOptionCommand() { m_name = L"オプション"; }
	void execute(Scene*)override;
};

class GoToSinglePlayCommand :public SceneCommand
{
public:
	GoToSinglePlayCommand() { m_name = L"ひとりであそぶ"; }
	void execute(Scene*)override;
};

class GoToDoublePlayCommand :public SceneCommand
{
public:
	GoToDoublePlayCommand() { m_name = L"ふたりであそぶ"; }
	void execute(Scene*)override;
};

class GoToSelectCharCommand :public SceneCommand
{
public:
	GoToSelectCharCommand() { m_name = L"キャラクターせんたく へ"; }
	void execute(Scene*)override;
};

class GoToSelectSpecialCommand :public SceneCommand
{
public:
	GoToSelectSpecialCommand() { m_name = L"スペシャルせんたく へ"; }
	void execute(Scene*)override;
};

class GoToSelectMapCommand :public SceneCommand
{
public:
	GoToSelectMapCommand() { m_name = L"マップせんたく へ"; }
	void execute(Scene*)override;
};

class GoToSelectPlayModeCommand :public SceneCommand
{
public:
	GoToSelectPlayModeCommand() { m_name = L"プレイモードせんたく へ"; }
	void execute(Scene*)override;
};

class GoToManualCommand :public SceneCommand
{
public:
	GoToManualCommand() { m_name = L"そうさせつめい へ"; }
	void execute(Scene*)override;
};

class GoToGameMainCommand :public SceneCommand
{
public:
	GoToGameMainCommand() { m_name = L"ゲームがめん へ"; }
	void execute(Scene*)override;
};

class GoToResultCommand :public SceneCommand
{
public:
	GoToResultCommand() { m_name = L"リザルトがめん へ"; }
	void execute(Scene*)override;
};

class ExitCommand :public SceneCommand
{
public:
	ExitCommand() { m_name = L"おわる"; }
	void execute(Scene*)override;
};

