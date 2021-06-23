#include "Graphic/Camera.hpp"

namespace GraphicImplementation {
	Camera2D camera2d;

    void Camera2D::init(GLFWwindow* pwindow, Transform* ptran) {
        transform = ptran;

        // compute camera window's aspect ratio
        GLsizei fb_width, fb_height;
        glfwGetFramebufferSize(pwindow, &fb_width, &fb_height);
        ar = static_cast<GLfloat>(fb_width) / fb_height;

        // compute camera's up and right vectors
        /*GLfloat rad = MathD::radians(pgo->orientation.x);
        up = glm::vec2(-sin(rad), cos(rad));
        right = glm::vec2(cos(rad), sin(rad));*/

        // at startup, the camera must be initialized to free camera
        MathD::Mat3 view_xform = MathD::Mat3(
            1.f, 0.f, 0.f,
            0.f, 1.f, 0.f,
            -transform->pos.x, -transform->pos.y, 1.f);
        MathD::Mat3 camwin_to_ndc_xform = MathD::Mat3(
            2.f / (ar * height), 0.f, 0.f,
            0.f, 2.f / height, 0.f,
            0.f, 0.f, 1.f);
        world_to_ndc_xform = camwin_to_ndc_xform * view_xform;
    }

    /*
    Update the camera
    check for flag to change the camera states
    */
    void  Camera2D::update(GLFWwindow* pwindow) {
        // check keyboard button presses to enable camera interactivity

        // update camera aspect ratio - this must be done every frame
        // because it is possible for the user to change viewport
        // dimensions
        GLsizei fb_width, fb_height;
        glfwGetFramebufferSize(pwindow, &fb_width, &fb_height);
        ar = static_cast<GLfloat>(fb_width) / fb_height;

        // update camera's orientation (if required)
        /*if (left_turn_flag) pgo->orientation.x += pgo->orientation.y;
        if (right_turn_flag) pgo->orientation.x -= pgo->orientation.y;*/

        // update camera's up and right vector (if required)
        //if (left_turn_flag || right_turn_flag) {
        //    // % 360 to prevent it from going out of range
        //    // vec2 is to prevent conversion error (from double to T)
        //    pgo->orientation.x = glm::vec2(fmod(pgo->orientation.x, 360.0), 0.f).x;
        //    GLfloat rad = glm::radians(pgo->orientation.x);
        //    up = glm::vec2(-sin(rad), cos(rad));
        //    right = glm::vec2(cos(rad), sin(rad));
        //}

        //// update camera's position (if required)
        //if (move_flag) {
        //    pgo->position += linear_speed * up;
        //}

        //// implement camera's zoom effect (if required)
        //if (zoom_flag) {
        //    if (height >= max_height) height_chf_dir = -1;
        //    else if (height <= min_height) height_chf_dir = 1;

        //    height += height_chf_dir * height_chg_val;
        //}

        //// compute appropriate world-to-camera view transformation matrix
        //if (!camtype_flag)
        //    view_xform = glm::mat3(
        //        1.f, 0.f, 0.f,
        //        0.f, 1.f, 0.f,
        //        -pgo->position.x, -pgo->position.y, 1.f);

        //else if (camtype_flag) {
        //    view_xform = glm::mat3(right.x, up.x, 0.f,
        //        right.y, up.y, 0.f,
        //        glm::dot(-right, pgo->position), glm::dot(-up, pgo->position), 1.f);
        //}

        // compute world-to-NDC transformation matrix
        world_to_ndc_xform = 
            MathD::Mat3(
            2.f / (ar * height), 0.f, 0.f,
            0.f, 2.f / height, 0.f,
            0.f, 0.f, 1.f)
            * 
            MathD::Mat3(
            1.f, 0.f, 0.f,
            0.f, 1.f, 0.f,
            -transform->pos.x, -transform->pos.y, 1.f);
        
    }
}