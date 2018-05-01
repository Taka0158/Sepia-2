#include"SceneCommand.h"

void GoToTitleCommand::execute(Scene* _owner)
{
	SceneType next_scene_type = SceneType::TITLE;
	SceneSwitchType switch_type = SceneSwitchType::IKAIKA;
	SceneParam sp=SceneParam(next_scene_type,switch_type);
	MSG_DIS->dispatch_message(0.0, UID_MGR_SCENE, UID_MGR_SCENE, msg::TYPE::SCENE_MGR_SET_NEXT_SCENE, &sp);
}

void GoToOptionCommand::execute(Scene* _owner)
{
	SceneType next_scene_type = SceneType::OPTION;
	SceneSwitchType switch_type = SceneSwitchType::IKAIKA;
	SceneParam sp = SceneParam(next_scene_type, switch_type);
	MSG_DIS->dispatch_message(0.0, UID_MGR_SCENE, UID_MGR_SCENE, msg::TYPE::SCENE_MGR_SET_NEXT_SCENE, &sp);
}

void GoToSinglePlayCommand::execute(Scene* _owner)
{
	SceneType next_scene_type = SceneType::SELECTCHAR;
	SceneSwitchType switch_type = SceneSwitchType::IKAIKA;
	SceneParam sp = SceneParam(next_scene_type, switch_type);
	Setting::set_is_single_play(true);
	MSG_DIS->dispatch_message(0.0, UID_MGR_SCENE, UID_MGR_SCENE, msg::TYPE::SCENE_MGR_SET_NEXT_SCENE, &sp);
}

void GoToDoublePlayCommand::execute(Scene* _owner)
{
	SceneType next_scene_type = SceneType::SELECTCHAR;
	SceneSwitchType switch_type = SceneSwitchType::IKAIKA;
	SceneParam sp = SceneParam(next_scene_type, switch_type);
	Setting::set_is_single_play(false);
	MSG_DIS->dispatch_message(0.0, UID_MGR_SCENE, UID_MGR_SCENE, msg::TYPE::SCENE_MGR_SET_NEXT_SCENE, &sp);
}

void GoToSelectCharCommand::execute(Scene* _owner)
{
	SceneType next_scene_type = SceneType::SELECTCHAR;
	SceneSwitchType switch_type = SceneSwitchType::IKAIKA;
	SceneParam sp = SceneParam(next_scene_type, switch_type);
	MSG_DIS->dispatch_message(0.0, UID_MGR_SCENE, UID_MGR_SCENE, msg::TYPE::SCENE_MGR_SET_NEXT_SCENE, &sp);
}

void GoToSelectSpecialCommand::execute(Scene* _owner)
{
	SceneType next_scene_type = SceneType::SELECTWEAPON;
	SceneSwitchType switch_type = SceneSwitchType::IKAIKA;
	SceneParam sp = SceneParam(next_scene_type, switch_type);
	MSG_DIS->dispatch_message(0.0, UID_MGR_SCENE, UID_MGR_SCENE, msg::TYPE::SCENE_MGR_SET_NEXT_SCENE, &sp);
}

void GoToSelectMapCommand::execute(Scene* _owner)
{
	SceneType next_scene_type = SceneType::SELECTMAP;
	SceneSwitchType switch_type = SceneSwitchType::IKAIKA;
	SceneParam sp = SceneParam(next_scene_type, switch_type);
	MSG_DIS->dispatch_message(0.0, UID_MGR_SCENE, UID_MGR_SCENE, msg::TYPE::SCENE_MGR_SET_NEXT_SCENE, &sp);
}

void GoToSelectPlayModeCommand::execute(Scene* _owner)
{
	SceneType next_scene_type = SceneType::SELECTPLAYMODE;
	SceneSwitchType switch_type = SceneSwitchType::IKAIKA;
	SceneParam sp = SceneParam(next_scene_type, switch_type);
	MSG_DIS->dispatch_message(0.0, UID_MGR_SCENE, UID_MGR_SCENE, msg::TYPE::SCENE_MGR_SET_NEXT_SCENE, &sp);
}

void GoToManualCommand::execute(Scene* _owner)
{
	SceneType next_scene_type = SceneType::MANUAL;
	SceneSwitchType switch_type = SceneSwitchType::IKAIKA;
	SceneParam sp = SceneParam(next_scene_type, switch_type);
	MSG_DIS->dispatch_message(0.0, UID_MGR_SCENE, UID_MGR_SCENE, msg::TYPE::SCENE_MGR_SET_NEXT_SCENE, &sp);
}

void GoToGameMainCommand::execute(Scene* _owner)
{
	SceneType next_scene_type = SceneType::GAMEMAIN;
	SceneSwitchType switch_type = SceneSwitchType::IKAIKA;
	SceneParam sp = SceneParam(next_scene_type, switch_type);
	MSG_DIS->dispatch_message(0.0, UID_MGR_SCENE, UID_MGR_SCENE, msg::TYPE::SCENE_MGR_SET_NEXT_SCENE, &sp);
}

void GoToResultCommand::execute(Scene* _owner)
{
	SceneType next_scene_type = SceneType::RESULT;
	SceneSwitchType switch_type = SceneSwitchType::IKAIKA;
	SceneParam sp = SceneParam(next_scene_type, switch_type);
	MSG_DIS->dispatch_message(0.0, UID_MGR_SCENE, UID_MGR_SCENE, msg::TYPE::SCENE_MGR_SET_NEXT_SCENE, &sp);
}

void ExitCommand::execute(Scene* _owner)
{
	System::Exit();
}