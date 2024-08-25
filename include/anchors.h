#pragma once
#include <iostream>
#include "vector2.h"

class Anchor {
    public:
        const float DIST_CONSTRAINT = 2;
        float radius;
        float angle;

        Vector2 position;
        Anchor *next; // the next anchor of a chain

        Anchor();
        Anchor(Vector2 point, float angle);
        virtual void MoveTo(Vector2 point);

    
};

class Head : public Anchor {
    public:
        Head();
        Head(Vector2 point, float angle);
        void MoveTo(Vector2 point) override;
};