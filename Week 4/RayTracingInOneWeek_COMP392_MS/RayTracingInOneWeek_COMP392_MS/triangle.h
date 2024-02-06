#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "hittable.h"
#include "vec3.h"

class triangle : public hittable {
public:
    triangle(point3 _v0, point3 _v1, point3 _v2) : v0(_v0), v1(_v1), v2(_v2) {}

    bool hit(const ray& r, double ray_tmin, double ray_tmax, hit_record& rec) const override {
        //         v2
        //        /\
        //    E2 /   \  
        //      /      \
        //     /     P   \  E1
        //    /            \
        //  v0  ------------- v1
        //          E0


        //The edges of the triagnle
        vec3 E0 = v1 - v0;
        vec3 E1 = v2 - v1;
        vec3 E2 = v0 - v2;



        //The plane of the triangle
        //N - normal to the plane
        vec3 N = cross(E0, -E2);

        //(N,v0) => specify the plane of the triangle

        //P - Ray intersecting plane at P(t)
        double t = dot((v0 - r.origin()), N) / dot(r.direction(), N);
        vec3 P = r.at(t);

        //Calculate if P is inside triangle or not
        // <=> all
        vec3 W0 = P - v0;
        vec3 W1 = P - v1;
        vec3 W2 = P - v2;

        bool inside = true;
        inside = inside && dot(cross(E0, W0), N) > 0;
        inside = inside && dot(cross(E1, W1), N) > 0;
        inside = inside && dot(cross(E2, W2), N) > 0;

        if (inside) {
            rec.t = t;
            rec.p = P;
            rec.normal = N;
        }

        return inside;
    }

private:
    point3 v0;
    point3 v1;
    point3 v2;


};

#endif

