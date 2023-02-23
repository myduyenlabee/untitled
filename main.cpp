#include <iostream>
#include <math.h>
#include <SDL.h>

using namespace std;
SDL_Window *_window;
SDL_Renderer *_renderer;
SDL_Color white = {255, 255, 255};
SDL_bool _inSampleRect=SDL_FALSE;
int _width = 1200;
int _height = 600;

//Button constants
const int BUTTON_WIDTH = 300;
const int BUTTON_HEIGHT = 200;
const int TOTAL_BUTTONS = 4;

enum LButtonSprite
{
    BUTTON_SPRITE_MOUSE_OUT = 0,
    BUTTON_SPRITE_MOUSE_OVER_MOTION = 1,
    BUTTON_SPRITE_MOUSE_DOWN = 2,
    BUTTON_SPRITE_MOUSE_UP = 3,
    BUTTON_SPRITE_TOTAL = 4
};
//The mouse button
class LButton
{
public:
    //Initializes internal variables
    LButton();

    //Sets top left position
    void setPosition( int x, int y );

    //Handles mouse event
    void handleEvent( SDL_Event* e );

    //Shows button sprite
    void render();

private:
    //Top left position
    SDL_Point mPosition;

    //Currently used global sprite
    LButtonSprite mCurrentSprite;
};
LButton gButtons[ TOTAL_BUTTONS ];

LButton::LButton()
{
    mPosition.x = 0;
    mPosition.y = 0;

    mCurrentSprite = BUTTON_SPRITE_MOUSE_OUT;
}

void LButton::setPosition( int x, int y )
{
    mPosition.x = x;
    mPosition.y = y;
}

void LButton::handleEvent( SDL_Event* e )
{
    //If mouse event happened
    if( e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP )
    {
        //Get mouse position
        int x, y;
        SDL_GetMouseState( &x, &y );

        //Check if mouse is in button
        bool inside = true;

        //Mouse is left of the button
        if( x < mPosition.x )
        {
            inside = false;
        }
            //Mouse is right of the button
        else if( x > mPosition.x + BUTTON_WIDTH )
        {
            inside = false;
        }
            //Mouse above the button
        else if( y < mPosition.y )
        {
            inside = false;
        }
            //Mouse below the button
        else if( y > mPosition.y + BUTTON_HEIGHT )
        {
            inside = false;
        }

        //Mouse is outside button
        if( !inside )
        {
            mCurrentSprite = BUTTON_SPRITE_MOUSE_OUT;
        }
            //Mouse is inside button
        else
        {
            //Set mouse over sprite
            switch( e->type )
            {
                case SDL_MOUSEMOTION:
                    mCurrentSprite = BUTTON_SPRITE_MOUSE_OVER_MOTION;
                    break;

                case SDL_MOUSEBUTTONDOWN:
                    mCurrentSprite = BUTTON_SPRITE_MOUSE_DOWN;
                    break;

                case SDL_MOUSEBUTTONUP:
                    mCurrentSprite = BUTTON_SPRITE_MOUSE_UP;
                    break;
            }
        }
    }
}

//void LButton::render()
//{
//    //Show current button sprite
//    gButtonSpriteSheetTexture.render( mPosition.x, mPosition.y, &gSpriteClips[ mCurrentSprite ] );
//}

SDL_Rect _sampleRect = {.x = 10, .y = 10, .w = 100, .h = 100};
void init_sdl()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        cout << "[Error] SDL Init : %s\n";
        SDL_GetError();
    } else {
        cout << "SDL INITIALISED\n";
        SDL_DisplayMode dm;
        SDL_GetCurrentDisplayMode(0, &dm);

        cout << "Display mode is %dx%dpx @ %dhz\n"; dm.w; dm.h; dm.refresh_rate;
    }
}
void hinhChuNhatDay(int x, int y, int w,int h){
    SDL_Rect filled_rect{.x=x,.y=y,.w=w,.h=h};
    SDL_RenderFillRect(_renderer, &filled_rect);
}
void hinhChuNhat(int x, int y, int w,int h){
    SDL_Rect drawline_rect{.x=x,.y=y,.w=w,.h=h};
    SDL_RenderDrawRect(_renderer,&drawline_rect);
}
void init_window_and_renderer()
{
    if (SDL_CreateWindowAndRenderer(_width, _height, SDL_WINDOW_SHOWN, &_window, &_renderer) != 0) {
        cout << "[Error] Creating Window and Renderer: %s\n"; SDL_GetError();
        exit(0);
    } else {
        cout << "Created Window and Renderer %dx%d\n", _width, _height;
    }
}
//void handle_mouse_drag(SDL_Event e)
//{
//    if (e.type == SDL_MOUSEBUTTONDOWN) {
//        // Point where mouse button down occurs
//        SDL_Point p = {.x = e.motion.x, .y = e.motion.y};
//
//        if (SDL_PointInRect(&p, &_sampleRect)) {
//            _inSampleRect = SDL_TRUE;
//        }
//    }
//
//    if (e.type == SDL_MOUSEBUTTONUP && _inSampleRect == SDL_TRUE) {
//        _inSampleRect = SDL_FALSE;
//    }
//
//    if (e.type == SDL_MOUSEMOTION && _inSampleRect == SDL_TRUE) {
//        _sampleRect.x += e.motion.xrel;
//        _sampleRect.y += e.motion.yrel;
//    }
//}
void main_loop()
{
    SDL_bool loop = SDL_TRUE;
    SDL_Event event;

    while (loop) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                loop = SDL_FALSE;
            } else if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        loop = SDL_FALSE;
                        break;
                    default:
                        loop = SDL_TRUE;
                }
            }
              //handle_mouse_drag(event);
        }

        SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 0);
        SDL_RenderClear(_renderer);

        for(int i=0;i<5;i++){
            SDL_SetRenderDrawColor(_renderer, 255, 228, 225, 1);
            hinhChuNhatDay(10+(185*i),10,150,100);
        }
        SDL_SetRenderDrawColor(_renderer, 127, 255, 212, 1);
        hinhChuNhatDay(10,120,_width-20,_height-130);
        SDL_SetRenderDrawColor(_renderer, 69, 139, 116, 1);
        hinhChuNhatDay(60,150,_width-140,_height-560);
        for(int i=0;i<3;i++){
            SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 0);
            hinhChuNhat(60+(120*i*sqrt(i)),150,_width-(140+2*120*i*sqrt(i)),_height-560);
        }
        for(int i=0;i<3;i++){
            SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 0);
            hinhChuNhat(60+(120*i*sqrt(i)),190,_width-(140+2*120*i*sqrt(i)),_height-280);
        }
        SDL_SetRenderDrawColor(_renderer,255,48,48,1);
        hinhChuNhatDay(_width-30,0,30,30);
        for( int i = 0; i < TOTAL_BUTTONS; ++i )
        {
            gButtons[ i ].render();
        }
        SDL_RenderPresent(_renderer);
        SDL_Delay(10);
    }

}

int main(int argv, char** args)
{
    init_sdl();

    init_window_and_renderer();

    SDL_RenderPresent(_renderer);
    SDL_Delay(1000);
    main_loop();
    SDL_DestroyWindow(_window);
    SDL_Quit();
    exit(0);
}