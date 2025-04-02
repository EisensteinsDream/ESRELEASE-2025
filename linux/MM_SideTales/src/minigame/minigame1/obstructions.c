#include "minigame/minigame1/function.h"

static size_t p_car0Tex = 0;
static size_t p_car1Tex = 0;
static size_t p_car2Tex = 0;
static size_t p_car3Tex = 0;
static size_t p_car4Tex = 0;
static size_t p_car5Tex = 0;
static size_t p_car6Tex = 0;
static size_t p_car7Tex = 0;
static size_t p_car8Tex = 0;
static size_t p_car9Tex = 0;
static size_t p_car10Tex = 0;
static size_t p_car11Tex = 0;
static size_t p_car12Tex = 0;
static size_t p_car13Tex = 0;
static size_t p_car14Tex = 0;
static size_t p_car15Tex = 0;

static size_t p_bikeTex = 0;
static size_t p_bikerTex = 0;

static size_t p_cactusTex = 0;
static size_t p_tumbleweedTex = 0;

static size_t p_bagTex = 0;
static size_t p_bag2Tex = 0;
static size_t p_barrelTex = 0;
static size_t p_bricksTex = 0;
static size_t p_crateTex = 0;
static size_t p_pipesTex = 0;

static PLEX_SPRITE* p_car0 = NULL;
static PLEX_SPRITE* p_car1 = NULL;
static PLEX_SPRITE* p_car2 = NULL;
static PLEX_SPRITE* p_car3 = NULL;
static PLEX_SPRITE* p_car4 = NULL;
static PLEX_SPRITE* p_car5 = NULL;
static PLEX_SPRITE* p_car6 = NULL;
static PLEX_SPRITE* p_car7 = NULL;
static PLEX_SPRITE* p_car8 = NULL;
static PLEX_SPRITE* p_car9 = NULL;
static PLEX_SPRITE* p_car10 = NULL;
static PLEX_SPRITE* p_car11 = NULL;
static PLEX_SPRITE* p_car12 = NULL;
static PLEX_SPRITE* p_car13 = NULL;
static PLEX_SPRITE* p_car14 = NULL;
static PLEX_SPRITE* p_car15 = NULL;

static PLEX_SPRITE* p_bike = NULL;
static PLEX_SPRITE* p_biker = NULL;

static PLEX_SPRITE* p_cactus = NULL;
static PLEX_SPRITE* p_tumbleweed = NULL;
static PLEX_SPRITE* p_bag = NULL;
static PLEX_SPRITE* p_bag2 = NULL;
static PLEX_SPRITE* p_barrel = NULL;
static PLEX_SPRITE* p_bricks = NULL;
static PLEX_SPRITE* p_crate = NULL;
static PLEX_SPRITE* p_pipes = NULL;

static void p_createCar0Sprite(const uint64_t time)
{
	PLEX_ANIMATION_PLATE car0Plate;

	PLEX_ANIMATION* car0Down = NULL;
	PLEX_ANIMATION* car0Up = NULL;
	PLEX_ANIMATION* car0Crash = NULL;

	p_car0Tex = PLEX_loadTextureFromFileOrHeaderless(512, 192, 255, 255, 255, 255, 0, MMS1_FILEPATH_TEX_CAR00, MMS1_FILEPATH_HEADERLESS_CAR00);

	car0Plate = PLEX_createAnimationPlate(0.25, 0.33333333, p_car0Tex);

	p_car0 = PLEX_genSprite(&car0Plate);

	PLEX_addAnimation(p_car0, 1000, PLEX_getGameTime());

	car0Down = PLEX_getAnimation(0, p_car0);

	PLEX_addAnimationFrame(0, car0Down);
	PLEX_addAnimationFrame(1, car0Down);
	PLEX_addAnimationFrame(2, car0Down);
	PLEX_addAnimationFrame(3, car0Down);

	PLEX_addAnimation(p_car0, 1000, PLEX_getGameTime());

	car0Up = PLEX_getAnimation(1, p_car0);

	PLEX_addAnimationFrame(4, car0Up);
	PLEX_addAnimationFrame(5, car0Up);
	PLEX_addAnimationFrame(6, car0Up);
	PLEX_addAnimationFrame(7, car0Up);

	PLEX_addAnimation(p_car0, 1000, PLEX_getGameTime());

	car0Crash = PLEX_getAnimation(2, p_car0);

	PLEX_addAnimationFrame(8, car0Crash);
	PLEX_addAnimationFrame(9, car0Crash);
	PLEX_addAnimationFrame(10, car0Crash);
	PLEX_addAnimationFrame(11, car0Crash);

	PLEX_startSprite(time, p_car0);
}

static void p_createCar1Sprite(const uint64_t time)
{
	PLEX_ANIMATION_PLATE car1Plate;

	PLEX_ANIMATION* car1Down = NULL;
	PLEX_ANIMATION* car1Up = NULL;
	PLEX_ANIMATION* car1Crash = NULL;

	p_car1Tex = PLEX_loadTextureFromFileOrHeaderless(512, 192, 255, 255, 255, 255, 0, MMS1_FILEPATH_TEX_CAR01, MMS1_FILEPATH_HEADERLESS_CAR01);

	car1Plate = PLEX_createAnimationPlate(0.25, 0.33333333, p_car1Tex);

	p_car1 = PLEX_genSprite(&car1Plate);

	PLEX_addAnimation(p_car1, 1000, PLEX_getGameTime());

	car1Down = PLEX_getAnimation(0, p_car1);

	PLEX_addAnimationFrame(0, car1Down);
	PLEX_addAnimationFrame(1, car1Down);
	PLEX_addAnimationFrame(2, car1Down);
	PLEX_addAnimationFrame(3, car1Down);

	PLEX_addAnimation(p_car1, 1000, PLEX_getGameTime());

	car1Up = PLEX_getAnimation(1, p_car1);

	PLEX_addAnimationFrame(4, car1Up);
	PLEX_addAnimationFrame(5, car1Up);
	PLEX_addAnimationFrame(6, car1Up);
	PLEX_addAnimationFrame(7, car1Up);

	PLEX_addAnimation(p_car1, 1000, PLEX_getGameTime());

	car1Crash = PLEX_getAnimation(2, p_car1);

	PLEX_addAnimationFrame(8, car1Crash);
	PLEX_addAnimationFrame(9, car1Crash);
	PLEX_addAnimationFrame(10, car1Crash);
	PLEX_addAnimationFrame(11, car1Crash);

	PLEX_startSprite(time, p_car1);
}

static void p_createCar2Sprite(const uint64_t time)
{
	PLEX_ANIMATION_PLATE car2Plate;

	PLEX_ANIMATION* car2Down = NULL;
	PLEX_ANIMATION* car2Up = NULL;
	PLEX_ANIMATION* car2Crash = NULL;

	p_car2Tex = PLEX_loadTextureFromFileOrHeaderless(512, 192, 255, 255, 255, 255, 0, MMS1_FILEPATH_TEX_CAR02, MMS1_FILEPATH_HEADERLESS_CAR02);

	car2Plate = PLEX_createAnimationPlate(0.25, 0.33333333, p_car2Tex);

	p_car2 = PLEX_genSprite(&car2Plate);

	PLEX_addAnimation(p_car2, 1000, PLEX_getGameTime());

	car2Down = PLEX_getAnimation(0, p_car2);

	PLEX_addAnimationFrame(0, car2Down);
	PLEX_addAnimationFrame(1, car2Down);
	PLEX_addAnimationFrame(2, car2Down);
	PLEX_addAnimationFrame(3, car2Down);

	PLEX_addAnimation(p_car2, 1000, PLEX_getGameTime());

	car2Up = PLEX_getAnimation(1, p_car2);

	PLEX_addAnimationFrame(4, car2Up);
	PLEX_addAnimationFrame(5, car2Up);
	PLEX_addAnimationFrame(6, car2Up);
	PLEX_addAnimationFrame(7, car2Up);

	PLEX_addAnimation(p_car2, 1000, PLEX_getGameTime());

	car2Crash = PLEX_getAnimation(2, p_car2);

	PLEX_addAnimationFrame(8, car2Crash);
	PLEX_addAnimationFrame(9, car2Crash);
	PLEX_addAnimationFrame(10, car2Crash);
	PLEX_addAnimationFrame(11, car2Crash);

	PLEX_startSprite(time, p_car2);
}

static void p_createCar3Sprite(const uint64_t time)
{
	PLEX_ANIMATION_PLATE car3Plate;

	PLEX_ANIMATION* car3Down = NULL;
	PLEX_ANIMATION* car3Up = NULL;
	PLEX_ANIMATION* car3Crash = NULL;

	p_car3Tex = PLEX_loadTextureFromFileOrHeaderless(512, 192, 255, 255, 255, 255, 0, MMS1_FILEPATH_TEX_CAR03, MMS1_FILEPATH_HEADERLESS_CAR03);

	car3Plate = PLEX_createAnimationPlate(0.25, 0.33333333, p_car3Tex);

	p_car3 = PLEX_genSprite(&car3Plate);

	PLEX_addAnimation(p_car3, 1000, PLEX_getGameTime());

	car3Down = PLEX_getAnimation(0, p_car3);

	PLEX_addAnimationFrame(0, car3Down);
	PLEX_addAnimationFrame(1, car3Down);
	PLEX_addAnimationFrame(2, car3Down);
	PLEX_addAnimationFrame(3, car3Down);

	PLEX_addAnimation(p_car3, 1000, PLEX_getGameTime());

	car3Up = PLEX_getAnimation(1, p_car3);

	PLEX_addAnimationFrame(4, car3Up);
	PLEX_addAnimationFrame(5, car3Up);
	PLEX_addAnimationFrame(6, car3Up);
	PLEX_addAnimationFrame(7, car3Up);

	PLEX_addAnimation(p_car3, 1000, PLEX_getGameTime());

	car3Crash = PLEX_getAnimation(2, p_car3);

	PLEX_addAnimationFrame(8, car3Crash);
	PLEX_addAnimationFrame(9, car3Crash);
	PLEX_addAnimationFrame(10, car3Crash);
	PLEX_addAnimationFrame(11, car3Crash);

	PLEX_startSprite(time, p_car3);
}

static void p_createCar4Sprite(const uint64_t time)
{
	PLEX_ANIMATION_PLATE car4Plate;

	PLEX_ANIMATION* car4Down = NULL;
	PLEX_ANIMATION* car4Up = NULL;
	PLEX_ANIMATION* car4Crash = NULL;

	p_car4Tex = PLEX_loadTextureFromFileOrHeaderless(512, 192, 255, 255, 255, 255, 0, MMS1_FILEPATH_TEX_CAR04, MMS1_FILEPATH_HEADERLESS_CAR04);

	car4Plate = PLEX_createAnimationPlate(0.25, 0.33333333, p_car4Tex);

	p_car4 = PLEX_genSprite(&car4Plate);

	PLEX_addAnimation(p_car4, 1000, PLEX_getGameTime());

	car4Down = PLEX_getAnimation(0, p_car4);

	PLEX_addAnimationFrame(0, car4Down);
	PLEX_addAnimationFrame(1, car4Down);
	PLEX_addAnimationFrame(2, car4Down);
	PLEX_addAnimationFrame(3, car4Down);

	PLEX_addAnimation(p_car4, 1000, PLEX_getGameTime());

	car4Up = PLEX_getAnimation(1, p_car4);

	PLEX_addAnimationFrame(4, car4Up);
	PLEX_addAnimationFrame(5, car4Up);
	PLEX_addAnimationFrame(6, car4Up);
	PLEX_addAnimationFrame(7, car4Up);

	PLEX_addAnimation(p_car4, 1000, PLEX_getGameTime());

	car4Crash = PLEX_getAnimation(2, p_car4);

	PLEX_addAnimationFrame(8, car4Crash);
	PLEX_addAnimationFrame(9, car4Crash);
	PLEX_addAnimationFrame(10, car4Crash);
	PLEX_addAnimationFrame(11, car4Crash);

	PLEX_startSprite(time, p_car4);
}

static void p_createCar5Sprite(const uint64_t time)
{
	PLEX_ANIMATION_PLATE car5Plate;

	PLEX_ANIMATION* car5Down = NULL;
	PLEX_ANIMATION* car5Up = NULL;
	PLEX_ANIMATION* car5Crash = NULL;

	p_car5Tex = PLEX_loadTextureFromFileOrHeaderless(512, 192, 255, 255, 255, 255, 0, MMS1_FILEPATH_TEX_CAR05, MMS1_FILEPATH_HEADERLESS_CAR05);

	car5Plate = PLEX_createAnimationPlate(0.25, 0.33333333, p_car5Tex);

	p_car5 = PLEX_genSprite(&car5Plate);

	PLEX_addAnimation(p_car5, 1000, PLEX_getGameTime());

	car5Down = PLEX_getAnimation(0, p_car5);

	PLEX_addAnimationFrame(0, car5Down);
	PLEX_addAnimationFrame(1, car5Down);
	PLEX_addAnimationFrame(2, car5Down);
	PLEX_addAnimationFrame(3, car5Down);

	PLEX_addAnimation(p_car5, 1000, PLEX_getGameTime());

	car5Up = PLEX_getAnimation(1, p_car5);

	PLEX_addAnimationFrame(4, car5Up);
	PLEX_addAnimationFrame(5, car5Up);
	PLEX_addAnimationFrame(6, car5Up);
	PLEX_addAnimationFrame(7, car5Up);

	PLEX_addAnimation(p_car5, 1000, PLEX_getGameTime());

	car5Crash = PLEX_getAnimation(2, p_car5);

	PLEX_addAnimationFrame(8, car5Crash);
	PLEX_addAnimationFrame(9, car5Crash);
	PLEX_addAnimationFrame(10, car5Crash);
	PLEX_addAnimationFrame(11, car5Crash);

	PLEX_startSprite(time, p_car5);
}

static void p_createCar6Sprite(const uint64_t time)
{
	PLEX_ANIMATION_PLATE car6Plate;

	PLEX_ANIMATION* car6Down = NULL;
	PLEX_ANIMATION* car6Up = NULL;
	PLEX_ANIMATION* car6Crash = NULL;

	p_car6Tex = PLEX_loadTextureFromFileOrHeaderless(512, 192, 255, 255, 255, 255, 0, MMS1_FILEPATH_TEX_CAR06, MMS1_FILEPATH_HEADERLESS_CAR06);

	car6Plate = PLEX_createAnimationPlate(0.25, 0.33333333, p_car6Tex);

	p_car6 = PLEX_genSprite(&car6Plate);

	PLEX_addAnimation(p_car6, 1000, PLEX_getGameTime());

	car6Down = PLEX_getAnimation(0, p_car6);

	PLEX_addAnimationFrame(0, car6Down);
	PLEX_addAnimationFrame(1, car6Down);
	PLEX_addAnimationFrame(2, car6Down);
	PLEX_addAnimationFrame(3, car6Down);

	PLEX_addAnimation(p_car6, 1000, PLEX_getGameTime());

	car6Up = PLEX_getAnimation(1, p_car6);

	PLEX_addAnimationFrame(4, car6Up);
	PLEX_addAnimationFrame(5, car6Up);
	PLEX_addAnimationFrame(6, car6Up);
	PLEX_addAnimationFrame(7, car6Up);

	PLEX_addAnimation(p_car6, 1000, PLEX_getGameTime());

	car6Crash = PLEX_getAnimation(2, p_car6);

	PLEX_addAnimationFrame(8, car6Crash);
	PLEX_addAnimationFrame(9, car6Crash);
	PLEX_addAnimationFrame(10, car6Crash);
	PLEX_addAnimationFrame(11, car6Crash);

	PLEX_startSprite(time, p_car6);

}

static void p_createCar7Sprite(const uint64_t time)
{
	PLEX_ANIMATION_PLATE car7Plate;

	PLEX_ANIMATION* car7Down = NULL;
	PLEX_ANIMATION* car7Up = NULL;
	PLEX_ANIMATION* car7Crash = NULL;

	p_car7Tex = PLEX_loadTextureFromFileOrHeaderless(512, 192, 255, 255, 255, 255, 0, MMS1_FILEPATH_TEX_CAR07, MMS1_FILEPATH_HEADERLESS_CAR07);

	car7Plate = PLEX_createAnimationPlate(0.25, 0.33333333, p_car7Tex);

	p_car7 = PLEX_genSprite(&car7Plate);

	PLEX_addAnimation(p_car7, 1000, PLEX_getGameTime());

	car7Down = PLEX_getAnimation(0, p_car7);

	PLEX_addAnimationFrame(0, car7Down);
	PLEX_addAnimationFrame(1, car7Down);
	PLEX_addAnimationFrame(2, car7Down);
	PLEX_addAnimationFrame(3, car7Down);

	PLEX_addAnimation(p_car7, 1000, PLEX_getGameTime());

	car7Up = PLEX_getAnimation(1, p_car7);

	PLEX_addAnimationFrame(4, car7Up);
	PLEX_addAnimationFrame(5, car7Up);
	PLEX_addAnimationFrame(6, car7Up);
	PLEX_addAnimationFrame(7, car7Up);

	PLEX_addAnimation(p_car7, 1000, PLEX_getGameTime());

	car7Crash = PLEX_getAnimation(2, p_car7);

	PLEX_addAnimationFrame(8, car7Crash);
	PLEX_addAnimationFrame(9, car7Crash);
	PLEX_addAnimationFrame(10, car7Crash);
	PLEX_addAnimationFrame(11, car7Crash);

	PLEX_startSprite(time, p_car7);
}

static void p_createCar8Sprite(const uint64_t time)
{
	PLEX_ANIMATION_PLATE car8Plate;

	PLEX_ANIMATION* car8Down = NULL;
	PLEX_ANIMATION* car8Up = NULL;
	PLEX_ANIMATION* car8Crash = NULL;

	p_car8Tex = PLEX_loadTextureFromFileOrHeaderless(512, 192, 255, 255, 255, 255, 0, MMS1_FILEPATH_TEX_CAR08, MMS1_FILEPATH_HEADERLESS_CAR08);

	car8Plate = PLEX_createAnimationPlate(0.25, 0.33333333, p_car8Tex);

	p_car8 = PLEX_genSprite(&car8Plate);

	PLEX_addAnimation(p_car8, 1000, PLEX_getGameTime());

	car8Down = PLEX_getAnimation(0, p_car8);

	PLEX_addAnimationFrame(0, car8Down);
	PLEX_addAnimationFrame(1, car8Down);
	PLEX_addAnimationFrame(2, car8Down);
	PLEX_addAnimationFrame(3, car8Down);

	PLEX_addAnimation(p_car8, 1000, PLEX_getGameTime());

	car8Up = PLEX_getAnimation(1, p_car8);

	PLEX_addAnimationFrame(4, car8Up);
	PLEX_addAnimationFrame(5, car8Up);
	PLEX_addAnimationFrame(6, car8Up);
	PLEX_addAnimationFrame(7, car8Up);

	PLEX_addAnimation(p_car8, 1000, PLEX_getGameTime());

	car8Crash = PLEX_getAnimation(2, p_car8);

	PLEX_addAnimationFrame(8, car8Crash);
	PLEX_addAnimationFrame(9, car8Crash);
	PLEX_addAnimationFrame(10, car8Crash);
	PLEX_addAnimationFrame(11, car8Crash);

	PLEX_startSprite(time, p_car8);
}

static void p_createCar9Sprite(const uint64_t time)
{
	PLEX_ANIMATION_PLATE car9Plate;

	PLEX_ANIMATION* car9Down = NULL;
	PLEX_ANIMATION* car9Up = NULL;
	PLEX_ANIMATION* car9Crash = NULL;

	p_car9Tex = PLEX_loadTextureFromFileOrHeaderless(512, 192, 255, 255, 255, 255, 0, MMS1_FILEPATH_TEX_CAR09, MMS1_FILEPATH_HEADERLESS_CAR09);

	car9Plate = PLEX_createAnimationPlate(0.25, 0.33333333, p_car9Tex);

	p_car9 = PLEX_genSprite(&car9Plate);

	PLEX_addAnimation(p_car9, 1000, PLEX_getGameTime());

	car9Down = PLEX_getAnimation(0, p_car9);

	PLEX_addAnimationFrame(0, car9Down);
	PLEX_addAnimationFrame(1, car9Down);
	PLEX_addAnimationFrame(2, car9Down);
	PLEX_addAnimationFrame(3, car9Down);

	PLEX_addAnimation(p_car9, 1000, PLEX_getGameTime());

	car9Up = PLEX_getAnimation(1, p_car9);

	PLEX_addAnimationFrame(4, car9Up);
	PLEX_addAnimationFrame(5, car9Up);
	PLEX_addAnimationFrame(6, car9Up);
	PLEX_addAnimationFrame(7, car9Up);

	PLEX_addAnimation(p_car9, 1000, PLEX_getGameTime());

	car9Crash = PLEX_getAnimation(2, p_car9);

	PLEX_addAnimationFrame(8, car9Crash);
	PLEX_addAnimationFrame(9, car9Crash);
	PLEX_addAnimationFrame(10, car9Crash);
	PLEX_addAnimationFrame(11, car9Crash);

	PLEX_startSprite(time, p_car9);
}

static void p_createCar10Sprite(const uint64_t time)
{
	PLEX_ANIMATION_PLATE car10Plate;

	PLEX_ANIMATION* car10Down = NULL;
	PLEX_ANIMATION* car10Up = NULL;
	PLEX_ANIMATION* car10Crash = NULL;

	p_car10Tex = PLEX_loadTextureFromFileOrHeaderless(512, 192, 255, 255, 255, 255, 0, MMS1_FILEPATH_TEX_CAR10, MMS1_FILEPATH_HEADERLESS_CAR10);

	car10Plate = PLEX_createAnimationPlate(0.25, 0.33333333, p_car10Tex);

	p_car10 = PLEX_genSprite(&car10Plate);

	PLEX_addAnimation(p_car10, 1000, PLEX_getGameTime());

	car10Down = PLEX_getAnimation(0, p_car10);

	PLEX_addAnimationFrame(0, car10Down);
	PLEX_addAnimationFrame(1, car10Down);
	PLEX_addAnimationFrame(2, car10Down);
	PLEX_addAnimationFrame(3, car10Down);

	PLEX_addAnimation(p_car10, 1000, PLEX_getGameTime());

	car10Up = PLEX_getAnimation(1, p_car10);

	PLEX_addAnimationFrame(4, car10Up);
	PLEX_addAnimationFrame(5, car10Up);
	PLEX_addAnimationFrame(6, car10Up);
	PLEX_addAnimationFrame(7, car10Up);

	PLEX_addAnimation(p_car10, 1000, PLEX_getGameTime());

	car10Crash = PLEX_getAnimation(2, p_car10);

	PLEX_addAnimationFrame(8, car10Crash);
	PLEX_addAnimationFrame(9, car10Crash);
	PLEX_addAnimationFrame(10, car10Crash);
	PLEX_addAnimationFrame(11, car10Crash);

	PLEX_startSprite(time, p_car10);
}

static void p_createCar11Sprite(const uint64_t time)
{
	PLEX_ANIMATION_PLATE car11Plate;

	PLEX_ANIMATION* car11Down = NULL;
	PLEX_ANIMATION* car11Up = NULL;
	PLEX_ANIMATION* car11Crash = NULL;

	p_car11Tex = PLEX_loadTextureFromFileOrHeaderless(512, 192, 255, 255, 255, 255, 0, MMS1_FILEPATH_TEX_CAR11, MMS1_FILEPATH_HEADERLESS_CAR11);

	car11Plate = PLEX_createAnimationPlate(0.25, 0.33333333, p_car11Tex);

	p_car11 = PLEX_genSprite(&car11Plate);

	PLEX_addAnimation(p_car11, 1000, PLEX_getGameTime());

	car11Down = PLEX_getAnimation(0, p_car11);

	PLEX_addAnimationFrame(0, car11Down);
	PLEX_addAnimationFrame(1, car11Down);
	PLEX_addAnimationFrame(2, car11Down);
	PLEX_addAnimationFrame(3, car11Down);

	PLEX_addAnimation(p_car11, 1000, PLEX_getGameTime());

	car11Up = PLEX_getAnimation(1, p_car11);

	PLEX_addAnimationFrame(4, car11Up);
	PLEX_addAnimationFrame(5, car11Up);
	PLEX_addAnimationFrame(6, car11Up);
	PLEX_addAnimationFrame(7, car11Up);

	PLEX_addAnimation(p_car11, 1000, PLEX_getGameTime());

	car11Crash = PLEX_getAnimation(2, p_car11);

	PLEX_addAnimationFrame(8, car11Crash);
	PLEX_addAnimationFrame(9, car11Crash);
	PLEX_addAnimationFrame(10, car11Crash);
	PLEX_addAnimationFrame(11, car11Crash);

	PLEX_startSprite(time, p_car11);
}

static void p_createCar12Sprite(const uint64_t time)
{
	PLEX_ANIMATION_PLATE car12Plate;

	PLEX_ANIMATION* car12Down = NULL;
	PLEX_ANIMATION* car12Up = NULL;
	PLEX_ANIMATION* car12Crash = NULL;

	p_car12Tex = PLEX_loadTextureFromFileOrHeaderless(512, 192, 255, 255, 255, 255, 0, MMS1_FILEPATH_TEX_CAR12, MMS1_FILEPATH_HEADERLESS_CAR12);

	car12Plate = PLEX_createAnimationPlate(0.25, 0.33333333, p_car12Tex);

	p_car12 = PLEX_genSprite(&car12Plate);

	PLEX_addAnimation(p_car12, 1000, PLEX_getGameTime());

	car12Down = PLEX_getAnimation(0, p_car12);

	PLEX_addAnimationFrame(0, car12Down);
	PLEX_addAnimationFrame(1, car12Down);
	PLEX_addAnimationFrame(2, car12Down);
	PLEX_addAnimationFrame(3, car12Down);

	PLEX_addAnimation(p_car12, 1000, PLEX_getGameTime());

	car12Up = PLEX_getAnimation(1, p_car12);

	PLEX_addAnimationFrame(4, car12Up);
	PLEX_addAnimationFrame(5, car12Up);
	PLEX_addAnimationFrame(6, car12Up);
	PLEX_addAnimationFrame(7, car12Up);

	PLEX_addAnimation(p_car12, 1000, PLEX_getGameTime());

	car12Crash = PLEX_getAnimation(2, p_car12);

	PLEX_addAnimationFrame(8, car12Crash);
	PLEX_addAnimationFrame(9, car12Crash);
	PLEX_addAnimationFrame(10, car12Crash);
	PLEX_addAnimationFrame(11, car12Crash);

	PLEX_startSprite(time, p_car12);
}

static void p_createCar13Sprite(const uint64_t time)
{
	PLEX_ANIMATION_PLATE car13Plate;

	PLEX_ANIMATION* car13Down = NULL;
	PLEX_ANIMATION* car13Up = NULL;
	PLEX_ANIMATION* car13Crash = NULL;

	p_car13Tex = PLEX_loadTextureFromFileOrHeaderless(512, 192, 255, 255, 255, 255, 0, MMS1_FILEPATH_TEX_CAR13, MMS1_FILEPATH_HEADERLESS_CAR13);

	car13Plate = PLEX_createAnimationPlate(0.25, 0.33333333, p_car13Tex);

	p_car13 = PLEX_genSprite(&car13Plate);

	PLEX_addAnimation(p_car13, 1000, PLEX_getGameTime());

	car13Down = PLEX_getAnimation(0, p_car13);

	PLEX_addAnimationFrame(0, car13Down);
	PLEX_addAnimationFrame(1, car13Down);
	PLEX_addAnimationFrame(2, car13Down);
	PLEX_addAnimationFrame(3, car13Down);

	PLEX_addAnimation(p_car13, 1000, PLEX_getGameTime());

	car13Up = PLEX_getAnimation(1, p_car13);

	PLEX_addAnimationFrame(4, car13Up);
	PLEX_addAnimationFrame(5, car13Up);
	PLEX_addAnimationFrame(6, car13Up);
	PLEX_addAnimationFrame(7, car13Up);

	PLEX_addAnimation(p_car13, 1000, PLEX_getGameTime());

	car13Crash = PLEX_getAnimation(2, p_car13);

	PLEX_addAnimationFrame(8, car13Crash);
	PLEX_addAnimationFrame(9, car13Crash);
	PLEX_addAnimationFrame(10, car13Crash);
	PLEX_addAnimationFrame(11, car13Crash);

	PLEX_startSprite(time, p_car13);
}

static void p_createCar14Sprite(const uint64_t time)
{
	PLEX_ANIMATION_PLATE car14Plate;

	PLEX_ANIMATION* car14Down = NULL;
	PLEX_ANIMATION* car14Up = NULL;
	PLEX_ANIMATION* car14Crash = NULL;

	p_car14Tex = PLEX_loadTextureFromFileOrHeaderless(512, 192, 255, 255, 255, 255, 0, MMS1_FILEPATH_TEX_CAR14, MMS1_FILEPATH_HEADERLESS_CAR14);

	car14Plate = PLEX_createAnimationPlate(0.25, 0.33333333, p_car14Tex);

	p_car14 = PLEX_genSprite(&car14Plate);

	PLEX_addAnimation(p_car14, 1000, PLEX_getGameTime());

	car14Down = PLEX_getAnimation(0, p_car14);

	PLEX_addAnimationFrame(0, car14Down);
	PLEX_addAnimationFrame(1, car14Down);
	PLEX_addAnimationFrame(2, car14Down);
	PLEX_addAnimationFrame(3, car14Down);

	PLEX_addAnimation(p_car14, 1000, PLEX_getGameTime());

	car14Up = PLEX_getAnimation(1, p_car14);

	PLEX_addAnimationFrame(4, car14Up);
	PLEX_addAnimationFrame(5, car14Up);
	PLEX_addAnimationFrame(6, car14Up);
	PLEX_addAnimationFrame(7, car14Up);

	PLEX_addAnimation(p_car14, 1000, PLEX_getGameTime());

	car14Crash = PLEX_getAnimation(2, p_car14);

	PLEX_addAnimationFrame(8, car14Crash);
	PLEX_addAnimationFrame(9, car14Crash);
	PLEX_addAnimationFrame(10, car14Crash);
	PLEX_addAnimationFrame(11, car14Crash);

	PLEX_startSprite(time, p_car14);
}

static void p_createCar15Sprite(const uint64_t time)
{
	PLEX_ANIMATION_PLATE car15Plate;

	PLEX_ANIMATION* car15Down = NULL;
	PLEX_ANIMATION* car15Up = NULL;
	PLEX_ANIMATION* car15Crash = NULL;

	p_car15Tex = PLEX_loadTextureFromFileOrHeaderless(512, 192, 255, 255, 255, 255, 0, MMS1_FILEPATH_TEX_CAR15, MMS1_FILEPATH_HEADERLESS_CAR15);

	car15Plate = PLEX_createAnimationPlate(0.25, 0.33333333, p_car15Tex);

	p_car15 = PLEX_genSprite(&car15Plate);

	PLEX_addAnimation(p_car15, 1000, PLEX_getGameTime());

	car15Down = PLEX_getAnimation(0, p_car15);

	PLEX_addAnimationFrame(0, car15Down);
	PLEX_addAnimationFrame(1, car15Down);
	PLEX_addAnimationFrame(2, car15Down);
	PLEX_addAnimationFrame(3, car15Down);

	PLEX_addAnimation(p_car15, 1000, PLEX_getGameTime());

	car15Up = PLEX_getAnimation(1, p_car15);

	PLEX_addAnimationFrame(4, car15Up);
	PLEX_addAnimationFrame(5, car15Up);
	PLEX_addAnimationFrame(6, car15Up);
	PLEX_addAnimationFrame(7, car15Up);

	PLEX_addAnimation(p_car15, 1000, PLEX_getGameTime());

	car15Crash = PLEX_getAnimation(2, p_car15);

	PLEX_addAnimationFrame(8, car15Crash);
	PLEX_addAnimationFrame(9, car15Crash);
	PLEX_addAnimationFrame(10, car15Crash);
	PLEX_addAnimationFrame(11, car15Crash);

	PLEX_startSprite(time, p_car15);
}

static void p_createBikeSprite(const uint64_t time)
{
	PLEX_ANIMATION_PLATE bikePlate;

	PLEX_ANIMATION* bikeDown = NULL;
	PLEX_ANIMATION* bikeUp = NULL;
	PLEX_ANIMATION* bikeCrash = NULL;

	p_bikeTex = PLEX_loadTextureFromFileOrHeaderless(256, 192, 255, 255, 255, 255, 0, MMS1_FILEPATH_TEX_BIKE, MMS1_FILEPATH_HEADERLESS_BIKE);

	bikePlate = PLEX_createAnimationPlate(0.25, 0.33333333, p_bikeTex);

	p_bike = PLEX_genSprite(&bikePlate);

	PLEX_addAnimation(p_bike, 1000, PLEX_getGameTime());

	bikeDown = PLEX_getAnimation(0, p_bike);

	PLEX_addAnimationFrame(0, bikeDown);
	PLEX_addAnimationFrame(1, bikeDown);
	PLEX_addAnimationFrame(2, bikeDown);
	PLEX_addAnimationFrame(3, bikeDown);

	PLEX_addAnimation(p_bike, 1000, PLEX_getGameTime());

	bikeUp = PLEX_getAnimation(1, p_bike);

	PLEX_addAnimationFrame(4, bikeUp);
	PLEX_addAnimationFrame(5, bikeUp);
	PLEX_addAnimationFrame(6, bikeUp);
	PLEX_addAnimationFrame(7, bikeUp);

	PLEX_addAnimation(p_bike, 1000, PLEX_getGameTime());

	bikeCrash = PLEX_getAnimation(2, p_bike);

	PLEX_addAnimationFrame(8, bikeCrash);
	PLEX_addAnimationFrame(9, bikeCrash);

	PLEX_startSprite(time, p_bike);
}

static void p_createBikerSprite(const uint64_t time)
{
	PLEX_ANIMATION_PLATE bikerPlate;

	PLEX_ANIMATION* bikerDown = NULL;
	PLEX_ANIMATION* bikerUp = NULL;
	PLEX_ANIMATION* bikerCrash = NULL;

	p_bikerTex = PLEX_loadTextureFromFileOrHeaderless(384, 192, 255, 255, 255, 255, 0, MMS1_FILEPATH_TEX_BIKER, MMS1_FILEPATH_HEADERLESS_BIKER);

	bikerPlate = PLEX_createAnimationPlate(0.33333333, 0.33333333, p_bikerTex);

	p_biker = PLEX_genSprite(&bikerPlate);

	PLEX_addAnimation(p_biker, 1000, PLEX_getGameTime());

	bikerDown = PLEX_getAnimation(0, p_biker);

	PLEX_addAnimationFrame(0, bikerDown);
	PLEX_addAnimationFrame(1, bikerDown);
	PLEX_addAnimationFrame(2, bikerDown);

	PLEX_addAnimation(p_biker, 1000, PLEX_getGameTime());

	bikerUp = PLEX_getAnimation(1, p_biker);

	PLEX_addAnimationFrame(3, bikerUp);
	PLEX_addAnimationFrame(4, bikerUp);
	PLEX_addAnimationFrame(5, bikerUp);

	PLEX_addAnimation(p_biker, 1000, PLEX_getGameTime());

	bikerCrash = PLEX_getAnimation(2, p_biker);

	PLEX_addAnimationFrame(7, bikerCrash);
	PLEX_addAnimationFrame(6, bikerCrash);

	PLEX_startSprite(time, p_biker);
}

static void p_createCactusSprite(const uint64_t time)
{
	PLEX_ANIMATION_PLATE cactusPlate;

	PLEX_ANIMATION* cactusDown = NULL;
	PLEX_ANIMATION* cactusUp = NULL;
	PLEX_ANIMATION* cactusCrash = NULL;

	p_cactusTex = PLEX_loadTextureFromFileOrHeaderless(64, 192, 255, 255, 255, 255, 0, MMS1_FILEPATH_TEX_CACTUS, MMS1_FILEPATH_HEADERLESS_CACTUS);

	cactusPlate = PLEX_createAnimationPlate(1, 0.33333333, p_cactusTex);

	p_cactus = PLEX_genSprite(&cactusPlate);

	PLEX_addAnimation(p_cactus, 1000, PLEX_getGameTime());

	cactusDown = PLEX_getAnimation(0, p_cactus);

	PLEX_addAnimationFrame(0, cactusDown);

	PLEX_addAnimation(p_cactus, 1000, PLEX_getGameTime());

	cactusUp = PLEX_getAnimation(1, p_cactus);

	PLEX_addAnimationFrame(1, cactusUp);

	PLEX_addAnimation(p_cactus, 1000, PLEX_getGameTime());

	cactusCrash = PLEX_getAnimation(2, p_cactus);

	PLEX_addAnimationFrame(2, cactusCrash);

	PLEX_startSprite(time, p_cactus);
}

static void p_createTumbleweedSprite(const uint64_t time)
{
	PLEX_ANIMATION_PLATE tumbleweedPlate;

	PLEX_ANIMATION* tumbleweedDown = NULL;
	PLEX_ANIMATION* tumbleweedUp = NULL;
	PLEX_ANIMATION* tumbleweedCrash = NULL;

	p_tumbleweedTex = PLEX_loadTextureFromFileOrHeaderless(256, 192, 255, 255, 255, 255, 0, MMS1_FILEPATH_TEX_TUMBLEWEED, MMS1_FILEPATH_HEADERLESS_TUMBLEWEED);

	tumbleweedPlate = PLEX_createAnimationPlate(0.25, 0.33333333, p_tumbleweedTex);

	p_tumbleweed = PLEX_genSprite(&tumbleweedPlate);

	PLEX_addAnimation(p_tumbleweed, 1000, PLEX_getGameTime());

	tumbleweedDown = PLEX_getAnimation(0, p_tumbleweed);

	PLEX_addAnimationFrame(0, tumbleweedDown);
	PLEX_addAnimationFrame(1, tumbleweedDown);
	PLEX_addAnimationFrame(2, tumbleweedDown);
	PLEX_addAnimationFrame(3, tumbleweedDown);

	PLEX_addAnimation(p_tumbleweed, 1000, PLEX_getGameTime());

	tumbleweedUp = PLEX_getAnimation(1, p_tumbleweed);

	PLEX_addAnimationFrame(4, tumbleweedUp);
	PLEX_addAnimationFrame(5, tumbleweedUp);
	PLEX_addAnimationFrame(6, tumbleweedUp);
	PLEX_addAnimationFrame(7, tumbleweedUp);

	PLEX_addAnimation(p_tumbleweed, 1000, PLEX_getGameTime());

	tumbleweedCrash = PLEX_getAnimation(2, p_tumbleweed);

	PLEX_addAnimationFrame(8, tumbleweedCrash);
	PLEX_addAnimationFrame(9, tumbleweedCrash);

	PLEX_startSprite(time, p_tumbleweed);
}

static void p_createBagSprite(const uint64_t time)
{
	PLEX_ANIMATION_PLATE bagPlate;

	PLEX_ANIMATION* bagDown = NULL;
	PLEX_ANIMATION* bagUp = NULL;
	PLEX_ANIMATION* bagCrash = NULL;

	p_bagTex = PLEX_loadTextureFromFileOrHeaderless(64, 192, 255, 255, 255, 255, 0, MMS1_FILEPATH_TEX_BAG, MMS1_FILEPATH_HEADERLESS_BAG);

	bagPlate = PLEX_createAnimationPlate(1, 0.33333333, p_bagTex);

	p_bag = PLEX_genSprite(&bagPlate);

	PLEX_addAnimation(p_bag, 1000, PLEX_getGameTime());

	bagDown = PLEX_getAnimation(0, p_bag);

	PLEX_addAnimationFrame(0, bagDown);

	PLEX_addAnimation(p_bag, 1000, PLEX_getGameTime());

	bagUp = PLEX_getAnimation(1, p_bag);

	PLEX_addAnimationFrame(1, bagUp);

	PLEX_addAnimation(p_bag, 1000, PLEX_getGameTime());

	bagCrash = PLEX_getAnimation(2, p_bag);

	PLEX_addAnimationFrame(2, bagCrash);

	PLEX_startSprite(time, p_bag);
}

static void p_createBag2Sprite(const uint64_t time)
{
	PLEX_ANIMATION_PLATE bag2Plate;

	PLEX_ANIMATION* bag2Down = NULL;
	PLEX_ANIMATION* bag2Up = NULL;
	PLEX_ANIMATION* bag2Crash = NULL;

	p_bag2Tex = PLEX_loadTextureFromFileOrHeaderless(64, 192, 255, 255, 255, 255, 0, MMS1_FILEPATH_TEX_BAG2, MMS1_FILEPATH_HEADERLESS_BAG2);

	bag2Plate = PLEX_createAnimationPlate(1, 0.33333333, p_bag2Tex);

	p_bag2 = PLEX_genSprite(&bag2Plate);

	PLEX_addAnimation(p_bag2, 1000, PLEX_getGameTime());

	bag2Down = PLEX_getAnimation(0, p_bag2);

	PLEX_addAnimationFrame(0, bag2Down);

	PLEX_addAnimation(p_bag2, 1000, PLEX_getGameTime());

	bag2Up = PLEX_getAnimation(1, p_bag2);

	PLEX_addAnimationFrame(1, bag2Up);

	PLEX_addAnimation(p_bag2, 1000, PLEX_getGameTime());

	bag2Crash = PLEX_getAnimation(2, p_bag2);

	PLEX_addAnimationFrame(2, bag2Crash);

	PLEX_startSprite(time, p_bag2);
}

static void p_createBarrelSprite(const uint64_t time)
{
	PLEX_ANIMATION_PLATE barrelPlate;

	PLEX_ANIMATION* barrelDown = NULL;
	PLEX_ANIMATION* barrelUp = NULL;
	PLEX_ANIMATION* barrelCrash = NULL;

	p_barrelTex = PLEX_loadTextureFromFileOrHeaderless(64, 192, 255, 255, 255, 255, 0, MMS1_FILEPATH_TEX_BARREL, MMS1_FILEPATH_HEADERLESS_BARREL);

	barrelPlate = PLEX_createAnimationPlate(1, 0.33333333, p_barrelTex);

	p_barrel = PLEX_genSprite(&barrelPlate);

	PLEX_addAnimation(p_barrel, 1000, PLEX_getGameTime());

	barrelDown = PLEX_getAnimation(0, p_barrel);

	PLEX_addAnimationFrame(0, barrelDown);

	PLEX_addAnimation(p_barrel, 1000, PLEX_getGameTime());

	barrelUp = PLEX_getAnimation(1, p_barrel);

	PLEX_addAnimationFrame(1, barrelUp);

	PLEX_addAnimation(p_barrel, 1000, PLEX_getGameTime());

	barrelCrash = PLEX_getAnimation(2, p_barrel);

	PLEX_addAnimationFrame(2, barrelCrash);

	PLEX_startSprite(time, p_barrel);
}

static void p_createBrickSprite(const uint64_t time)
{
	PLEX_ANIMATION_PLATE bricksPlate;

	PLEX_ANIMATION* bricksDown = NULL;
	PLEX_ANIMATION* bricksUp = NULL;
	PLEX_ANIMATION* bricksCrash = NULL;

	p_bricksTex = PLEX_loadTextureFromFileOrHeaderless(64, 192, 255, 255, 255, 255, 0, MMS1_FILEPATH_TEX_BRICKS, MMS1_FILEPATH_HEADERLESS_BRICKS);

	bricksPlate = PLEX_createAnimationPlate(1, 0.33333333, p_bricksTex);

	p_bricks = PLEX_genSprite(&bricksPlate);

	PLEX_addAnimation(p_bricks, 1000, PLEX_getGameTime());

	bricksDown = PLEX_getAnimation(0, p_bricks);

	PLEX_addAnimationFrame(0, bricksDown);

	PLEX_addAnimation(p_bricks, 1000, PLEX_getGameTime());

	bricksUp = PLEX_getAnimation(1, p_bricks);

	PLEX_addAnimationFrame(1, bricksUp);

	PLEX_addAnimation(p_bricks, 1000, PLEX_getGameTime());

	bricksCrash = PLEX_getAnimation(2, p_bricks);

	PLEX_addAnimationFrame(2, bricksCrash);

	PLEX_startSprite(time, p_bricks);
}

static void p_createCrateSprite(const uint64_t time)
{
	PLEX_ANIMATION_PLATE cratePlate;

	PLEX_ANIMATION* crateDown = NULL;
	PLEX_ANIMATION* crateUp = NULL;
	PLEX_ANIMATION* crateCrash = NULL;

	p_crateTex = PLEX_loadTextureFromFileOrHeaderless(64, 192, 255, 255, 255, 255, 0, MMS1_FILEPATH_TEX_CRATE, MMS1_FILEPATH_HEADERLESS_CRATE);

	cratePlate = PLEX_createAnimationPlate(1, 0.33333333, p_crateTex);

	p_crate = PLEX_genSprite(&cratePlate);

	PLEX_addAnimation(p_crate, 1000, PLEX_getGameTime());

	crateDown = PLEX_getAnimation(0, p_crate);

	PLEX_addAnimationFrame(0, crateDown);

	PLEX_addAnimation(p_crate, 1000, PLEX_getGameTime());

	crateUp = PLEX_getAnimation(1, p_crate);

	PLEX_addAnimationFrame(1, crateUp);

	PLEX_addAnimation(p_crate, 1000, PLEX_getGameTime());

	crateCrash = PLEX_getAnimation(2, p_crate);

	PLEX_addAnimationFrame(2, crateCrash);

	PLEX_startSprite(time, p_crate);
}

static void p_createPipesSprite(const uint64_t time)
{
	PLEX_ANIMATION_PLATE pipesPlate;

	PLEX_ANIMATION* pipesDown = NULL;
	PLEX_ANIMATION* pipesUp = NULL;
	PLEX_ANIMATION* pipesCrash = NULL;

	p_pipesTex = PLEX_loadTextureFromFileOrHeaderless(64, 192, 255, 255, 255, 255, 0, MMS1_FILEPATH_TEX_PIPES, MMS1_FILEPATH_HEADERLESS_PIPES);

	pipesPlate = PLEX_createAnimationPlate(1, 0.33333333, p_pipesTex);

	p_pipes = PLEX_genSprite(&pipesPlate);

	PLEX_addAnimation(p_pipes, 1000, PLEX_getGameTime());

	pipesDown = PLEX_getAnimation(0, p_pipes);

	PLEX_addAnimationFrame(0, pipesDown);

	PLEX_addAnimation(p_pipes, 1000, PLEX_getGameTime());

	pipesUp = PLEX_getAnimation(1, p_pipes);

	PLEX_addAnimationFrame(1, pipesUp);

	PLEX_addAnimation(p_pipes, 1000, PLEX_getGameTime());

	pipesCrash = PLEX_getAnimation(2, p_pipes);

	PLEX_addAnimationFrame(2, pipesCrash);

	PLEX_startSprite(time, p_pipes);
}

static void p_loadObstructionGraphics(const uint64_t time)
{
	p_createCar0Sprite(time);
	p_createCar1Sprite(time);
	p_createCar2Sprite(time);
	p_createCar3Sprite(time);
	p_createCar4Sprite(time);
	p_createCar5Sprite(time);
	p_createCar6Sprite(time);
	p_createCar7Sprite(time);
	p_createCar8Sprite(time);
	p_createCar9Sprite(time);
	p_createCar10Sprite(time);
	p_createCar11Sprite(time);
	p_createCar12Sprite(time);
	p_createCar13Sprite(time);
	p_createCar14Sprite(time);
	p_createCar15Sprite(time);

	p_createBikeSprite(time);
	p_createBikerSprite(time);

	p_createCactusSprite(time);
	p_createTumbleweedSprite(time);
	p_createBagSprite(time);
	p_createBag2Sprite(time);
	p_createBarrelSprite(time);
	p_createBrickSprite(time);
	p_createCrateSprite(time);
	p_createPipesSprite(time);
}

static void p_destroyObstructionGraphics()
{
	if(p_car0 != NULL) PLEX_destroySprite(&p_car0);
	if(p_car1 != NULL) PLEX_destroySprite(&p_car1);
	if(p_car2 != NULL) PLEX_destroySprite(&p_car2);
	if(p_car3 != NULL) PLEX_destroySprite(&p_car3);
	if(p_car4 != NULL) PLEX_destroySprite(&p_car4);
	if(p_car5 != NULL) PLEX_destroySprite(&p_car5);
	if(p_car6 != NULL) PLEX_destroySprite(&p_car6);
	if(p_car7 != NULL) PLEX_destroySprite(&p_car7);
	if(p_car8 != NULL) PLEX_destroySprite(&p_car8);
	if(p_car9 != NULL) PLEX_destroySprite(&p_car9);
	if(p_car10 != NULL) PLEX_destroySprite(&p_car10);
	if(p_car11 != NULL) PLEX_destroySprite(&p_car11);
	if(p_car12 != NULL) PLEX_destroySprite(&p_car12);
	if(p_car13 != NULL) PLEX_destroySprite(&p_car13);
	if(p_car14 != NULL) PLEX_destroySprite(&p_car14);
	if(p_car15 != NULL) PLEX_destroySprite(&p_car15);

	if(p_bike != NULL) PLEX_destroySprite(&p_bike);
	if(p_biker != NULL) PLEX_destroySprite(&p_biker);

	if(p_cactus != NULL) PLEX_destroySprite(&p_cactus);
	if(p_tumbleweed != NULL) PLEX_destroySprite(&p_tumbleweed);
	if(p_bag != NULL) PLEX_destroySprite(&p_bag);
	if(p_bag2 != NULL) PLEX_destroySprite(&p_bag2);
	if(p_barrel != NULL) PLEX_destroySprite(&p_barrel);
	if(p_bricks != NULL) PLEX_destroySprite(&p_bricks);
	if(p_crate != NULL) PLEX_destroySprite(&p_crate);
	if(p_pipes != NULL) PLEX_destroySprite(&p_pipes);

	if(p_car0Tex) PLEX_destroyTexture(p_car0Tex);
	if(p_car1Tex) PLEX_destroyTexture(p_car1Tex);
	if(p_car2Tex) PLEX_destroyTexture(p_car2Tex);
	if(p_car3Tex) PLEX_destroyTexture(p_car3Tex);
	if(p_car4Tex) PLEX_destroyTexture(p_car4Tex);
	if(p_car5Tex) PLEX_destroyTexture(p_car5Tex);
	if(p_car6Tex) PLEX_destroyTexture(p_car6Tex);
	if(p_car7Tex) PLEX_destroyTexture(p_car7Tex);
	if(p_car8Tex) PLEX_destroyTexture(p_car8Tex);
	if(p_car9Tex) PLEX_destroyTexture(p_car9Tex);
	if(p_car10Tex) PLEX_destroyTexture(p_car10Tex);
	if(p_car11Tex) PLEX_destroyTexture(p_car11Tex);
	if(p_car12Tex) PLEX_destroyTexture(p_car12Tex);
	if(p_car13Tex) PLEX_destroyTexture(p_car13Tex);
	if(p_car14Tex) PLEX_destroyTexture(p_car14Tex);
	if(p_car15Tex) PLEX_destroyTexture(p_car15Tex);

	if(p_bikeTex) PLEX_destroyTexture(p_bikeTex);
	if(p_bikerTex) PLEX_destroyTexture(p_bikerTex);

	if(p_cactusTex) PLEX_destroyTexture(p_cactusTex);
	if(p_tumbleweedTex) PLEX_destroyTexture(p_tumbleweedTex);
	if(p_bagTex) PLEX_destroyTexture(p_bagTex);
	if(p_bag2Tex) PLEX_destroyTexture(p_bag2Tex);
	if(p_barrelTex) PLEX_destroyTexture(p_barrelTex);
	if(p_bricksTex) PLEX_destroyTexture(p_bricksTex);
	if(p_crateTex) PLEX_destroyTexture(p_crateTex);
	if(p_pipesTex) PLEX_destroyTexture(p_pipesTex);

	p_car0Tex = 0;
	p_car1Tex = 0;
	p_car2Tex = 0;
	p_car3Tex = 0;
	p_car4Tex = 0;
	p_car5Tex = 0;
	p_car6Tex = 0;
	p_car7Tex = 0;
	p_car8Tex = 0;
	p_car9Tex = 0;
	p_car10Tex = 0;
	p_car11Tex = 0;
	p_car12Tex = 0;
	p_car13Tex = 0;
	p_car14Tex = 0;
	p_car15Tex = 0;

	p_bikeTex = 0;
	p_bikerTex = 0;

	p_cactusTex = 0;
	p_tumbleweedTex = 0;
	p_bagTex = 0;
	p_bag2Tex = 0;
	p_barrelTex = 0;
	p_bricksTex = 0;
	p_crateTex = 0;
	p_pipesTex = 0;
}

static PLEX_SPRITE* p_typeSprite(const MMS1_OBSTRUCTION_TYPE type)
{
	switch(type)
	{
		case MMS1_OBSTRUCTION_TYPE_CAR0: return p_car0;
		case MMS1_OBSTRUCTION_TYPE_CAR1: return p_car1;
		case MMS1_OBSTRUCTION_TYPE_CAR2: return p_car2;
		case MMS1_OBSTRUCTION_TYPE_CAR3: return p_car3;
		case MMS1_OBSTRUCTION_TYPE_CAR4: return p_car4;
		case MMS1_OBSTRUCTION_TYPE_CAR5: return p_car5;
		case MMS1_OBSTRUCTION_TYPE_CAR6: return p_car6;
		case MMS1_OBSTRUCTION_TYPE_CAR7: return p_car7;
		case MMS1_OBSTRUCTION_TYPE_CAR8: return p_car8;
		case MMS1_OBSTRUCTION_TYPE_CAR9: return p_car9;
		case MMS1_OBSTRUCTION_TYPE_CAR10: return p_car10;
		case MMS1_OBSTRUCTION_TYPE_CAR11: return p_car11;
		case MMS1_OBSTRUCTION_TYPE_CAR12: return p_car12;
		case MMS1_OBSTRUCTION_TYPE_CAR13: return p_car13;
		case MMS1_OBSTRUCTION_TYPE_CAR14: return p_car14;
		case MMS1_OBSTRUCTION_TYPE_CAR15: return p_car15;
		case MMS1_OBSTRUCTION_TYPE_BIKE: return p_bike;
		case MMS1_OBSTRUCTION_TYPE_BIKER: return p_biker;
		case MMS1_OBSTRUCTION_TYPE_CACTUS: return p_cactus;
		case MMS1_OBSTRUCTION_TYPE_TUMBLEWEED: return p_tumbleweed;
		case MMS1_OBSTRUCTION_TYPE_BAG: return p_bag;
		case MMS1_OBSTRUCTION_TYPE_BAG2: return p_bag2;
		case MMS1_OBSTRUCTION_TYPE_BARREL: return p_barrel;
		case MMS1_OBSTRUCTION_TYPE_BRICKS: return p_bricks;
		case MMS1_OBSTRUCTION_TYPE_CRATE: return p_crate;
		case MMS1_OBSTRUCTION_TYPE_PIPES: return p_pipes;
	};

	return NULL;
}

// public functions

MMS1_OBSTRUCTION MMS1_genObstruction(const size_t lane, const double w, const double h, const double velocity, const double driftVelocity, const double leftDrift, const double rightDrift, const double weight, const bool startDriftRight, const MMS1_OBSTRUCTION_TYPE type)
{
	MMS1_OBSTRUCTION ret;

	PLEX_SPRITE* sprite = p_typeSprite(type);

	memset(&ret, 0, sizeof(ret));

	if(sprite == NULL)
	{
		PLEX_error2(PLEX_ERROR_CATEGORY_INPROJECT, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_MINOR, MMS1_ERRORMESS_ONCREATEOBSTRUCTION, MMS1_ERRORMESS_OBSTRUCTIONSPRITE);
		return ret;
	}

	ret.lane = lane;
	ret.space.dimens.w = w;
	ret.space.dimens.h = h;
	ret.velocity = velocity;
	ret.leftDrift = leftDrift;
	ret.rightDrift = rightDrift;
	ret.driftVelocity = driftVelocity;
	ret.weight = weight;
	ret.sprite = sprite;

	if(rightDrift && startDriftRight) ret.drift = driftVelocity;
	else if(leftDrift && !startDriftRight) ret.drift = driftVelocity * -1;

	return ret;
}

bool MMS1_beginObstructions(const size_t chapter1SpriteTex, const uint64_t time)
{
	p_loadObstructionGraphics(time);

	return true;
}

bool MMS1_updateObstructions(const size_t phase, const size_t lane, const uint64_t time)
{
	return true;
}

void MMS1_endObstructions()
{
	p_destroyObstructionGraphics();
}
