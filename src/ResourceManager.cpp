#include "ResourceManager.h"

ResourceManager* ResourceManager::m_Instance = nullptr;

ResourceManager::ResourceManager()
{
	if (!m_Instance)
		m_Instance = this;
}

ResourceManager::~ResourceManager()
{
}

bool ResourceManager::loadResources()
{
	//Load sprites
	m_SpritesMap.emplace(ECAVERN_SPRITES::BACKGROUND_0, LoadTexture(ASSETS_PATH"images/bg0.png"));
	m_SpritesMap.emplace(ECAVERN_SPRITES::BACKGROUND_1, LoadTexture(ASSETS_PATH"images/bg1.png"));
	m_SpritesMap.emplace(ECAVERN_SPRITES::BACKGROUND_2, LoadTexture(ASSETS_PATH"images/bg2.png"));
	m_SpritesMap.emplace(ECAVERN_SPRITES::BACKGROUND_3, LoadTexture(ASSETS_PATH"images/bg3.png"));
	m_SpritesMap.emplace(ECAVERN_SPRITES::BLOCK_0, LoadTexture(ASSETS_PATH"images/block0.png"));
	m_SpritesMap.emplace(ECAVERN_SPRITES::BLOCK_1, LoadTexture(ASSETS_PATH"images/block1.png"));
	m_SpritesMap.emplace(ECAVERN_SPRITES::BLOCK_2, LoadTexture(ASSETS_PATH"images/block2.png"));
	m_SpritesMap.emplace(ECAVERN_SPRITES::BLOCK_3, LoadTexture(ASSETS_PATH"images/block3.png"));
	m_SpritesMap.emplace(ECAVERN_SPRITES::BLOW_0, LoadTexture(ASSETS_PATH"images/blow0.png"));
	m_SpritesMap.emplace(ECAVERN_SPRITES::BLOW_1, LoadTexture(ASSETS_PATH"images/blow1.png"));
	m_SpritesMap.emplace(ECAVERN_SPRITES::BOLT_00, LoadTexture(ASSETS_PATH"images/bolt00.png"));
	m_SpritesMap.emplace(ECAVERN_SPRITES::BOLT_01, LoadTexture(ASSETS_PATH"images/bolt01.png"));
	m_SpritesMap.emplace(ECAVERN_SPRITES::BOLT_10, LoadTexture(ASSETS_PATH"images/bolt10.png"));
	m_SpritesMap.emplace(ECAVERN_SPRITES::BOLT_11, LoadTexture(ASSETS_PATH"images/bolt11.png"));
	m_SpritesMap.emplace(ECAVERN_SPRITES::FALL_0, LoadTexture(ASSETS_PATH"images/fall0.png"));
	m_SpritesMap.emplace(ECAVERN_SPRITES::FALL_1, LoadTexture(ASSETS_PATH"images/fall1.png"));
	m_SpritesMap.emplace(ECAVERN_SPRITES::FONT_48, LoadTexture(ASSETS_PATH"images/font048.png"));
	m_SpritesMap.emplace(ECAVERN_SPRITES::FONT_49, LoadTexture(ASSETS_PATH"images/font049.png"));
	m_SpritesMap.emplace(ECAVERN_SPRITES::FONT_50, LoadTexture(ASSETS_PATH"images/font050.png"));
	m_SpritesMap.emplace(ECAVERN_SPRITES::FONT_51, LoadTexture(ASSETS_PATH"images/font051.png"));
	m_SpritesMap.emplace(ECAVERN_SPRITES::FONT_52, LoadTexture(ASSETS_PATH"images/font052.png"));
	m_SpritesMap.emplace(ECAVERN_SPRITES::FONT_53, LoadTexture(ASSETS_PATH"images/font053.png"));
	m_SpritesMap.emplace(ECAVERN_SPRITES::FONT_54, LoadTexture(ASSETS_PATH"images/font054.png"));
	m_SpritesMap.emplace(ECAVERN_SPRITES::FONT_55, LoadTexture(ASSETS_PATH"images/font055.png"));
	m_SpritesMap.emplace(ECAVERN_SPRITES::FONT_56, LoadTexture(ASSETS_PATH"images/font056.png"));
	m_SpritesMap.emplace(ECAVERN_SPRITES::FONT_57, LoadTexture(ASSETS_PATH"images/font057.png"));
	m_SpritesMap.emplace(ECAVERN_SPRITES::FONT_65, LoadTexture(ASSETS_PATH"images/font065.png"));
	m_SpritesMap.emplace(ECAVERN_SPRITES::FONT_66, LoadTexture(ASSETS_PATH"images/font066.png"));
	m_SpritesMap.emplace(ECAVERN_SPRITES::FONT_67, LoadTexture(ASSETS_PATH"images/font067.png"));
	m_SpritesMap.emplace(ECAVERN_SPRITES::FONT_68, LoadTexture(ASSETS_PATH"images/font068.png"));
	m_SpritesMap.emplace(ECAVERN_SPRITES::FONT_69, LoadTexture(ASSETS_PATH"images/font069.png"));
	m_SpritesMap.emplace(ECAVERN_SPRITES::FONT_70, LoadTexture(ASSETS_PATH"images/font070.png"));
	m_SpritesMap.emplace(ECAVERN_SPRITES::FONT_71, LoadTexture(ASSETS_PATH"images/font071.png"));
	m_SpritesMap.emplace(ECAVERN_SPRITES::FONT_72, LoadTexture(ASSETS_PATH"images/font072.png"));
	m_SpritesMap.emplace(ECAVERN_SPRITES::FONT_73, LoadTexture(ASSETS_PATH"images/font073.png"));
	m_SpritesMap.emplace(ECAVERN_SPRITES::FONT_74, LoadTexture(ASSETS_PATH"images/font074.png"));
	m_SpritesMap.emplace(ECAVERN_SPRITES::FONT_75, LoadTexture(ASSETS_PATH"images/font075.png"));
	m_SpritesMap.emplace(ECAVERN_SPRITES::FONT_76, LoadTexture(ASSETS_PATH"images/font076.png"));
	m_SpritesMap.emplace(ECAVERN_SPRITES::FONT_77, LoadTexture(ASSETS_PATH"images/font077.png"));
	m_SpritesMap.emplace(ECAVERN_SPRITES::FONT_78, LoadTexture(ASSETS_PATH"images/font078.png"));
	m_SpritesMap.emplace(ECAVERN_SPRITES::FONT_79, LoadTexture(ASSETS_PATH"images/font079.png"));
	m_SpritesMap.emplace(ECAVERN_SPRITES::FONT_80, LoadTexture(ASSETS_PATH"images/font080.png"));
	m_SpritesMap.emplace(ECAVERN_SPRITES::FONT_81, LoadTexture(ASSETS_PATH"images/font081.png"));
	m_SpritesMap.emplace(ECAVERN_SPRITES::FONT_82, LoadTexture(ASSETS_PATH"images/font082.png"));
	m_SpritesMap.emplace(ECAVERN_SPRITES::FONT_83, LoadTexture(ASSETS_PATH"images/font083.png"));
	m_SpritesMap.emplace(ECAVERN_SPRITES::FONT_84, LoadTexture(ASSETS_PATH"images/font084.png"));
	m_SpritesMap.emplace(ECAVERN_SPRITES::FONT_85, LoadTexture(ASSETS_PATH"images/font085.png"));
	m_SpritesMap.emplace(ECAVERN_SPRITES::FONT_86, LoadTexture(ASSETS_PATH"images/font086.png"));
	m_SpritesMap.emplace(ECAVERN_SPRITES::FONT_87, LoadTexture(ASSETS_PATH"images/font087.png"));
	m_SpritesMap.emplace(ECAVERN_SPRITES::FONT_88, LoadTexture(ASSETS_PATH"images/font088.png"));
	m_SpritesMap.emplace(ECAVERN_SPRITES::FONT_89, LoadTexture(ASSETS_PATH"images/font089.png"));
	m_SpritesMap.emplace(ECAVERN_SPRITES::FONT_90, LoadTexture(ASSETS_PATH"images/font090.png"));
	m_SpritesMap.emplace(ECAVERN_SPRITES::FRUIT_00, LoadTexture(ASSETS_PATH"images/fruit00.png"));
	m_SpritesMap.emplace(ECAVERN_SPRITES::FRUIT_01, LoadTexture(ASSETS_PATH"images/fruit01.png"));
	m_SpritesMap.emplace(ECAVERN_SPRITES::FRUIT_02, LoadTexture(ASSETS_PATH"images/fruit02.png"));
	m_SpritesMap.emplace(ECAVERN_SPRITES::FRUIT_10, LoadTexture(ASSETS_PATH"images/fruit10.png"));
	m_SpritesMap.emplace(ECAVERN_SPRITES::FRUIT_11, LoadTexture(ASSETS_PATH"images/fruit11.png"));
	m_SpritesMap.emplace(ECAVERN_SPRITES::FRUIT_12, LoadTexture(ASSETS_PATH"images/fruit12.png"));
	m_SpritesMap.emplace(ECAVERN_SPRITES::FRUIT_20, LoadTexture(ASSETS_PATH"images/fruit20.png"));
	m_SpritesMap.emplace(ECAVERN_SPRITES::FRUIT_21, LoadTexture(ASSETS_PATH"images/fruit21.png"));
	m_SpritesMap.emplace(ECAVERN_SPRITES::FRUIT_22, LoadTexture(ASSETS_PATH"images/fruit22.png"));
	m_SpritesMap.emplace(ECAVERN_SPRITES::FRUIT_30, LoadTexture(ASSETS_PATH"images/fruit30.png"));
	m_SpritesMap.emplace(ECAVERN_SPRITES::FRUIT_31, LoadTexture(ASSETS_PATH"images/fruit31.png"));
	m_SpritesMap.emplace(ECAVERN_SPRITES::FRUIT_32, LoadTexture(ASSETS_PATH"images/fruit32.png"));
	m_SpritesMap.emplace(ECAVERN_SPRITES::FRUIT_40, LoadTexture(ASSETS_PATH"images/fruit40.png"));
	m_SpritesMap.emplace(ECAVERN_SPRITES::FRUIT_41, LoadTexture(ASSETS_PATH"images/fruit41.png"));
	m_SpritesMap.emplace(ECAVERN_SPRITES::FRUIT_42, LoadTexture(ASSETS_PATH"images/fruit42.png"));
	m_SpritesMap.emplace(ECAVERN_SPRITES::JUMP_0, LoadTexture(ASSETS_PATH"images/jump0.png"));
	m_SpritesMap.emplace(ECAVERN_SPRITES::JUMP_1, LoadTexture(ASSETS_PATH"images/jump1.png"));
	m_SpritesMap.emplace(ECAVERN_SPRITES::LIFE, LoadTexture(ASSETS_PATH"images/life.png"));
	m_SpritesMap.emplace(ECAVERN_SPRITES::ORB_0, LoadTexture(ASSETS_PATH"images/orb0.png"));
	m_SpritesMap.emplace(ECAVERN_SPRITES::ORB_1, LoadTexture(ASSETS_PATH"images/orb1.png"));
	m_SpritesMap.emplace(ECAVERN_SPRITES::ORB_2, LoadTexture(ASSETS_PATH"images/orb2.png"));
	m_SpritesMap.emplace(ECAVERN_SPRITES::ORB_3, LoadTexture(ASSETS_PATH"images/orb3.png"));
	m_SpritesMap.emplace(ECAVERN_SPRITES::ORB_4, LoadTexture(ASSETS_PATH"images/orb4.png"));
	m_SpritesMap.emplace(ECAVERN_SPRITES::ORB_5, LoadTexture(ASSETS_PATH"images/orb5.png"));
	m_SpritesMap.emplace(ECAVERN_SPRITES::ORB_6, LoadTexture(ASSETS_PATH"images/orb6.png"));
	m_SpritesMap.emplace(ECAVERN_SPRITES::OVER, LoadTexture(ASSETS_PATH"images/over.png"));
	m_SpritesMap.emplace(ECAVERN_SPRITES::PLUS, LoadTexture(ASSETS_PATH"images/plus.png"));
	m_SpritesMap.emplace(ECAVERN_SPRITES::POP_0, LoadTexture(ASSETS_PATH"images/pop00.png"));
	m_SpritesMap.emplace(ECAVERN_SPRITES::POP_1, LoadTexture(ASSETS_PATH"images/pop01.png"));
	m_SpritesMap.emplace(ECAVERN_SPRITES::POP_2, LoadTexture(ASSETS_PATH"images/pop02.png"));
	m_SpritesMap.emplace(ECAVERN_SPRITES::POP_3, LoadTexture(ASSETS_PATH"images/pop03.png"));
	m_SpritesMap.emplace(ECAVERN_SPRITES::POP_4, LoadTexture(ASSETS_PATH"images/pop04.png"));
	m_SpritesMap.emplace(ECAVERN_SPRITES::POP_5, LoadTexture(ASSETS_PATH"images/pop05.png"));
	m_SpritesMap.emplace(ECAVERN_SPRITES::POP_10, LoadTexture(ASSETS_PATH"images/pop10.png"));
	m_SpritesMap.emplace(ECAVERN_SPRITES::POP_11, LoadTexture(ASSETS_PATH"images/pop11.png"));
	m_SpritesMap.emplace(ECAVERN_SPRITES::POP_12, LoadTexture(ASSETS_PATH"images/pop12.png"));
	m_SpritesMap.emplace(ECAVERN_SPRITES::POP_13, LoadTexture(ASSETS_PATH"images/pop13.png"));
	m_SpritesMap.emplace(ECAVERN_SPRITES::POP_14, LoadTexture(ASSETS_PATH"images/pop14.png"));
	m_SpritesMap.emplace(ECAVERN_SPRITES::RECOIL_0, LoadTexture(ASSETS_PATH"images/recoil0.png"));
	m_SpritesMap.emplace(ECAVERN_SPRITES::RECOIL_1, LoadTexture(ASSETS_PATH"images/recoil1.png"));
	m_SpritesMap.emplace(ECAVERN_SPRITES::ROBOT_001, LoadTexture(ASSETS_PATH"images/robot001.png"));
	m_SpritesMap.emplace(ECAVERN_SPRITES::ROBOT_002, LoadTexture(ASSETS_PATH"images/robot002.png"));
	m_SpritesMap.emplace(ECAVERN_SPRITES::ROBOT_003, LoadTexture(ASSETS_PATH"images/robot003.png"));
	m_SpritesMap.emplace(ECAVERN_SPRITES::ROBOT_004, LoadTexture(ASSETS_PATH"images/robot004.png"));
	m_SpritesMap.emplace(ECAVERN_SPRITES::ROBOT_005, LoadTexture(ASSETS_PATH"images/robot005.png"));
	m_SpritesMap.emplace(ECAVERN_SPRITES::ROBOT_006, LoadTexture(ASSETS_PATH"images/robot006.png"));
	m_SpritesMap.emplace(ECAVERN_SPRITES::ROBOT_007, LoadTexture(ASSETS_PATH"images/robot007.png"));
	m_SpritesMap.emplace(ECAVERN_SPRITES::ROBOT_010, LoadTexture(ASSETS_PATH"images/robot010.png"));
	m_SpritesMap.emplace(ECAVERN_SPRITES::ROBOT_011, LoadTexture(ASSETS_PATH"images/robot011.png"));
	m_SpritesMap.emplace(ECAVERN_SPRITES::ROBOT_012, LoadTexture(ASSETS_PATH"images/robot012.png"));
	m_SpritesMap.emplace(ECAVERN_SPRITES::ROBOT_013, LoadTexture(ASSETS_PATH"images/robot013.png"));
	m_SpritesMap.emplace(ECAVERN_SPRITES::ROBOT_014, LoadTexture(ASSETS_PATH"images/robot014.png"));
	m_SpritesMap.emplace(ECAVERN_SPRITES::ROBOT_015, LoadTexture(ASSETS_PATH"images/robot015.png"));
	m_SpritesMap.emplace(ECAVERN_SPRITES::ROBOT_016, LoadTexture(ASSETS_PATH"images/robot016.png"));
	m_SpritesMap.emplace(ECAVERN_SPRITES::ROBOT_017, LoadTexture(ASSETS_PATH"images/robot017.png"));
	m_SpritesMap.emplace(ECAVERN_SPRITES::ROBOT_101, LoadTexture(ASSETS_PATH"images/robot101.png"));
	m_SpritesMap.emplace(ECAVERN_SPRITES::ROBOT_102, LoadTexture(ASSETS_PATH"images/robot102.png"));
	m_SpritesMap.emplace(ECAVERN_SPRITES::ROBOT_103, LoadTexture(ASSETS_PATH"images/robot103.png"));
	m_SpritesMap.emplace(ECAVERN_SPRITES::ROBOT_104, LoadTexture(ASSETS_PATH"images/robot104.png"));
	m_SpritesMap.emplace(ECAVERN_SPRITES::ROBOT_105, LoadTexture(ASSETS_PATH"images/robot105.png"));
	m_SpritesMap.emplace(ECAVERN_SPRITES::ROBOT_106, LoadTexture(ASSETS_PATH"images/robot106.png"));
	m_SpritesMap.emplace(ECAVERN_SPRITES::ROBOT_107, LoadTexture(ASSETS_PATH"images/robot107.png"));
	m_SpritesMap.emplace(ECAVERN_SPRITES::ROBOT_110, LoadTexture(ASSETS_PATH"images/robot110.png"));
	m_SpritesMap.emplace(ECAVERN_SPRITES::ROBOT_111, LoadTexture(ASSETS_PATH"images/robot111.png"));
	m_SpritesMap.emplace(ECAVERN_SPRITES::ROBOT_112, LoadTexture(ASSETS_PATH"images/robot112.png"));
	m_SpritesMap.emplace(ECAVERN_SPRITES::ROBOT_113, LoadTexture(ASSETS_PATH"images/robot113.png"));
	m_SpritesMap.emplace(ECAVERN_SPRITES::ROBOT_114, LoadTexture(ASSETS_PATH"images/robot114.png"));
	m_SpritesMap.emplace(ECAVERN_SPRITES::ROBOT_115, LoadTexture(ASSETS_PATH"images/robot115.png"));
	m_SpritesMap.emplace(ECAVERN_SPRITES::ROBOT_116, LoadTexture(ASSETS_PATH"images/robot116.png"));
	m_SpritesMap.emplace(ECAVERN_SPRITES::ROBOT_117, LoadTexture(ASSETS_PATH"images/robot117.png"));
	m_SpritesMap.emplace(ECAVERN_SPRITES::RUN_00, LoadTexture(ASSETS_PATH"images/run00.png"));
	m_SpritesMap.emplace(ECAVERN_SPRITES::RUN_01, LoadTexture(ASSETS_PATH"images/run01.png"));
	m_SpritesMap.emplace(ECAVERN_SPRITES::RUN_02, LoadTexture(ASSETS_PATH"images/run02.png"));
	m_SpritesMap.emplace(ECAVERN_SPRITES::RUN_03, LoadTexture(ASSETS_PATH"images/run03.png"));
	m_SpritesMap.emplace(ECAVERN_SPRITES::RUN_10, LoadTexture(ASSETS_PATH"images/run10.png"));
	m_SpritesMap.emplace(ECAVERN_SPRITES::RUN_11, LoadTexture(ASSETS_PATH"images/run11.png"));
	m_SpritesMap.emplace(ECAVERN_SPRITES::RUN_12, LoadTexture(ASSETS_PATH"images/run12.png"));
	m_SpritesMap.emplace(ECAVERN_SPRITES::RUN_13, LoadTexture(ASSETS_PATH"images/run13.png"));
	m_SpritesMap.emplace(ECAVERN_SPRITES::SPACE_0, LoadTexture(ASSETS_PATH"images/space0.png"));
	m_SpritesMap.emplace(ECAVERN_SPRITES::SPACE_1, LoadTexture(ASSETS_PATH"images/space1.png"));
	m_SpritesMap.emplace(ECAVERN_SPRITES::SPACE_2, LoadTexture(ASSETS_PATH"images/space2.png"));
	m_SpritesMap.emplace(ECAVERN_SPRITES::SPACE_3, LoadTexture(ASSETS_PATH"images/space3.png"));
	m_SpritesMap.emplace(ECAVERN_SPRITES::SPACE_4, LoadTexture(ASSETS_PATH"images/space4.png"));
	m_SpritesMap.emplace(ECAVERN_SPRITES::SPACE_5, LoadTexture(ASSETS_PATH"images/space5.png"));
	m_SpritesMap.emplace(ECAVERN_SPRITES::SPACE_6, LoadTexture(ASSETS_PATH"images/space6.png"));
	m_SpritesMap.emplace(ECAVERN_SPRITES::SPACE_7, LoadTexture(ASSETS_PATH"images/space7.png"));
	m_SpritesMap.emplace(ECAVERN_SPRITES::SPACE_8, LoadTexture(ASSETS_PATH"images/space8.png"));
	m_SpritesMap.emplace(ECAVERN_SPRITES::SPACE_9, LoadTexture(ASSETS_PATH"images/space9.png"));
	m_SpritesMap.emplace(ECAVERN_SPRITES::STAND_0, LoadTexture(ASSETS_PATH"images/stand0.png"));
	m_SpritesMap.emplace(ECAVERN_SPRITES::STAND_1, LoadTexture(ASSETS_PATH"images/stand1.png"));
	m_SpritesMap.emplace(ECAVERN_SPRITES::STILL, LoadTexture(ASSETS_PATH"images/still.png"));
	m_SpritesMap.emplace(ECAVERN_SPRITES::TITLE, LoadTexture(ASSETS_PATH"images/title.png"));
	m_SpritesMap.emplace(ECAVERN_SPRITES::TRAP_00, LoadTexture(ASSETS_PATH"images/trap00.png"));
	m_SpritesMap.emplace(ECAVERN_SPRITES::TRAP_01, LoadTexture(ASSETS_PATH"images/trap01.png"));
	m_SpritesMap.emplace(ECAVERN_SPRITES::TRAP_02, LoadTexture(ASSETS_PATH"images/trap02.png"));
	m_SpritesMap.emplace(ECAVERN_SPRITES::TRAP_03, LoadTexture(ASSETS_PATH"images/trap03.png"));
	m_SpritesMap.emplace(ECAVERN_SPRITES::TRAP_04, LoadTexture(ASSETS_PATH"images/trap04.png"));
	m_SpritesMap.emplace(ECAVERN_SPRITES::TRAP_05, LoadTexture(ASSETS_PATH"images/trap05.png"));
	m_SpritesMap.emplace(ECAVERN_SPRITES::TRAP_06, LoadTexture(ASSETS_PATH"images/trap06.png"));
	m_SpritesMap.emplace(ECAVERN_SPRITES::TRAP_07, LoadTexture(ASSETS_PATH"images/trap07.png"));
	m_SpritesMap.emplace(ECAVERN_SPRITES::TRAP_10, LoadTexture(ASSETS_PATH"images/trap10.png"));
	m_SpritesMap.emplace(ECAVERN_SPRITES::TRAP_11, LoadTexture(ASSETS_PATH"images/trap11.png"));
	m_SpritesMap.emplace(ECAVERN_SPRITES::TRAP_12, LoadTexture(ASSETS_PATH"images/trap12.png"));
	m_SpritesMap.emplace(ECAVERN_SPRITES::TRAP_13, LoadTexture(ASSETS_PATH"images/trap13.png"));
	m_SpritesMap.emplace(ECAVERN_SPRITES::TRAP_14, LoadTexture(ASSETS_PATH"images/trap14.png"));
	m_SpritesMap.emplace(ECAVERN_SPRITES::TRAP_15, LoadTexture(ASSETS_PATH"images/trap15.png"));
	m_SpritesMap.emplace(ECAVERN_SPRITES::TRAP_16, LoadTexture(ASSETS_PATH"images/trap16.png"));
	m_SpritesMap.emplace(ECAVERN_SPRITES::TRAP_17, LoadTexture(ASSETS_PATH"images/trap17.png"));
	

	//Load Sounds
	m_SoundsMap.emplace(ECAVERN_SOUNDS::APPEAR_0, LoadSound(ASSETS_PATH"sounds/appear0.ogg"));
	m_SoundsMap.emplace(ECAVERN_SOUNDS::BLOW_0, LoadSound(ASSETS_PATH"sounds/blow0.ogg"));
	m_SoundsMap.emplace(ECAVERN_SOUNDS::BLOW_1, LoadSound(ASSETS_PATH"sounds/blow1.ogg"));
	m_SoundsMap.emplace(ECAVERN_SOUNDS::BLOW_2, LoadSound(ASSETS_PATH"sounds/blow2.ogg"));
	m_SoundsMap.emplace(ECAVERN_SOUNDS::BLOW_3, LoadSound(ASSETS_PATH"sounds/blow3.ogg"));
	m_SoundsMap.emplace(ECAVERN_SOUNDS::BONUS_0, LoadSound(ASSETS_PATH"sounds/bonus0.ogg"));
	m_SoundsMap.emplace(ECAVERN_SOUNDS::DIE_0, LoadSound(ASSETS_PATH"sounds/die0.ogg"));
	m_SoundsMap.emplace(ECAVERN_SOUNDS::JUMP_0, LoadSound(ASSETS_PATH"sounds/jump0.ogg"));
	m_SoundsMap.emplace(ECAVERN_SOUNDS::LAND_0, LoadSound(ASSETS_PATH"sounds/land0.ogg"));
	m_SoundsMap.emplace(ECAVERN_SOUNDS::LAND_1, LoadSound(ASSETS_PATH"sounds/land1.ogg"));
	m_SoundsMap.emplace(ECAVERN_SOUNDS::LAND_2, LoadSound(ASSETS_PATH"sounds/land2.ogg"));
	m_SoundsMap.emplace(ECAVERN_SOUNDS::LAND_3, LoadSound(ASSETS_PATH"sounds/land3.ogg"));
	m_SoundsMap.emplace(ECAVERN_SOUNDS::LASER_0, LoadSound(ASSETS_PATH"sounds/laser0.ogg"));
	m_SoundsMap.emplace(ECAVERN_SOUNDS::LASER_1, LoadSound(ASSETS_PATH"sounds/laser1.ogg"));
	m_SoundsMap.emplace(ECAVERN_SOUNDS::LASER_2, LoadSound(ASSETS_PATH"sounds/laser2.ogg"));
	m_SoundsMap.emplace(ECAVERN_SOUNDS::LASER_3, LoadSound(ASSETS_PATH"sounds/laser3.ogg"));
	m_SoundsMap.emplace(ECAVERN_SOUNDS::LEVEL_0, LoadSound(ASSETS_PATH"sounds/level0.ogg"));
	m_SoundsMap.emplace(ECAVERN_SOUNDS::LIFE_0, LoadSound(ASSETS_PATH"sounds/life0.ogg"));
	m_SoundsMap.emplace(ECAVERN_SOUNDS::OUCH_0, LoadSound(ASSETS_PATH"sounds/ouch0.ogg"));
	m_SoundsMap.emplace(ECAVERN_SOUNDS::OUCH_1, LoadSound(ASSETS_PATH"sounds/ouch1.ogg"));
	m_SoundsMap.emplace(ECAVERN_SOUNDS::OUCH_2, LoadSound(ASSETS_PATH"sounds/ouch2.ogg"));
	m_SoundsMap.emplace(ECAVERN_SOUNDS::OUCH_3, LoadSound(ASSETS_PATH"sounds/ouch3.ogg"));
	m_SoundsMap.emplace(ECAVERN_SOUNDS::OVER_0, LoadSound(ASSETS_PATH"sounds/over0.ogg"));
	m_SoundsMap.emplace(ECAVERN_SOUNDS::POP_0, LoadSound(ASSETS_PATH"sounds/pop0.ogg"));
	m_SoundsMap.emplace(ECAVERN_SOUNDS::POP_1, LoadSound(ASSETS_PATH"sounds/pop1.ogg"));
	m_SoundsMap.emplace(ECAVERN_SOUNDS::POP_2, LoadSound(ASSETS_PATH"sounds/pop2.ogg"));
	m_SoundsMap.emplace(ECAVERN_SOUNDS::POP_3, LoadSound(ASSETS_PATH"sounds/pop3.ogg"));
	m_SoundsMap.emplace(ECAVERN_SOUNDS::TRAP_0, LoadSound(ASSETS_PATH"sounds/trap0.ogg"));
	m_SoundsMap.emplace(ECAVERN_SOUNDS::TRAP_1, LoadSound(ASSETS_PATH"sounds/trap1.ogg"));
	m_SoundsMap.emplace(ECAVERN_SOUNDS::TRAP_2, LoadSound(ASSETS_PATH"sounds/trap2.ogg"));
	m_SoundsMap.emplace(ECAVERN_SOUNDS::TRAP_3, LoadSound(ASSETS_PATH"sounds/trap3.ogg"));
	m_SoundsMap.emplace(ECAVERN_SOUNDS::SCORE_0, LoadSound(ASSETS_PATH"sounds/score0.ogg"));
	m_SoundsMap.emplace(ECAVERN_SOUNDS::VANISH_0, LoadSound(ASSETS_PATH"sounds/vanish0.ogg"));

	//Load Music
	m_MusicMap.emplace(ECAVERN_MUSIC::THEME, LoadMusicStream(ASSETS_PATH"music/theme.ogg"));

	return true;
}

Texture2D* ResourceManager::getSprite(ECAVERN_SPRITES obj)
{
	auto& spritesMap = m_Instance->m_SpritesMap;
	auto it = spritesMap.find(obj);
	if (it == spritesMap.end()) {
		return nullptr;
	}
	return &(it->second);
}

Sound* ResourceManager::getSound(ECAVERN_SOUNDS obj)
{
	auto& soundsMap = m_Instance->m_SoundsMap;
	auto it = soundsMap.find(obj);
	if (it == soundsMap.end()) {
		return nullptr;
	}
	return &(it->second);
}

Music* ResourceManager::getMusic(ECAVERN_MUSIC obj)
{
	auto& musciMap = m_Instance->m_MusicMap;
	auto it = musciMap.find(obj);
	if (it == musciMap.end()) {
		return nullptr;
	}
	return &(it->second);
}

void ResourceManager::cleanup()
{
	auto& spritesMap = m_Instance->m_SpritesMap;
	for (auto& sprite : spritesMap)
	{
		UnloadTexture(sprite.second);
	}
	spritesMap.clear();

	auto& soundsMap = m_Instance->m_SoundsMap;
	for (auto& sound : soundsMap)
	{
		UnloadSound(sound.second);
	}
	soundsMap.clear();

	auto& musicMap = m_Instance->m_MusicMap;
	for (auto& music : musicMap)
	{
		UnloadMusicStream(music.second);
	}
	musicMap.clear();
}