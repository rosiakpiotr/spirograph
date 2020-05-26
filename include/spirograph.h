#ifndef SPIROGRAPH_H
#define SPIROGRAPH_H

#include <SFML/System/Vector2.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include "arm.h"

using namespace sf;

class Spirograph : public Drawable
{
    public:
        Spirograph(Vector2f pos, std::vector<Arm> arms);

        void tick(Time& deltaTime);
        void setRunning(bool state);
        bool getRunning();
        void setVisible(bool state);
        bool getVisibility();

        // Updates position of all arms.
        // Also it connects arms together.
        void setPosition(Vector2f position);

    private:

        void draw(RenderTarget& target, RenderStates states) const;

        bool mRunning;
        bool mVisible;
        std::vector<Arm> mArms;
        VertexArray mTrace;
};

#endif // SPIROGRAPH_H
