#pragma once
#include "vector_math.h"

class Anchor {
    public:
        Vector2D position;
        Anchor *next; // the next anchor of a chain
        Anchor *prev; // the previous anchor of a chain

        Anchor();
        virtual void Move(Vector2D point);

    protected:
        float dist_const;
};

class Head : public Anchor {
    public:
        void Move(Vector2D point) override;
};

class Tail : public Anchor {
    public:
        void Move(Vector2D point) override;
};