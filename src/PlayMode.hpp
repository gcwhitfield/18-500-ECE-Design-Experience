#ifndef PLAYMODE
#define PLAYMODE

#include "Beatmap.hpp"
#include "ColorTextureProgram.hpp"
#include "DrumPeripheral.hpp"
#include "FadingScreenTransition.hpp"
#include "Input.hpp"
#include "LoadImage.hpp"
#include "Mode.hpp"
#include "ScoreScreenMode.hpp"
#include "Sound.hpp"
#include "TextRenderer.hpp"
#include "Vertex.hpp"


#include <glm.hpp>
#include <iostream>
#include <vector>
#include <map>
#include <random>

// PlayMode is where all of the drawing and logic related to gameplay is stored. 
// The scene where the player plays the game is typically referred to as the "play mode"
struct PlayMode : Mode {
    PlayMode(std::string song_path);
    ~PlayMode();

    // ---------- gameplay ---------- 
    std::string song_path;
    std::string beatmap_file;
    Sound::Sample music_file;
    Sound::PlayingSample *music = NULL;

    enum BeatGrade {
        PERFECT, // player hit the note exactly with the beat
        GOOD,  // player hit the note more-or-less with the beat
        MISS, // player did not hit the note on beat at all
        NONE // the player did not hit or miss the beat 
    };
    
    struct BeatGradeDisplay {
        BeatGrade grade;
        float lifetime; // the amount of time that the display is on the screen
    };
    BeatGradeDisplay beat_grade_display;

    int score = 0;

    // update is called every frame
    virtual void update(float elapsed) override;

    // level_finished is called when the player completes the level. The level is completed
    // if the user makes it all the way to the end.
    //
    // level_finished changes the current mode to ScoreScreenMode
    void level_finished();

    // handle_key gets called whenever the user presses a key which is detected by GLFW
    virtual void handle_key(
        GLFWwindow *window, 
        int key, 
        int scancode, 
        int action, 
        int mods) override;

    Beatmap *beatmap;

    // given a beat location 'location', returns the score to assign to the beat
    BeatGrade grade_input(Beatmap::BeatLocation location);

    // ---------- drums input ----------
    DrumPeripheral *drums;

    // handle_drum gets called whenever the user hits something on the drum
    virtual void handle_drum(std::vector<char> hits) override;

    // ---------- drawing ----------
    TextRenderer text_renderer;
    GLuint tex = -1U;
    ColorTextureProgram program;
    GLuint vertex_buffer_object = -1U;
    GLuint vertex_array_object = -1U;
    GLuint white_texture = -1U;
    GLuint notes_texture = -1U;
    GLuint background_texture = -1U;
    GLuint healthbar_background_texture = -1U;
    GLuint healthbar_top_texture = -1U;

    std::vector<Vertex> vertices;

    FadingScreenTransition fading_screen_transition;

    // draw is called whenever we want to draw something to the screen
    virtual void draw(glm::uvec2 const &drawable_size) override;
    
    // ------------ sound ------------

};

#endif