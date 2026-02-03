#include <SFML/Graphics.hpp>
#include <cmath>
using namespace sf;

int main()
{
    // Fenêtre SFML 3 : VideoMode prend un Vector2u
    RenderWindow window(
        VideoMode(Vector2u(800, 600)),
        "Courbe avec SFML 3"
    );
    window.setFramerateLimit(60);

    // Courbe
    const std::size_t pointCount = 500;
    const float amplitude = 100.f;
    const float offsetY = 300.f;

    // SFML 3 : PrimitiveType::LineStrip
    VertexArray curve(PrimitiveType::LineStrip, pointCount);

    for (std::size_t i = 0; i < pointCount; ++i)
    {
        float x = static_cast<float>(i)*8/5;
        float y = std::sin(static_cast<float>(i) * 0.02f) * amplitude;

        curve[i].position = { x, offsetY - y };
        curve[i].color = Color::Green;
    }

    VertexArray axes(PrimitiveType::Lines, 4);

// Axe X
axes[0].position = {0.f, 300.f};
axes[1].position = {800.f, 300.f};

// Axe Y
axes[2].position = {400.f, 0.f};
axes[3].position = {400.f, 600.f};

for (int i = 0; i < 4; ++i)
    axes[i].color = Color(150, 150, 150);


    std::vector<CircleShape> points;
points.reserve(pointCount);

const float radius = 3.f;

for (std::size_t i = 0; i < 20 ; ++i)
{
    CircleShape dot(radius);
    dot.setFillColor(Color::Red);
    dot.setOrigin({radius, radius});
    dot.setPosition(curve[i*20].position);
    points.push_back(dot);
}



    while (window.isOpen())
    {
        // SFML 3 : pollEvent() -> std::optional<Event>
        while (auto ev = window.pollEvent())
        {
            // SFML 3 : event est une variante (std::variant-like)
            if (ev->is<Event::Closed>())
                window.close();
        }

        window.clear(Color::Black);
        window.draw(curve);
        for (const auto& p : points)
    window.draw(p);
        window.draw(axes);
        window.display();

    }

    return 0;
}


