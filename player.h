#ifndef PLAYER_H
#define PLAYER_H

#include <vector>

#include <QPoint>
#include <QColor>

class Player
{
public:
    enum class Direction {
        None,
        Up,
        Down,
        Left,
        Right
    };

public:
    Player(QString name, QColor color, QPoint position, Direction direction = Direction::None);

    //! Change `position` based on `direction`.
    void step();

    //! Check if this player is colliding with `other`.
    auto collidesWith(const Player &other) const -> bool;
    //! Check if this player's trail occupies `position`.
    auto trailContains(QPoint position) const -> bool;

    //! Change `direction` of player.
    void turn(Direction direction);

    auto getName() const -> QString; //!< Get user-friendly name.
    auto getColor() const -> QColor; //!< Get displayable color.
    auto getPosition() const -> QPoint; //!< Get position.
    auto getDirection() const -> Direction; //!< Get direction.
    //! Check if player is in play.
    auto getIsPlaying() const -> bool;
    //! Set whether player is in play.
    void setIsPlaying(bool isPlaying);
    //! Get a reference to trial container.
    /*!
     * Usefull for drawing routines.
     */
    auto getTrail() const -> const std::vector<QPoint>&;

private:
    //! User-friendly (displayable) name.
    QString name;
    //! Color to be displayed for this player.
    QColor color;
    //! Where player is.
    QPoint position;
    //! Which direction the player is traveling.
    Direction direction;
    //! All locations the player has been.
    /*!
     * Does not include `position` currently at.
     */
    std::vector<QPoint> trail;
    //! Whether we are playing (can move) or not.
    bool isPlaying = true;

};

#endif // PLAYER_H
