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

    int dormir = 1000;   // tiempo  de retardo para que empieze

    // BEGIN código del alumno

	//delta frame x e y desplazamiento y giro
	float frame_desp = 0;
	int angulos_girados = 0;
    
	// time global
	float time_global = 0;
	float time_global_lapse = 1.0f / JUEGO_FPS;
	
	// Mi nave:
    size_t nave_tam = 9;

	int rapidez_ang = 5;

	int angulo_nave = 0;

    // El chorro de la nave:
    size_t chorro_tam = 3;

    bool chorro_prendido = false;

	//centro de rotacion y seguimiento de la nave
	float seek_point_x = VENTANA_ANCHO / 2;
	float seek_point_y = VENTANA_ALTO / 2;
	float dseek_x = 0;
	float dseek_y = 0;
    // Queremos que todo se dibuje escalado por f:
    float f = 3;


	//
	//test objeto inmovil
		float test[][2] = {{0, 0},{-2, 0},{-4, 0}};
		size_t test_tam = 3;
    // END código del alumno

    unsigned int ticks = SDL_GetTicks();
    float nave_test[9][2];
    for(size_t i = 0; i < nave_tam; i++)
        for(size_t j = 0; j < 2 ; j++)
            nave_test[i][j] = nave[i][j]; 

    /**/
    size_t contador = 0;
    while(1) {
        if(SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT)
                break;
            // BEGIN código del alumno
			
			 //tiempo independiente, accion  de la gravedad


			if (event.type == SDL_KEYDOWN) {
                // Se apretó una tecla
                switch(event.key.keysym.sym) {
                    case SDLK_LALT:
                        // Prendemos el chorro:
                        componentes_segun_angulo(angulo_nave, &dseek_x, &dseek_y);
                        chorro_prendido = true;
						break;
                    case SDLK_LCTRL: //disparo
						break;
                    case SDLK_SPACE:    // escudo y recolectar 
                        break;      
                    case SDLK_RIGHT: 
                        rotar_nave(nave, nave_tam, -rapidez_ang);
				        rotar_nave(chorro,chorro_tam, -rapidez_ang);
				        angulos_girados += rapidez_ang;   
						break;
                    case SDLK_LEFT:
						rotar_nave(nave, nave_tam, rapidez_ang);
						rotar_nave(chorro, chorro_tam, rapidez_ang);
						angulos_girados += rapidez_ang;
                    	break;
					case SDLK_ESCAPE:
						return 1;
                }
            }
            else if (event.type == SDL_KEYUP) {
                // Se soltó una tecla
                switch(event.key.keysym.sym) {
                    case SDLK_LALT:
                        // Apagamos el chorro:
                        chorro_prendido = false;
                        break;
					case SDLK_RIGHT:
						angulo_nave = angulo_rotado(angulo_nave, -angulos_girados);
						rotar_nave(test, test_tam, -angulos_girados);
						angulos_girados = 0;
						break;
					case SDLK_LEFT:
						angulo_nave = angulo_rotado(angulo_nave, angulos_girados);
						rotar_nave(test, test_tam, angulos_girados);
						angulos_girados = 0;
						break;
                }
            }
            /*
            for(size_t i = 0; i < nave_tam; i++)
                for(size_t j = 0; j < 2 ; j++)
                    nave_test[i][j] = nave[i][j]; 
            */
            




            // END código del alumno
            continue;
        }
        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00); // fondo
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0x00);

        // BEGIN código del alumno
		
		
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
			

        // Dibujamos la nave escalada por f en el centro de la pantalla:
        SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0x00, 0x00);
        for(int i = 0; i < nave_tam - 1; i++){
			SDL_RenderDrawLine(
                renderer,
                nave_test[i][0] * f + seek_point_x,		//eje x
                -nave_test[i][1] * f + seek_point_y, 		//eje y 
                nave_test[i+1][0] * f + seek_point_x,		//eje x
                -nave_test[i+1][1] * f + seek_point_y		//eje y
            );
		}

        if(chorro_prendido) {
            // Dibujamos el chorro escalado por f en el centro de la pantalla:
            SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0x00, 0x00);
            for(int i = 0; i < chorro_tam - 1; i++){
				SDL_RenderDrawLine(
                    renderer,
                    chorro[i][0] * f + seek_point_x,
                    -chorro[i][1] * f + seek_point_y,
                    chorro[i+1][0] * f + seek_point_x,
                    -chorro[i+1][1] * f + seek_point_y
                );
			}
        }
        // END código del alumno

        SDL_RenderPresent(renderer);
        ticks = SDL_GetTicks() - ticks;
        if(dormir) {
            SDL_Delay(dormir);
            dormir = 0;
        }
        else if(ticks < 1000 / JUEGO_FPS)
            SDL_Delay(1000 / JUEGO_FPS - ticks);  // esto hace que el tiempo vaya lento
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

