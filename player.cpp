#include <algorithm>

#include "player.h"

Player::Player(QString name, QColor color, QPoint position, Direction direction)
    : name(name)
    , color(color)
    , position(position)
    , direction(direction)
{}

void Player::step()
{
    if(getIsPlaying()) {
        // Remember we were here
        if (direction != Direction::None)
            trail.push_back(position);
        // Move
        switch(direction) {
        case Direction::None:
            break;
        case Direction::Up:
            position.ry()--; break;
        case Direction::Down:
            position.ry()++; break;
        case Direction::Left:
            position.rx()--; break;
        case Direction::Right:
            position.rx()++; break;
        default:
            throw std::logic_error("Unimplemented Player::Direction.");
        }
    }
}

auto Player::collidesWith(const Player &other) const -> bool
{
    // Only check if heads collide if a) other player is actually playing,
    // and b) other player is not actually this player.
    if (other.getIsPlaying() && &other != this) {
        if (this->getPosition() == other.getPosition()) {
            return true;
        }
    }
    // Always check to see if we are hitting the other player's trail
    // as it is valid for a non-playing player and for ourselves
    if (other.trailContains(this->getPosition())) {
        return true;
    }
    return false;
}

auto Player::trailContains(QPoint position) const -> bool
{
    return std::any_of(trail.begin(), trail.end(),
                       [position](QPoint p){return p == position;});
}

void Player::turn(Direction direction) {
    this->direction = direction;
}

auto Player::getName() const -> QString
{
    return name;
}

auto Player::getColor() const -> QColor
{
    return color;
}

auto Player::getPosition() const -> QPoint
{
    return position;
}

auto Player::getDirection() const -> Direction
{
    return direction;
}

auto Player::getIsPlaying() const -> bool
{
    return isPlaying;
}

void Player::setIsPlaying(bool isPlaying)
{
    this->isPlaying = isPlaying;
}

auto Player::getTrail() const -> const std::vector<QPoint>&
{
    return trail;
}
