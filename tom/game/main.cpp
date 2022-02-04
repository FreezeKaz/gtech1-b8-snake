#define SIZE 35
#define PAS 35 //sizeof my snake and also the constant that i'll use to draw my board and define the size of my window
#define UP 0
#define DOWN 1
#define RIGHT 2
#define LEFT 3


#include "window.hpp"
#include "snake.hpp"
#include "segment.hpp"
#include "window.cpp"
#include "snake.cpp"
#include "segment.cpp"
#include "playground.cpp"
#include "playground.hpp"



#include <SDL2/SDL.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>




Game window;
int game = true;
int rgb = true;


int direction(int direction)
{
    const Uint8 *state = SDL_GetKeyboardState(NULL);
    if (state[SDL_SCANCODE_W] && direction != DOWN) 
    {
        direction = UP;

    }
    else if (state[SDL_SCANCODE_S] && direction != UP) 
    {
        direction = DOWN;

    }
    else if (state[SDL_SCANCODE_D] && direction != LEFT) 
    {
        direction = RIGHT;

    }
    else if (state[SDL_SCANCODE_A] && direction != RIGHT) 
    {
        direction = LEFT;

    }
    return direction;
}


int main(){
    
    int dir = UP;
    int frame_rate_ms = 60;
    int timer = 0;
    int frame_delay,snake_status;
    Uint32 frame_start;

    Uint32 iter;

    window.init("Snake",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,PAS*SIZE,PAS*SIZE,false);
    SDL_SetRenderDrawColor(window.getRenderer(),255,255,255,SDL_ALPHA_OPAQUE);
    Snake *snake = new Snake(3,RIGHT);
    Playground *playground = new Playground();
    //std::cout << "Bein" << std::endl;

    do{
        frame_start = SDL_GetTicks();

        SDL_Event event;
        if (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
            window.clean();
            break;
            }
        }

        
        dir = direction(dir);
        snake->turnSnake(dir);

        const Uint8 *state = SDL_GetKeyboardState(NULL);
        if (state[SDL_SCANCODE_C]) 
        {
            snake->growBack();
        }    

      /*  if (rgbtrigger == true)
        {
            timer = 100;
            rgbtrigger = false;
            
        }
        if (timer > 0){

        }*/
        SDL_SetRenderDrawColor(window.getRenderer(),0,0,0,SDL_ALPHA_OPAQUE);
        SDL_RenderClear(window.getRenderer());
        SDL_SetRenderDrawColor(window.getRenderer(),255,255,255,SDL_ALPHA_OPAQUE);
        playground->create(window.getRenderer());
        snake->print(window.getRenderer(),rgb);
        window.update();;
            

        frame_delay = frame_rate_ms - (SDL_GetTicks() - frame_start);
        if (frame_delay > 0)
            SDL_Delay(frame_delay);
            snake->move();
        if (frame_delay > frame_rate_ms)
            printf("WARNING: frame rate drop: %d ms\n", frame_delay - frame_rate_ms);


        // Get the next event

        iter++;
    }while (snake->collisionMur() == false && snake->collisionSnake() == false);
    
    return 0;
}
