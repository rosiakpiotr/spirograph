#ifndef ARM_H
#define ARM_H

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Time.hpp>
#include <math.h>

class Arm
{
public:
    Arm(int length, float rotationSpeed);

    void tick(sf::Time& deltaTime);

    void rotate(float angle);

    sf::Vector2f getConnectionPoint();

    void setPosition(sf::Vector2f position);

    float getRotationSpeed();

    int getLength();

    sf::RectangleShape& getShape() const;

    void setParent(Arm* arm);

private:
    sf::RectangleShape mShape;
    float mRotationSpeed;
    int length;
    Arm* mParent;
};

#endif // ARM_H
