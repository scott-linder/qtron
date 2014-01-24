#include <exception>

#include "tron.h"
#include "clamp.h"

Tron::Tron(QSize mapSize,
           int playerCount,
           std::vector<QString> playerNames,
           std::vector<QColor> playerColors) :
    mapSize(mapSize)
  , playerCount(playerCount)
{
    if (mapSize.width() < MIN_MAP_WIDTH
            || mapSize.width() > MAX_MAP_WIDTH
            || mapSize.height() < MIN_MAP_HEIGHT
            || mapSize.height() > MAX_MAP_HEIGHT) {
        throw std::logic_error{"Bad map size."};
    }
    if (playerCount < MIN_PLAYER_COUNT
            || playerCount > MAX_PLAYER_COUNT) {
        throw std::logic_error{"Bad player count."};
    }
    for (int i = 0; i < playerCount; ++i) {
        players.emplace_back(playerNames[i], playerColors[i], startPos(i));
    }
}

/*!
 * The object iterates over all players, updates them
 * and then checks for collisions and removes players
 * from the game accordingly.
 * \return Whether the game is now over.
 */
auto Tron::step() -> bool
{
    if (allReady() && !gameIsOver()) {
        // Update each player
        for (Player &player : players) {
            player.step();
        }
        // Check each player for collision;
        // We do this after all updates to ensure
        // _both_ players are stopped in event of tie
        for (Player &player : players) {
            if (isColliding(player)) {
                player.setIsPlaying(false);
            }
        }
    }

    return !gameIsOver();
}

/*!
 * A game is considered "over" when it has either a winner or
 * is a draw (tie).
 * \return Whether the game is over.
 */
auto Tron::gameIsOver() -> bool
{
    auto still_playing = std::count_if(players.begin(), players.end(),
                         [](Player &p) { return p.getIsPlaying(); });
    return still_playing <= 1;
}

/*!
 * If the game is over, this function will return an iterator to
 * its winner. In the event of a tie this iterator will point
 * to the end() of the `players` container.
 * \return Iterator to winning player.
 */
auto Tron::getWinner() -> PlayerContainer::iterator
{
    if (!gameIsOver()) {
        throw std::logic_error{"Game has no winner (game not over)."};
    }

    PlayerContainer::iterator iter;
    for (iter = players.begin(); iter != players.end(); ++iter) {
        if (iter->getIsPlaying()) {
            break;
        }
    }
    return iter;
}

auto Tron::allReady() -> bool
{
    return std::all_of(players.begin(), players.end(),
                       [](const Player &p){return p.getDirection() != Player::Direction::None;});
}

/*!
 * Determine if `player` is colliding with map geometry
 * or any other players.
 * \param player to check collision status of.
 * \return Whether `player` is colliding.
 */
auto Tron::isColliding(const Player &player) -> bool
{
    QPoint position = player.getPosition();
    int x = position.x();
    int y = position.y();
    // Check map bound collisions
    if (x < 0 || y < 0
            || x >= mapSize.width()
            || y >= mapSize.height()) {
        return true;
    }
    // Check collisions with other players
    for(const Player& otherPlayer : players) {
        if (player.collidesWith(otherPlayer))
            return true;
    }
    return false;
}

auto Tron::startPos(int index) -> QPoint
{
    // TODO: This just assumes at most 4 players.
    int x, y;
    switch(index) {
    case 0: // Top Left
        x = (mapSize.width() / 4);
        y = (mapSize.height() / 4);
        break;
    case 1: // Bottom Right
        x = 3 * (mapSize.width() / 4);
        y = 3 * (mapSize.height() / 4);
        break;
    case 2: // Top Right
        x = 3 * (mapSize.width() / 4);
        y = (mapSize.height() / 4);
        break;
    case 3: // Bottom Left
        x = (mapSize.width() / 4);
        y = 3 * (mapSize.height() / 4);
        break;
    default:
        throw std::logic_error{"Can't compute start position for player."};
    }
    return {x, y};
}

auto Tron::getMapSize() const -> QSize
{
    return mapSize;
}

auto Tron::getPlayerCount() const -> int
{
    return playerCount;
}

auto Tron::getPlayer(int index) -> Player&
{
    return players[index];
}

auto Tron::getPlayers() const -> const PlayerContainer&
{
    return players;
}

// Constants
const int Tron::MIN_PLAYER_COUNT{2};
const int Tron::MAX_PLAYER_COUNT{4};

const int Tron::MIN_MAP_WIDTH{10};
const int Tron::MAX_MAP_WIDTH{100};

const int Tron::MIN_MAP_HEIGHT{10};
const int Tron::MAX_MAP_HEIGHT{100};
