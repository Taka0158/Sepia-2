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
	//�\�����閼�O
	String m_name;
};

class GoToTitleCommand :public SceneCommand
{
public:
	GoToTitleCommand() { m_name = L"�^�C�g���ւ��ǂ�"; }
	void execute(Scene*)override;
};

class GoToOptionCommand :public SceneCommand
{
public:
	GoToOptionCommand() { m_name = L"�I�v�V����"; }
	void execute(Scene*)override;
};

class GoToSinglePlayCommand :public SceneCommand
{
public:
	GoToSinglePlayCommand() { m_name = L"�ЂƂ�ł�����"; }
	void execute(Scene*)override;
};

class GoToDoublePlayCommand :public SceneCommand
{
public:
	GoToDoublePlayCommand() { m_name = L"�ӂ���ł�����"; }
	void execute(Scene*)override;
};

class GoToSelectCharCommand :public SceneCommand
{
public:
	GoToSelectCharCommand() { m_name = L"�L�����N�^�[���񂽂� ��"; }
	void execute(Scene*)override;
};

class GoToSelectSpecialCommand :public SceneCommand
{
public:
	GoToSelectSpecialCommand() { m_name = L"�X�y�V�������񂽂� ��"; }
	void execute(Scene*)override;
};

class GoToSelectMapCommand :public SceneCommand
{
public:
	GoToSelectMapCommand() { m_name = L"�}�b�v���񂽂� ��"; }
	void execute(Scene*)override;
};

class GoToSelectPlayModeCommand :public SceneCommand
{
public:
	GoToSelectPlayModeCommand() { m_name = L"�v���C���[�h���񂽂� ��"; }
	void execute(Scene*)override;
};

class GoToManualCommand :public SceneCommand
{
public:
	GoToManualCommand() { m_name = L"���������߂� ��"; }
	void execute(Scene*)override;
};

class GoToGameMainCommand :public SceneCommand
{
public:
	GoToGameMainCommand() { m_name = L"�Q�[�����߂� ��"; }
	void execute(Scene*)override;
};

class GoToResultCommand :public SceneCommand
{
public:
	GoToResultCommand() { m_name = L"���U���g���߂� ��"; }
	void execute(Scene*)override;
};

class ExitCommand :public SceneCommand
{
public:
	ExitCommand() { m_name = L"�����"; }
	void execute(Scene*)override;
};
