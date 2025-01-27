#include "Food.h"

Food::Food(int screenWidth, int screenHeight)

    : width(screenWidth), height(screenHeight) {
    //for (int i = 0; i < 16; ++i) {
    int x = width / 2 + rand() % (width / 2 - rad);
    int y = rad + rand() % (height - 2 * rad);
    center = sf::Vector2f(x, y);
    positions = generateRandomPoints(center);
    used = 0;
    //}
}

sf::Vector2f Food::moveToOppositeSide(int num)
{
    // std::cout << "used\t" <<used << std::endl;
    if (used == 0) {
        int x;
        int y = rad + rand() % (height - 2 * rad);
        if (center.x < width / 2) {
            x = width / 2 + rand() % (width / 2 - rad);
        }
        else {
            x = width / 2 - rad - (rand() % (width / 2 - 2 * rad));
        }
        center = sf::Vector2f(x, y);
        std::cout << "rand\t" << center.x << "\t" << center.y << std::endl;
        positions = generateRandomPoints(center);

    }
    used++;
    used %= 16;

    return positions[num];
}

std::vector<sf::Vector2f> Food::getPostions()
{
    return positions;
}

void Food::setPosition(size_t index, int x, int y)
{
    if (index >= positions.size()) {
        std::cout << "Error: Index out of bounds.\n";
        return;
    }
    if (x < 0 || x > width || y < 0 || y > height) {
        std::cout << "Error: Position out of screen bounds.\n";
        return;
    }
    positions[index] = sf::Vector2f(x, y);
}

bool Food::isOverlapping(const sf::Vector2f& pos1, const sf::Vector2f& pos2, float minDistance)
{
    float dx = pos1.x - pos2.x;
    float dy = pos1.y - pos2.y;
    return (dx * dx + dy * dy) < (minDistance * minDistance);
}

std::vector<sf::Vector2f> Food::generateRandomPoints(const sf::Vector2f& center, float circleRadius, float pointRadius, int pointCount)
{
    std::vector<sf::Vector2f> points;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> distAngle(0.0f, 2 * 3.14159265359f);
    std::uniform_real_distribution<float> distRadius(0.0f, circleRadius - pointRadius);

    while (points.size() < static_cast<size_t>(pointCount)) {
        float angle = distAngle(gen);
        float r = std::sqrt(distRadius(gen) * distRadius(gen));

        float x = center.x + r * std::cos(angle);
        float y = center.y + r * std::sin(angle);

        sf::Vector2f newPosition(x, y);

        bool valid = true;
        for (const auto& point : points) {
            if (isOverlapping(newPosition, point, 2 * pointRadius)) {
                valid = false;
                break;
            }
        }

        if (valid) {

            points.push_back(sf::Vector2f{ x - pointRadius, y - pointRadius });
        }
    }

    return points;
}

