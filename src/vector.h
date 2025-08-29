#ifndef SG_TEST_VECTOR_H
#define SG_TEST_VECTOR_H

typedef struct {
    double x;
    double y;

} Vector2D;


double getLength(Vector2D vector);
double dot(Vector2D vector1, Vector2D vector2);


#endif 