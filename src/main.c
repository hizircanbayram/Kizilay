#include <allegro5/allegro.h> //Main Allegro header
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_primitives.h>

#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

#include <stdlib.h>  // rand(), srand()
#include <time.h>    // time()
#include <math.h>
#include <stdio.h>

#define ENEMY0_HEALTH 1
#define ENEMY1_HEALTH 2
#define ENEMY2_HEALTH 3
#define ENEMY3_HEALTH 1
#define ENEMY4_HEALTH 2

#define WIDTH 750
#define HEIGHT 750
#define FPS 60
#define NUM_BULLETS 5
#define NUM_EXPLOSIONS 1
#define NUM_TRANSFORM 1
#define NUM_ENEMIES 15
#define NUM_MISSILES 1
#define NUM_LASERS 30
#define NUM_LIGHTENINGS 30
#define NUM_NEAREST 30
#define NUM_LEVEL 1
#define NUM_START 1

#define boole int
#define true 1
#define false 0

#define USERNAME 25
#define LIST_SIZE 200

#include "Bullet.h"
#include "Missile.h"
#include "Explosion.h"
#include "SpaceShip.h"
#include "Enemy.h"
#include "Transform.h"
#include "Level.h"
#include "Start.h"
#include "Background.h"
#include "Laser.h"
#include "Lightening.h"
#include "Nearest.h"

int killed_enemies = 0;
float gravity = 49;

bool keys[] = {false, false, false, false, false, false, false, false};

enum STATE{TITLE, PLAYING, LOST, AUTOPILOT, SCORETABLE};
enum IDS {PLAYER, BULLET, ENEMY0, ENEMY1, ENEMY2, ENEMY3, ENEMY4, LASER, LIGHTENING, NEAREST};
enum KEYS {UP, DOWN, RIGHT, LEFT, SPACE, D, P, T};


typedef struct user
 {
   char name[USERNAME];
   int score;
 }user;


SpaceShip ship;
Bullets bullet[NUM_BULLETS];
Enemies enemy[NUM_ENEMIES];
Enemies enemy0, enemy1, enemy2, enemy3, enemy4;
Explosion explosions[NUM_EXPLOSIONS];
Lasers laser[NUM_LASERS];
Lightening lights[NUM_LIGHTENINGS];
Nearest neary[NUM_NEAREST];
Transform tr_ship[NUM_TRANSFORM];
Level level[NUM_LEVEL],
levelup[NUM_LEVEL];
Start startup[NUM_START];

ALLEGRO_SAMPLE *shot = NULL;
ALLEGRO_SAMPLE *near_skill = NULL;
ALLEGRO_SAMPLE *light_skill = NULL;
ALLEGRO_SAMPLE *laser_skill = NULL;
ALLEGRO_SAMPLE *shooted = NULL;
ALLEGRO_SAMPLE *collision = NULL;
ALLEGRO_SAMPLE *bomb = NULL;
ALLEGRO_SAMPLE *song = NULL;
ALLEGRO_SAMPLE_INSTANCE *songInstance = NULL;


void collisionBullets(Bullets bullet[], int bsize, Enemies enemy[], int esize, SpaceShip *ship, Explosion explosions[], int expsize, int *state);
void collisionEnemies(SpaceShip *ship, Enemies enemy[], int esize, Explosion explosions[], int expSize, int *state);


void ChangeState(int *state, int newState);

int findClosest(int *x, int *y, boole *enemydetected, int *the_enemy);



int main() {
        //This command create a screen
    //variables for loop
    boole done = false;
    boole redraw = true;
    int cnt = 0;
    int state = -1;

    //variables for lasers
    int killedenemies = -1;
    int cntLaser = -1;
    int laserTimer = 0;
    boole flagLaser = false;

    //variables for lightenings
    int cntLight = -1;
    int lightTimer = 0;
    boole flagLight = false;

    //variables for near
    int cntNear = -1;
    int nearTimer = 0;
    boole flagNear = false;

    //variables for autopilot
    boole autoBool = false;
    boole enemydetected = false;
    int the_enemy;
	int oto_skill_cnt = 0;

	boole highscore = false;

	int ch;
	int list[LIST_SIZE] = {9999};
	int list_cnt = 0;
	int onbes = 15;//silinecek
	int row = 170;
	int list2[10][25];

	Background wp0;
	Background wp1;
	Background wp2;
	Background wp3;
	Background wp4;
	Background wp5;
    Background wp6;

    ALLEGRO_DISPLAY *display = NULL;
    ALLEGRO_EVENT_QUEUE *event_queue = NULL;
    ALLEGRO_TIMER *timer = NULL;
    ALLEGRO_FONT *font18 = NULL;


    ALLEGRO_BITMAP *shipImage;
    ALLEGRO_BITMAP *enemyImage[NUM_ENEMIES]; //enemy type kadar olacak...
    ALLEGRO_BITMAP *expImage;
	ALLEGRO_BITMAP *title = NULL;
	ALLEGRO_BITMAP *lost = NULL;
	ALLEGRO_BITMAP *m_image = NULL;
	ALLEGRO_BITMAP *l_image = NULL;
	ALLEGRO_BITMAP *tr_ship_image = NULL;
	ALLEGRO_BITMAP *levelup_image = NULL;
	ALLEGRO_BITMAP *start_image = NULL;

	ALLEGRO_BITMAP *wp0Image = NULL;
	ALLEGRO_BITMAP *wp1Image = NULL;
	ALLEGRO_BITMAP *wp2Image = NULL;
	ALLEGRO_BITMAP *wp3Image = NULL;
	ALLEGRO_BITMAP *wp4Image = NULL;
	ALLEGRO_BITMAP *wp5Image = NULL;
	ALLEGRO_BITMAP *wp6Image = NULL;

	ALLEGRO_BITMAP *light_image = NULL;
	ALLEGRO_BITMAP *near_image = NULL;

	ALLEGRO_BITMAP *level_image = NULL;

	ALLEGRO_FILE *fp = NULL;
	ALLEGRO_FILE *fp2 = NULL;


    if(!al_init())
    al_show_native_message_box(NULL, NULL, NULL, "Could not initialize Allegro 5", NULL, NULL);

    display = al_create_display(WIDTH, HEIGHT);

    if(!display)
    al_show_native_message_box(NULL, NULL, NULL, "Could not create Allegro 5 display", NULL, NULL);

    al_init_primitives_addon();
    al_install_keyboard();
    al_init_font_addon();
    al_init_ttf_addon();
    al_init_image_addon();
    al_install_audio();
    al_init_acodec_addon();

    /*******************************/
    /***********HIGHSCORE***********/
    /*******************************/
   ALLEGRO_FONT* font = al_create_builtin_font();
   ALLEGRO_EVENT_QUEUE* q = al_create_event_queue();
   al_register_event_source(q, al_get_keyboard_event_source());
   al_register_event_source(q, al_get_display_event_source(display));
   ALLEGRO_USTR* str = al_ustr_new("Enter your name...");
   int pos = (int)al_ustr_size(str);
   int text = 18;
   int i = 0;
   user player1, player1_write;
   int letter;
   int sayi = 4;
   char *access;


   boole quit = false;

   boole file_flag = false;

    bool deneme1 = false;
    bool deneme2 = false;
    bool deneme3 = false;


    event_queue = al_create_event_queue();
    timer = al_create_timer(1. / FPS);

    /*******************************/
    /*************BITMAPS***********/
    /*******************************/
    shipImage = al_load_bitmap("ally0.png");
    al_convert_mask_to_alpha(shipImage, al_map_rgb(255, 0, 255));

    enemyImage[0] = al_load_bitmap("enemy0.png");
    enemyImage[1] = al_load_bitmap("enemy1.png");
    enemyImage[2] = al_load_bitmap("enemy2.png");
    enemyImage[3] = al_load_bitmap("enemy3.png");
    enemyImage[4] = al_load_bitmap("enemy4.png");

    m_image = al_load_bitmap("missile.png");
    expImage = al_load_bitmap("explosion0.png");

    l_image = al_load_bitmap("laser.png");
    light_image = al_load_bitmap("skill3.png");
    near_image = al_load_bitmap("lightening.png");

	title = al_load_bitmap("Shooter_Title.png");
	lost = al_load_bitmap("Shooter_Lose.png");

	tr_ship_image = al_load_bitmap("transform.png");


	wp0Image = al_load_bitmap("wallpaper0.png");
	wp1Image = al_load_bitmap("wallpaper1.png");
	wp2Image = al_load_bitmap("wallpaper2.png");
	wp3Image = al_load_bitmap("wallpaper3.png");
	wp4Image = al_load_bitmap("wallpaper4.png");
	wp5Image = al_load_bitmap("wallpaper5.png");
	wp6Image = al_load_bitmap("wallpaper6.png");

	level_image = al_load_bitmap("levelup.png");
	levelup_image = al_load_bitmap("levelup2.png");
	start_image  = al_load_bitmap("start.png");

	/*******************************/
    /*************AUDIOS***********/
    /*******************************/

	al_reserve_samples(10);

	shot = al_load_sample("1.ogg");
	laser_skill = al_load_sample("lazer.ogg");
	near_skill = al_load_sample("en_yakin_dusman.ogg");
	light_skill = al_load_sample("cani_az_olan_dusman.ogg");
	shooted = al_load_sample("hasar.ogg");
	collision = al_load_sample("hasar1.ogg");
	song = al_load_sample("shot.ogg");
	bomb = al_load_sample("3.ogg");

	songInstance = al_create_sample_instance(song);
	al_set_sample_instance_playmode(songInstance, ALLEGRO_PLAYMODE_LOOP);

	al_attach_sample_instance_to_mixer(songInstance, al_get_default_mixer());



    srand(time(NULL));

    ChangeState(&state, TITLE);

    /*******************************/
    /**********INITIALIZES**********/
    /*******************************/

    initShip(&ship, shipImage);
    initBullets(bullet, NUM_BULLETS);
    initLasers(laser, NUM_LASERS, l_image);
    initLightening(lights, NUM_LIGHTENINGS, light_image);
    initNear(neary, NUM_NEAREST, near_image);
    initEnemy0(&enemy0, enemyImage[0]);
    initEnemy1(&enemy1, enemyImage[1]);
    initEnemy2(&enemy2, enemyImage[2], m_image);
    initEnemy3(&enemy3, enemyImage[3]);
    initEnemy4(&enemy4, enemyImage[4]);
    initEnemies(enemy, &enemy0, &enemy1, &enemy2, &enemy3, &enemy4, &ship);
    InitMissile(&enemy2, m_image);
    initExplosions(explosions, NUM_EXPLOSIONS, expImage);
    initTransform(tr_ship, NUM_TRANSFORM, tr_ship_image);
    initLevel(level, NUM_LEVEL, level_image);
    initLevel(levelup, NUM_LEVEL, levelup_image);
    initStart(startup, NUM_START, start_image);

	InitBackground(&wp0, 0, 0, 0, 0, 750, 4000, -1, 1, wp0Image);
	InitBackground(&wp1, 0, 0, 0, 3, 750, 1752, -1, 1, wp1Image);
	InitBackground(&wp2, 0, 0, 0, 0.6, 750, 4000, -1, 1, wp2Image);
	InitBackground(&wp3, 0, 0, 0, 0.7, 750, 1885, -1, 1, wp3Image);
	InitBackground(&wp4, 0, 0, 0, 3, 750, 1885, -1, 1, wp4Image);
	InitBackground(&wp5, 0, 0, 0, ship.speed * 2.5, 750, 1885, -1, -1, wp5Image);
	InitBackground(&wp6, 0, 0, 0, 13, 750, 1885, -1, 1, wp6Image);


	font18 = al_load_font("gothic.otf", 18, 0);


    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));

    int bulletTimer = 0;

    al_start_timer(timer);

/*******************************/
    /***********GAME LOOP***********/
    /*******************************/

    while(!done)
    {
        ALLEGRO_EVENT ev;

        al_wait_for_event(event_queue, &ev);


        if (ev.type == ALLEGRO_EVENT_TIMER)
        {
            redraw = true;
            if (keys[UP] && state != AUTOPILOT)
                moveShipUp(&ship);
            else if(keys[DOWN] && state != AUTOPILOT)
                moveShipDown(&ship);
            else if  (state != AUTOPILOT)
                resetShipAnimation(&ship, 1);

            if (keys[LEFT] && state != AUTOPILOT)
                moveShipLeft(&ship);
            else if (keys[RIGHT] && state != AUTOPILOT)
                moveShipRight(&ship);
            else if (state != AUTOPILOT)
                resetShipAnimation(&ship, 2);

            if(state == TITLE)
            {
                startStart(startup, NUM_START, WIDTH/2, HEIGHT/2);
            }
            else if(state == PLAYING || state == AUTOPILOT)
            {

                /*******************************/
                /************UPDATING***********/
                /*******************************/

                UpdateBackground(&wp0);
                UpdateBackground(&wp1);
                UpdateBackground(&wp2);
                UpdateBackground(&wp3);
                UpdateBackground(&wp4);
                UpdateBackground(&wp5);

                initEnemies(enemy, &enemy0, &enemy1, &enemy2, &enemy3, &enemy4, &ship);
                updateExplosions(explosions, NUM_EXPLOSIONS);
                updateBullets(bullet, NUM_BULLETS);
                startEnemies(enemy, NUM_ENEMIES, font18, &ship);
                updateEnemies(enemy, NUM_ENEMIES, font18, &ship);
                AttractMissile(enemy, NUM_ENEMIES, NUM_MISSILES, &ship);
                collisionMissile(enemy, NUM_ENEMIES, NUM_MISSILES, &ship, m_image, &state);
                collisionBullets(bullet, NUM_BULLETS, enemy, NUM_ENEMIES, &ship, explosions, NUM_EXPLOSIONS, &state);
                collisionEnemies(&ship, enemy, NUM_ENEMIES, explosions, NUM_EXPLOSIONS, &state);
                updateTransform(tr_ship, NUM_TRANSFORM);
                updateLevel(level, NUM_LEVEL);
                updateLevel(levelup, NUM_LEVEL);

                /*******************************/
                /**********LEVEL CONTROL********/
                /*******************************/

                if (killed_enemies == 55 && !cnt)
                {
                    fireNear(neary, NUM_NEAREST, &cntNear);
                    ship.image = al_load_bitmap("ally2.png");
                    startTransform(tr_ship, NUM_TRANSFORM, ship.x, ship.y);
                    startLevel(level, NUM_LEVEL, WIDTH/2, HEIGHT/2);
                    startLevel(levelup, NUM_LEVEL, WIDTH/2, HEIGHT/2);
                    ++cnt;
                }
                else if (killed_enemies == 25 && !cnt)
                {
                    fireLightening(lights, NUM_LIGHTENINGS, &cntLight);
                    ship.image = al_load_bitmap("ally1.png");
                    startTransform(tr_ship, NUM_TRANSFORM, ship.x, ship.y);
                    startLevel(level, NUM_LEVEL, WIDTH/2, HEIGHT/2);
                    startLevel(levelup, NUM_LEVEL, WIDTH/2, HEIGHT/2);
                    ++cnt;
                }
                else if (killed_enemies == 90 && !cnt)
                {
                    fireLasers(laser, NUM_LASERS, &cntLaser);
                    ship.image = al_load_bitmap("ally3.png");
                    startTransform(tr_ship, NUM_TRANSFORM, ship.x, ship.y);
                    startLevel(level, NUM_LEVEL, WIDTH/2, HEIGHT/2);
                    startLevel(levelup, NUM_LEVEL, WIDTH/2, HEIGHT/2);
                    ++cnt;
                }
                else if (killed_enemies == 200 && !cnt)
                {
                    startTransform(tr_ship, NUM_TRANSFORM, ship.x, ship.y);
                    startLevel(level, NUM_LEVEL, WIDTH/2, HEIGHT/2);
                    startLevel(levelup, NUM_LEVEL, WIDTH/2, HEIGHT/2);
                    ++cnt;
                }

                if (killed_enemies == 26)
                    cnt = 0;
                else if (killed_enemies == 91)
                    cnt = 0;
                else if (killed_enemies == 56)
                    cnt = 0;
                else if (killed_enemies == 201)
                    cnt = 0;

                /*******************************/
                /**********SKILL CONTROL********/
                /*******************************/

              /* if (killed_enemies > 24 && killed_enemies < 55 && nearTimer > 120))
                {

                    if (cntNear < NUM_NEAREST)
                    {
                        keys[D] = true;
                        if (cntNear < NUM_NEAREST-1)
                            flagNear = true;
                        ++cntNear;

                    }
                    else
                    {
                        flagNear = false;
                    }
                    nearTimer = 0;
                }
                else if (killed_enemies > 54 && killed_enemies < 90 && lightTimer > 120)
                {
                    if (cntLight < NUM_LIGHTENINGS)
                    {
                        keys[D] = true;
                        flagLight = true;
                        ++cntLight;
                    }
                    else
                    {
                        flagLight = false;
                    }
                    lightTimer = 0;
                }
                else if (killed_enemies > 89 && killed_enemies < 200  && laserTimer > 120)
                {
                    if (cntLaser < NUM_LASERS)
                    {
                        keys[D] = true;
                        flagLaser = true;
                        ++cntLaser;
                    }
                    else
                    {
                        flagLaser = false;
                    }
                    laserTimer = 0;
                }*/

                /*******************************/
                /*********UPDATING SKILLS*******/
                /*******************************/

                if (flagLaser == true && cntLaser > -1 && cntLaser < NUM_LASERS)
                {
                    updateLasers(laser, &cntLaser);
                }

                if (flagLight == true && cntLight > -1 && cntLight < NUM_LIGHTENINGS)
                {
                    updateLightening(lights, &cntLight, findMinimumLightening(enemy, NUM_LIGHTENINGS));
                }

                if (flagNear == true && cntNear > -1 && cntNear < NUM_NEAREST)
                {
                    updateNear(neary, &cntNear);
                }

                /*******************************/
                /********COLLISION SKILLS*******/
                /*******************************/

                if (cntLaser != -1)
                {
                    collisionLasers(enemy, NUM_ENEMIES, laser, &cntLaser, &ship, explosions, NUM_EXPLOSIONS, &flagLaser);
                }

                if (cntLight != -1 && flagLight == true && lights[cntLight].curFrame + 1 == lights[cntLight].maxFrame)
                {

                    collisionLightening(enemy, NUM_ENEMIES, lights, &cntLight, &ship, explosions, NUM_EXPLOSIONS, &flagLight, findMinimumLightening(enemy, NUM_LIGHTENINGS));
                }

                if (cntNear != -1 && flagNear == true && neary[cntNear].curFrame + 1 == neary[cntNear].maxFrame)
                {
                    collisionNear(enemy, NUM_ENEMIES, neary, &cntNear, &ship, explosions, NUM_EXPLOSIONS, &flagNear);
                }


                if (bulletTimer > 45)
                {
                    fireBullets(bullet, NUM_BULLETS, &ship);
                    bulletTimer = 0;
                }


                killedenemies = killed_enemies;

            }
            else if(state == LOST)
            {}
            if(state == AUTOPILOT)
            {

                /*******************************/
                /********AUTOPILOT CONTROL******/
                /*******************************/

                if (enemydetected == false)
                {
                   int closest_x, closest_y;

                   if (findClosest(&closest_x, &closest_y, &enemydetected, &the_enemy))
                   {
                        if (enemy[the_enemy].y >= 10)
                        {
                           if (ship.y < 500)
                           {
                               ship.y += ship.speed;
                           }

                           if (enemy[the_enemy].e_bullets[0].y > (ship.y - (ship.boundy * 8))
                               && enemy[the_enemy].e_bullets[0].y < (ship.y + ship.boundy + 5)
                               && the_enemy < NUM_ENEMIES)
                           {

                               if (ship.x < WIDTH / 2)
                               {
                                   if (ship.x - enemy[the_enemy].x < ship.boundx + 5)
                                     ship.x += ship.speed;
                               }
                               else
                               {
                                   if (enemy[the_enemy].x - ship.x < ship.boundx + 5)
                                    ship.x -= ship.speed;
                               }
                           }
                           else
                            {

                                if (ship.x > closest_x)
                                {
                                    if (ship.x != closest_x)
                                    {
                                        ship.x -= ship.speed;

                                        if (ship.x < closest_x)
                                            ship.x += 1;
                                    }
                                }
                                else if (ship.x < closest_x)
                                {
                                    if(ship.x != closest_x)
                                    {
                                        ship.x += ship.speed;

                                        if (ship.x > closest_x)
                                            ship.x += 1;
                                    }

                                }
                            }
                        }
                }
                else
                {

                    if (ship.x < WIDTH / 2)
                    {
                        ship.x += ship.speed;

                        if (ship.x > WIDTH / 2)
                        {
                            while (ship.x != WIDTH / 2)
                            {
                                ship.x -= 1;
                            }
                        }
                    }
                    else if (ship.x > WIDTH / 2)
                    {
                        ship.x -= ship.speed;

                        if (ship.x < WIDTH / 2)
                        {
                            while (ship.x != WIDTH / 2)
                            {
                                ship.x += 1;
                            }
                        }
                    }



                    if (ship.y < HEIGHT / 2)
                    {
                        ship.y += ship.speed;

                        if (ship.y > HEIGHT / 2)
                        {
                            while (ship.y != HEIGHT / 2)
                            {
                                ship.y -= 1;
                            }
                        }
                    }
                    else if (ship.y > HEIGHT / 2)
                    {
                        ship.y -= ship.speed;

                        if (ship.y < HEIGHT / 2)
                        {
                            while (ship.y != HEIGHT / 2)
                            {
                                ship.y += 1;
                            }
                        }
                    }
                }
            }

                /************************************/
                /**SKILL CONTROLS ON AUTOPILOT MODE**/
                /************************************/

                int isenemy = 0;
                for (int i = 0; i < NUM_ENEMIES; ++i)
                {
                    if (enemy[i].live > 0)
                        ++isenemy;
                }
                    if (killed_enemies > 54 && killed_enemies < 90 && (isenemy >= 1) &&
                        (oto_skill_cnt > 120 || (enemy[the_enemy].y < ship.y + ship.boundy*2 && enemy[the_enemy].y > ship.y - ship.boundy*2)))
                    {

                        if (cntNear < NUM_NEAREST)
                        {
                            keys[D] = true;
                            if (cntNear < NUM_NEAREST-1)
                                flagNear = true;
                            ++cntNear;

                        }
                        else
                        {
                            flagNear = false;
                        }
                        oto_skill_cnt = 0;
                    }
                    else if (killed_enemies > 24 && killed_enemies < 55 && oto_skill_cnt > 120 && isenemy >= 1 &&
                        (oto_skill_cnt > 120 || (enemy[the_enemy].y < ship.y + ship.boundy*2 && enemy[the_enemy].y > ship.y - ship.boundy*2)))
                    {
                        if (cntLight < NUM_LIGHTENINGS)
                        {
                            keys[D] = true;
                            flagLight = true;
                            ++cntLight;
                        }
                        else
                        {
                            flagLight = false;
                        }
                        oto_skill_cnt = 0;
                    }
                    else if (killed_enemies > 89 && killed_enemies < 200  && oto_skill_cnt > 120)
                    {
                        if (cntLaser < NUM_LASERS)
                        {
                            keys[D] = true;
                            flagLaser = true;
                            ++cntLaser;
                        }
                        else
                        {
                            flagLaser = false;
                        }
                        oto_skill_cnt = 0;
                    }

               }
            }

        else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            done = true;
        else if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
        {

            /************************************/
            /***STATE CONTROL AND SKILL USAGES***/
            /************************************/

            switch (ev.keyboard.keycode)
            {
            case ALLEGRO_KEY_P:
                if (autoBool == false)
                {
                     ChangeState(&state, AUTOPILOT);
                     autoBool = true;
                }
                else
                {
                    ChangeState(&state, PLAYING);
                    autoBool = false;
                }
                break;
            case ALLEGRO_KEY_T:
                if (highscore == false)
                {
                    ChangeState(&state, SCORETABLE);
                    highscore = true;
                }
                else
                {
                    ChangeState(&state, PLAYING);
                    highscore = false;
                }
                break;
            case ALLEGRO_KEY_ESCAPE:
                done = true;
                break;
            case ALLEGRO_KEY_UP:
                keys[UP] = true;
                break;
            case ALLEGRO_KEY_DOWN:
                keys[DOWN] = true;
                break;
            case ALLEGRO_KEY_LEFT:
                keys[LEFT] = true;
                break;
            case ALLEGRO_KEY_RIGHT:
                keys[RIGHT] = true;
                break;
            case ALLEGRO_KEY_SPACE:
                keys[SPACE] = true;
                if (state == TITLE)
                    ChangeState(&state, PLAYING);
                else if (state == LOST)
                    ChangeState(&state, PLAYING);
                break;
            case ALLEGRO_KEY_D:
                if (state == PLAYING)
                {
                    if (killed_enemies > 54 && killed_enemies < 90)
                    {
                        if (cntNear < NUM_NEAREST)
                        {
                            keys[D] = true;
                            if (cntNear < NUM_NEAREST-1)
                                flagNear = true;
                            ++cntNear;
                        }
                        else
                        {
                            flagNear = false;
                        }
                    }
                    else if (killed_enemies > 24 && killed_enemies < 55)
                    {
                        if (cntLight < NUM_LIGHTENINGS)
                        {
                            keys[D] = true;
                            flagLight = true;
                            ++cntLight;
                        }
                        else
                        {
                            flagLight = false;
                        }
                    }
                    else if (killed_enemies > 89 && killed_enemies < 200)
                    {
                        if (cntLaser < NUM_LASERS)
                        {
                            keys[D] = true;
                            flagLaser = true;
                            ++cntLaser;
                        }
                        else
                        {
                            flagLaser = false;
                        }
                    }
                }
            break;
            }
        }

        else if (ev.type == ALLEGRO_EVENT_KEY_UP)
        {
            switch (ev.keyboard.keycode)
            {
            case ALLEGRO_KEY_ESCAPE:
                done = true;
				break;
            case ALLEGRO_KEY_UP:
                keys[UP] = false;
                break;
            case ALLEGRO_KEY_DOWN:
                keys[DOWN] = false;
                break;
            case ALLEGRO_KEY_LEFT:
                keys[LEFT] = false;
                break;
            case ALLEGRO_KEY_RIGHT:
                keys[RIGHT] = false;
                break;
			case ALLEGRO_KEY_SPACE:
				keys[SPACE] = false;
				break;
            case ALLEGRO_KEY_D:
                keys[D] = false;
                break;

            }
        }

        /*******************************/
        /************RENDERING**********/
        /*******************************/

        if(redraw && al_is_event_queue_empty(event_queue))
		{
			redraw = false;

            if(state == TITLE)
            {
                updateStart(startup, NUM_START);
                drawStart(startup, NUM_START);

            }
            else if(state == PLAYING || state == AUTOPILOT)
            {
               DrawBackground(&wp0);
               DrawBackground(&wp1);
               DrawBackground(&wp2);
               DrawBackground(&wp3);
               DrawBackground(&wp4);
               DrawBackground(&wp5);

                drawLevel(level, NUM_LEVEL);
                drawLevel(levelup, NUM_LEVEL);
                drawTransform(tr_ship, NUM_TRANSFORM);
                drawShip(&ship);
                drawBullets(bullet, NUM_BULLETS);
                drawEnemies(enemy, NUM_ENEMIES, font18);
                DrawMissile(enemy, NUM_ENEMIES, NUM_MISSILES);
                drawExplosions(explosions, NUM_EXPLOSIONS);

               if (flagLaser == true && cntLaser > -1)
               {
                    drawLasers(laser, NUM_LASERS, &cntLaser, &flagLaser);
               }
               if (flagLight == true && cntLight > -1)
               {
                   drawLightening(lights, NUM_LIGHTENINGS, &cntLight, &flagLight);
               }
               if (flagNear == true && cntNear > -1)
               {
                   drawNear(neary, NUM_NEAREST, &cntNear, &flagNear);
               }

                al_draw_textf(font18, al_map_rgb(125, 249, 255), 70, 20, ALLEGRO_ALIGN_CENTRE, "lives : %i", ship.lives);
                al_draw_textf(font18, al_map_rgb(125, 249, 255), 70, 40, ALLEGRO_ALIGN_CENTRE, "your score : %i", ship.score);
                al_draw_textf(font18, al_map_rgb(125, 249, 255), 70, 60, ALLEGRO_ALIGN_CENTRE, "killed enemies : %i", killed_enemies);
            }
            else if(state == LOST)
            {
                /*******************************/
                /************GETS NAME**********/
                /*******************************/
                for (int a = 0; a < USERNAME && deneme1 == false; ++a){
                    if (a == USERNAME-1)
                        deneme1 = true;
                    player1.name[a] = -1;
                    player1_write.name[a] = 0;
                }

                while(!quit)
                {
                     al_clear_to_color(al_map_rgb_f(0, 0, 0));
                     al_draw_ustr(font, al_map_rgb_f(1, 1, 1), 400, 300, ALLEGRO_ALIGN_CENTRE, str);
                     al_flip_display();

                     ALLEGRO_EVENT e;
                     al_wait_for_event(q, &e);
                     switch(e.type)
                     {
                       case ALLEGRO_EVENT_DISPLAY_CLOSE:
                         quit = true;
                         break;

                       case ALLEGRO_EVENT_KEY_CHAR:
                         if(e.keyboard.unichar >= 32)
                         {
                            letter = e.keyboard.unichar;
                            access = (char *)&letter;
                            player1.name[i] = *access;
                            ++i;
                           while (text)
                           {
                                if(al_ustr_prev(str, &pos))
                                    al_ustr_truncate(str, pos);
                                --text;
                           }
                           pos += al_ustr_append_chr(str, e.keyboard.unichar);

                         }
                         else if(e.keyboard.keycode == ALLEGRO_KEY_BACKSPACE)
                         {
                           if(al_ustr_prev(str, &pos))
                             al_ustr_truncate(str, pos);
                         }
                         else if(e.keyboard.keycode == ALLEGRO_KEY_ENTER)
                         {
                             quit = true;
                         }
                         break;
                    }
                }
                player1.name[i] = '_';

                if (!file_flag)
                {
                    file_flag = true;

                    fp = al_fopen("scoretable_game.txt", "a");

                    if (!fp)
                        printf("dosya acilamadi\n");
                    else
                        printf("dosya acildi yazmak icin\n");

                    itoa(ship.score, (player1.name + i + 1), 10);

                for (int a = 0; a < USERNAME && deneme2 == false; ++a)
                {
                    if (a == USERNAME-1)
                        deneme2 = true;
                }
                    al_fputs(fp, player1.name);

                    al_fclose(fp);

                    fp2 = al_fopen("scoretable_game.txt", "r");

                    if (!fp2)
                        printf("dosya acilamadi\n");
                    else
                        printf("dosya acildi okumak icin\n");

                    ch = al_fgetc(fp2);
                    int i = 0, k = 0;
                    while(ch != EOF)
                    {
                        while (ch != EOF && ch != 10)
                        {
                            list2[i][k] = ch;
                            ++k;
                            ch = al_fgetc(fp);
                        }
                        al_draw_textf(font18, al_map_rgb(255, 0, 0), 170, row, ALLEGRO_ALIGN_CENTRE, "%s\n", player1_write.name);
                        k = 0;
                        row += 10;
                        ++i;
                        list_cnt = 0;
                        ch = al_fgetc(fp);
                    }
                    i = 0;

                }
            }

            al_flip_display();
            al_clear_to_color(al_map_rgb(0, 0, 0));

		}

		++bulletTimer;
		++laserTimer;
		++lightTimer;
		++nearTimer;
		++oto_skill_cnt;
    }


    al_destroy_bitmap(title);
	al_destroy_bitmap(lost);
    al_destroy_bitmap(expImage);
    al_destroy_bitmap(enemyImage[0]);
    al_destroy_bitmap(enemyImage[1]);
    al_destroy_bitmap(enemyImage[2]);
    al_destroy_bitmap(m_image);
    al_destroy_bitmap(shipImage);
	al_destroy_event_queue(event_queue);
	al_destroy_timer(timer);
	al_destroy_font(font18);
	al_destroy_display(display);
	al_destroy_bitmap(l_image);
	al_destroy_bitmap(light_image);
	al_destroy_bitmap(wp1Image);
	al_destroy_bitmap(wp2Image);
	al_destroy_bitmap(wp3Image);
	al_destroy_bitmap(wp4Image);
	al_destroy_bitmap(wp5Image);
	al_destroy_bitmap(tr_ship_image);

	al_destroy_sample(shot);
	al_destroy_sample(near_skill);
	al_destroy_sample(light_skill);
	al_destroy_sample(laser_skill);
	al_destroy_sample(shooted);
	al_destroy_sample(collision);
	al_destroy_sample(bomb);
	al_destroy_sample_instance(songInstance);

    return 0;
}


void collisionBullets(Bullets bullet[], int bsize, Enemies enemy[], int esize, SpaceShip *ship, Explosion explosions[], int expsize, int *state)
{
    for (int i = 0; i < bsize; ++i)
    {
        if (bullet[i].live)
        {
            for (int j = 0; j < esize; ++j)
            {
                if (enemy[j].live)
                {
                    if ((bullet[i].x > (enemy[j].x - enemy[j].boundx)) && (bullet[i].x < (enemy[j].x + enemy[j].boundx))
                    && (bullet[i].y > enemy[j].y - enemy[j].boundy) && (bullet[i].y < (enemy[j].y + enemy[j].boundy)))
                    {
                        bullet[i].live = false;
                        enemy[j].live--;
                        al_play_sample(collision, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
                        if (enemy[j].live == 0)
                        {
                            ++killed_enemies;
                            if (enemy[j].ID == ENEMY0)
                                ship->score += ENEMY0_HEALTH;
                            else if (enemy[j].ID == ENEMY1)
                                ship->score += ENEMY1_HEALTH;
                            else if (enemy[j].ID == ENEMY2)
                                ship->score += ENEMY2_HEALTH;
                            else if (enemy[j].ID == ENEMY3)
                                ship->score += ENEMY3_HEALTH;
                            else if (enemy[j].ID == ENEMY4)
                                ship->score += ENEMY4_HEALTH;
                        }
                        startExplosions(explosions, expsize, bullet[i].x, bullet[i].y);
                    }
                }
            }
        }
    }

    for (int i = 0; i < esize; ++i)
    {
        if (enemy[i].e_bullets[0].live && ship->lives > 0)
        {
            if ((enemy[i].e_bullets[0].x > (ship->x - ship->boundx)) && (enemy[i].e_bullets[0].x < (ship->x + ship->boundx))
                && (enemy[i].e_bullets[0].y > ship->y - ship->boundy) && (enemy[i].e_bullets[0].y < (ship->y + ship->boundy)))
            {
                enemy[i].e_bullets[0].live = false;
                al_play_sample(shooted, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
                --ship->lives;
                startExplosions(explosions, expsize, ship->x, ship->y);
            }
            if (ship->lives <= 0)
                ChangeState(state, LOST);
        }
    }
}


void collisionEnemies(SpaceShip *ship, Enemies enemy[], int esize, Explosion explosions[], int expSize, int *state)
{
    for (int i = 0; i < esize; ++i)
    {
        if (enemy[i].live)
        {
            if ( ( (enemy[i].x - enemy[i].boundx) < (ship->x+ship->boundx) ) && ((enemy[i].y + enemy[i].boundy) > (ship->y - ship->boundy))
                  && ( (enemy[i].y - enemy[i].boundy) < (ship->y + ship->boundy) ) && ( (enemy[i].x+enemy[i].boundx) > (ship->x-ship->boundx) )  )
            {
                al_play_sample(shooted, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
                ship->lives--;
                enemy[i].live--;
                startExplosions(explosions, expSize, ship->x, ship->y);
                if (ship->lives <= 0)
                    ChangeState(state, LOST);
            }
            else if (enemy[i].y > HEIGHT)
            {
                enemy[i].live = 0;
            }
        }
    }
}


void ChangeState(int *state, int newState)
{
	if(*state == TITLE)
	{}
	else if(*state == PLAYING)
	{
        al_stop_sample_instance(songInstance);
	}
	else if(*state == LOST)
	{}
	else if(*state == SCORETABLE)
	{}

	*state = newState;

	if(*state == TITLE)
	{}
	else if(*state == PLAYING)
	{}
	else if(*state == LOST)
	{}
	else if(*state == SCORETABLE)
	{}
}


int findClosest(int *x, int *y, boole *enemydetected, int *the_enemy)
{
    int closest = NUM_ENEMIES, distance, curDistance;

    for (closest = 0; closest < NUM_ENEMIES; ++closest)
        if (enemy[closest].live > 0)
            break;

    if (closest != NUM_ENEMIES)
    {
        curDistance = ((ship.x - enemy[closest].x) * (ship.x - enemy[closest].x)) + ((ship.y - enemy[closest].y) * (ship.y - enemy[closest].y));

        for (int i = 0; i < NUM_ENEMIES; ++i)
        {
            if ((enemy[i].y > 0) && (enemy[i].x > 0) && (enemy[i].live > 0))
            {
                distance = ( (ship.x - enemy[i].x) * (ship.x - enemy[i].x) ) + ( (ship.y - enemy[i].y) * (ship.y - enemy[i].y) );

                if (distance < curDistance)
                {
                    curDistance = distance;
                    closest = i;
                }

            }
        }

        *x = enemy[closest].x;
        *y = enemy[closest].y;

        if (*the_enemy != NUM_ENEMIES) //the_enemy != NUM_ENEMIES idi
            *the_enemy = closest;

        if (enemy[*the_enemy].live == false && *the_enemy != NUM_ENEMIES)
            *enemydetected = true;
    }

    return (closest == NUM_ENEMIES) ? 0 : 1;
}
