#include "Camera.h"
// #include "glm/glm.hpp"
// #include <glm/ext/matrix_transform.hpp>
// #include <glfw/include/GLFW/glfw3.h>

Camera::Camera()
{
        // //Setting Camera Pos
        // glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
        //
        //
        // //Setting Camera Dir (look at to scene center)
        // glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
        // glm::vec3 cameraDirection = glm::normalize(cameraPos - cameraTarget);
        //
        //
        // //Set Right Axis (represents positive X)
        // //use cross product to get perpendicular of up
        // glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
        // glm::vec3 cameraRight = glm::normalize(glm::cross(up, cameraDirection));
        //
        // //Set Up Axis
        // //use same method as right axis
        // glm::vec3 cameraUp = glm::cross(cameraDirection, cameraRight);
    
        //Look At
        //"Camera" - vec sets position (if "Camera" should move to the right, mvp matrix will move everything to the left)
        //glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0,0,0));
        //glm::mat4 view = glm::lookAt(glm::vec3(0.0f, 0.0f, 1.0f),
        // 							glm::vec3(0.0f, 0.0f, 0.0f),
        // 							glm::vec3(0.0f, 1.0f, 0.0f));
        //view = glm::lookAt(glm::vec3(camX, 0.0, camZ), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
        //view = glm::lookAt(glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    	
        vecs[0] = {0.0f, 0.0f, 1.0f};//zero;
        vecs[1] = zero;
        vecs[2] = {0.0f, 1.0f, 0.0f};
        //vecs[2].z = 1.0f;
}
Camera::~Camera() {}
void Camera::Update() {}

void Camera::GetView(Vector3 cameraVecs[3])
{
    cameraVecs[0] = vecs[0];
    cameraVecs[1] = vecs[1];
    cameraVecs[2] = vecs[2];
}