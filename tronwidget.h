#ifndef TRONWIDGET_H
#define TRONWIDGET_H

#include <memory>

#include <QtGui>
#include <QWidget>
#include <QTimer>
#include <QColor>

#include "tron.h"

class TronWidget : public QWidget
{
    Q_OBJECT
public:
    static const int DEFAULT_TILE_SIZE;
    static const int DEFAULT_TICK_INTERVAL;

    explicit TronWidget(QWidget *parent = 0);
    ~TronWidget();

    auto getPlayerName(int) const -> QString;
    auto getPlayerColor(int) const -> QColor;
    
protected:
    void resizeEvent(QResizeEvent *);
    void paintEvent(QPaintEvent *);
    void keyPressEvent(QKeyEvent *);

private:
    QTimer ticker{this};
    std::unique_ptr<Tron> tron{nullptr};
    int tileSize{DEFAULT_TILE_SIZE};
    QSize mapSize{Tron::MIN_MAP_WIDTH, Tron::MIN_MAP_HEIGHT};
    int playerCount{Tron::MIN_PLAYER_COUNT};
    std::vector<QString> playerNames{"Player One", "Player Two", "Player Three", "Player Four"};
    std::vector<QColor> playerColors{Qt::red, Qt::green, Qt::blue, Qt::yellow};
    //! Keybindings of Qt::Key -> (playerIndex, direction)
    static std::map<int, std::pair<int, Player::Direction>> keybindings;

    //! Adjust tile-size to maximize screen-usage.
    void resizeMap();

signals:
    //! Emitted when a game starts (true) or stops (false).
    void gameInProgress(bool);
    
public slots:
    //! Create a new game.
    void start();
    //! Halt current game.
    void stop();

    //! Set player count for next game.
    void setPlayerCount(int);
    //! Set name to be used to display player.
    void setPlayerName(int, QString);
    //! Set color to be used to display player.
    void setPlayerColor(int, QColor);
    //! Set width of map in tiles.
    void setMapWidth(int);
    //! Set height of map in tiles.
    void setMapHeight(int);

    //! Update game.
    void step();
    
};

#endif // TRONWIDGET_H
