#pragma once

#define IntEnum(value) static_cast<int>(value)
#define PlusEnum(type, target, value) static_cast<type>(IntEnum(target) + value)

#include <iostream>
#include <string>
#include <queue>
#include <vector>
#include <map>
#include <filesystem>
#include <fstream>
#include <cwctype>
#include <algorithm>
#include <functional>
#include <thread>
#include <mutex>
#include <random>

#include "Singleton.h"
#include "Input.h"
#include "Camera.h"
#include "CTime.h"

#include "Texture.h"
#include "Sprite.h"

#include "ShaderManager.h"
#include "ColorShader.h"
#include "OutlineShader.h"

#include "SoundManager.h"

#include "Collider.h"
#include "Object.h"	

#include "CState.h"

#include "Bullet.h"

#include "AttackCollider.h"

#include "Range.h"
#include "Unit.h"

#include "PlayerUI.h"
#include "Player.h"
#include "PlayerState.h"

#include "EnemyUI.h"
#include "CEnemy.h"
#include "Enemy1.h"
#include "Enemy2.h"
#include "Enemy3.h"
#include "Enemy4.h"
#include "EnemyState.h"
#include "EnemyManager.h"

#include "BossUI.h"
#include "CBoss.h"
#include "Boss1.h"
#include "Boss2.h"
#include "BossState.h"

// 시스템
#include "Box.h"
#include "Item.h"
#include "CalcPage.h"

// 이펙트
#include "Effect.h"
#include "StageFont.h"
#include "AfterImage.h"
#include "Spectrum.h"
#include "SkillEffect.h"
#include "Nuclear.h"
#include "Fade.h"
#include "BossIntro.h"
#include "Mp.h"

#include "UIEffect.h"
#include "Damage.h"

// UI
#include "Font.h"

#include "Map.h"

#include "Ranking.h"

#include "LoadSprite.h"
#include "Main.h"
#include "Help.h"
#include "Option.h"

#include "Rank.h"

#include "Scene.h"
extern Scene* nowScene;
#include "MainScene.h"
#include "GameScene.h"
#include "GameScene2.h"
#include "GameScene3.h"
#include "RankingScene.h"

#include "Game.h"