#pragma once

#pragma region OBJECT TYPE
#define OBJECT_TYPE_MARIO	0

#define OBJECT_TYPE_GOOMBA	20
#define OBJECT_TYPE_KOOPAS	30

#define OBJECT_TYPE_VENUS	40

#define OBJECT_TYPE_MUSHROOM 50
#define OBJECT_TYPE_LEAF 51
#define OBJECT_TYPE_1UP 52
#define OBJECT_TYPE_COIN 53

#define OBJECT_TYPE_BREAKABLE_BRICK	600
#define OBJECT_TYPE_QUESTION_BLOCK	601

#define OBJECT_TYPE_UNBREAKABLE_BRICK	610


#define OBJECT_TYPE_PLATFORM 700
#define OBJECT_TYPE_GROUND 701
#define OBJECT_TYPE_COLOR_BOX 710
#define OBJECT_TYPE_TUBE 720


#define OBJECT_TYPE_PORTAL	1000

#define OBJECT_TYPE_BACKGROUND	8000
#define OBJECT_TYPE_TILE_BACKGROUND	8100

#define OBJECT_TYPE_SPAWN_CHECK	9999

#pragma endregion

#pragma region ENEMIES
#pragma region GOOMBA 
#define ID_ANI_GOOMBA_WALKING 200000
#define ID_ANI_GOOMBA_DIE 200100

#define ID_ANI_PARA_GOOMBA_WALKING 210000
#define ID_ANI_PARA_GOOMBA_DIE	210100
#define ID_ANI_PARA_GOOMBA_WALKING_NO_WING 210200
#define ID_ANI_PARA_GOOMBA_HOPPING 210300
#define ID_ANI_PARA_GOOMBA_FLYING 210400

#pragma endregion

#pragma region KOOPAS
#define ID_ANI_KOOPAS_WALKING 300000
#define ID_ANI_KOOPAS_FLIP_WALKING 300010
#define ID_ANI_KOOPAS_HIDE 300100
#define ID_ANI_KOOPAS_REVIVE 300200
#define ID_ANI_KOOPAS_SLIDE 300300

#define ID_ANI_GREEN_KOOPAS_WALKING 310000
#define ID_ANI_GREEN_KOOPAS_FLIP_WALKING 310010
#define ID_ANI_GREEN_KOOPAS_HIDE 310100
#define ID_ANI_GREEN_KOOPAS_REVIVE 310200
#define ID_ANI_GREEN_KOOPAS_SLIDE 310300

#define ID_ANI_WING_KOOPAS_WALKING 320000
#define ID_ANI_WING_KOOPAS_FLIP_WALKING 320010

#define ID_ANI_WING_GREEN_KOOPAS_WALKING 330000
#define ID_ANI_WING_GREEN_KOOPAS_FLIP_WALKING 330010

#pragma endregion

#pragma region PLANT

#define ID_VENUS_IDLE_RIGHT 420000
#define ID_VENUS_IDLE_LEFT 420010
#define ID_VENUS_FIRE_RIGHT 420100
#define ID_VENUS_FIRE_LEFT 420110

#define ID_VENUS_FIRE_BALL 429990

#pragma endregion

#pragma endregion

#pragma region ITEMS
#define ID_ANI_MUSHROOM 500000
#define ID_ANI_LEAF 510000
#define ID_ANI_1UP 520000

#define ID_ANI_COIN 530000
#define ID_ANI_COIN_FAST 530100

#pragma endregion

#pragma region BLOCK
#pragma region Interactable
#define ID_ANI_BREAKABLE_BRICK 600000

#define ID_ANI_QUESTION_BLOCK 601000
#define ID_ANI_QUESTION_BLOCK_HIT 601100

#pragma endregion

#pragma region Terrain
#define ID_ANI_UNBREAKABLE_BRICK 610000
#define ID_SPRITE_CLOUD_BLOCK 610100


#pragma endregion

#pragma endregion

#pragma region GROUND

#define ID_SPRITE_OVERGROUND 700000
#define ID_SPRITE_UNDERGROUND 700100
#define ID_SPRITE_DEEPERROUND 700200

#pragma endregion

#pragma region COLOR BOX
#define ID_PINK_BOX 710000
#define ID_BLUE_BOX 710100
#define ID_GREEN_BOX 710200
#define ID_WHITE_BOX 710300
#pragma endregion

#pragma region TUBE
#define ID_SPRITE_TUBE_MOUTH 720100
#define ID_SPRITE_TUBE_BODY 720200

#pragma endregion

#pragma region BACKGROUND
#define ID_SPRITE_SKY_BACKGROUND 990000
#define ID_SPRITE_CLOUD_BACKGROUND 900000
#define ID_SPRITE_BUSH_BACKGROUND_SMALL 910100
#define ID_SPRITE_BUSH_BACKGROUND_BIG 910110
#define ID_SPRITE_SMALL_GRASS_BACKGROUND 920000

#pragma endregion

#pragma region MARIO 
#define ID_ANI_MARIO_DIE 199990
#pragma region MARIO SMALL
#define ID_ANI_MARIO_SMALL_IDLE_RIGHT 100000
#define ID_ANI_MARIO_SMALL_IDLE_LEFT 100010

#define ID_ANI_MARIO_SMALL_WALK_RIGHT 100100
#define ID_ANI_MARIO_SMALL_WALK_LEFT 100110

#define ID_ANI_MARIO_SMALL_WALK_FAST_RIGHT 100200
#define ID_ANI_MARIO_SMALL_WALK_FAST_LEFT 100210

#define ID_ANI_MARIO_SMALL_RUN_RIGHT 100300
#define ID_ANI_MARIO_SMALL_RUN_LEFT 100310

#define ID_ANI_MARIO_SMALL_BRACE_RIGHT 100400
#define ID_ANI_MARIO_SMALL_BRACE_LEFT 100410

#define ID_ANI_MARIO_SMALL_JUMP_WALK_RIGHT 100500
#define ID_ANI_MARIO_SMALL_JUMP_WALK_LEFT 100510

#define ID_ANI_MARIO_SMALL_JUMP_RUN_RIGHT 100600
#define ID_ANI_MARIO_SMALL_JUMP_RUN_LEFT 100610

#define ID_ANI_MARIO_SMALL_PICK_UP_IDLE_RIGHT 101000
#define ID_ANI_MARIO_SMALL_PICK_UP_IDLE_LEFT 101010

#define ID_ANI_MARIO_SMALL_PICK_UP_WALK_RIGHT 101100
#define ID_ANI_MARIO_SMALL_PICK_UP_WALK_LEFT 101110

#define ID_ANI_MARIO_SMALL_PICK_UP_WALK_FAST_RIGHT 101200
#define ID_ANI_MARIO_SMALL_PICK_UP_WALK_FAST_LEFT 101210

#define ID_ANI_MARIO_SMALL_PICK_UP_JUMP_RIGHT 101300
#define ID_ANI_MARIO_SMALL_PICK_UP_JUMP_LEFT 101310

#define ID_ANI_MARIO_SMALL_KICK_RIGHT 101400
#define ID_ANI_MARIO_SMALL_KICK_LEFT 101410

#pragma endregion

#pragma region MARIO BIG
#define ID_ANI_MARIO_IDLE_RIGHT 110000
#define ID_ANI_MARIO_IDLE_LEFT 110010

#define ID_ANI_MARIO_WALK_RIGHT 110100
#define ID_ANI_MARIO_WALK_LEFT 110110

#define ID_ANI_MARIO_WALK_FAST_RIGHT 110200
#define ID_ANI_MARIO_WALK_FAST_LEFT 110210

#define ID_ANI_MARIO_RUN_RIGHT 110300
#define ID_ANI_MARIO_RUN_LEFT 110310

#define ID_ANI_MARIO_BRACE_RIGHT 110400
#define ID_ANI_MARIO_BRACE_LEFT 110410

#define ID_ANI_MARIO_JUMP_WALK_RIGHT 110500
#define ID_ANI_MARIO_JUMP_WALK_LEFT 110510

#define ID_ANI_MARIO_JUMP_RUN_RIGHT 110600
#define ID_ANI_MARIO_JUMP_RUN_LEFT 110610

#define ID_ANI_MARIO_SIT_RIGHT 110700
#define ID_ANI_MARIO_SIT_LEFT 110710

#define ID_ANI_MARIO_PICK_UP_IDLE_RIGHT 111000
#define ID_ANI_MARIO_PICK_UP_IDLE_LEFT 111010

#define ID_ANI_MARIO_PICK_UP_WALK_RIGHT 111100
#define ID_ANI_MARIO_PICK_UP_WALK_LEFT 111110

#define ID_ANI_MARIO_PICK_UP_WALK_FAST_RIGHT 111200
#define ID_ANI_MARIO_PICK_UP_WALK_FAST_LEFT 111210

#define ID_ANI_MARIO_PICK_UP_JUMP_RIGHT 111300
#define ID_ANI_MARIO_PICK_UP_JUMP_LEFT 111310

#define ID_ANI_MARIO_KICK_RIGHT 111400
#define ID_ANI_MARIO_KICK_LEFT 111410

#pragma endregion

#pragma region MARIO RACOON
#define ID_ANI_RACOON_MARIO_IDLE_RIGHT 120000
#define ID_ANI_RACOON_MARIO_IDLE_LEFT 120010

#define ID_ANI_RACOON_MARIO_WALK_RIGHT 120100
#define ID_ANI_RACOON_MARIO_WALK_LEFT 120110

#define ID_ANI_RACOON_MARIO_WALK_FAST_RIGHT 120200
#define ID_ANI_RACOON_MARIO_WALK_FAST_LEFT 120210

#define ID_ANI_RACOON_MARIO_RUN_RIGHT 120300
#define ID_ANI_RACOON_MARIO_RUN_LEFT 120310

#define ID_ANI_RACOON_MARIO_BRACE_RIGHT 120400
#define ID_ANI_RACOON_MARIO_BRACE_LEFT 120410

#define ID_ANI_RACOON_MARIO_JUMP_WALK_RIGHT 120500
#define ID_ANI_RACOON_MARIO_JUMP_WALK_LEFT 120510

#define ID_ANI_RACOON_MARIO_JUMP_RUN_RIGHT 120600
#define ID_ANI_RACOON_MARIO_JUMP_RUN_LEFT 120610

#define ID_ANI_RACOON_MARIO_SIT_RIGHT 120700
#define ID_ANI_RACOON_MARIO_SIT_LEFT 120710

#define ID_ANI_RACOON_MARIO_PICK_UP_IDLE_RIGHT 121000
#define ID_ANI_RACOON_MARIO_PICK_UP_IDLE_LEFT 121010

#define ID_ANI_RACOON_MARIO_PICK_UP_WALK_RIGHT 121100
#define ID_ANI_RACOON_MARIO_PICK_UP_WALK_LEFT 121110

#define ID_ANI_RACOON_MARIO_PICK_UP_WALK_FAST_RIGHT 121200
#define ID_ANI_RACOON_MARIO_PICK_UP_WALK_FAST_LEFT 121210

#define ID_ANI_RACOON_MARIO_PICK_UP_JUMP_RIGHT 121300
#define ID_ANI_RACOON_MARIO_PICK_UP_JUMP_LEFT 121310

#define ID_ANI_RACOON_MARIO_KICK_RIGHT 121400
#define ID_ANI_RACOON_MARIO_KICK_LEFT 121410

#define ID_ANI_RACOON_MARIO_WHIP_RIGHT 122000
#define ID_ANI_RACOON_MARIO_WHIP_LEFT 122010

#define ID_ANI_RACOON_MARIO_FLY_RIGHT 122100
#define ID_ANI_RACOON_MARIO_FLY_LEFT 122110

#define ID_ANI_RACOON_MARIO_BOOST_RIGHT 122200
#define ID_ANI_RACOON_MARIO_BOOST_LEFT 122210

#define ID_ANI_RACOON_MARIO_FALL_RIGHT 122300
#define ID_ANI_RACOON_MARIO_FALL_LEFT 122310
#pragma endregion


#pragma endregion 




