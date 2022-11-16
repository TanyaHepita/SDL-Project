// SDL_Test.h: Includedatei für Include-Standardsystemdateien
// oder projektspezifische Includedateien.

#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <map>
#include <memory>
#include <optional>
#include <vector>
#include <stdlib.h>

// Defintions
constexpr double frame_rate = 60.0; // refresh rate
constexpr double frame_time = 1. / frame_rate;
constexpr unsigned frame_width = 1400; // Width of window in pixel
constexpr unsigned frame_height = 900; // Height of window in pixel
// Minimal distance of animals to the border
// of the screen
constexpr unsigned frame_boundary = 100;

// Helper function to initialize SDL
void init();

class animal {
private:
  SDL_Surface* window_surface_ptr_; // ptr to the surface on which we want the
                                    // animal to be drawn, also non-owning
  SDL_Surface* image_ptr_; // The texture of the sheep (the loaded image), use
                           // load_surface_for
    SDL_Rect position;
    // todo: Attribute(s) to define its position
public:
  animal(const char *file_path, SDL_Surface* window_surface_ptr){
      window_surface_ptr_ = window_surface_ptr;
      image_ptr_ = IMG_Load(file_path);
      std::cout << file_path<<'\n';
      if (!image_ptr_)
          std::cout << "image cannont be load";
      else
          std::cout << "image loaded";
  };
  // todo: The constructor has to load the sdl_surface that corresponds to the
  // texture
  ~animal(){
      SDL_FreeSurface(image_ptr_);
      SDL_FreeSurface(window_surface_ptr_);
  }; // todo: Use the destructor to release memory and "clean up
               // behind you"

  void draw(){

        int range_x = (frame_width-frame_boundary) - frame_boundary + 1;
        int range_y = (frame_height-frame_boundary) - frame_boundary + 1;
        position.x = rand() % range_x + frame_boundary;
        position.y = rand() % range_y + frame_boundary;
      SDL_BlitSurface(image_ptr_, NULL, window_surface_ptr_, &position);



  }; // todo: Draw the animal on the screen <-> window_surface_ptr.
                 // Note that this function is not virtual, it does not depend
                 // on the static type of the instance

  virtual void move(){
  int animal::virtual_move(int limite, POSITION targ) {
  int min, max;
  if (targ == POSITION::HORIZONTAL) {
    if (position_.x - limite <= frame_boundary) {
      min = frame_boundary;
    } else {
      min = position_.x - limite;
    }

    if (position_.x + limite >= frame_width - frame_boundary) {
      max = frame_width - frame_boundary;
    } else {
      max = position_.x + limite;
    }
  } else {
    if (position_.y - limite<= frame_boundary) {
      min = frame_boundary;
    } else {
      min = position_.y - limite;
    }

    if (position_.y + limite >= frame_height - frame_boundary) {
      max = frame_height - frame_boundary;
    } else {
      max = position_.y + limite;
    }
  }
  std::random_device rand_dev;
  std::mt19937 generator(rand_dev());
  std::uniform_int_distribution<int> distr(min, max);
  return distr(generator);
}
  }; // todo: Animals move around, but in a different
                             // fashion depending on which type of animal
};
/*
// Insert here:
// class sheep, derived from animal
class sheep : public animal {
  // todo
  // Ctor
  // Dtor
  // implement functions that are purely virtual in base class
};

// Insert here:
// class wolf, derived from animal
// Use only sheep at first. Once the application works
// for sheep you can add the wolves

// The "ground" on which all the animals live (like the std::vector
// in the zoo example).
class ground {
private:
  // Attention, NON-OWNING ptr, again to the screen
  SDL_Surface* window_surface_ptr_;

  // Some attribute to store all the wolves and sheep
  // here

public:
  ground(SDL_Surface* window_surface_ptr); // todo: Ctor
  ~ground(){}; // todo: Dtor, again for clean up (if necessary)
  void add_animal(some argument here); // todo: Add an animal
  void update(); // todo: "refresh the screen": Move animals and draw them
  // Possibly other methods, depends on your implementation
};
*/
// The application class, which is in charge of generating the window
class application {
private:
  // The following are OWNING ptrs
  SDL_Window* window_ptr_;
  SDL_Surface* window_surface_ptr_;
  //SDL_Event window_event_;

    unsigned nb_sheep;
    unsigned nb_wolf;
    bool continuer = true;
  // Other attributes here, for example an instance of ground

public:
  application(unsigned n_sheep, unsigned n_wolf){
      window_ptr_ = SDL_CreateWindow("Sheep and Wolves",SDL_WINDOWPOS_UNDEFINED,
                                     SDL_WINDOWPOS_UNDEFINED,
                                     frame_width,
                                     frame_height,
                                     SDL_WINDOW_SHOWN);
      window_surface_ptr_ = SDL_GetWindowSurface(window_ptr_);

      nb_sheep = n_sheep;
      nb_wolf = n_wolf;
  };// Ctor
  ~application(){
      if (window_ptr_)
          SDL_DestroyWindow(window_ptr_);
      if (window_surface_ptr_)
          SDL_FreeSurface(window_surface_ptr_);
      window_ptr_ = nullptr;
      window_surface_ptr_ = nullptr;
      SDL_Quit();
  };                                 // dtor

  int loop(unsigned period){

      if( window_ptr_ )
      {
          SDL_Surface *s;
          /* Creating the surface. */
          s = SDL_CreateRGBSurface(0, frame_width, frame_height, 32, 0, 0, 0, 0);
          SDL_FillRect(s, NULL, SDL_MapRGB(s ->format, 0, 255, 0));
          SDL_BlitSurface(s, NULL, window_surface_ptr_, nullptr);
          for (unsigned n = nb_sheep; n > 0; n--){
            animal sheep("./sheep.png",window_surface_ptr_);
            sheep.draw();
            sheep.move();
          }
          for (unsigned n = nb_wolf; n > 0; n--){
            animal wolf("./wolf.png",window_surface_ptr_);
            wolf.draw();
            wolf.move();
          }
          SDL_UpdateWindowSurface(window_ptr_);
          while((SDL_GetTicks() < (period*1000)) && continuer ) {
              SDL_PollEvent(&windowevent);
              switch(windowevent.type)
              {
                  case SDL_QUIT:
                      continuer = false;
                      break;
              }
          }

      }
      else
      {
          fprintf(stderr,"Erreur de création de la fenêtre: %s\n",SDL_GetError());
      }
      return 0;
  }; // main loop of the application.
                             // this ensures that the screen is updated
                             // at the correct rate.
                             // See SDL_GetTicks() and SDL_Delay() to enforce a
                             // duration the application should terminate after
                             // 'period' seconds
};
