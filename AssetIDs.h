#pragma once

//
// This file contains all IDs of game assets 
//

#define ID_TEX_MARIO 0

#define ID_TEX_ENEMY 10
#define ID_TEX_ENEMY_FLIP 11

#define ID_TEX_MISC 20


#define OBJECT_TYPE_MARIO	0

#define OBJECT_TYPE_GOOMBA	10
#define OBJECT_TYPE_KOOPAS	20

#define OBJECT_TYPE_PLATFORM 50
#define OBJECT_TYPE_VISUAL_PLATFORM 51

#define OBJECT_TYPE_BRICK	60
#define OBJECT_TYPE_QUESTION_BLOCK	61

#define OBJECT_TYPE_COIN 70

#define OBJECT_TYPE_MUSHROOM 80

#define OBJECT_TYPE_PORTAL	1000

#define OBJECT_TYPE_BACKGROUND	8000

#define OBJECT_TYPE_SPAWN_CHECK	9999


#pragma region MARIO 

#define ID_SPRITE_MARIO 10000
#define ID_SPRITE_MARIO_BIG (ID_SPRITE_MARIO + 1000)
#define ID_SPRITE_MARIO_BIG_IDLE (ID_SPRITE_MARIO_BIG + 100)
#define ID_SPRITE_MARIO_BIG_IDLE_LEFT (ID_SPRITE_MARIO_BIG_IDLE + 10)
#define ID_SPRITE_MARIO_BIG_IDLE_RIGHT (ID_SPRITE_MARIO_BIG_IDLE + 20)

#define ID_SPRITE_MARIO_BIG_WALKING (ID_SPRITE_MARIO_BIG + 200)
#define ID_SPRITE_MARIO_BIG_WALKING_LEFT (ID_SPRITE_MARIO_BIG_WALKING + 10)
#define ID_SPRITE_MARIO_BIG_WALKING_RIGHT (ID_SPRITE_MARIO_BIG_WALKING + 20)
#define ID_SPRITE_MARIO_BIG_RUNNING (ID_SPRITE_MARIO_BIG + 300)
#define ID_SPRITE_MARIO_BIG_RUNNING_LEFT (ID_SPRITE_MARIO_BIG_RUNNING + 10)
#define ID_SPRITE_MARIO_BIG_RUNNING_RIGHT (ID_SPRITE_MARIO_BIG_RUNNING + 20)
#define ID_SPRITE_MARIO_BIG_JUMP (ID_SPRITE_MARIO_BIG + 400)
#define ID_SPRITE_MARIO_BIG_JUMP_WALK (ID_SPRITE_MARIO_BIG_JUMP + 10)
#define ID_SPRITE_MARIO_BIG_JUMP_WALK_LEFT (ID_SPRITE_MARIO_BIG_JUMP_WALK + 2)
#define ID_SPRITE_MARIO_BIG_JUMP_WALK_RIGHT (ID_SPRITE_MARIO_BIG_JUMP_WALK + 6)
#define ID_SPRITE_MARIO_BIG_JUMP_RUN (ID_SPRITE_MARIO_BIG_JUMP + 20)
#define ID_SPRITE_MARIO_BIG_JUMP_RUN_LEFT (ID_SPRITE_MARIO_BIG_JUMP_RUN + 2)
#define ID_SPRITE_MARIO_BIG_JUMP_RUN_RIGHT (ID_SPRITE_MARIO_BIG_JUMP_RUN + 6)
#define ID_SPRITE_MARIO_BIG_SIT (ID_SPRITE_MARIO_BIG + 500)
#define ID_SPRITE_MARIO_BIG_SIT_LEFT (ID_SPRITE_MARIO_BIG_SIT + 10)
#define ID_SPRITE_MARIO_BIG_SIT_RIGHT (ID_SPRITE_MARIO_BIG_SIT + 20)
#define ID_SPRITE_MARIO_BIG_BRACE (ID_SPRITE_MARIO_BIG + 600)
#define ID_SPRITE_MARIO_BIG_BRACE_LEFT (ID_SPRITE_MARIO_BIG_BRACE + 10)
#define ID_SPRITE_MARIO_BIG_BRACE_RIGHT (ID_SPRITE_MARIO_BIG_BRACE + 20)

#define ID_SPRITE_MARIO_DIE (ID_SPRITE_MARIO + 3000)

#define ID_SPRITE_MARIO_SMALL (ID_SPRITE_MARIO + 2000)
#define ID_SPRITE_MARIO_SMALL_IDLE (ID_SPRITE_MARIO_SMALL + 100)
#define ID_SPRITE_MARIO_SMALL_IDLE_LEFT (ID_SPRITE_MARIO_SMALL_IDLE + 10)
#define ID_SPRITE_MARIO_SMALL_IDLE_RIGHT (ID_SPRITE_MARIO_SMALL_IDLE + 20)

#define ID_SPRITE_MARIO_SMALL_WALKING (ID_SPRITE_MARIO_SMALL + 200)
#define ID_SPRITE_MARIO_SMALL_WALKING_LEFT (ID_SPRITE_MARIO_SMALL_WALKING + 10)
#define ID_SPRITE_MARIO_SMALL_WALKING_RIGHT (ID_SPRITE_MARIO_SMALL_WALKING + 20)
#define ID_SPRITE_MARIO_SMALL_RUNNING (ID_SPRITE_MARIO_SMALL + 300)
#define ID_SPRITE_MARIO_SMALL_RUNNING_LEFT (ID_SPRITE_MARIO_SMALL_RUNNING + 10)
#define ID_SPRITE_MARIO_SMALL_RUNNING_RIGHT (ID_SPRITE_MARIO_SMALL_RUNNING + 20)
#define ID_SPRITE_MARIO_SMALL_JUMP (ID_SPRITE_MARIO_SMALL + 400)
#define ID_SPRITE_MARIO_SMALL_JUMP_WALK (ID_SPRITE_MARIO_SMALL_JUMP + 10)
#define ID_SPRITE_MARIO_SMALL_JUMP_WALK_LEFT (ID_SPRITE_MARIO_SMALL_JUMP_WALK + 2)
#define ID_SPRITE_MARIO_SMALL_JUMP_WALK_RIGHT (ID_SPRITE_MARIO_SMALL_JUMP_WALK + 6)
#define ID_SPRITE_MARIO_SMALL_JUMP_RUN (ID_SPRITE_MARIO_SMALL_JUMP + 20)
#define ID_SPRITE_MARIO_SMALL_JUMP_RUN_LEFT (ID_SPRITE_MARIO_SMALL_JUMP_RUN + 2)
#define ID_SPRITE_MARIO_SMALL_JUMP_RUN_RIGHT (ID_SPRITE_MARIO_SMALL_JUMP_RUN + 6)

#define ID_SPRITE_MARIO_SMALL_SIT (ID_SPRITE_MARIO_SMALL + 500)
#define ID_SPRITE_MARIO_SMALL_SIT_LEFT (ID_SPRITE_MARIO_SMALL_SIT + 10)
#define ID_SPRITE_MARIO_SMALL_SIT_RIGHT (ID_SPRITE_MARIO_SMALL_SIT + 20)

#define ID_SPRITE_MARIO_SMALL_BRACE (ID_SPRITE_MARIO_SMALL + 500)
#define ID_SPRITE_MARIO_SMALL_BRACE_LEFT (ID_SPRITE_MARIO_SMALL_BRACE + 10)
#define ID_SPRITE_MARIO_SMALL_BRACE_RIGHT (ID_SPRITE_MARIO_SMALL_BRACE + 20)

#pragma endregion 

#define ID_GOOMBA 10000
#define ID_ANI_GOOMBA_WALKING (ID_GOOMBA + 10)
#define ID_ANI_GOOMBA_DIE (ID_GOOMBA + 20)

#define ID_KOOPAS 20000
#define ID_ANI_KOOPAS_WALKING (ID_KOOPAS + 10)
#define ID_ANI_KOOPAS_FLIP_WALKING (ID_KOOPAS + 20)
#define ID_ANI_KOOPAS_HIDE (ID_KOOPAS + 30)
#define ID_ANI_KOOPAS_REVIVE (ID_KOOPAS + 40)
#define ID_ANI_KOOPAS_SLIDE (ID_KOOPAS + 50)


#define ID_SPRITE_CLOUD 50000
#define ID_SPRITE_CLOUD_BEGIN (ID_SPRITE_CLOUD+1)
#define ID_SPRITE_CLOUD_MIDDLE (ID_SPRITE_CLOUD+2)
#define ID_SPRITE_CLOUD_END (ID_SPRITE_CLOUD+3)

#define ID_SPRITE_GROUND 51000
#define ID_SPRITE_GROUND_BEGIN (ID_SPRITE_GROUND+1)
#define ID_SPRITE_GROUND_MIDDLE (ID_SPRITE_GROUND+2)
#define ID_SPRITE_GROUND_END (ID_SPRITE_GROUND+3)

#define ID_SPRITE_COLOR_BOX 52000
#define ID_SPRITE_COLOR_BOX_TOP (ID_SPRITE_COLOR_BOX + 10)
#define ID_SPRITE_COLOR_BOX_TOP_BEGIN (ID_SPRITE_COLOR_BOX_TOP + 1)
#define ID_SPRITE_COLOR_BOX_TOP_MIDDLE (ID_SPRITE_COLOR_BOX_TOP + 2)
#define ID_SPRITE_COLOR_BOX_TOP_END (ID_SPRITE_COLOR_BOX_TOP + 3)

#define ID_SPRITE_COLOR_BOX_BODY (ID_SPRITE_COLOR_BOX + 20)
#define ID_SPRITE_COLOR_BOX_BODY_BEGIN (ID_SPRITE_COLOR_BOX_BODY + 1)
#define ID_SPRITE_COLOR_BOX_BODY_MIDDLE (ID_SPRITE_COLOR_BOX_BODY + 2)
#define ID_SPRITE_COLOR_BOX_BODY_END (ID_SPRITE_COLOR_BOX_BODY + 3)

#define ID_SPRITE_COLOR_BOX_BOT (ID_SPRITE_COLOR_BOX + 30)
#define ID_SPRITE_COLOR_BOX_BOT_BEGIN (ID_SPRITE_COLOR_BOX_BOT + 1)
#define ID_SPRITE_COLOR_BOX_BOT_MIDDLE (ID_SPRITE_COLOR_BOX_BOT + 2)
#define ID_SPRITE_COLOR_BOX_BOT_END (ID_SPRITE_COLOR_BOX_BOT + 3)

#define ID_ANI_BRICK 60000

#define ID_SPRITE_QUESTION_BLOCK 61000

#define ID_SPRITE_TUBE 70000
#define ID_SPRITE_TUBE_MOUTH 70010
#define ID_SPRITE_TUBE_BODY 70020

#define ID_ANI_MUSHROOM 80000

#define ID_ANI_COIN 90000
