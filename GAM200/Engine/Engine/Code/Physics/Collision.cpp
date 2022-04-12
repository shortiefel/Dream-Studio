/* Start Header**********************************************************************************/
/*
@file    Collision.cpp
@author  Ow Jian Wen	jianwen.o@digipen.edu   	100%
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
#include "Engine/Header/Physics/Collision.hpp"
#include "Engine/Header/ECS/Component/Physics/ColliderComponent.hpp"
#include "Engine/Header/ECS/Component/Graphics/TransformComponent.hpp"

#include "Engine/Header/Parent/ParentManager.hpp"

#include "Engine/Header/Physics/Ray.hpp"
#include <iostream>

//https://en.wikipedia.org/wiki/Line%E2%80%93line_intersection
#define GET_T(det, v1, v2, v3, v4)\
((v1.x - v3.x) * (v3.y - v4.y) - (v1.y - v3.y) * (v3.x - v4.x)) / det

#define GET_U(det, v1, v2, v3, v4)\
-((v1.x - v2.x) * (v1.y - v3.y) - (v1.y - v2.y) * (v1.x - v3.x)) / det

#define GET_DET(v1, v2, v3, v4)\
(v1.x - v2.x) * (v3.y - v4.y) - (v1.y - v2.y) * (v3.x - v4.x)


namespace Engine {
    //Check if entity have rigidbody (movable)
    bool ent1IsMoveable, ent2IsMoveable;

    namespace CollisionImplementation {
        //Collision checks-------------------------------------------------------------------------------
        bool isColliding(Math::vec2& dir, const ColliderComponent& obj1, bool ent1Moveable, const ColliderComponent& obj2, bool ent2Moveable) {
            ent1IsMoveable = ent1Moveable;
            ent2IsMoveable = ent2Moveable;

            if (obj1.cType == ColliderType::Circle) {
                if (obj2.cType == ColliderType::Circle)
                    return isCollidingCIRCLEtoCIRCLE(dir, obj1, obj2);
                else
                    return isCollidingCIRCLEtoSQUARE(dir, obj1, obj2);
            }

            else {
                if (obj2.cType == ColliderType::Circle)
                    return isCollidingSQUAREtoCIRCLE(dir, obj1, obj2);
                else
                    return isCollidingSQUAREtoSQUARE(dir, obj1, obj2);
            }

            return false;
        }

        bool isCollidingSQUAREtoSQUARE(Math::vec2& dir, const ColliderComponent& obj1, const ColliderComponent& obj2) {
            //SAT method
            std::vector<Math::vec2> obj1Corner(4);
            Math::vec2 xaxis1{ Math::cos(Math::radians(obj1.angle)), Math::sin(Math::radians(obj1.angle)) };
            Math::vec2 yaxis1{ Math::cos(Math::radians(90.f + obj1.angle)), Math::sin(Math::radians(90.f + obj1.angle)) };

            obj1Corner[0] = obj1.offset_position + obj1.offset_scale.x * xaxis1 + obj1.offset_scale.y * yaxis1; //top right
            obj1Corner[1] = obj1.offset_position - obj1.offset_scale.x * xaxis1 + obj1.offset_scale.y * yaxis1; //top left
            obj1Corner[2] = obj1.offset_position - obj1.offset_scale.x * xaxis1 - obj1.offset_scale.y * yaxis1; //bot left
            obj1Corner[3] = obj1.offset_position + obj1.offset_scale.x * xaxis1 - obj1.offset_scale.y * yaxis1; //bot right

            std::vector<Math::vec2> obj2Corner(4);
            Math::vec2 xaxis2{ Math::cos(Math::radians(obj2.angle)), Math::sin(Math::radians(obj2.angle)) };
            Math::vec2 yaxis2{ Math::cos(Math::radians(90 + obj2.angle)), Math::sin(Math::radians(90 + obj2.angle)) };

            obj2Corner[0] = obj2.offset_position + obj2.offset_scale.x * xaxis2 + obj2.offset_scale.y * yaxis2; //top right
            obj2Corner[1] = obj2.offset_position - obj2.offset_scale.x * xaxis2 + obj2.offset_scale.y * yaxis2; //top left
            obj2Corner[2] = obj2.offset_position - obj2.offset_scale.x * xaxis2 - obj2.offset_scale.y * yaxis2; //bot left
            obj2Corner[3] = obj2.offset_position + obj2.offset_scale.x * xaxis2 - obj2.offset_scale.y * yaxis2; //bot right

            std::vector<Math::vec2>* shape1 = &obj1Corner;
            std::vector<Math::vec2>* shape2 = &obj2Corner;

            float overlap = INFINITY;

            for (int num = 0; num < 2; num++) {
                if (num == 1) {
                    shape1 = &obj2Corner;
                    shape2 = &obj1Corner;
                }
                for (int a = 0; a < shape1->size(); a++) {
                    int b = (a + (int)1) % (int)shape1->size();
                    Math::vec2 axisProj = { -((*shape1)[b].y - (*shape1)[a].y), (*shape1)[b].x - (*shape1)[a].x };
                    axisProj = Math::normalize(axisProj);

                    // Work out min and max 1D points for r1
                    float min_r1 = INFINITY, max_r1 = -INFINITY;
                    for (int p = 0; p < shape1->size(); p++)
                    {
                        float q = ((*shape1)[p].x * axisProj.x + (*shape1)[p].y * axisProj.y);
                        min_r1 = Math::Min(min_r1, q);
                        max_r1 = Math::Max(max_r1, q);
                    }

                    // Work out min and max 1D points for r2
                    float min_r2 = INFINITY, max_r2 = -INFINITY;
                    for (int p = 0; p < shape2->size(); p++)
                    {
                        float q = ((*shape2)[p].x * axisProj.x + (*shape2)[p].y * axisProj.y);
                        min_r2 = Math::Min(min_r2, q);
                        max_r2 = Math::Max(max_r2, q);
                    }

                    overlap = Math::Min(Math::Min(max_r1, max_r2) - Math::Max(min_r1, min_r2), overlap);

                    if (!(max_r2 >= min_r1 && max_r1 >= min_r2))
                        return false;
                }
            }

            dir = (obj2.offset_position - obj1.offset_position);
            dir = Math::normalize(dir);
            dir *= overlap;
            return true;
        }

        bool isCollidingSQUAREtoCIRCLE(Math::vec2& dir, const ColliderComponent& obj1, const ColliderComponent& obj2) {
            //SAT method
            std::vector<Math::vec2> obj1Corner(4);
            Math::vec2 xaxis1{ Math::cos(Math::radians(obj1.angle)), Math::sin(Math::radians(obj1.angle)) };
            Math::vec2 yaxis1{ Math::cos(Math::radians(90.f + obj1.angle)), Math::sin(Math::radians(90.f + obj1.angle)) };

            obj1Corner[0] = obj1.offset_position + obj1.offset_scale.x * xaxis1 + obj1.offset_scale.y * yaxis1; //top right
            obj1Corner[1] = obj1.offset_position - obj1.offset_scale.x * xaxis1 + obj1.offset_scale.y * yaxis1; //top left
            obj1Corner[2] = obj1.offset_position - obj1.offset_scale.x * xaxis1 - obj1.offset_scale.y * yaxis1; //bot left
            obj1Corner[3] = obj1.offset_position + obj1.offset_scale.x * xaxis1 - obj1.offset_scale.y * yaxis1; //bot right

            float overlap = INFINITY;
            Math::vec2 closestPoint = obj1Corner[0];
            for (int a = 0; a < obj1Corner.size(); a++) {
                Math::vec2 temVec = { obj1Corner[a].x - obj2.offset_position.x, obj1Corner[a].y - obj2.offset_position.y };
                Math::vec2 temVec2 = { closestPoint.x - obj2.offset_position.x, closestPoint.y - obj2.offset_position.y };
                if (Math::dot(temVec, temVec) < Math::dot(temVec2, temVec2))
                    closestPoint = obj1Corner[a];
            }

            //Check circle axis (center of circle to closest point)
            Math::vec2 axisProj = { closestPoint.x - obj2.offset_position.x, closestPoint.y - obj2.offset_position.y };
            axisProj = Math::normalize(axisProj);

            float min_r1 = INFINITY, max_r1 = -INFINITY;
            for (int p = 0; p < obj1Corner.size(); p++)
            {
                float q = (obj1Corner[p].x * axisProj.x + obj1Corner[p].y * axisProj.y);
                min_r1 = Math::Min(min_r1, q);
                max_r1 = Math::Max(max_r1, q);
            }

            //Circle min and max is the same for a single axis (no need for loop)
            float min_r2 = INFINITY, max_r2 = -INFINITY;
            float q = (obj2.offset_position.x * axisProj.x + obj2.offset_position.y * axisProj.y);
            min_r2 = Math::Min(min_r2, q - obj2.offset_scale.x);
            max_r2 = Math::Max(max_r2, q + obj2.offset_scale.x);

            overlap = Math::Min(Math::Min(max_r1, max_r2) - Math::Max(min_r1, min_r2), overlap);

            if (!(max_r2 >= min_r1 && max_r1 >= min_r2))
                return false;

            for (int a = 0; a < obj1Corner.size(); a++) {
                int b = (a + (int)1) % (int)obj1Corner.size();
                Math::vec2 axisProj2 = { -(obj1Corner[b].y - obj1Corner[a].y), obj1Corner[b].x - obj1Corner[a].x };
                axisProj2 = Math::normalize(axisProj2);

                // Work out min and max 1D points for r1
                float min2_r1 = INFINITY, max2_r1 = -INFINITY;
                for (int p = 0; p < obj1Corner.size(); p++)
                {
                    float q1 = (obj1Corner[p].x * axisProj2.x + obj1Corner[p].y * axisProj2.y);
                    min2_r1 = Math::Min(min2_r1, q1);
                    max2_r1 = Math::Max(max2_r1, q1);
                }

                //Circle min and max is the same for a single axis (no need for loop)
                float min2_r2 = INFINITY, max2_r2 = -INFINITY;
                float q1 = (obj2.offset_position.x * axisProj2.x + obj2.offset_position.y * axisProj2.y);
                min2_r2 = Math::Min(min2_r2, q1 - obj2.offset_scale.x);
                max2_r2 = Math::Max(max2_r2, q1 + obj2.offset_scale.x);

                overlap = Math::Min(Math::Min(max2_r1, max2_r2) - Math::Max(min2_r1, min2_r2), overlap);

                if (!(max2_r2 >= min2_r1 && max2_r1 >= min2_r2))
                    return false;
            }

            dir = (obj2.offset_position - obj1.offset_position);
            dir = Math::normalize(dir);
            dir *= overlap;
            return true;
        }

        bool isCollidingCIRCLEtoSQUARE(Math::vec2& dir, const ColliderComponent& obj1, const ColliderComponent& obj2) {
            return isCollidingSQUAREtoCIRCLE(dir, obj2, obj1);
        }

        bool isCollidingCIRCLEtoCIRCLE(Math::vec2& dir, const ColliderComponent& obj1, const ColliderComponent& obj2) {
            //if (obj1.scale.x == obj1.scale.y && obj2.scale.x == obj2.scale.y) {
            float rad = obj1.offset_scale.x + obj2.offset_scale.x;
            rad = (float)pow(rad, 2);
            dir = obj1.offset_position - obj2.offset_position;
            float tl = dir.x * dir.x + dir.y * dir.y;

            if (rad < tl) return false;
            //only calculate if it collides
            dir = Math::normalize(dir);
            return true;
        }


        //Collision resolution-------------------------------------------------------------------------------
        void CollisionResolution(Math::vec2& dir, TransformComponent& trans1, const ColliderComponent& col1, TransformComponent& trans2, const ColliderComponent& col2) {
            if (col1.cType == ColliderType::Circle) {
                if (col2.cType == ColliderType::Circle) {
                    CollisionResolutionCIRCLEtoCIRCLE(dir, trans1, col1, trans2, col2);
                    return;
                }

                else if (col2.cType == ColliderType::Square) {
                    dir = -dir;
                }
            }
            CollisionResolutionMain(dir, trans1, col1, trans2, col2);
        }

        void CollisionResolutionMain(Math::vec2& dir, TransformComponent& trans1, const ColliderComponent&, TransformComponent& trans2, const ColliderComponent&) {
            if (ent1IsMoveable && ent2IsMoveable) {
                trans1.position -= (dir * 0.5f);
                ParentManager::GetInstance().UpdateLocalPos(trans1.GetEntityId());
                trans2.position += (dir * 0.5f);
                ParentManager::GetInstance().UpdateLocalPos(trans2.GetEntityId());
            }

            //if only one moveable it should move by the full length amount
            else if (ent1IsMoveable) {
                trans1.position -= dir;
                ParentManager::GetInstance().UpdateLocalPos(trans1.GetEntityId());
            }

            else if (ent2IsMoveable) {
      
                trans2.position += dir;
                ParentManager::GetInstance().UpdateLocalPos(trans2.GetEntityId());
            }
        }

        //void CollisionResolutionSQUAREtoSQUARE(Math::vec2& dir, Transform& trans1, const Collider& col1, Transform& trans2, const Collider& col2) {
        //    //float lenX = 0.f, lenY = 0.f;
        //    ////Get difference in distance (see how much they intersect)
        //    //lenY = col1.offset_scale.y + col2.offset_scale.y - abs(col2.offset_position.y - col1.offset_position.y);
        //    //lenX = col1.offset_scale.x + col2.offset_scale.x - abs(col2.offset_position.x - col1.offset_position.x);
        //    ////more x mean intersect on y
        //    ////E.g one square on top of another square, lenX is huge but they are intersecting in y axis
        //    //if (lenX > lenY) lenX = 0.f;
        //    //else if (lenX < lenY) lenY = 0.f;

        //    //Math::vec2 up{ 0.f, dir.y }, right{ dir.x, 0.f };

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

        //void CollisionResolutionSQUAREtoCIRCLE(Math::vec2& dir, Transform& trans1, const Collider& col1, Transform& trans2, const Collider& col2) {
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

        /*void CollisionResolutionCIRCLEtoSQUARE(Math::vec2& dir, Transform& trans1, const Collider& col1, Transform& trans2, const Collider& col2) {

            CollisionResolutionSQUAREtoCIRCLE(dir, trans2, col2, trans1, col1);
        }*/

        void CollisionResolutionCIRCLEtoCIRCLE(Math::vec2& dir, TransformComponent& trans1, const ColliderComponent& col1, TransformComponent& trans2, const ColliderComponent& col2) {
            Math::vec2 len = col1.offset_position - col2.offset_position;
            float length = Math::length(len);

            //length is the distance between the two object
            length = col1.offset_scale.x + col2.offset_scale.x - length;

            //E.g object1 is radius 5, object2 is radius 3
            //distance between the two object is 7, difference between distance and total radius is 1
            //but if both object were to move, they would only move by 0.5 (hence the first if statement)

            //if both moveable then both will move length/2 in direction opposite each other
            //since dir is from col1, object2 will move in dir and object1 will move in -dir
            if (ent1IsMoveable && ent2IsMoveable) {
                trans1.position += length / 2 * dir; //for col1
                ParentManager::GetInstance().UpdateLocalPos(trans1.GetEntityId());
                trans2.position += length / 2 * -dir; //for col2
                ParentManager::GetInstance().UpdateLocalPos(trans2.GetEntityId());
            }

            //if only one moveable it should move by the full length amount
            else if (ent1IsMoveable) {
                trans1.position += length * dir; //for col1
                ParentManager::GetInstance().UpdateLocalPos(trans1.GetEntityId());
            }

            else if (ent2IsMoveable) {
                trans2.position += length * -dir; //for col2
                ParentManager::GetInstance().UpdateLocalPos(trans2.GetEntityId());
            }
        }

        bool PointToSquareAABB(const Math::vec2& pt, const ColliderComponent& obj) {
            std::vector<Math::vec2> obj1Corner(4);
            obj1Corner[0] = obj.offset_position + obj.offset_scale.x * Math::vec2{ 1.f, 0.f } + obj.offset_scale.y * Math::vec2{ 0.f, 1.f }; //top right
            obj1Corner[1] = obj.offset_position - obj.offset_scale.x * Math::vec2{ 1.f, 0.f } + obj.offset_scale.y * Math::vec2{ 0.f, 1.f }; //top left
            obj1Corner[2] = obj.offset_position - obj.offset_scale.x * Math::vec2{ 1.f, 0.f } - obj.offset_scale.y * Math::vec2{ 0.f, 1.f }; //bot left
            obj1Corner[3] = obj.offset_position + obj.offset_scale.x * Math::vec2{ 1.f, 0.f } - obj.offset_scale.y * Math::vec2{ 0.f, 1.f }; //bot right

            float
                left = obj.offset_position.x - obj.offset_scale.x,
                right = obj.offset_position.x + obj.offset_scale.x,
                top = obj.offset_position.y + obj.offset_scale.y,
                bot = obj.offset_position.y - obj.offset_scale.y;

            return (pt.x > left && pt.x < right&& pt.y > bot && pt.y < top);
        }

        bool PointToSquareSAT(const Math::vec2& pt, const ColliderComponent& obj) {
            std::vector<Math::vec2> objCorner(4);
            Math::vec2 xaxis{ Math::cos(Math::radians(obj.angle)), Math::sin(Math::radians(obj.angle)) };
            Math::vec2 yaxis{ Math::cos(Math::radians(90.f + obj.angle)), Math::sin(Math::radians(90.f + obj.angle)) };

            objCorner[0] = obj.offset_position + obj.offset_scale.x * xaxis + obj.offset_scale.y * yaxis; //top right
            objCorner[1] = obj.offset_position - obj.offset_scale.x * xaxis + obj.offset_scale.y * yaxis; //top left
            objCorner[2] = obj.offset_position - obj.offset_scale.x * xaxis - obj.offset_scale.y * yaxis; //bot left
            objCorner[3] = obj.offset_position + obj.offset_scale.x * xaxis - obj.offset_scale.y * yaxis; //bot right

            return
                (Math::dot(pt - objCorner[0], objCorner[1] - objCorner[0]) >= 0.f) &&
                (Math::dot(pt - objCorner[1], objCorner[2] - objCorner[1]) >= 0.f) &&
                (Math::dot(pt - objCorner[2], objCorner[3] - objCorner[2]) >= 0.f) &&
                (Math::dot(pt - objCorner[3], objCorner[0] - objCorner[3]) >= 0.f);
        }

        bool RayCast_Internal(const Engine::Ray& ray, const TransformComponent& transform, const ColliderComponent& collider, RaycastHit* hit) {
            ColliderComponent combined = collider;
            combined.offset_position += Math::vec2{ transform.position };
            combined.offset_scale *= transform.scale;
            combined.angle += transform.angle;

            const Math::vec2 rayEnd = ray.pos + (ray.dir * ray.length);

            std::vector<Math::vec2> obj1Corner(4);
            Math::vec2 xaxis1{ Math::cos(Math::radians(combined.angle)), Math::sin(Math::radians(combined.angle)) };
            Math::vec2 yaxis1{ Math::cos(Math::radians(90.f + combined.angle)), Math::sin(Math::radians(90.f + combined.angle)) };

            obj1Corner[0] = combined.offset_position + combined.offset_scale.x * xaxis1 + combined.offset_scale.y * yaxis1; //top right
            obj1Corner[1] = combined.offset_position - combined.offset_scale.x * xaxis1 + combined.offset_scale.y * yaxis1; //top left
            obj1Corner[2] = combined.offset_position - combined.offset_scale.x * xaxis1 - combined.offset_scale.y * yaxis1; //bot left
            obj1Corner[3] = combined.offset_position + combined.offset_scale.x * xaxis1 - combined.offset_scale.y * yaxis1; //bot right

            auto& ht = *hit;
            //Point in square check
            if (Math::EpsilonCheck(ray.pos, rayEnd)) {

                for (int i = 0; i < 4; i++) {
                    Math::vec2 nl = obj1Corner[(i + 1) < 4 ? i + 1 : 0] - obj1Corner[i];
                    Math::vec2 normal{ -nl.y, nl.x };
                    normal = Math::normalize(normal);

                    float tem = Math::dot(rayEnd - obj1Corner[i], normal);
                    /*if (tem < ht.distance) {
                        ht.distance = tem;
                        ht.point = rayEnd + -normal * tem;
                    }*/
                    if (tem < 0) return false;
                }
                //Set point as checking point (ray.pos) as its point vs ray
                ht.distance = 0.f;
                ht.point = ray.pos;

                return true;
            }

            //Intersection
            //Ray = p + uv : 0 < u
            //Line = q + tv : 0 < t < 1
            for (int i = 0; i < 4; i++) {
                const float det1 = GET_DET(obj1Corner[i], obj1Corner[(i + 1) < 4 ? i + 1 : 0], ray.pos, rayEnd);
                if (Math::EpsilonCheck(det1)) {
                    continue;
                }

                const float t1 = GET_T(det1, obj1Corner[i], obj1Corner[(i + 1) < 4 ? i + 1 : 0], ray.pos, rayEnd);
                const float u1 = GET_U(det1, obj1Corner[i], obj1Corner[(i + 1) < 4 ? i + 1 : 0], ray.pos, rayEnd);
                if (t1 > 0 && t1 < 1 && u1 > 0 && u1 < 1) {
                    ht.point = ray.pos + (u1 * (rayEnd - ray.pos));
                    ht.distance = Math::distance(ray.pos, ht.point);
                    return true;
                }
            }

            return false;
        }
    }
}