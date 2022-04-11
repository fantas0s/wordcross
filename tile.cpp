#include "tile.h"
#include "charutils.h"

Tile::Tile()
    : m_state(State::Empty)
    , m_char(' ')
    , m_points(-1)
{
}

Tile::Tile(QChar value)
    : m_state(State::Proposal)
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
    const int startFlagMask = static_cast<int>(m_state) & static_cast<int>(State::Start);
    m_state = static_cast<State>(static_cast<int>(other.getState()) | startFlagMask);
    m_char = other.m_char;
    m_points = other.m_points;
    return *this;
}

Tile Tile::startTile()
{
    Tile tileToReturn;
    tileToReturn.m_state = static_cast<State>(static_cast<int>(State::Empty) | static_cast<int>(State::Start));
    return tileToReturn;
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
    return static_cast<State>(static_cast<int>(m_state) & ~static_cast<int>(State::Start));
}

bool Tile::getStart() const
{
    return static_cast<State>(static_cast<int>(m_state) & static_cast<int>(State::Start)) == State::Start;
}

bool Tile::levelUp()
{
    switch(getState()) {
    case State::Proposal:
        m_state = State::Recent;
        return true;
    case State::Recent:
        m_state = State::Old;
        return true;
    case State::Old:
    case State::Empty:
    default:
        /* No change */
        return false;
    }
}
