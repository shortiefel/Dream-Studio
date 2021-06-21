/* Start Header**********************************************************************************/
/*
@file    Physic.cpp
@author  Ow Jian Wen	jianwen123321@hotmail.com
@date    19/06/2021
\brief
This file has the function definition for Physic

collider position is in the center of itself and width and height is only half of itself total width and height

*/
/* End Header **********************************************************************************/

#include "Debug Tools/Logging.hpp" // to be removed
#include "Physic/Physic.hpp"
#include "Math/MathLib.hpp"


namespace PhysicImplementation {
   /*struct BoxCollider : Collider {
        float w, h;

       BoxCollider (float xPos, float yPos, float width, float height, bool istrigger = false) :
             w{ width }, h{ height }, Collider { xPos, yPos, ColliderType::BOX, istrigger } {}

        BoxCollider(MathD::Vec2 position, float width, float height, bool istrigger = false) :

           BoxCollider { position.x, position.y, width, height , istrigger } {}
   };

   struct CircleCollider : Collider {
       float r;

      CircleCollider(float xPos, float yPos, float radius, bool istrigger = false) :
           r { radius }, Collider{ xPos, yPos, ColliderType::CIRCLE, istrigger } {}

        CircleCollider(MathD::Vec2 position, float radius, bool istrigger = false) :

            CircleCollider{ position.x, position.y, radius, istrigger } {}
    };
   */
    
    //Collision checks-------------------------------------------------------------------------------
    bool isColliding(const Collider& obj1, const Collider& obj2) {
        if (obj1.cType == ColliderType::CIRCLE) {
            if (obj2.cType == ColliderType::CIRCLE)
                return isCollidingCIRCLEtoCIRCLE(obj1, obj2);
            else
                return isCollidingCIRCLEtoBOX(obj1, obj2);

        }

        else {
            if (obj2.cType == ColliderType::CIRCLE)
                return isCollidingBOXtoCIRCLE(obj1, obj2);
            else
                return isCollidingBOXtoBOX(obj1, obj2);
        }

        return false;
    }

    bool isCollidingBOXtoBOX(const Collider& obj1, const Collider& obj2) {
        if (obj1.pos.x + obj1.scale.x < obj2.pos.x - obj2.scale.x ||
            obj1.pos.x - obj1.scale.x > obj2.pos.x + obj2.scale.x ||
            obj1.pos.y + obj1.scale.y < obj2.pos.y - obj2.scale.y ||
            obj1.pos.y - obj1.scale.y > obj2.pos.y + obj2.scale.y)
            return false;
        return true;
    }

    bool isCollidingBOXtoCIRCLE(const Collider& obj1, const Collider& obj2) {
        //Reference: https://gamedev.stackexchange.com/questions/96337/collision-between-aabb-and-circle

        //if collision between box as a circle (longest side = radius) and circle is false 
        //then box and circle doesnt collide
        //longest side is pythagaros theorem of width/2 and height/2
        Collider tem{ ColliderType::CIRCLE, obj1.pos,
                            MathD::Vec2 { MathD::getLength(obj1.scale.x, obj1.scale.y), 0.f},
                            obj1.isMoveable,
                            obj1.isTrigger };


        if (!isCollidingCIRCLEtoCIRCLE(tem, obj2)) return false;

        //Colliding with inner circle
        //tem.scale.x = obj1.scale.x < obj1.scale.y ? obj1.scale.x / 2.f : obj1.scale.y / 2.f;
        tem.scale.x = obj1.scale.x < obj1.scale.y ? obj1.scale.x : obj1.scale.y;
        if (isCollidingCIRCLEtoCIRCLE(tem, obj2)) return true;

        //p = Point on circle that is closest to the box object
        MathD::Vec2 p = obj2.pos + obj2.scale.x * (obj1.pos - obj2.pos);
        //if p is in box then there is collision
        /*if (p.x > obj1.pos.x && p.x < obj1.pos.x + obj1.scale.x && 
            p.y > obj1.pos.y && p.y < obj1.pos.y + obj1.scale.y)*/
        if (p.x > obj1.pos.x - obj1.scale.x && p.x < obj1.pos.x + obj1.scale.x &&
            p.y > obj1.pos.y - obj1.scale.y && p.y < obj1.pos.y + obj1.scale.y)
            return true;

        return false;
    }

    bool isCollidingCIRCLEtoBOX(const Collider& obj1, const Collider& obj2) {
        return isCollidingBOXtoCIRCLE(obj2, obj1);
    }

    bool isCollidingCIRCLEtoCIRCLE(const Collider& obj1, const Collider& obj2) {
        float rad = obj1.scale.x + obj2.scale.x;
        rad = pow(rad,2);
        MathD::Vec2 tem = obj1.pos - obj2.pos;
        /*float tl = abs(tem.x) + abs(tem.y);
        tl = pow(tl, 2);*/
        float tl = tem.x * tem.x + tem.y * tem.y;

        if (rad < tl) return false;
        return true;
    }


    //Collision resolution-------------------------------------------------------------------------------
    void CollisionResolution(Transform& trans1, const Collider& col1, Transform& trans2, const Collider& col2) {
        if (col1.cType == ColliderType::CIRCLE) {
            if (col2.cType == ColliderType::CIRCLE)
                CollisionResolutionCIRCLEtoCIRCLE(trans1, col1, trans2, col2);
            else
                CollisionResolutionCIRCLEtoBOX(trans1, col1, trans2, col2);
        }

        else {
            if (col2.cType == ColliderType::CIRCLE)
                CollisionResolutionBOXtoCIRCLE(trans1, col1, trans2, col2);
            else
                CollisionResolutionBOXtoBOX(trans1, col1, trans2, col2);
        }
    }

    void CollisionResolutionBOXtoBOX(Transform& trans1, const Collider& col1, Transform& trans2, const Collider& col2) {
        MathD::Vec2 dir = col2.pos - col1.pos;
        Normalize(dir, dir);
        //dot product normalized dir with x-axis vector = cos rad between them
        //acos give rad of angle and degree changes it to degress
        //int angle = static_cast<int>(MathD::degrees(acos(DotProduct(dir, MathD::Vec2{ 1.f, 0.f }))));
        ////make angle between 0 - 360
        //angle = angle % 360;
        ////make angle between 0 - 180
        //angle -= 180;
        //angle = abs(angle);
        //angle = static_cast<int>(angle * (col1.scale.x / col1.scale.y));
        //angle = static_cast<int>(angle * (col2.scale.x / col2.scale.y));
        
        float lenX = 0.f, lenY = 0.f;
        //if angle = 45/135 move in x and y axis
        /*if (angle == 45 || angle == 135) {
            lenX = col1.scale.x + col2.scale.x - abs(col2.pos.x - col1.pos.x);
            lenY = col1.scale.y + col2.scale.y - abs(col2.pos.y - col1.pos.y);
        }*/

        //between 45 and 135 move in y axis
        //if (angle > 45 && angle < 135) {
            lenY = col1.scale.y + col2.scale.y - abs(col2.pos.y - col1.pos.y);
        //}

        //0 - 45, 135 - 180 move in x axis
        //else {
            lenX = col1.scale.x + col2.scale.x - abs(col2.pos.x - col1.pos.x);
        //}

            if (lenX > lenY) lenX = 0.f;
            else if (lenX < lenY) lenY = 0.f;

        MathD::Vec2 up{ 0.f, dir.y }, right{ dir.x, 0.f };

        if (col1.isMoveable && col2.isMoveable) {
            trans1.pos += lenX / 2 * -right; //for col1
            trans2.pos += lenX / 2 * right; //for col2
            trans1.pos += lenY / 2 * -up; //for col1
            trans2.pos += lenY / 2 * up; //for col2
        }

        //if only one moveable it should move by the full length amount
        else if (col1.isMoveable) {
            trans1.pos += lenX * -right; //for col1
            trans1.pos += lenY * -up; //for col1
        }

        else if (col2.isMoveable) {
            trans2.pos += lenX * right; //for col2
            trans2.pos += lenY * up; //for col2
        }
    }

    void CollisionResolutionBOXtoCIRCLE(Transform& trans1, const Collider& col1, Transform& trans2, const Collider& col2) {

    }

    void CollisionResolutionCIRCLEtoBOX(Transform& trans1, const Collider& col1, Transform& trans2, const Collider& col2) {
        CollisionResolutionBOXtoCIRCLE(trans2, col2, trans1, col1);
    }

    void CollisionResolutionCIRCLEtoCIRCLE(Transform& trans1, const Collider& col1, Transform& trans2, const Collider& col2) {
        MathD::Vec2 dir = col2.pos - col1.pos;
        float length = Length(dir);
        dir = dir / length; //normalize
        //length is the distance between the two object
        length = col1.scale.x + col2.scale.x - length;

        //E.g object1 is radius 5, object2 is radius 3
        //distance between the two object is 7, difference between distance and total radius is 1
        //but if both object were to move, they would only move by 0.5 (hence the first if statement)

        //if both moveable then both will move length/2 in direction opposite each other
        //since dir is from col1, object2 will move in dir and object1 will move in -dir
        if (col1.isMoveable && col2.isMoveable) {
            trans1.pos += length / 2 * -dir; //for col1
            trans2.pos += length / 2 * dir; //for col2
        }

        //if only one moveable it should move by the full length amount
        else if (col1.isMoveable) {
            trans1.pos += length * -dir; //for col1
        }

        else if (col2.isMoveable) {
            trans2.pos += length * dir; //for col2
        }
    }
   
}

//    bool isColliding(BoxCollider obj1, BoxCollider obj2) {
//        /*if (obj1.pos.x + obj1.w < obj2.pos.x ||
//            obj1.pos.x          > obj2.pos.x + obj2.w  ||
//            obj1.pos.y + obj1.h < obj2.pos.y ||
//            obj1.pos.y          > obj2.pos.y + obj2.h)
//            return false;*/
//        return true;
//    }
//
//    bool isColliding(BoxCollider obj1, CircleCollider obj2) {
//        //Reference: https://gamedev.stackexchange.com/questions/96337/collision-between-aabb-and-circle
//
//        //if collision between box as a circle (longest side = radius) and circle is false 
//        //then box and circle doesnt collide
//        //longest side is pythagaros theorem of width/2 and height/2
//        //CircleCollider tem{ obj1.pos,
//        //                    getLongestSide (obj1.w, obj1.h),
//        //                    obj1.isTrigger };
//
//
//        //if (!isColliding(tem, obj2)) return false;
//
//        ////Colliding with inner circle
//        //tem.r = obj1.w < obj1.h ? obj1.w/2.f : obj1.h/2.f;
//        //if (isColliding(tem, obj2)) return true;
//
//        ////p = Point on circle that is closest to the box object
//        //Vec2 p = obj2.pos + obj2.r * (obj1.pos - obj2.pos);
//        ////if p is in box then there is collision
//        //if (p.x > obj1.pos.x && p.x < obj1.pos.x + obj1.w && 
//        //    p.y > obj1.pos.y && p.y < obj1.pos.y + obj1.h)
//        //    return true;
//
//        return false;
//    }
//
//    bool isColliding(CircleCollider obj1, BoxCollider obj2) {
//        return isColliding(obj2, obj1);
//    }
//
//    bool isColliding(CircleCollider obj1, CircleCollider obj2) {
//        /*float rad = obj1.r + obj2.r;
//        rad = pow(rad,2);
//        Vec2 tem = obj1.pos - obj2.pos;
//        float tl = abs(tem.x) + abs(tem.y);
//        tl = pow(tl, 2);
//
//        if (rad < tl) return false;*/
//        return true;
//    }
//}