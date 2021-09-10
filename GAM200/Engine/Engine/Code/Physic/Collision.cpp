/* Start Header**********************************************************************************/
/*
@file    Collision.cpp
@author  Ow Jian Wen	jianwen123321@hotmail.com
@date    19/06/2021
\brief
This file has the function definition for Physic

The physic here simulate pushing physic by moving objects out of each other 
in opposite direction (Note: Need ti have rigidbody) and when applied 
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
    //Check if entity have rigidbody (movable)
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
            //SAT method
            std::vector<glm::vec2> obj1Corner(4);
            glm::vec2 xaxis1{ glm::cos(glm::radians(obj1.angle)), glm::sin(glm::radians(obj1.angle)) };
            glm::vec2 yaxis1{ glm::cos(glm::radians(90.f + obj1.angle)), glm::sin(glm::radians(90.f + obj1.angle)) };
            
            obj1Corner[0] = obj1.offset_position + obj1.offset_scale.x * xaxis1 + obj1.offset_scale.y * yaxis1; //top right
            obj1Corner[1] = obj1.offset_position - obj1.offset_scale.x * xaxis1 + obj1.offset_scale.y * yaxis1; //top left
            obj1Corner[2] = obj1.offset_position - obj1.offset_scale.x * xaxis1 - obj1.offset_scale.y * yaxis1; //bot left
            obj1Corner[3] = obj1.offset_position + obj1.offset_scale.x * xaxis1 - obj1.offset_scale.y * yaxis1; //bot right
            
            std::vector<glm::vec2> obj2Corner(4);
            glm::vec2 xaxis2{ glm::cos(glm::radians(obj2.angle)), glm::sin(glm::radians(obj2.angle)) };
            glm::vec2 yaxis2{ glm::cos(glm::radians(90 + obj2.angle)), glm::sin(glm::radians(90 + obj2.angle)) };

            obj2Corner[0] = obj2.offset_position + obj2.offset_scale.x * xaxis2 + obj2.offset_scale.y * yaxis2; //top right
            obj2Corner[1] = obj2.offset_position - obj2.offset_scale.x * xaxis2 + obj2.offset_scale.y * yaxis2; //top left
            obj2Corner[2] = obj2.offset_position - obj2.offset_scale.x * xaxis2 - obj2.offset_scale.y * yaxis2; //bot left
            obj2Corner[3] = obj2.offset_position + obj2.offset_scale.x * xaxis2 - obj2.offset_scale.y * yaxis2; //bot right

            std::vector<glm::vec2>* shape1 = &obj1Corner;
            std::vector<glm::vec2>* shape2 = &obj2Corner;

            float overlap = INFINITY;

            for (int num = 0; num < 2; num++) {
                if (num == 1) {
                    shape1 = &obj2Corner;
                    shape2 = &obj1Corner;
                }
                for (int a = 0; a < shape1->size(); a++) {
                    int b = (a + 1) % shape1->size();
                    glm::vec2 axisProj = { -((*shape1)[b].y - (*shape1)[a].y), (*shape1)[b].x - (*shape1)[a].x };
                    axisProj = glm::normalize(axisProj);

                    // Work out min and max 1D points for r1
                    float min_r1 = INFINITY, max_r1 = -INFINITY;
                    for (int p = 0; p < shape1->size(); p++)
                    {
                        float q = ((*shape1)[p].x * axisProj.x + (*shape1)[p].y * axisProj.y);
                        min_r1 = std::min(min_r1, q);
                        max_r1 = std::max(max_r1, q);
                    }

                    // Work out min and max 1D points for r2
                    float min_r2 = INFINITY, max_r2 = -INFINITY;
                    for (int p = 0; p < shape2->size(); p++)
                    {
                        float q = ((*shape2)[p].x * axisProj.x + (*shape2)[p].y * axisProj.y);
                        min_r2 = std::min(min_r2, q);
                        max_r2 = std::max(max_r2, q);
                    }

                    overlap = std::min(std::min(max_r1, max_r2) - std::max(min_r1, min_r2), overlap);

                    if (!(max_r2 >= min_r1 && max_r1 >= min_r2))
                        return false;
                }
            }

            dir = (obj2.offset_position - obj1.offset_position);
            dir = glm::normalize(dir);
            dir *= overlap;
            return true;
        }

        bool isCollidingSQUAREtoCIRCLE(glm::vec2& dir, const Collider& obj1, const Collider& obj2) {
            //SAT method
            std::vector<glm::vec2> obj1Corner(4);
            glm::vec2 xaxis1{ glm::cos(glm::radians(obj1.angle)), glm::sin(glm::radians(obj1.angle)) };
            glm::vec2 yaxis1{ glm::cos(glm::radians(90.f + obj1.angle)), glm::sin(glm::radians(90.f + obj1.angle)) };

            obj1Corner[0] = obj1.offset_position + obj1.offset_scale.x * xaxis1 + obj1.offset_scale.y * yaxis1; //top right
            obj1Corner[1] = obj1.offset_position - obj1.offset_scale.x * xaxis1 + obj1.offset_scale.y * yaxis1; //top left
            obj1Corner[2] = obj1.offset_position - obj1.offset_scale.x * xaxis1 - obj1.offset_scale.y * yaxis1; //bot left
            obj1Corner[3] = obj1.offset_position + obj1.offset_scale.x * xaxis1 - obj1.offset_scale.y * yaxis1; //bot right

            float overlap = INFINITY;
            glm::vec2 closestPoint = obj1Corner[0];
            for (int a = 0; a < obj1Corner.size(); a++) {
                glm::vec2 temVec = { obj1Corner[a].x - obj2.offset_position.x, obj1Corner[a].y - obj2.offset_position.y };
                glm::vec2 temVec2 = { closestPoint.x - obj2.offset_position.x, closestPoint.y - obj2.offset_position.y };
                if (glm::dot(temVec, temVec) < glm::dot(temVec2, temVec2))
                    closestPoint = obj1Corner[a];
            }

            //Check circle axis (center of circle to closest point)
            glm::vec2 axisProj = { closestPoint.x - obj2.offset_position.x, closestPoint.y - obj2.offset_position.y };
            axisProj = glm::normalize(axisProj);

            float min_r1 = INFINITY, max_r1 = -INFINITY;
            for (int p = 0; p < obj1Corner.size(); p++)
            {
                float q = (obj1Corner[p].x * axisProj.x + obj1Corner[p].y * axisProj.y);
                min_r1 = std::min(min_r1, q);
                max_r1 = std::max(max_r1, q);
            }

            //Circle min and max is the same for a single axis (no need for loop)
            float min_r2 = INFINITY, max_r2 = -INFINITY;
            float q = (obj2.offset_position.x * axisProj.x + obj2.offset_position.y * axisProj.y);
            min_r2 = std::min(min_r2, q - obj2.offset_scale.x);
            max_r2 = std::max(max_r2, q + obj2.offset_scale.x);

            overlap = std::min(std::min(max_r1, max_r2) - std::max(min_r1, min_r2), overlap);

            if (!(max_r2 >= min_r1 && max_r1 >= min_r2))
                return false;

            for (int a = 0; a < obj1Corner.size(); a++) {
                int b = (a + 1) % obj1Corner.size();
                glm::vec2 axisProj = { -(obj1Corner[b].y - obj1Corner[a].y), obj1Corner[b].x - obj1Corner[a].x };
                axisProj = glm::normalize(axisProj);
                
                // Work out min and max 1D points for r1
                float min_r1 = INFINITY, max_r1 = -INFINITY;
                for (int p = 0; p < obj1Corner.size(); p++)
                {
                    float q = (obj1Corner[p].x * axisProj.x + obj1Corner[p].y * axisProj.y);
                    min_r1 = std::min(min_r1, q);
                    max_r1 = std::max(max_r1, q);
                }
                
                //Circle min and max is the same for a single axis (no need for loop)
                float min_r2 = INFINITY, max_r2 = -INFINITY;
                float q = (obj2.offset_position.x * axisProj.x + obj2.offset_position.y * axisProj.y);
                min_r2 = std::min(min_r2, q - obj2.offset_scale.x);
                max_r2 = std::max(max_r2, q + obj2.offset_scale.x);

                overlap = std::min(std::min(max_r1, max_r2) - std::max(min_r1, min_r2), overlap);

                if (!(max_r2 >= min_r1 && max_r1 >= min_r2))
                    return false;
            }

            dir = (obj2.offset_position - obj1.offset_position);
            dir = glm::normalize(dir);
            dir *= overlap;
            return true;
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
        }


        //Collision resolution-------------------------------------------------------------------------------
        void CollisionResolution(glm::vec2& dir, Transform& trans1, const Collider& col1, Transform& trans2, const Collider& col2) {
            if (col1.cType == ColliderType::CIRCLE) {
                if (col2.cType == ColliderType::CIRCLE) {
                    CollisionResolutionCIRCLEtoCIRCLE(dir, trans1, col1, trans2, col2);
                    return;
                }

                else if (col2.cType == ColliderType::SQUARE) {
                    dir = -dir;
                }
            }
            CollisionResolutionMain(dir, trans1, col1, trans2, col2);
        }

        void CollisionResolutionMain(glm::vec2& dir, Transform& trans1, const Collider& col1, Transform& trans2, const Collider& col2) {
            if (ent1IsMoveable && ent2IsMoveable) {
                trans1.position -= (dir * 0.5f);
                trans2.position += (dir * 0.5f);
            }

            //if only one moveable it should move by the full length amount
            else if (ent1IsMoveable) {
                trans1.position -= dir;
            }

            else if (ent2IsMoveable) {
                //std::cout << "Resolving 3\n";
                trans2.position += dir;
            }
        }

        //void CollisionResolutionSQUAREtoSQUARE(glm::vec2& dir, Transform& trans1, const Collider& col1, Transform& trans2, const Collider& col2) {
        //    //float lenX = 0.f, lenY = 0.f;
        //    ////Get difference in distance (see how much they intersect)
        //    //lenY = col1.offset_scale.y + col2.offset_scale.y - abs(col2.offset_position.y - col1.offset_position.y);
        //    //lenX = col1.offset_scale.x + col2.offset_scale.x - abs(col2.offset_position.x - col1.offset_position.x);
        //    ////more x mean intersect on y
        //    ////E.g one square on top of another square, lenX is huge but they are intersecting in y axis
        //    //if (lenX > lenY) lenX = 0.f;
        //    //else if (lenX < lenY) lenY = 0.f;

        //    //glm::vec2 up{ 0.f, dir.y }, right{ dir.x, 0.f };

        //    //if (ent1IsMoveable && ent2IsMoveable) {
        //    //    trans1.position += lenX / 2 * right; //for col1
        //    //    trans2.position += lenX / 2 * -right; //for col2
        //    //    trans1.position += lenY / 2 * up; //for col1
        //    //    trans2.position += lenY / 2 * -up; //for col2
        //    //}

        //    ////if only one moveable it should move by the full length amount
        //    //else if (ent1IsMoveable) {
        //    //    trans1.position += lenX * right; //for col1
        //    //    trans1.position += lenY * up; //for col1
        //    //}

        //    //else if (ent2IsMoveable) {
        //    //    trans2.position += lenX * -right; //for col2
        //    //    trans2.position += lenY * -up; //for col2
        //    //}

        //    if (ent1IsMoveable && ent2IsMoveable) {
        //        trans1.position -= (dir * 0.5f);
        //        trans2.position += (dir * 0.5f);
        //    }

        //    //if only one moveable it should move by the full length amount
        //    else if (ent1IsMoveable) {
        //        trans1.position -= dir;
        //    }

        //    else if (ent2IsMoveable) {
        //        //std::cout << "Resolving 3\n";
        //        trans2.position += dir;
        //    }

        //}

        //void CollisionResolutionSQUAREtoCIRCLE(glm::vec2& dir, Transform& trans1, const Collider& col1, Transform& trans2, const Collider& col2) {
        //    /*if (!cornerBool) {
        //        CollisionResolutionSQUAREtoSQUARE(dir, trans1, col1, trans2, col2);
        //        return;
        //    }*/

        //    //if (ent1IsMoveable && ent2IsMoveable) {
        //    //    trans1.position += length / 2 * dir;
        //    //    trans2.position += length / 2 * -dir; // for col2
        //    //}

        //    ////if only one moveable it should move by the full length amount
        //    //else if (ent1IsMoveable) {
        //    //    trans1.position += length * dir;

        //    //}

        //    //else if (ent2IsMoveable) {
        //    //    //length is calculated in collision detection
        //    //    trans2.position += length * -dir; // for col2
        //    //}
        //    if (ent1IsMoveable && ent2IsMoveable) {
        //        trans1.position -= (dir * 0.5f);
        //        trans2.position += (dir * 0.5f);
        //    }

        //    //if only one moveable it should move by the full length amount
        //    else if (ent1IsMoveable) {
        //        //std::cout << "Resolving 2\n";
        //        trans1.position -= dir;
        //    }

        //    else if (ent2IsMoveable) {
        //        //std::cout << "Resolving 3\n";
        //        trans2.position += dir;
        //    }
        //}

        /*void CollisionResolutionCIRCLEtoSQUARE(glm::vec2& dir, Transform& trans1, const Collider& col1, Transform& trans2, const Collider& col2) {
            
            CollisionResolutionSQUAREtoCIRCLE(dir, trans2, col2, trans1, col1);
        }*/

        void CollisionResolutionCIRCLEtoCIRCLE(glm::vec2& dir, Transform& trans1, const Collider& col1, Transform& trans2, const Collider& col2) {
            glm::vec2 len = col1.offset_position - col2.offset_position;
            float length = glm::length(len);

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