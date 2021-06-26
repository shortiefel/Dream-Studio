#include "Graphic/Camera.hpp"

namespace GraphicImplementation {
    CameraTemp camera2d;

    void CameraTemp::init(GLFWwindow* pwindow, Transform* ptran) {
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
    void  CameraTemp::update(GLFWwindow* pwindow) {
        // check keyboard button presses to enable camera interactivity

        // update camera aspect ratio - this must be done every frame
        // because it is possible for the user to change viewport
        // dimensions
        GLsizei fb_width, fb_height;
        glfwGetFramebufferSize(pwindow, &fb_width, &fb_height);
        ar = static_cast<GLfloat>(fb_width) / fb_height;

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