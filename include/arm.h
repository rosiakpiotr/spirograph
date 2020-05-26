#ifndef ARM_H
#define ARM_H

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Time.hpp>
#include <math.h>

using namespace sf;

class Arm
{
public:
    Arm(int length, float rotationSpeed);

    void tick(Time& deltaTime);

    void rotate(float angle);

    Vector2f getConnectionPoint();

    void setPosition(Vector2f position);

    float getRotationSpeed();

    int getLength();

    RectangleShape& getShape() const;

    void setParent(Arm* arm);

private:
    RectangleShape mShape;
    float mRotationSpeed;
    int length;
    Arm* mParent;
};

#endif // ARM_H
