#pragma once
#include <iostream>
#include "vector_math.h"

class Anchor {
    public:
        const float DIST_CONSTRAINT = 4;
        float radius;
        float angle;

        Vector2D position;
        Anchor *next; // the next anchor of a chain

        Anchor();
        Anchor(Vector2D point, float angle);
        virtual void MoveTo(Vector2D point);

    
};

class Head : public Anchor {
    public:
        Head();
        Head(Vector2D point, float angle);
        void MoveTo(Vector2D point) override;
};