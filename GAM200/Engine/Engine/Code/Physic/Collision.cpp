/* Start Header**********************************************************************************/
/*
@file    Collision.cpp
@author  Ow Jian Wen	jianwen123321@hotmail.com
@date    19/06/2021
\brief
This file has the function definition for Physic

The physic here simulate pushing physic by moving objects out of each other 
in opposite direction (Note: is moveable have to be true) and when applied 
for a period of time, it looks like one object is pushing another.

collider position is in the center of itself and width and height is only half of itself total width and height
Note: Currently Oval collider does not exist as it is complicated and hard to compute


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#include "Engine/Header/Debug Tools/Logging.hpp" // to be removed
#include "Engine/Header/Physic/Collision.hpp"
#include "Engine/Header/ECS/Component/Physics/ColliderComponent.hpp"
#include "Engine/Header/ECS/Component/Graphics/TransformComponent.hpp"

namespace Engine {
    //Both used only for square to circle collision
    //Nearest point on square to circle
    glm::vec2 nearestPoint = glm::vec2{};
    //Length of nearest point to center of circle
    float length = float{}; //Reused for circle circle
    //Check whether it is in corner
    bool cornerBool = bool{};

    bool ent1IsMoveable, ent2IsMoveable;

    namespace CollisionImplementation {
        //Collision checks-------------------------------------------------------------------------------
        bool isColliding(glm::vec2& dir, const Collider& obj1, bool ent1Moveable, const Collider& obj2, bool ent2Moveable) {
            ent1IsMoveable = ent1Moveable;
            ent2IsMoveable = ent2Moveable;
            if (obj1.cType == ColliderType::CIRCLE) {
                if (obj2.cType == ColliderType::CIRCLE)
                    return isCollidingCIRCLEtoCIRCLE(dir, obj1, obj2);
                else
                    return isCollidingCIRCLEtoSQUARE(dir, obj1, obj2);

            }

            else {
                if (obj2.cType == ColliderType::CIRCLE)
                    return isCollidingSQUAREtoCIRCLE(dir, obj1, obj2);
                else
                    return isCollidingSQUAREtoSQUARE(dir, obj1, obj2);
            }

            return false;
        }

        bool isCollidingSQUAREtoSQUARE(glm::vec2& dir, const Collider& obj1, const Collider& obj2) {
            //Check whether obj1 is outside range of obj2
            if (obj1.offset_position.x + obj1.offset_scale.x < obj2.offset_position.x - obj2.offset_scale.x ||
                obj1.offset_position.x - obj1.offset_scale.x > obj2.offset_position.x + obj2.offset_scale.x ||
                obj1.offset_position.y + obj1.offset_scale.y < obj2.offset_position.y - obj2.offset_scale.y ||
                obj1.offset_position.y - obj1.offset_scale.y > obj2.offset_position.y + obj2.offset_scale.y)
                return false;

            dir = (obj1.offset_position - obj2.offset_position);
            dir = glm::normalize(dir);
            return true;
        }

        bool isCollidingSQUAREtoCIRCLE(glm::vec2& dir, const Collider& col1, const Collider& col2) {
            cornerBool = true;
            //Check if circle is corner of square (same logic as square to square collision
            if (col2.offset_position.x < col1.offset_position.x - col1.offset_scale.x)
                nearestPoint.x = col1.offset_position.x - col1.offset_scale.x;
            else if (col2.offset_position.x > col1.offset_position.x + col1.offset_scale.x)
                nearestPoint.x = col1.offset_position.x + col1.offset_scale.x;
            else {
                cornerBool = false;
            }

            if (col2.offset_position.y < col1.offset_position.y - col1.offset_scale.y)
                nearestPoint.y = col1.offset_position.y - col1.offset_scale.y;
            else if (col2.offset_position.y > col1.offset_position.y + col1.offset_scale.y)
                nearestPoint.y = col1.offset_position.y + col1.offset_scale.y;
            else {
                cornerBool = false;
            }

            if (cornerBool) {
                //Store how much it intersect
                length = col2.offset_scale.x - glm::length(nearestPoint - col2.offset_position);
                if (length < 0) return false;

                dir = col1.offset_position - col2.offset_position;
                dir = glm::normalize(dir);
                return true;
            }

            else {
                return isCollidingSQUAREtoSQUARE(dir, col1, col2);
            }

            return false;
        }

        bool isCollidingCIRCLEtoSQUARE(glm::vec2& dir, const Collider& obj1, const Collider& obj2) {
            return isCollidingSQUAREtoCIRCLE(dir, obj2, obj1);
        }

        bool isCollidingCIRCLEtoCIRCLE(glm::vec2& dir, const Collider& obj1, const Collider& obj2) {
            //if (obj1.scale.x == obj1.scale.y && obj2.scale.x == obj2.scale.y) {
            float rad = obj1.offset_scale.x + obj2.offset_scale.x;
            rad = (float)pow(rad, 2);
            dir = obj1.offset_position - obj2.offset_position;
            float tl = dir.x * dir.x + dir.y * dir.y;

            if (rad < tl) return false;
            //only calculate if it collides
            dir = glm::normalize(dir);
            return true;
            /*}

            else {
                return false;
            }*/
        }


        //Collision resolution-------------------------------------------------------------------------------
        void CollisionResolution(glm::vec2& dir, Transform& trans1, const Collider& col1, Transform& trans2, const Collider& col2) {
            if (col1.cType == ColliderType::CIRCLE) {
                if (col2.cType == ColliderType::CIRCLE)
                    CollisionResolutionCIRCLEtoCIRCLE(dir, trans1, col1, trans2, col2);
                else
                    CollisionResolutionCIRCLEtoSQUARE(dir, trans1, col1, trans2, col2);
            }

            else {
                if (col2.cType == ColliderType::CIRCLE)
                    CollisionResolutionSQUAREtoCIRCLE(dir, trans1, col1, trans2, col2);
                else
                    CollisionResolutionSQUAREtoSQUARE(dir, trans1, col1, trans2, col2);
            }
        }

        void CollisionResolutionSQUAREtoSQUARE(glm::vec2& dir, Transform& trans1, const Collider& col1, Transform& trans2, const Collider& col2) {
            float lenX = 0.f, lenY = 0.f;
            //Get difference in distance (see how much they intersect)
            lenY = col1.offset_scale.y + col2.offset_scale.y - abs(col2.offset_position.y - col1.offset_position.y);
            lenX = col1.offset_scale.x + col2.offset_scale.x - abs(col2.offset_position.x - col1.offset_position.x);
            //more x mean intersect on y
            //E.g one square on top of another square, lenX is huge but they are intersecting in y axis
            if (lenX > lenY) lenX = 0.f;
            else if (lenX < lenY) lenY = 0.f;

            glm::vec2 up{ 0.f, dir.y }, right{ dir.x, 0.f };

            if (ent1IsMoveable && ent2IsMoveable) {
                trans1.position += lenX / 2 * right; //for col1
                trans2.position += lenX / 2 * -right; //for col2
                trans1.position += lenY / 2 * up; //for col1
                trans2.position += lenY / 2 * -up; //for col2
            }

            //if only one moveable it should move by the full length amount
            else if (ent1IsMoveable) {
                trans1.position += lenX * right; //for col1
                trans1.position += lenY * up; //for col1
            }

            else if (ent2IsMoveable) {
                trans2.position += lenX * -right; //for col2
                trans2.position += lenY * -up; //for col2
            }
        }

        void CollisionResolutionSQUAREtoCIRCLE(glm::vec2& dir, Transform& trans1, const Collider& col1, Transform& trans2, const Collider& col2) {
            if (!cornerBool) {
                CollisionResolutionSQUAREtoSQUARE(dir, trans1, col1, trans2, col2);
                return;
            }

            if (ent1IsMoveable && ent2IsMoveable) {
                trans1.position += length / 2 * dir;
                trans2.position += length / 2 * -dir; // for col2
            }

            //if only one moveable it should move by the full length amount
            else if (ent1IsMoveable) {
                trans1.position += length * dir;

            }

            else if (ent2IsMoveable) {
                //length is calculated in collision detection
                trans2.position += length * -dir; // for col2
            }
        }

        void CollisionResolutionCIRCLEtoSQUARE(glm::vec2& dir, Transform& trans1, const Collider& col1, Transform& trans2, const Collider& col2) {
            CollisionResolutionSQUAREtoCIRCLE(dir, trans2, col2, trans1, col1);
        }

        void CollisionResolutionCIRCLEtoCIRCLE(glm::vec2& dir, Transform& trans1, const Collider& col1, Transform& trans2, const Collider& col2) {
            glm::vec2 len = col1.offset_position - col2.offset_position;
            length = glm::length(len);

            //length is the distance between the two object
            length = col1.offset_scale.x + col2.offset_scale.x - length;

            //E.g object1 is radius 5, object2 is radius 3
            //distance between the two object is 7, difference between distance and total radius is 1
            //but if both object were to move, they would only move by 0.5 (hence the first if statement)

            //if both moveable then both will move length/2 in direction opposite each other
            //since dir is from col1, object2 will move in dir and object1 will move in -dir
            if (ent1IsMoveable && ent2IsMoveable) {
                trans1.position += length / 2 * dir; //for col1
                trans2.position += length / 2 * -dir; //for col2
            }

            //if only one moveable it should move by the full length amount
            else if (ent1IsMoveable) {
                trans1.position += length * dir; //for col1
            }

            else if (ent2IsMoveable) {
                trans2.position += length * -dir; //for col2
            }
        }
    }
}