#ifndef CHARUTILS_H
#define CHARUTILS_H
#include <QChar>

class CharUtils {
public:
    static int getPointsForChar(const QChar input);
    static const QChar getRandomChar();
};
#endif // CHARUTILS_H
