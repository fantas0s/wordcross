#include "testingstate.h"
#include "tile.h"

bool TestingState::isValid() const
{
    return !(m_currentState == State::RowInvalid);
}

void TestingState::stateChange(const Tile &tile)
{
    switch (m_currentState) {
    case TestingState::State::WaitingFirstProposal:
        if (tile.getState() == Tile::State::Proposal) {
            /* Proposal found. */
            m_currentState = TestingState::State::WaitingFirstSpace;
        }
        break;
    case TestingState::State::WaitingFirstSpace:
        if (tile.getState() == Tile::State::Empty) {
            /* space found. */
            m_currentState = TestingState::State::TestingForNoMoreProposals;
        }
        break;
    case TestingState::State::TestingForNoMoreProposals:
        if (tile.getState() == Tile::State::Proposal) {
            /* More proposals after space. */
            m_currentState = TestingState::State::RowInvalid;
        }
        break;
    default:
        /* RowInvalid is final state. */
        m_currentState = TestingState::State::RowInvalid;
        break;
    }
}
