#include "Physic.hpp"
#include "cmath"

float getLongestSide(float n1, float n2) {
    return sqrt(pow(n1 / 2, 2) + pow(n2 / 2, 2));
}




bool isColliding(BoxCollider obj1, BoxCollider obj2) {
    /*if (obj1.pos.x + obj1.w < obj2.pos.x ||
        obj1.pos.x          > obj2.pos.x + obj2.w  ||
        obj1.pos.y + obj1.h < obj2.pos.y ||
        obj1.pos.y          > obj2.pos.y + obj2.h)
        return false;*/
    return true;
}

bool isColliding(BoxCollider obj1, CircleCollider obj2) {
    //Reference: https://gamedev.stackexchange.com/questions/96337/collision-between-aabb-and-circle

    //if collision between box as a circle (longest side = radius) and circle is false 
    //then box and circle doesnt collide
    //longest side is pythagaros theorem of width/2 and height/2
    //CircleCollider tem{ obj1.pos,
    //                    getLongestSide (obj1.w, obj1.h),
    //                    obj1.isTrigger };


    //if (!isColliding(tem, obj2)) return false;

    ////Colliding with inner circle
    //tem.r = obj1.w < obj1.h ? obj1.w/2.f : obj1.h/2.f;
    //if (isColliding(tem, obj2)) return true;

    ////p = Point on circle that is closest to the box object
    //Vec2 p = obj2.pos + obj2.r * (obj1.pos - obj2.pos);
    ////if p is in box then there is collision
    //if (p.x > obj1.pos.x && p.x < obj1.pos.x + obj1.w && 
    //    p.y > obj1.pos.y && p.y < obj1.pos.y + obj1.h)
    //    return true;

	return false;
}

bool isColliding(CircleCollider obj1, BoxCollider obj2) {
	return isColliding(obj2, obj1);
}

bool isColliding(CircleCollider obj1, CircleCollider obj2) {
    /*float rad = obj1.r + obj2.r;
    rad = pow(rad,2);
    Vec2 tem = obj1.pos - obj2.pos;
    float tl = abs(tem.x) + abs(tem.y);
    tl = pow(tl, 2);

    if (rad < tl) return false;*/
	return true;
}