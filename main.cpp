#include <iostream>

#include <allegro5/allegro.h>
#include "allegro5/allegro_image.h"
#include "allegro5/allegro_native_dialog.h"
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <vector>
//#include <Highscores.h>
using namespace std;

ALLEGRO_DISPLAY *display = NULL;
ALLEGRO_EVENT_QUEUE *event_queue = NULL;
//ALLEGRO_MAP *mapa = al_open_map("/tmx", "lab.tmx");
//al_draw_map(mapa, 0, 0, 0); // (map, dx, dy, flags)

//EVENTOS Y TIMERS
ALLEGRO_EVENT ev;
ALLEGRO_TIMEOUT timeout;
ALLEGRO_TIMER *timer = NULL;
ALLEGRO_SAMPLE_INSTANCE *songInstance;

//Elementos Generales
vector<ALLEGRO_BITMAP*> blobs;

ALLEGRO_SAMPLE *music = NULL;
ALLEGRO_SAMPLE_ID imusic;
ALLEGRO_SAMPLE *effect = NULL;
ALLEGRO_SAMPLE_ID ieffect;
ALLEGRO_SAMPLE *game = NULL;
ALLEGRO_SAMPLE_ID igame;

ALLEGRO_KEYBOARD_STATE keystate;

int width = 400, height = 400, FPS = 30, seconds=1, timer2=0, moveSpeed=5, x=0, y=0, blob=0;

int initAllegro()
{
    if(!al_init())
    {
        cout<<"failed to initialize allegro!\n"<<endl;
        return -1;
    }

    if(!al_init_image_addon())
    {
        cout<<"Error: Failed to initialize al_init_image_addon!"<<endl;
        return -1;
    }

    display = al_create_display(width, height);
    if(!display)
    {
        cout<<"failed to create display!\n"<<endl;
        return -1;
    }

    event_queue = al_create_event_queue();
    if(!event_queue)
    {
        cout<<"failed to create event_queue!\n"<<endl;
        al_destroy_display(display);
        return -1;
    }

    timer = al_create_timer(1.0 / FPS);
    if(!timer)
    {
        cout<<"failed to create timer!"<<endl;
    }

    if(!al_install_keyboard())
    {
        cout<<"failed to initialize the keyboard!"<<endl;
    }

    if(!al_install_audio() || !al_init_acodec_addon() || !al_reserve_samples(2))
    {
        cout<<"failed to initialize Audio!"<<endl;
    }

    al_init_font_addon(); // initialize the font addon
    al_init_ttf_addon();// initialize the ttf (True Type Font) addon
    cout<<"Llego aki";
//    cartoonFont = al_load_ttf_font("GameFiles/fonts/kenpixel_blocks.ttf",50,0 );


    al_register_event_source(event_queue, al_get_display_event_source(display));//registrar eventos del display
    al_register_event_source(event_queue, al_get_timer_event_source(timer));//registrar eventos del timer
    al_register_event_source(event_queue, al_get_keyboard_event_source());//registrar eventos del teclado

    al_start_timer(timer);
    al_init_timeout(&timeout, 0.06);
}

int main()
{
    initAllegro();

    music=al_load_sample("music.wav");
    effect=al_load_sample("soundeffect.wav");
    songInstance=al_create_sample_instance(music);
    al_set_sample_instance_playmode(songInstance, ALLEGRO_PLAYMODE_LOOP);
    al_attach_sample_instance_to_mixer(songInstance, al_get_default_mixer());
    al_play_sample_instance(songInstance);


    blobs.push_back(al_load_bitmap("blob/green1.png"));
    blobs.push_back(al_load_bitmap("blob/green2.png"));
    blobs.push_back(al_load_bitmap("blob/green3.png"));
    blobs.push_back(al_load_bitmap("blob/green4.png"));

    while(true)
    {
        bool get_event = al_wait_for_event_until(event_queue, &ev, &timeout);

//            al_get_keyboard_state(&keystate);

        if(ev.type == ALLEGRO_EVENT_TIMER)
        {
            al_clear_to_color(al_map_rgb(150,0,255));
            timer2++;
            if(timer2==60)
            {
                cout<<seconds++<<endl;
                timer2=0;
            }
            if(timer2%10==0)
            {
                blob++;
            }
        }
        if(get_event && ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
        {
            break;
        }
        if(ev.keyboard.keycode == ALLEGRO_KEY_RIGHT)
        {
            x+=moveSpeed;
        }
        if(ev.keyboard.keycode == ALLEGRO_KEY_LEFT)
        {
            x-=moveSpeed;
        }
        if(ev.keyboard.keycode == ALLEGRO_KEY_UP)
        {
            y-=moveSpeed;
        }
        if(ev.keyboard.keycode == ALLEGRO_KEY_DOWN)
        {
            y+=moveSpeed;
        }

        if(x>=300)
        {
            al_play_sample(effect, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
            x-=moveSpeed;
        }
        if(x<0)
        {
            al_play_sample(effect, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
            x+=moveSpeed;
        }
        if(y>=300)
        {
            al_play_sample(effect, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
            y-=moveSpeed;
        }
        if(y<0)
        {
            al_play_sample(effect, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
            y+=moveSpeed;
        }


        if(blob==4)
            blob=0;

        al_draw_bitmap(blobs[blob], x, y,100);
        al_flip_display();

    }
    return 0;
}
