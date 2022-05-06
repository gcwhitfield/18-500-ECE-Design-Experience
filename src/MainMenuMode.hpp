#ifndef MAIN_MENU_MODE
#define MAIN_MENU_MODE

#include "ColorTextureProgram.hpp"
#include "FadingScreenTransition.hpp"
#include "Input.hpp"
#include "LoadImage.hpp"
#include "Mode.hpp"
#include "SongSelectionMode.hpp"
#include "TextRenderer.hpp"
#include "Vertex.hpp"

#include <glm.hpp>
#include <vector>


struct MainMenuMode : Mode 
{
    MainMenuMode();
    ~MainMenuMode();

    // ---------- main menu state ------------
    enum MainMenuState 
    {
        OPEN, // while the open animation is playing
        WAIT, // while the menu is waiting for user input
        CLOSE // while the menu is playing the closing animation
    };
    MainMenuState curr_state = OPEN;

    float t = 0; // internal time variable for making text fade in and out over time

    virtual void update(float elapsed) override;

    // this function is called when the user presses a key on the keyboard
    virtual void handle_key(
        GLFWwindow *window, 
        int key,
        int scancode, 
        int action, 
        int mods) override;
    
    // ---------- drums input ----------
    DrumPeripheral *drums;

    // this function is called when the user hits the drum
    virtual void handle_drum(std::vector<char> hits) override;

    // plays exit animation and bloop sound before transitioning to song selection mode
    void go_to_song_selection_mode();
    
    // ---------- drawing ----------
    TextRenderer text_renderer;
    GLuint tex = -1U;
    ColorTextureProgram program;
    GLuint vertex_buffer_object = -1U;
    GLuint vertex_array_object = -1U;
    GLuint white_texture = -1U;
    GLuint background_texture = -1U;
    GLuint logo_texture = -1U;
    GLuint start_texture = -1U;
    GLuint exit_texture = -1U;
    GLuint hit_drums_to_begin_texture = -1U;
    std::vector<Vertex> vertices;

    FadingScreenTransition fading_screen_transition;

    virtual void draw(glm::uvec2 const &drawable_size) override;
};

#endif