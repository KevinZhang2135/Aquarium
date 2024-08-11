#pragma once
#include <iostream>
#include "vector_math.h"

class Anchor {
    public:
        float dist_const;
        Vector2D position;
        Anchor *next; // the next anchor of a chain

        Anchor();
        Anchor(Vector2D point);
        virtual void MoveTo(Vector2D point);
        
};

class Head : public Anchor {
    public:
        Head();
        Head(Vector2D point);
        void MoveTo(Vector2D point) override;
};

class Tail : public Anchor {
    public:
        void MoveTo(Vector2D point) override;
};