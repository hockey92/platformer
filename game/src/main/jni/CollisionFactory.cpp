#include <stddef.h>
#include <stl/_vector.h>
#include "CollisionFactory.h"

bool CollisionFactory::pointBelongsToSegment(SegmentShape *s, const Vec2 &p) {
    float d = 0.001f;
    for (int i = 0; i < 2; i++) {
        float a1 = s->get(0).get(i);
        float a2 = s->get(1).get(i);
        float a = p.get(i);

        if (!(a1 - d <= a && a <= a2 + d) && !(a2 - d <= a && a <= a1 + d)) {
            return false;
        }
    }
    return true;
}

Vec2 CollisionFactory::createDistance(const Vec2 &p, SegmentShape *s, Vec2 &point) {
    Line line = Line(s->get(0), s->get(1));
    Line pLine = Line(p, p + line.getNormal());
    Vec2 mutualPoint = Vec2(Line::getMutualPoint(line, pLine));
    if (pointBelongsToSegment(s, mutualPoint)) {
        point = mutualPoint;
        return (mutualPoint - p);
    } else {
        Vec2 a;
        float aLen = 0;
        int pointNum = 0;
        for (int i = 0; i < 2; i++) {
            Vec2 d = s->get(i) - p;
            float len = d.len();
            if (i == 0 || len < aLen) {
                a = d;
                aLen = len;
                pointNum = i;
            }
        }
        point = s->get(pointNum);
        return a;
    }
}

Collision *CollisionFactory::createCollision(BaseShape *shape1, BaseShape *shape2) {
    if (shape1->type() == ShapeTypes::CIRCLE && shape2->type() == ShapeTypes::CIRCLE) {
        return createCollision((CircleShape *) shape1, (CircleShape *) shape2);
    } else if (shape1->type() == ShapeTypes::CIRCLE && shape2->type() == ShapeTypes::SEGMENT) {
        return createCollision((CircleShape *) shape1, (SegmentShape *) shape2);
    } else if (shape1->type() == ShapeTypes::SEGMENT && shape2->type() == ShapeTypes::CIRCLE) {
        Collision *result = createCollision((CircleShape *) shape2, (SegmentShape *) shape1);
        result->swap();
        return result;
    }/* else if (shape1->type() == ShapeTypes::POLYGON && shape2->type() == ShapeTypes::POLYGON) {
        return createCollision((PolygonShape *) shape1, (PolygonShape *) shape2);
    }*/
    return NULL;
}

Collision *CollisionFactory::createCollision(CircleShape *c1, CircleShape *c2) {
    Vec2 v = c2->getCenter() - c1->getCenter();
    float d = v.len();
    float r = c1->getR() + c2->getR();
    Vec2 n = v * (1.f / d);
    Vec2 r1 = n * c1->getR();
    Vec2 r2 = -c2->getR() * n;
    return new Collision(n, r1, r2, r - d);
}

Collision *CollisionFactory::createCollision(CircleShape *c, SegmentShape *s) {
    Vec2 mutualPoint;
    Vec2 v1 = createDistance(c->getCenter(), s, mutualPoint);
    float len = v1.len();
    Vec2 n = v1 * (1.f / len);
    Vec2 r1 = n * c->getR();
    Vec2 r2 = mutualPoint - s->getCenter();
    float penetration = c->getR() - len;
    return new Collision(n, r1, r2, penetration);
}

std::vector<Collision *> CollisionFactory::createCollision(PolygonShape *polygon1,
                                                           PolygonShape *polygon2) {
    float penDepth;
    std::vector<std::pair<float, int> > pointNumbers(10);
    int lineNumber;
    float penetratedPoints[100];

    std::vector<Collision *> collisions;

    CollisionFactory::createCollision(polygon1, polygon2, penDepth,
                                      lineNumber, pointNumbers, penetratedPoints);

    if (penDepth < 0.0f) {
        collisions.clear();
        return collisions;
    }

    for (int i = 0; i < pointNumbers.size(); i++) {
        Vec2 n = polygon1->getLines()[lineNumber].getNormal();
        Vec2 r1 = polygon2->getVertex(pointNumbers[i].second) -
                  polygon1->getCenter();
        Vec2 r2 = polygon2->getVertices()[pointNumbers[i].second];
        if (penetratedPoints[pointNumbers[i].second]) {
            collisions.push_back(new Collision(n, r1, r2, pointNumbers[i].first));
        }
    }

    CollisionFactory::createCollision(polygon2, polygon1, penDepth,
                                      lineNumber, pointNumbers, penetratedPoints);

    if (penDepth < 0.0f) {
        collisions.clear();
        return collisions;
    }

    for (int i = 0; i < pointNumbers.size(); i++) {
        Vec2 n = polygon2->getLines()[lineNumber].getNormal();
        Vec2 r2 = polygon1->getVertex(pointNumbers[i].second) -
                  polygon2->getCenter();
        Vec2 r1 = polygon1->getVertices()[pointNumbers[i].second];
        if (penetratedPoints[pointNumbers[i].second]) {
            collisions.push_back(new Collision(n * -1, r1, r2, pointNumbers[i].first));
        }
    }

    return collisions;
}

bool CollisionFactory::createCollision(PolygonShape *polygon1, PolygonShape *polygon2,
                                       float &penDepth, int &lineNumber,
                                       std::vector<std::pair<float, int> > &pointNumbers,
                                       float *penetratedPoints) {
    penDepth = -1;
    for (int i = 0; i < polygon2->getVerticesSize(); i++) {
        penetratedPoints[i] = 1;
    }
    for (int i = 0; i < polygon1->getVerticesSize(); i++) {
        Vec2 point = polygon1->getVertex(i);
        Line line = polygon1->getLines()[i];
        Line perpLine = Line(point, point + line.getNormal());

        float penDepthForCurrLine = -1.0f;
        std::vector<std::pair<float, int> > pointNumbersForCurrLine;
        for (int j = 0; j < polygon2->getVerticesSize(); j++) {
            Vec2 currentPoint = polygon2->getVertex(j);
            Line currentLine = Line(currentPoint, currentPoint + perpLine.getNormal());
            Vec2 mutualPoint = Line::getMutualPoint(perpLine, currentLine);
            float penDepthForCurrPoint = -line.getDistToPoint(mutualPoint);
            if (penDepthForCurrPoint >= 0) {
                penDepthForCurrLine = penDepthForCurrPoint > penDepthForCurrLine
                                      ? penDepthForCurrPoint
                                      : penDepthForCurrLine;
                pointNumbersForCurrLine.push_back(std::pair<float, int>(penDepthForCurrPoint, j));
            } else {
                penetratedPoints[j] = 0;
            }
        }

        if (penDepthForCurrLine < 0) {
            penDepth = -1.0f;
            return false;
        }

        if (penDepth < 0 || penDepthForCurrLine < penDepth) {
            penDepth = penDepthForCurrLine;
            lineNumber = i;
            pointNumbers = pointNumbersForCurrLine;
        }
    }
    return true;
}
