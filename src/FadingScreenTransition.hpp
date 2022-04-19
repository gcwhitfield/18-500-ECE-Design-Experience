#ifndef FADING_SCREEN_TRANSITION
#define FADING_SCREEN_TRANSITION

#include "Vertex.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm.hpp>

#include <vector>

struct FadingScreenTransition {
    FadingScreenTransition() {};
    ~FadingScreenTransition() {};

    enum ScreenTransitionAnimType {
        OPEN, // plays when a scene is first loaded
        CLOSE // plays when a scene is being closed
    };

    ScreenTransitionAnimType anim_type;

    float anim_time = 1.0f; // the total amount of time that it takes for the animation to play

    // returns true the screen transition is currently animating
    bool is_active() { return t < anim_time && t >= 0; }

    // returns true when the screen transition has finished animating
    bool is_finished() { return t > anim_time; }

    void play(ScreenTransitionAnimType anim_type_, float anim_time_, glm::u8vec4 color_); // plays the screen transition. 

    float t = -1; // internal timer that the screen transition uses to keep track of its progress 
    // through the animation

    void update(float elapsed); // called every frame

    // ---------- drawing ----------
    std::vector<Vertex> vertices;
    glm::u8vec4 color; // the color of the screen transition
    // called every time that the game needs to draw something to the screen
    void draw(glm::uvec2 const &drawable_size);
};

#endif