#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdio.h>

#include "config.h"

//prototipos nave mia 
typedef struct{
    float (*nave_pos)[2];
    size_t nave_tam;
    float (*chorro_pos)[2];
    size_t chorro_tam;
    bool chorro_start;
    float vel_x;
    float vel_y;
}nave_t;


void update_state(nave_t *nave, float t_lapse, float acc, bool chorro_state){
    nave->chorro_start = chorro_state;
    float new_vel_y = nave->vel_y - acc * t_lapse; 
    for(size_t i = 0; i < nave->nave_tam; i++){
        nave->nave_pos[i][1] -= new_vel_y * t_lapse;
    }
    for(size_t i = 0; i < nave->chorro_tam; i++){
        nave->chorro_pos[i][1] -= new_vel_y * t_lapse;
    }
}



void drawNave(nave_t *nave, SDL_Renderer *renderer, float f){

 // Dibujamos la nave escalada por f en el centro de la pantalla:
    SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0x00, 0x00);
    for(int i = 0; i < nave->nave_tam - 1; i++){
		SDL_RenderDrawLine(
        renderer,
        nave->nave_pos[i][0] * f + VENTANA_ANCHO / 2,		
        -nave->nave_pos[i][1] * f + VENTANA_ALTO / 2, 		
        nave->nave_pos[i+1][0] * f + VENTANA_ANCHO / 2,		
        -nave->nave_pos[i+1][1] * f + VENTANA_ALTO / 2 		
        );
	}

    if(nave->chorro_start) {
            // Dibujamos el chorro escalado por f en el centro de la pantalla:
            SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0x00, 0x00);
            for(int i = 0; i < nave->chorro_tam - 1; i++){
				SDL_RenderDrawLine(
                    renderer,
                    nave->chorro_pos[i][0] * f + VENTANA_ANCHO / 2,
                    -nave->chorro_pos[i][1] * f + VENTANA_ALTO / 2, 
                    nave->chorro_pos[i+1][0] * f + VENTANA_ANCHO / 2,
                    -nave->chorro_pos[i+1][1] * f + VENTANA_ALTO / 2 
                );
			}
        }


}







int main() {
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Event event;

    SDL_CreateWindowAndRenderer(VENTANA_ANCHO, VENTANA_ALTO, 0, &window, &renderer);
    SDL_SetWindowTitle(window, "Gravitar");

    int dormir = 0;

    // BEGIN código del alumno

	//delta frame x e y desplazamiento y giro
	float frame_desp = 0;
	int angulos_girados = 0;
    
	// time global
	float time_lapse = 1.0f/JUEGO_FPS;
    float time_global = 0;
	
	// Mi nave:
    float puntos[][2]= {{8, 0}, {-1, 6}, {-4, 4}, {-4, 2}, {-2, 0}, {-4, -2}, {-4, -4}, {-1, -6}, {8, 0}};
    size_t nave_tamanio = 9;

	int rapidez_ang = 5;

	int angulo_nave = 0;

    // El chorro de la nave:
    float chorro [][2]= {{-4, 2}, {-8, 0}, {-4, -2}};
    size_t chorro_tamanio = 3;
    bool chorro_prendido = false;

    //// BUILD NAVE
    nave_t nave = {puntos, nave_tamanio, chorro, chorro_tamanio, chorro_prendido, 0, 0};



    // Queremos que todo se dibuje escalado por f:
    float f = 3;


	//
	//test objeto inmovil
		float test[][2] = {{0, 0},{-2, 0},{-4, 0}};
		size_t test_tam = 3;
    // END código del alumno

    unsigned int ticks = SDL_GetTicks();
    while(1) {
        if(SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT)
                break;
            // BEGIN código del alumno
            
			if (event.type == SDL_KEYDOWN) {
                // Se apretó una tecla
                switch(event.key.keysym.sym) {
                    case SDLK_UP:
                        // Prendemos el chorro:
                        chorro_prendido = true;
						//componentes_segun_angulo(angulo_nave, &dseek_x, &dseek_y);
						break;
                    case SDLK_DOWN: //para recojer barriles
						break;
                    case SDLK_RIGHT:
						/*
                        rotar_nave(nave, nave_tam, -rapidez_ang);
						rotar_nave(chorro,chorro_tam, -rapidez_ang);
						angulos_girados += rapidez_ang;
						*/
                        break;
                    case SDLK_LEFT:
						/*
                        rotar_nave(nave, nave_tam, rapidez_ang);
						rotar_nave(chorro, chorro_tam, rapidez_ang);
						angulos_girados += rapidez_ang;
                    	*/
                        break;
					case SDLK_ESCAPE:
						return 1;
                }
            }
            else if (event.type == SDL_KEYUP) {
                // Se soltó una tecla
                switch(event.key.keysym.sym) {
                    case SDLK_UP:
                        // Apagamos el chorro:
                        chorro_prendido = false;
                        break;
					case SDLK_RIGHT:
						/*
                        angulo_nave = angulo_rotado(angulo_nave, -angulos_girados);
						rotar_nave(test, test_tam, -angulos_girados);
				        angulos_girados = 0;
						*/
                        break;
					case SDLK_LEFT:
						/*
                        angulo_nave = angulo_rotado(angulo_nave, angulos_girados);
						rotar_nave(test, test_tam, angulos_girados);
						angulos_girados = 0;
						*/
                        break;
                }
            }
            // END código del alumno
            continue;
        }

        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00); // fondo
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0x00);

        // BEGIN código del alumno
        
        time_global += time_lapse; 

		update_state(&nave, time_global, -(float)G/JUEGO_FPS, chorro_prendido);
        printf("t_lapse: %.5f\t %.5f\n",time_global,nave.nave_pos[0][1]);
        drawNave(&nave, renderer, f);

		/*
		SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0x00);
		for(int i = 0; i < test_tam - 1; i++){
			SDL_RenderDrawLine(
				renderer,
				test[i][0] * f + seek_point_x,
                -test[i][1] * f + seek_point_y,
                test[i+1][0] * f + seek_point_x,
                -test[i+1][1] * f + seek_point_y
			);
		}
	    */
        
        // END código del alumno

        SDL_RenderPresent(renderer);
        ticks = SDL_GetTicks() - ticks;
        if(dormir) {
            SDL_Delay(dormir);
            dormir = 0;
        }
        else if(ticks < 1000 / JUEGO_FPS)
            SDL_Delay(1000 / JUEGO_FPS - ticks);
        ticks = SDL_GetTicks();
    }

    // BEGIN código del alumno
    // No tengo nada que destruir.
    // END código del alumno

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();
    return 0;
}

