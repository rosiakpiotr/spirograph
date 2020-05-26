#include "spirograph.h"

Spirograph::Spirograph(Vector2f pos, std::vector<Arm> arms)
{
    this->mArms = arms;
    this->mVisible = true;
    this->mRunning = true;

    mTrace.setPrimitiveType(PrimitiveType::LineStrip);

    // Tell arms to who are they supposed to be glued.
    Arm* armBefore = nullptr;
    for (auto& arm : mArms)
    {
        if (armBefore != nullptr)
        {
            arm.setParent(armBefore);
        }

        armBefore = &arm;
    }

    setPosition(pos);
}

void Spirograph::tick(Time& deltaTime)
{
    if (mRunning)
    {
        std::for_each(mArms.begin(), mArms.end(), [&deltaTime = deltaTime](Arm& arm)
        {
            arm.tick(deltaTime);
        });

        // Add point to trace array.
        // The last arm draws so take its connection point as position of Vertex.
        mTrace.append(Vertex(mArms.back().getConnectionPoint()));
    }
}

void Spirograph::setRunning(bool state)
{
    this->mRunning = state;
}

void Spirograph::setVisible(bool state)
{
    this->mVisible = state;
}

bool Spirograph::getVisibility()
{
    return mVisible;
}

void Spirograph::setPosition(Vector2f pos)
{
    // We are setting position of only frist arm
    // because the rest will update their positions on tick() method.
    if (!mArms.empty())
    {
        mArms.front().setPosition(pos);
    }
}

void Spirograph::draw(RenderTarget& target, RenderStates states) const
{
    // Draw trace.
    target.draw(mTrace);

    if (mVisible)
    {
        for (const auto& arm : mArms)
        {
            target.draw(arm.getShape());
        }
    }
}

bool Spirograph::getRunning()
{
    return this->mRunning;
}
