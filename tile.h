#ifndef TILE_H
#define TILE_H
#include <QChar>

class Tile {
public:
    enum State {
        Start,
        Empty,
        Proposal,
        Recent,
        Old
    };
    Tile();
    Tile(QChar value);
    Tile(const Tile& other);
    static Tile startTile();
    bool isValid() const;
    QChar getChar() const;
    int getPoints() const;
    State getState() const;
    void levelUp();
private:
    State m_state;
    QChar m_char;
    int m_points;
};
#endif // TILE_H
