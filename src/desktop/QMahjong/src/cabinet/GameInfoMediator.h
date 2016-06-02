#pragma once
#include <QObject>
#include <QVariantList>
#include "../persistence/Participant.h"
#include "../persistence/Game.h"

namespace cabinet {
class GameInfoMediator : public QObject
{
    Q_OBJECT

    enum Roles {
        LNAME_ROLE,
        LDATE_ROLE,
    };

    Q_PROPERTY(int participatedIn READ participatedIn NOTIFY participatedInChanged)
    Q_PROPERTY(QString lastPlayed READ lastPlayed NOTIFY lastPlayedChanged)
    Q_PROPERTY(int countMahjong READ countMahjong NOTIFY countMahjongChanged)
    Q_PROPERTY(int bestMahjong READ bestMahjong NOTIFY bestMahjongChanged)
    Q_PROPERTY(int worstMahjong READ worstMahjong NOTIFY worstMahjongChanged)
    Q_PROPERTY(QString bestMDate READ bestMDate NOTIFY bestMDateChanged)
    Q_PROPERTY(QString worstMDate READ worstMDate NOTIFY worstMDateChanged)
    Q_PROPERTY(int countLimit READ countLimit NOTIFY countLimitChanged)
    Q_PROPERTY(QVariantList ulimit READ ulimit NOTIFY ulimitChanged)
    Q_PROPERTY(QVariantList gameDetail READ gameDetail NOTIFY gameDetailChanged)
    Q_PROPERTY(QVariantList handDetail READ handDetail NOTIFY handDetailChanged)
    Q_PROPERTY(QString playerOne READ playerOne NOTIFY playerOneChanged)
    Q_PROPERTY(QString playerTwo READ playerTwo NOTIFY playerTwoChanged)
    Q_PROPERTY(QString playerThree READ playerThree NOTIFY playerThreeChanged)
    Q_PROPERTY(QString playerFour READ playerFour NOTIFY playerFourChanged)


 public:
    GameInfoMediator(QObject *parent = 0);
    int participatedIn() const;
    QString lastPlayed() const;
    int countMahjong() const;
    int bestMahjong() const;
    int worstMahjong() const;
    QString bestMDate() const;
    QString worstMDate() const;
    int countLimit() const;
    QVariantList ulimit() const;
    QVariantList gameDetail() const;
    QVariantList handDetail() const;
    QString playerOne() const;
    QString playerTwo() const;
    QString playerThree() const;
    QString playerFour() const;

 signals:
    void participationChanged();
    void participatedInChanged();
    void lastPlayedChanged();
    void countMahjongChanged();
    void bestMahjongChanged();
    void worstMahjongChanged();
    void bestMDateChanged();
    void worstMDateChanged();
    void countLimitChanged();
    void ulimitChanged();
    void gameDetailChanged();
    void handDetailChanged();
    void playerOneChanged();
    void playerTwoChanged();
    void playerThreeChanged();
    void playerFourChanged();

 public slots:
    void setParticipation(QString login);

private:
    void quickSort(int left, int right);

 private:

    enum Place{
        first,
        second,
        third,
        fourth};

    struct userPlace {
        unsigned long gameId;
        Place place;
    };

    struct userLimits {
        QString date;
        QString limit;
    };

    QVector <persistence::Participant> participated;
    QVector <persistence::Game> participatedGames;
    QVector <userLimits> ul;
    QVector <userPlace> up;
    int mcount;
    int mbest;
    int mworst;
    QString mbestDate;
    QString mworstDate;
    QString player1;
    QString player2;
    QString player3;
    QString player4;

}; // gameInfoMediator
} // cabinet
