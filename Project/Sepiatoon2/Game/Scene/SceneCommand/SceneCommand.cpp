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
	Setting::set_playmode(PlayModeType::P1_VS_COM);
	MSG_DIS->dispatch_message(0.0, UID_MGR_SCENE, UID_MGR_SCENE, msg::TYPE::SCENE_MGR_SET_NEXT_SCENE, &sp);
}

void GoToDoublePlayCommand::execute(Scene* _owner)
{
	SceneType next_scene_type = SceneType::SELECTCHAR;
	SceneSwitchType switch_type = SceneSwitchType::IKAIKA;
	SceneParam sp = SceneParam(next_scene_type, switch_type);
	Setting::set_is_single_play(false);
	Setting::set_playmode(PlayModeType::P1_COM_VS_P2_COM);
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

//---------------------------PlayModeTypeÝ’èƒRƒ}ƒ“ƒh---------------

void SetPC::execute(Scene* _owner)
{
	Setting::set_playmode(PlayModeType::P1_VS_COM);
	Setting::set_ika_1_team(TeamType::TEAM_A);
	Setting::set_ika_2_team(TeamType::TEAM_B);
	Setting::set_controller_1(ControllerType::PLAYER_1);
	Setting::set_controller_2(ControllerType::CPU);

	SceneType next_scene_type = SceneType::SELECTMAP;
	SceneSwitchType switch_type = SceneSwitchType::IKAIKA;
	SceneParam sp = SceneParam(next_scene_type, switch_type);
	MSG_DIS->dispatch_message(0.0, UID_MGR_SCENE, UID_MGR_SCENE, msg::TYPE::SCENE_MGR_SET_NEXT_SCENE, &sp);
}

void SetPCCC::execute(Scene* _owner)
{
	Setting::set_playmode(PlayModeType::P1_COM_VS_COM_COM);
	Setting::set_ika_1_team(TeamType::TEAM_A);
	Setting::set_ika_2_team(TeamType::TEAM_A);
	Setting::set_ika_3_team(TeamType::TEAM_B);
	Setting::set_ika_4_team(TeamType::TEAM_B);
	Setting::set_controller_1(ControllerType::PLAYER_1);
	Setting::set_controller_2(ControllerType::CPU);
	Setting::set_controller_3(ControllerType::CPU);
	Setting::set_controller_4(ControllerType::CPU);

	SceneType next_scene_type = SceneType::SELECTMAP;
	SceneSwitchType switch_type = SceneSwitchType::IKAIKA;
	SceneParam sp = SceneParam(next_scene_type, switch_type);
	MSG_DIS->dispatch_message(0.0, UID_MGR_SCENE, UID_MGR_SCENE, msg::TYPE::SCENE_MGR_SET_NEXT_SCENE, &sp);
}

void SetPP::execute(Scene* _owner)
{
	Setting::set_playmode(PlayModeType::P1_VS_P2);
	Setting::set_ika_1_team(TeamType::TEAM_A);
	Setting::set_ika_3_team(TeamType::TEAM_B);
	Setting::set_controller_1(ControllerType::PLAYER_1);
	Setting::set_controller_3(ControllerType::PLAYER_2);

	SceneType next_scene_type = SceneType::SELECTMAP;
	SceneSwitchType switch_type = SceneSwitchType::IKAIKA;
	SceneParam sp = SceneParam(next_scene_type, switch_type);
	MSG_DIS->dispatch_message(0.0, UID_MGR_SCENE, UID_MGR_SCENE, msg::TYPE::SCENE_MGR_SET_NEXT_SCENE, &sp);
}

void SetPCPC::execute(Scene* _owner)
{
	Setting::set_playmode(PlayModeType::P1_COM_VS_P2_COM);
	Setting::set_ika_1_team(TeamType::TEAM_A);
	Setting::set_ika_2_team(TeamType::TEAM_A);
	Setting::set_ika_3_team(TeamType::TEAM_B);
	Setting::set_ika_4_team(TeamType::TEAM_B);
	Setting::set_controller_1(ControllerType::PLAYER_1);
	Setting::set_controller_2(ControllerType::CPU);
	Setting::set_controller_3(ControllerType::PLAYER_2);
	Setting::set_controller_4(ControllerType::CPU);

	SceneType next_scene_type = SceneType::SELECTMAP;
	SceneSwitchType switch_type = SceneSwitchType::IKAIKA;
	SceneParam sp = SceneParam(next_scene_type, switch_type);
	MSG_DIS->dispatch_message(0.0, UID_MGR_SCENE, UID_MGR_SCENE, msg::TYPE::SCENE_MGR_SET_NEXT_SCENE, &sp);
}

void SetPPCC::execute(Scene* _owner)
{
	Setting::set_playmode(PlayModeType::P1_P2_VS_COM_COM);
	Setting::set_ika_1_team(TeamType::TEAM_A);
	Setting::set_ika_3_team(TeamType::TEAM_A);
	Setting::set_ika_2_team(TeamType::TEAM_B);
	Setting::set_ika_4_team(TeamType::TEAM_B);
	Setting::set_controller_1(ControllerType::PLAYER_1);
	Setting::set_controller_3(ControllerType::PLAYER_2);
	Setting::set_controller_2(ControllerType::CPU);
	Setting::set_controller_4(ControllerType::CPU);

	SceneType next_scene_type = SceneType::SELECTMAP;
	SceneSwitchType switch_type = SceneSwitchType::IKAIKA;
	SceneParam sp = SceneParam(next_scene_type, switch_type);
	MSG_DIS->dispatch_message(0.0, UID_MGR_SCENE, UID_MGR_SCENE, msg::TYPE::SCENE_MGR_SET_NEXT_SCENE, &sp);
}


void SetMapSimple::execute(Scene* _owner)
{
	Setting::set_map(MapType::SIMPLE);

	SceneType next_scene_type = SceneType::MANUAL;
	SceneSwitchType switch_type = SceneSwitchType::IKAIKA;
	SceneParam sp = SceneParam(next_scene_type, switch_type);
	MSG_DIS->dispatch_message(0.0, UID_MGR_SCENE, UID_MGR_SCENE, msg::TYPE::SCENE_MGR_SET_NEXT_SCENE, &sp);
}
void SetMapSimpleBig::execute(Scene* _owner)
{
	Setting::set_map(MapType::SIMPLE_BIG);

	SceneType next_scene_type = SceneType::MANUAL;
	SceneSwitchType switch_type = SceneSwitchType::IKAIKA;
	SceneParam sp = SceneParam(next_scene_type, switch_type);
	MSG_DIS->dispatch_message(0.0, UID_MGR_SCENE, UID_MGR_SCENE, msg::TYPE::SCENE_MGR_SET_NEXT_SCENE, &sp);
}
void SetMapClassic::execute(Scene* _owner)
{
	Setting::set_map(MapType::CLASSIC);

	SceneType next_scene_type = SceneType::MANUAL;
	SceneSwitchType switch_type = SceneSwitchType::IKAIKA;
	SceneParam sp = SceneParam(next_scene_type, switch_type);
	MSG_DIS->dispatch_message(0.0, UID_MGR_SCENE, UID_MGR_SCENE, msg::TYPE::SCENE_MGR_SET_NEXT_SCENE, &sp);
}