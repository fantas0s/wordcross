#include "charutils.h"
#include <QRandomGenerator>
#include <QDebug>
static QRandomGenerator* rand_gen = QRandomGenerator::global();

/*
Letter  Count  Points
A       11     1
B       1      8
C       1      10
D       1      6
E       9      1
F       1      8
G       1      8
H       2      4
I       10     1
J       2      4
K       6      3
L       6      2
M       3      3
N       9      1
O       5      2
P       2      4
R       2      4
S       7      1
T       9      1
U       4      3
V       2      4
Y       2      4
Ä       5      2
Ö       1      7
 */
#define NUM_OF_DIFFERENT_CHARS  24
#define REF_NUM_OF_CHARS        102 /* Count of all characters summed up */

struct CharStats {
    QChar letter;
    int count;
    int points;
};

static const CharStats s_charStatTable[NUM_OF_DIFFERENT_CHARS] = {
    {QChar('A'), 11, 1},
    {QChar('B'), 1 , 8},
    {QChar('C'), 1 , 10},
    {QChar('D'), 1 , 6},
    {QChar('E'), 9 , 1},
    {QChar('F'), 1 , 8},
    {QChar('G'), 1 , 8},
    {QChar('H'), 2 , 4},
    {QChar('I'), 10 ,1},
    {QChar('J'), 2 , 4},
    {QChar('K'), 6 , 3},
    {QChar('L'), 6 , 2},
    {QChar('M'), 3 , 3},
    {QChar('N'), 9 , 1},
    {QChar('O'), 5 , 2},
    {QChar('P'), 2 , 4},
    {QChar('R'), 2 , 4},
    {QChar('S'), 7 , 1},
    {QChar('T'), 9 , 1},
    {QChar('U'), 4 , 3},
    {QChar('V'), 2 , 4},
    {QChar('Y'), 2 , 4},
    {QChar(0x00C4), 5 , 2},
    {QChar(0x00D6), 1 , 7}
};

int CharUtils::getPointsForChar(QChar input)
{
    for (int i = 0 ; i < NUM_OF_DIFFERENT_CHARS ; ++i) {
        if (s_charStatTable[i].letter == input) {
            return s_charStatTable[i].points;
        }
    }
    return 0;
}

const QChar CharUtils::getRandomChar()
{
    int idxToPick = rand_gen->generate()%(REF_NUM_OF_CHARS+1);
    int compareIdx = 0;
    int currentIdx = 0;
    while ((compareIdx < idxToPick) &&
           (currentIdx < NUM_OF_DIFFERENT_CHARS)) {
        compareIdx += s_charStatTable[currentIdx].count;
        if (compareIdx < idxToPick) {
            currentIdx++;
        }
    }
    if (currentIdx < NUM_OF_DIFFERENT_CHARS) {
        return s_charStatTable[currentIdx].letter;
    }
    qWarning() << Q_FUNC_INFO << "search exceeded limit!";
    return '8';
}
