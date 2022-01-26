#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm.hpp>
#include <memory>

// The Mode is convinient way to bundle instructions for drawing to the window and handling user 
// input all together into one class. Mode::update, Mode::handle_key, and Mode::draw 
// are all called from within main.cpp's render loop. 

// Heavily derived from https://github.com/15-466/15-466-f21-base0/blob/main/Mode.hpp
struct Mode : std::enable_shared_from_this<Mode> {
    Mode() { };
    virtual ~Mode() {};

    // update is called every frame after mouse and keyboard have been processed
    virtual void update(float elapsed);

    // Input callback functions. For more details about input callbacks with GLFW, check out 
    // https://www.glfw.org/docs/3.3/input_guide.html#events
    // This function is called whenever keyboard inputs are received by GLFW
    virtual void handle_key(GLFWwindow *window, int key, int scancode, int action, int mods);    
    // Wrapper functions for input callbacks. GLFWSetKeyCallback cannot be called with a member 
    // function as its second argument, therefore, a static wrapper function must be used instead
    static void handle_key_wrapper(GLFWwindow *window, int key, int scancode, int action, int mods){ 
            Mode::current->handle_key(window, key, scancode, action, mods);
    }

    // Draws to the window
    virtual void draw(glm::uvec2 const &drawable_size);

    static std::shared_ptr<Mode> current;
    // Sets the current mode to the new mode. This will typically get called whenever the
    // application needs to switch between screens. For example, a pause screen or a menu can 
    // be implemented by changing the mode
    static void set_current(std::shared_ptr<Mode> const &new_mode);
};