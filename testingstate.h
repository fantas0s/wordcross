#ifndef TESTINGSTATE_H
#define TESTINGSTATE_H

class Tile;

class TestingState
{
public:
    bool isValid() const;
    void stateChange(const Tile& tile);
private:
    enum class State {
        WaitingFirstProposal,
        WaitingFirstSpace,
        TestingForNoMoreProposals,
        RowInvalid
    };
    State m_currentState = State::WaitingFirstProposal;
};

#endif // TESTINGSTATE_H
