#include <glm.hpp>
#include <vector>

#ifndef VERTEX
#define VERTEX

struct Vertex {
     // 'Vertex' stores the information that we give to OpenGL in the vertex buffer
    Vertex(glm::vec3 pos, glm::u8vec4 col, glm::vec2 tex) : position(pos), color(col), tex_coord(tex) {
        position = pos;
        color = col;
        tex_coord = tex;
    }
    ~Vertex() {};
    glm::vec3 position;
    glm::u8vec4 color;
    glm::vec2 tex_coord;
};

    // inline helper functions for drawing shapes. The triangles are being counter clockwise.
    // draw_rectangle copied from NEST framework 
    // https://github.com/gcwhitfield/Game-Programming-f21-base6/blob/main/NEST.md
    inline void draw_rectangle (std::vector<Vertex> &verts, glm::vec2 const &center, glm::vec2 const &radius, glm::u8vec4 const &color) {
        verts.emplace_back(Vertex(glm::vec3(center.x-radius.x, center.y-radius.y, 0.0f), color, glm::vec2(0.0f, 1.0f))); // top left
        verts.emplace_back(Vertex(glm::vec3(center.x+radius.x, center.y-radius.y, 0.0f), color, glm::vec2(1.0f, 1.0f))); // top right
        verts.emplace_back(Vertex(glm::vec3(center.x+radius.x, center.y+radius.y, 0.0f), color, glm::vec2(1.0f, 0.0f))); // bottom right

        verts.emplace_back(Vertex(glm::vec3(center.x-radius.x, center.y-radius.y, 0.0f), color, glm::vec2(0.0f, 1.0f))); // top left
        verts.emplace_back(Vertex(glm::vec3(center.x+radius.x, center.y+radius.y, 0.0f), color, glm::vec2(1.0f, 0.0f))); // bottom right
        verts.emplace_back(Vertex(glm::vec3(center.x-radius.x, center.y+radius.y, 0.0f), color, glm::vec2(0.0f, 0.0f))); // bottom left
    };

#endif