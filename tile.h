#ifndef TILE_H
#define TILE_H
#include <QChar>

class Tile {
public:
    enum class State {
        Empty = 0,
        Proposal = 1,
        Recent = 2,
        Old = 3,
        Start = 0x10
    };
    Tile();
    Tile(QChar value);
    Tile(const Tile& other);
    const Tile& operator =(const Tile& other);
    static Tile startTile();
    QChar getChar() const;
    int getPoints() const;
    State getState() const;
    bool getStart() const;
    bool levelUp();
private:
    State m_state;
    QChar m_char;
    int m_points;
};
#endif // TILE_H
