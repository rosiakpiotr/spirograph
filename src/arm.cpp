#include "arm.h"

Arm::Arm(int length, float rotationSpeed)
{
    this->length = length;
    this->mRotationSpeed = rotationSpeed;
    this->mShape = sf::RectangleShape(sf::Vector2f(length, 2)); // Fixed height of 2.
    this->mParent = nullptr;

    mShape.setOrigin(0, 2); // left middle point
}

void Arm::tick(sf::Time& deltaTime)
{
    rotate(mRotationSpeed * deltaTime.asSeconds());

    if (mParent)
    {
        setPosition(mParent->getConnectionPoint());
    }
}

void Arm::setParent(Arm* arm)
{
    this->mParent = arm;
}

sf::Vector2f Arm::getConnectionPoint()
{
    sf::Vector2f point;
    const sf::FloatRect rect = mShape.getGlobalBounds();
    float currentAngle = mShape.getRotation();
    // This point keep changing if arm rotates and depends on rotation.

    if (currentAngle >= 0 && currentAngle <= 90)
    {
        point = sf::Vector2f(rect.left + rect.width, rect.top + rect.height);
    }
    else if (currentAngle > 90 && currentAngle <= 180)
    {
        point = sf::Vector2f(rect.left, rect.top + rect.height);
    }
    else if (currentAngle > 180 && currentAngle <= 270)
    {
        point = sf::Vector2f(rect.left, rect.top);
    }
    else if (currentAngle > 270 && currentAngle <= 360)
    {
        point = sf::Vector2f(rect.left + rect.width, rect.top);
    }

    return point;
}

void Arm::setPosition(sf::Vector2f pos)
{
    mShape.setPosition(pos);
}

void Arm::rotate(float angle)
{
    // Rotate arm, but first convert angle given in degrees to radians.
    mShape.rotate(angle * 3.14 / 180.f);
}

float Arm::getRotationSpeed()
{
    return this->mRotationSpeed;
}

int Arm::getLength()
{
    return this->length;
}

sf::RectangleShape& Arm::getShape() const
{
    return const_cast<sf::RectangleShape&>(mShape);
}
