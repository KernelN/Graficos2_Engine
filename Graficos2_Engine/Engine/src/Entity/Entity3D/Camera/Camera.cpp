#include "Camera.h"
//#include "glm/glm.hpp"
#include <glm/ext/matrix_transform.hpp>
#include <glfw/include/GLFW/glfw3.h>

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
    	
        translation = { 0.0f, 0.0f, -1.0f };
        vecs[0] = translation;                    //eye (camera pos)
        vecs[1] = zero;                          //center (camera target)
        vecs[2] = { 0.0f, 1.0f, 0.0f }; //up

        for (int i = 0; i < 3; i++)
        {
            originalVecs[i] = vecs[i];
            originalMags[i] = originalVecs[i].GetMagnitude();
        }
}
Camera::~Camera() {}
void Camera::Update()
{    
    //Rotation
    // const float radius = 10.0f;
    //  float camX = sin(glfwGetTime()) * radius;
    //  float camZ = cos(glfwGetTime()) * radius;

     //vecs[0].y = camX;
     //vecs[0].z = camZ;
	
    //view = glm::lookAt(glm::vec3(camX, 0.0, camZ), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
}

void Camera::GetView(Vector3 cameraVecs[3])
{
    cameraVecs[0] = vecs[0]; //eye (camera pos)
    cameraVecs[1] = vecs[1]; //center (camera target)
    cameraVecs[2] = vecs[2]; //up
}

void Camera::SetFollow(Entity* target, Vector3 offset)
{
    followTarget = target;
    this->offset = originalVecs[0] + offset;
}

void Camera::FollowTarget(bool rotateWithTarget)
{
    //vecs[0] = followTarget->GetTranslation() + offset;
    Vector3 trans = followTarget->GetTranslation() + offset;
    SetTranslation(trans.x, trans.y, trans.z);

    if(!rotateWithTarget) return;

    SetRotation(followTarget->GetRotation());
}

void Camera::LookAtTarget()
{
    //vecs[1] = followTarget->GetTranslation();
    LookAt(followTarget->GetTranslation());
    UpdateEyePos();
    UpdateEyeUp();
}

void Camera::Translate(float x, float y, float z)
{
    //Translate Camera
    static_cast<Entity*>(this)->Translate(x, y, z);

    //Update offset
    offset.x += x;
    offset.y += y;
    offset.z += z;

    //Update Vectors
    UpdateEyePos();
    UpdateEyeTarget();
}

void Camera::Translate(Vector3 trans)
{
    //Translate Camera
    static_cast<Entity*>(this)->Translate(trans);

    //Update offset
    offset += trans;

    //Update Vectors
    UpdateEyePos();
    UpdateEyeTarget();
}

void Camera::Rotate(float angle, float angleY, float angleZ)
{
    //Rotate Camera
    static_cast<Entity*>(this)->Rotate(angle, angleY, angleZ);  
    UpdateEyeTarget();
    UpdateEyeUp();
}

void Camera::Rotate(Vector3 rot)
{
    //Rotate Camera
    static_cast<Entity*>(this)->Rotate(rot);  
    UpdateEyeTarget();
    UpdateEyeUp();
}

void Camera::SetTranslation(float x, float y, float z)
{
    static_cast<Entity*>(this)->SetTranslation(x, y, z);
        
    UpdateEyePos();
    UpdateEyeTarget();
}

void Camera::SetTranslation(Vector3 trans)
{
    static_cast<Entity*>(this)->SetTranslation(trans);
    
    UpdateEyePos();
    UpdateEyeTarget();
}

void Camera::SetRotation(float angle, float angleY, float angleZ)
{
    static_cast<Entity*>(this)->SetRotation(angle, angleY, angleZ);
    UpdateEyeTarget();
    UpdateEyeUp();
}

void Camera::SetRotation(Vector3 rot)
{
    static_cast<Entity*>(this)->SetRotation(rot);
    UpdateEyeTarget();
    UpdateEyeUp();
}

void Camera::UpdateEyePos()
{
    vecs[0] = translation - originalVecs[0];
}

void Camera::UpdateEyeTarget()
{
    vecs[1] = translation - GetForward() * originalMags[0];
}

void Camera::UpdateEyeUp()
{
    vecs[2] = GetUp();
}