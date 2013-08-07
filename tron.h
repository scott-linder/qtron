#ifndef TRON_H
#define TRON_H

#include <vector>

#include <QSize>
#include <QColor>
#include <QString>

#include "player.h"

typedef std::vector<Player> PlayerContainer;

class Tron
{
public:
    static const int MIN_PLAYER_COUNT;
    static const int MAX_PLAYER_COUNT;

    static const int MIN_MAP_WIDTH;
    static const int MAX_MAP_WIDTH;

    static const int MIN_MAP_HEIGHT;
    static const int MAX_MAP_HEIGHT;

    explicit Tron(QSize mapSize,
                  int playerCount,
                  std::vector<QColor> playerColors);

    //! Update all players.
    auto step() -> bool;
    //! Check if game is complete.
    auto gameIsOver() -> bool;
    //! Get an iterator to the winner, if there is one.
    auto getWinner() -> PlayerContainer::iterator;

    auto getMapSize() const -> QSize; //!< Get map size in tiles.
    auto getPlayerCount() const -> int; //!< Get player count.
    auto getPlayer(int index) -> Player&; //! Get player at `index`.
    //! Get a reference to player container.
    /*!
     * Useful for drawing routines.
     */
    auto getPlayers() const -> const PlayerContainer&;

private:
    //! Size of the map in tiles.
    const QSize mapSize;
    //! Number of players.
    const int playerCount;
    //! Players.
    PlayerContainer players;

    //! Check if all players have a valid (non-none) direction.
    auto allReady() -> bool;
    //! Check if a player is collding.
    auto isColliding(const Player &) -> bool;
    //! Determine proper starting position for player at `index`
    auto startPos(int) -> QPoint;

};


#endif // TRON_H
