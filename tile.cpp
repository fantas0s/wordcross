#include "tile.h"
#include "charutils.h"

Tile::Tile()
    : m_state(Empty)
    , m_char(' ')
    , m_points(-1)
{
}

Tile::Tile(QChar value)
    : m_state(Proposal)
    , m_char(value)
{
    m_points = CharUtils::getPointsForChar(m_char);
}

Tile::Tile(const Tile& other)
    : m_state(other.m_state)
    , m_char(other.m_char)
    , m_points(other.m_points)
{
}

const Tile &Tile::operator =(const Tile &other)
{
    m_state = other.m_state;
    m_char = other.m_char;
    m_points = other.m_points;
    return *this;
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

int Tile::getPoints() const
{
    return m_points;
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
