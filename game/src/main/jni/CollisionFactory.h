#ifndef NATIVE_ACTIVITY_COLLISIONFACTORY_H
#define NATIVE_ACTIVITY_COLLISIONFACTORY_H

#include "SegmentShape.h"
#include "CircleShape.h"
#include "Collision.h"
#include "BaseShape.h"
#include "PolygonShape.h"

class CollisionFactory {
public:
    static bool pointBelongsToSegment(SegmentShape *s, const Vec2 &p);

    static Vec2 createDistance(const Vec2 &p, SegmentShape *s, Vec2 &point);

    static Collision *createCollision(BaseShape *shape1, BaseShape *shape2);

    static bool createCollision(PolygonShape *polygon1, PolygonShape *polygon2, float &penDepth,
                                int &lineNumber, std::vector<std::pair<float, int> > &pointNumbers,
                                float *penetratedPoints);

    static std::vector<Collision *> createCollision(PolygonShape *polygon1, PolygonShape *polygon2);

private:
    static Collision *createCollision(CircleShape *circle1, CircleShape *circle2);

    static Collision *createCollision(CircleShape *circle, SegmentShape *segment);
};

#endif //NATIVE_ACTIVITY_COLLISIONFACTORY_H