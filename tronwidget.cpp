#include <exception>
#include <utility>

#include <QMessageBox>

#include "tronwidget.h"
#include "clamp.h"

TronWidget::TronWidget(QWidget *parent) :
    QWidget(parent)
{
    QObject::connect(&ticker, SIGNAL(timeout()),
                     this, SLOT(step()));
    // TODO: Let user modify this interval?
    ticker.setInterval(DEFAULT_TICK_INTERVAL);
}

TronWidget::~TronWidget()
{
    tron.reset(nullptr);
}

void TronWidget::start()
{
    tron.reset(new Tron(mapSize, playerCount, playerNames, playerColors));
    resizeMap();
    setFocus(Qt::OtherFocusReason);
    ticker.start();
    emit gameInProgress(true);
}

void TronWidget::stop()
{
    ticker.stop();
    emit gameInProgress(false);
}

void TronWidget::step()
{
    if (tron) {
        if (tron->step()) {
            repaint(rect());
        } else {
            stop();
            repaint(rect());
            auto winner = tron->getWinner();
            QString winnerString;
            QString colorString;
            if (winner == tron->getPlayers().end()) {
                winnerString = "Tie Game";
                colorString = "black";
            } else {
                winnerString = QString{"%1 won!"}.arg(winner->getName());
                colorString = winner->getColor().name();
            }
            QMessageBox gameOverDialog{QMessageBox::Information, "Game Over", winnerString, QMessageBox::Ok, this};
            gameOverDialog.setStyleSheet(QString("color: %1").arg(colorString));
            gameOverDialog.exec();
        }
    }
}

void TronWidget::setPlayerCount(int playerCount)
{
    this->playerCount = clamp(playerCount,
                              Tron::MIN_PLAYER_COUNT,
                              Tron::MAX_PLAYER_COUNT);
}

void TronWidget::setPlayerName(int player, QString name)
{
    this->playerNames[player] = name;
}

auto TronWidget::getPlayerName(int player) const -> QString
{
    return this->playerNames[player];
}

void TronWidget::setPlayerColor(int player, QColor color)
{
    this->playerColors[player] = color;
}

auto TronWidget::getPlayerColor(int player) const -> QColor
{
    return this->playerColors[player];
}

void TronWidget::setMapWidth(int width)
{
    this->mapSize.setWidth(clamp(width,
                                 Tron::MIN_MAP_WIDTH,
                                 Tron::MAX_MAP_WIDTH));
}

void TronWidget::setMapHeight(int height)
{
    this->mapSize.setHeight(clamp(height,
                                  Tron::MIN_MAP_HEIGHT,
                                  Tron::MAX_MAP_HEIGHT));
}

void TronWidget::resizeMap()
{
    if (tron) {
        // We need to keep the map on-screen no matter
        // how the window is resized, so we choose the
        // smallest dimension and divide it evenly.
        int tileWidth = rect().width() / tron->getMapSize().width();
        int tileHeight = rect().height() / tron->getMapSize().height();
        tileSize = std::min(tileWidth, tileHeight);
    } else {
        tileSize = DEFAULT_TILE_SIZE;
    }
}

void TronWidget::resizeEvent(QResizeEvent *)
{
    resizeMap();
}

void TronWidget::paintEvent(QPaintEvent *)
{
    if (tron) {
        QPainter painter{this};

        // Paint playing board
        painter.setBrush(Qt::black);
        painter.setPen(QPen(QBrush(Qt::white), 1));
        painter.drawRect(rect().x(), rect().y(),
                         tron->getMapSize().width()*tileSize,
                         tron->getMapSize().height()*tileSize);

        // Draw each player and its trail
        painter.setPen(QPen(QBrush(Qt::white), 1));
        for(int i = 0; i < tron->getPlayerCount(); ++i) {
            auto player = tron->getPlayer(i);
            painter.setBrush(player.getColor());
            if (player.getIsPlaying()) {
                QPoint p = player.getPosition();
                painter.drawRect(p.x() * tileSize, p.y() * tileSize,
                                 tileSize, tileSize);
            }
            for (QPoint pt : player.getTrail()) {
                painter.drawRect(pt.x() * tileSize, pt.y() * tileSize,
                                 tileSize, tileSize);
            }
        }
    }
}

void TronWidget::keyPressEvent(QKeyEvent *event)
{
    if (tron) {
        if (keybindings.count(event->key()) > 0) {
            // This key press is a game control
            auto binding = keybindings.at(event->key());
            // Check if this binding applies to an active player
            if (binding.first < tron->getPlayerCount()) {
                // Make the turn
                tron->getPlayer(binding.first).turn(binding.second);
            }
        } else {
            // This key press doesn't concern our game directly
            // Pass it on to the default Qt implementation
            QWidget::keyPressEvent(event);
        }
    }
}

std::map<int, std::pair<int, Player::Direction>>
TronWidget::keybindings
{
    // Player One
    {Qt::Key_Up, {0, Player::Direction::Up}},
    {Qt::Key_Down, {0, Player::Direction::Down}},
    {Qt::Key_Left, {0, Player::Direction::Left}},
    {Qt::Key_Right, {0, Player::Direction::Right}},
    // Player Two
    {Qt::Key_W, {1, Player::Direction::Up}},
    {Qt::Key_S, {1, Player::Direction::Down}},
    {Qt::Key_A, {1, Player::Direction::Left}},
    {Qt::Key_D, {1, Player::Direction::Right}},
    // Player Three
    {Qt::Key_I, {2, Player::Direction::Up}},
    {Qt::Key_K, {2, Player::Direction::Down}},
    {Qt::Key_J, {2, Player::Direction::Left}},
    {Qt::Key_L, {2, Player::Direction::Right}},
    // Player Four
    {Qt::Key_T, {3, Player::Direction::Up}},
    {Qt::Key_G, {3, Player::Direction::Down}},
    {Qt::Key_F, {3, Player::Direction::Left}},
    {Qt::Key_H, {3, Player::Direction::Right}},
};

const int TronWidget::DEFAULT_TILE_SIZE{20};
const int TronWidget::DEFAULT_TICK_INTERVAL{80};

