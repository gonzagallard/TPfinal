#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdio.h>

#include "config.h"
#include "nave.h"

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
	int frame_giro = 0;
    
	// time global
	float time_global = 0;
	float time_global_lapse = 1 / JUEGO_FPS;
	
	// Mi nave:
    size_t nave_tam = 9;

	int rapidez_ang = 15;

	int angle_nave = 0;

    // El chorro de la nave:
    size_t chorro_tam = 3;

    bool chorro_prendido = false;

	//centro de rotacion y seguimiento de la nave
	float seek_point_x = VENTANA_ANCHO / 2;
	float seek_point_y = VENTANA_ALTO / 2;

    // Queremos que todo se dibuje escalado por f:
    float f = 5;


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
			
			time_global += time_global_lapse;   //tiempo independiente, accion  de la gravedad
            
			if (event.type == SDL_KEYDOWN) {
                // Se apretó una tecla
                switch(event.key.keysym.sym) {
                    case SDLK_UP:
                        // Prendemos el chorro:
                        chorro_prendido = true;
						frame_desp++;
                        break;
                    case SDLK_DOWN: //para recojer barriles
						break;
                    case SDLK_RIGHT:
						rotar_nave(nave, nave_tam, -rapidez_ang);
						rotar_nave(chorro,chorro_tam, -rapidez_ang);
						frame_giro += rapidez_ang;
						printf("##%d\n",frame_giro);
						break;
                    case SDLK_LEFT:
						rotar_nave(nave, nave_tam, rapidez_ang);
						rotar_nave(chorro, chorro_tam, rapidez_ang);
						frame_giro += rapidez_ang;
						printf("##%d\n",frame_giro);
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
						angle_nave = angulo_rotado(angle_nave, -frame_giro);
						printf("%d\n",angle_nave);
						rotar_nave(test, test_tam, -frame_giro);
						frame_giro = 0;
						break;
					case SDLK_LEFT:
						angle_nave = angulo_rotado(angle_nave, frame_giro);
						printf("%d\n",angle_nave);
						rotar_nave(test, test_tam, frame_giro);
						frame_giro = 0;
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
		
		
		SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0x00);
		for(int i = 0; i < test_tam - 1; i++)
			SDL_RenderDrawLine(
				renderer,
				test[i][0] * f + VENTANA_ANCHO / 2,
                -test[i][1] * f + VENTANA_ALTO / 2,
                test[i+1][0] * f + VENTANA_ANCHO / 2,
                -test[i+1][1] * f + VENTANA_ALTO / 2
			);
			

        // Dibujamos la nave escalada por f en el centro de la pantalla:
        SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0x00, 0x00);
		
        for(int i = 0; i < nave_tam - 1; i++){
			//seek_point_x += ;
			//seek_point_y += ;
            SDL_RenderDrawLine(
                renderer,
                nave[i][0] * f + VENTANA_ANCHO / 2,
                -nave[i][1] * f + VENTANA_ALTO / 2,
                nave[i+1][0] * f + VENTANA_ANCHO / 2,
                -nave[i+1][1] * f + VENTANA_ALTO / 2
            );
		}

        if(chorro_prendido) {
            // Dibujamos el chorro escalado por f en el centro de la pantalla:
            SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0x00, 0x00);
            for(int i = 0; i < chorro_tam - 1; i++)
                SDL_RenderDrawLine(
                    renderer,
                    chorro[i][0] * f + VENTANA_ANCHO / 2,
                    -chorro[i][1] * f + VENTANA_ALTO / 2,
                    chorro[i+1][0] * f + VENTANA_ANCHO / 2,
                    -chorro[i+1][1] * f + VENTANA_ALTO / 2
                );
        }
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

