/* Start Header**********************************************************************************/
/*
@file    Physic.cpp
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

#include "Debug Tools/Logging.hpp" // to be removed
#include "Physic/Physic.hpp"
#include "ECS/Component/Physics/ColliderComponent.hpp"
#include "ECS/Component/Graphics/TransformComponent.hpp"

//Both used only for square to circle collision
//Nearest point on square to circle
MathD::Vec2 nearestPoint = MathD::Vec2{};
//Length of nearest point to center of circle
float length = float{}; //Reused for circle circle
//Check whether it is in corner
bool cornerBool = bool{};

namespace PhysicImplementation {
    //Collision checks-------------------------------------------------------------------------------
    bool isColliding(MathD::Vec2& dir, const Collider& obj1, const Collider& obj2) {
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

    bool isCollidingSQUAREtoSQUARE(MathD::Vec2& dir, const Collider& obj1, const Collider& obj2) {
        //Check whether obj1 is outside range of obj2
        if (obj1.pos.x + obj1.scale.x < obj2.pos.x - obj2.scale.x ||
            obj1.pos.x - obj1.scale.x > obj2.pos.x + obj2.scale.x ||
            obj1.pos.y + obj1.scale.y < obj2.pos.y - obj2.scale.y ||
            obj1.pos.y - obj1.scale.y > obj2.pos.y + obj2.scale.y)
            return false;

        dir = (obj1.pos - obj2.pos);
        Normalize(dir, dir);
        return true;
    }

    bool isCollidingSQUAREtoCIRCLE(MathD::Vec2& dir, const Collider& col1, const Collider& col2) {
        cornerBool = true;
        //Check if circle is corner of square (same logic as square to square collision
        if (col2.pos.x < col1.pos.x - col1.scale.x)
            nearestPoint.x = col1.pos.x - col1.scale.x;
        else if (col2.pos.x > col1.pos.x + col1.scale.x)
            nearestPoint.x = col1.pos.x + col1.scale.x;
        else {
            cornerBool = false;
        }

        if (col2.pos.y < col1.pos.y - col1.scale.y)
            nearestPoint.y = col1.pos.y - col1.scale.y;
        else if (col2.pos.y > col1.pos.y + col1.scale.y)
            nearestPoint.y = col1.pos.y + col1.scale.y;
        else {
            cornerBool = false;
        }
    
        if (cornerBool) {
            //Store how much it intersect
            length = col2.scale.x - Length(nearestPoint - col2.pos);
            if (length < 0) return false;
    
            dir = col1.pos - col2.pos;
            Normalize(dir, dir);
            return true;
        }
    
        else {
            return isCollidingSQUAREtoSQUARE(dir, col1, col2);
        }
    
        return false;
    }

    bool isCollidingCIRCLEtoSQUARE(MathD::Vec2& dir, const Collider& obj1, const Collider& obj2) {
        return isCollidingSQUAREtoCIRCLE(dir, obj2, obj1);
    }

    bool isCollidingCIRCLEtoCIRCLE(MathD::Vec2& dir, const Collider& obj1, const Collider& obj2) {
        //if (obj1.scale.x == obj1.scale.y && obj2.scale.x == obj2.scale.y) {
            float rad = obj1.scale.x + obj2.scale.x;
            rad = pow(rad, 2);
            dir = obj1.pos - obj2.pos;
            float tl = dir.x * dir.x + dir.y * dir.y;
            
            if (rad < tl) return false;
            //only calculate if it collides
            Normalize(dir, dir);
            return true;
        /*}

        else {
            return false;
        }*/
    }


    //Collision resolution-------------------------------------------------------------------------------
    void CollisionResolution(MathD::Vec2& dir, Transform& trans1, const Collider& col1, Transform& trans2, const Collider& col2) {
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

    void CollisionResolutionSQUAREtoSQUARE(MathD::Vec2& dir, Transform& trans1, const Collider& col1, Transform& trans2, const Collider& col2) {
        float lenX = 0.f, lenY = 0.f;
        //Get difference in distance (see how much they intersect)
        lenY = col1.scale.y + col2.scale.y - abs(col2.pos.y - col1.pos.y);
        lenX = col1.scale.x + col2.scale.x - abs(col2.pos.x - col1.pos.x);
        //more x mean intersect on y
        //E.g one square on top of another square, lenX is huge but they are intersecting in y axis
        if (lenX > lenY) lenX = 0.f;
        else if (lenX < lenY) lenY = 0.f;

        MathD::Vec2 up{ 0.f, dir.y }, right{ dir.x, 0.f };

        if (col1.isMoveable && col2.isMoveable) {
            trans1.pos += lenX / 2 * right; //for col1
            trans2.pos += lenX / 2 * -right; //for col2
            trans1.pos += lenY / 2 * up; //for col1
            trans2.pos += lenY / 2 * -up; //for col2
        }

        //if only one moveable it should move by the full length amount
        else if (col1.isMoveable) {
            trans1.pos += lenX * right; //for col1
            trans1.pos += lenY * up; //for col1
        }

        else if (col2.isMoveable) {
            trans2.pos += lenX * -right; //for col2
            trans2.pos += lenY * -up; //for col2
        }
    }

    void CollisionResolutionSQUAREtoCIRCLE(MathD::Vec2& dir, Transform& trans1, const Collider& col1, Transform& trans2, const Collider& col2) {
        if (!cornerBool) {
            CollisionResolutionSQUAREtoSQUARE(dir, trans1, col1, trans2, col2);
            return;
        }

        if (col1.isMoveable && col2.isMoveable) {
            trans1.pos += length / 2 * dir;
            trans2.pos += length / 2 * -dir; // for col2
        }

        //if only one moveable it should move by the full length amount
        else if (col1.isMoveable) {
            trans1.pos += length * dir;
            
        }

        else if (col2.isMoveable) {
            //length is calculated in collision detection
            trans2.pos += length * -dir; // for col2
        }
    }

    void CollisionResolutionCIRCLEtoSQUARE(MathD::Vec2& dir, Transform& trans1, const Collider& col1, Transform& trans2, const Collider& col2) {
        CollisionResolutionSQUAREtoCIRCLE(dir, trans2, col2, trans1, col1);
    }

    void CollisionResolutionCIRCLEtoCIRCLE(MathD::Vec2& dir, Transform& trans1, const Collider& col1, Transform& trans2, const Collider& col2) {
        MathD::Vec2 len = col1.pos - col2.pos;
        length = Length(len);
        
        //length is the distance between the two object
        length = col1.scale.x + col2.scale.x - length;

        //E.g object1 is radius 5, object2 is radius 3
        //distance between the two object is 7, difference between distance and total radius is 1
        //but if both object were to move, they would only move by 0.5 (hence the first if statement)

        //if both moveable then both will move length/2 in direction opposite each other
        //since dir is from col1, object2 will move in dir and object1 will move in -dir
        if (col1.isMoveable && col2.isMoveable) {
            trans1.pos += length / 2 * dir; //for col1
            trans2.pos += length / 2 * -dir; //for col2
        }

        //if only one moveable it should move by the full length amount
        else if (col1.isMoveable) {
            trans1.pos += length * dir; //for col1
        }

        else if (col2.isMoveable) {
            trans2.pos += length * -dir; //for col2
        }
    }
}