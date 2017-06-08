#pragma once
#include "icg_common.h"

///- Adapted from..
///  https://learnopengl.com/#!In-Practice/2D-Game/Particles

struct Particle {
    vec2 pos, speed;
    vec4 color;
    GLfloat life;
    Particle() : pos(0.0f), speed(0.0f), color(1.0f), life(0.0f) {}
};

class Particles {
public:

    GLuint first_unused_particle(){
        // Search from last used particle, this will usually return almost instantly
        for (GLuint i = last_used_particle; i < nr_particles; ++i){
            if (particles[i].life <= 0.0f){
                last_used_particle = i;
                return i;
            }
        }
        // Otherwise, do a linear search
        for (GLuint i = 0; i < last_used_particle; ++i){
            if (particles[i].life <= 0.0f){
                last_used_particle = i;
                return i;
            }
        }
        // Override first particle if all others are alive
        last_used_particle = 0;
        return 0;
    }

    void respawn_particle(Particle &particle, Particle &object, vec2 offset){
        GLfloat random = ((rand() % 100) - 50) / 10.0f;
        GLfloat rColor = 0.5 + ((rand() % 100) / 100.0f);
        particle.pos = object.pos + offset;
        particle.color = vec4(rColor, rColor, rColor, 1.0f);
        particle.life = 1.0f;
        particle.speed = object.speed * 0.1f;
    }

    void update_particles(){
        GLfloat dt = 0.1;
        GLuint nr_new_particles = 2;
    }


    GLuint last_used_particle = 0;
    GLuint nr_particles = 500;
    struct Particle particles[500];

};
