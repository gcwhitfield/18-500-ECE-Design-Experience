#ifndef SONG_SELECTION_MODE
#define SONG_SELECTION_MODE

#include "Beatmap.hpp"
#include "ColorTextureProgram.hpp"
#include "Directory.hpp"
#include "Input.hpp"
#include "LoadImage.hpp"
#include "Mode.hpp"
#include "PlayMode.hpp"
#include "Sound.hpp"
#include "TextRenderer.hpp"
#include "Vertex.hpp"

#include <glm.hpp>
#include <vector>


struct SongSelectionMode : Mode 
{
    SongSelectionMode();
    ~SongSelectionMode();

    // ---------- song selection logic ----------
    enum SongSelectionState {
        SELECTING, // the player is currently selecting their song
        CONFIRMED // the player has confirmed their selection
    };
    SongSelectionState state = SELECTING;

    struct SongInfo {
        Beatmap::BeatFileData data;
        glm::vec2 curr_pos; // the position of the song info on the screen
        glm::vec2 desired_pos; // used for smoothly interpolating position of song info
    };
    size_t curr_selected = 0; // the song (index into 'songs') that is currently selected by the player
    std::vector<std::string> song_files; // vector of filepaths to song dirs
    std::vector<SongInfo> songs; // vector of song data

    // sets the positions of the songs based on the value of 'curr_selected'
    void set_song_positions();

    virtual void update(float elapsed) override;

    virtual void handle_key(
        GLFWwindow *window, 
        int key,
        int scancode, 
        int action, 
        int mods) override;

    // this function is called when the user hits the drum
    virtual void handle_drum(std::vector<char> hits) override;


    // ---------- drawing ----------
    std::vector<Vertex> vertices;
    TextRenderer text_renderer;
    GLuint tex = -1U;
    ColorTextureProgram program;
    GLuint vertex_buffer_object = -1U;
    GLuint vertex_array_object = -1U;
    GLuint white_texture = -1U;
    GLuint song_selection_box_texture = -1U;
    GLuint background_texture = -1U;
    
    FadingScreenTransition fading_screen_transition;

    virtual void draw(glm::uvec2 const &drawable_size) override;
};

#endif