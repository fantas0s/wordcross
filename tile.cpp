#include "tile.h"

Tile::Tile()
    : m_state(Empty)
    , m_char(' ')
{
}

Tile::Tile(QChar value)
    : m_state(Proposal)
    , m_char(value)
{
}

Tile::Tile(const Tile& other)
    : m_state(other.m_state)
    , m_char(other.m_char)
{
}

Tile Tile::startTile()
{
    Tile tileToReturn;
    tileToReturn.m_state = Start;
    return tileToReturn;
}

bool Tile::isValid() const
{
    return (m_state != Empty) && (m_state != Start);
}

QChar Tile::getChar() const
{
    return m_char;
}

Tile::State Tile::getState() const
{
    return m_state;
}

void Tile::levelUp()
{
    switch(m_state) {
    case Proposal:
        m_state = Recent;
        break;
    case Recent:
        m_state = Old;
        break;
    case Old:
    case Empty:
    case Start:
    default:
        /* No change */
        break;
    }
}
