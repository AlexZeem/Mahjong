#include "GameInfoMediator.h"
#include "../persistence/DBHandler.h"
#include "../persistence/Participant.h"
#include "../persistence/Game.h"
#include "../persistence/User.h"
#include "../persistence/Hand.h"
#include <QDebug>
#include <QVariantMap>
#include <QDate>

void Quicksort(QVector <persistence::Game>);

namespace cabinet {
GameInfoMediator::GameInfoMediator(QObject *parent)
    :QObject(parent)
{}

int GameInfoMediator::participatedIn() const
{
    return participated.size();
}

QString GameInfoMediator::lastPlayed() const
{
    if (! participatedGames.isEmpty()) return participatedGames.last().getDate();
    else return " ";
}

int GameInfoMediator::countMahjong() const
{
    return mcount;
}

int GameInfoMediator::bestMahjong() const
{
    return mbest;
}

int GameInfoMediator::worstMahjong() const
{
    return mworst;
}

QString GameInfoMediator::bestMDate() const
{
    return mbestDate;
}

QString GameInfoMediator::worstMDate() const
{
    return mworstDate;
}

int GameInfoMediator::countLimit() const
{
    return ul.size();
}

QVariantList GameInfoMediator::ulimit() const
{
    QVariantList result;
    for (auto &i : ul){
        QVariantMap temp;
        temp["name"] = i.limit;
        temp["date"] = i.date;
        result.push_back(temp);
    }
    return result;
}

QVariantList GameInfoMediator::gameDetail() const
{
    QVariantList result;
    for (auto &i : participatedGames){
        QVariantMap temp;
        temp["date"] = i.getDate();
        for (auto &j : up){
            temp["personalScore"] = i.getScore()[j.place];
        }
        temp["winner"] = i.getWinner();
        result.push_back(temp);
    }
    return result;
}

QVariantList GameInfoMediator::handDetail() const
{
    QVariantList result;
    for (auto&i : participatedGames){
        QVariantMap temp;
        temp ["player1Score"] = i.getScore()[0];
        temp ["player2Score"] = i.getScore()[1];
        temp ["player3Score"] = i.getScore()[2];
        temp ["player4Score"] = i.getScore()[3];

        for (auto&j : persistence::DBHandler::instance()->getHands(i.getGameId())){

            temp ["player1wind"] = j.getWind();

            qDebug() << "j.getMahjong()" << (j.getMahjong());
            if(j.getMahjong() == 0){
                temp ["player1mahjong"] = true;
            }
            else if(j.getMahjong() == 1){
                temp ["player2mahjong"] = true;
            }
            else if(j.getMahjong() == 2){
                temp ["player3mahjong"] = true;
            }
            else if(j.getMahjong() == 3){
                temp ["player4mahjong"] = true;
            }

            temp ["player1point"] = j.getCombo()[0];
            temp ["player2point"] = j.getCombo()[1];
            temp ["player3point"] = j.getCombo()[2];
            temp ["player4point"] = j.getCombo()[3];

            temp ["player1score"] = j.getScore()[0];
            temp ["player2score"] = j.getScore()[1];
            temp ["player3score"] = j.getScore()[2];
            temp ["player4score"] = j.getScore()[3];
        }

        result.push_back(temp);
    }

    return result;
}

QString GameInfoMediator::playerOne() const
{
    return player1;
}

QString GameInfoMediator::playerTwo() const
{
    return player2;
}

QString GameInfoMediator::playerThree() const
{
    return player3;
}

QString GameInfoMediator::playerFour() const
{
    return player4;
}

void GameInfoMediator::setParticipation(QString login)
{
    participated = persistence::DBHandler::instance()->getParticipant(login);
    participatedGames.clear();

    for (auto & i : participated){
        i.getGameId();
        for(auto & j : persistence::DBHandler::instance()->getGames()){
            if(j.getGameId() == i.getGameId())
                participatedGames.push_back(j);
        }
    }

    if (! participatedGames.isEmpty()) {
        quickSort(0, participatedGames.size() - 1);
    }

    //получим имена участников игры
    for (auto& i : participated){
        player1 = i.getUserId()[0];
        player2 = i.getUserId()[1];
        player3 = i.getUserId()[2];
        player4 = i.getUserId()[3];
    }

    // получим кол-во сыгранных маджонгов
    int count = 0;
    for (const auto & i : participatedGames){
        if (i.getWinner() == login){
            count++;
        }
        mcount = count;

        //заполним вектор структур, чтобы получить позицию нашего игрока в играх, где он выиграл маджонг
        userPlace temp;
        for (const auto & j : participated){
            temp.gameId = j.getGameId();
            QVector<QString> tempUser = j.getUserId();
            if (tempUser[0] == login){
                temp.place = first;
            }
            if (tempUser[1] == login){
                temp.place = second;
            }
            if (tempUser[2] == login){
                temp.place = third;
            }
            if (tempUser[3] == login){
                temp.place = fourth;
            }
            up.push_back(temp);

            //получим лучший маджонг и его дату.
            int best = -10000;
            int worst = 10000;
            QString mdate;
            for (auto &k : persistence::DBHandler::instance()->getHands(j.getGameId())) {
                if (best < k.getScore()[temp.place]) {
                    best = k.getScore()[temp.place];
                    mdate = persistence::DBHandler::instance()->selectGame(temp.gameId).getDate();
                }
                mbest = best;
                mbestDate = mdate;

                if (worst > k.getScore()[temp.place]) {
                    worst = k.getScore()[temp.place];
                    mdate = persistence::DBHandler::instance()->selectGame(temp.gameId).getDate();
                }
                mworst = worst;
                mworstDate = mdate;

                // получим инфо по лимитам
                if(i.getWinner() == login && !k.getLimit().isEmpty())
                {
                    userLimits templ;
                    templ.date = persistence::DBHandler::instance()->selectGame(temp.gameId).getDate();
                    for (auto & l : persistence::DBHandler::instance()->getHands(j.getGameId())){
                        templ.limit = l.getLimit();
                        qDebug() << "Temp limit" << templ.limit;
                    }
                    ul.clear();
                    ul.push_back(templ);
                    emit ulimitChanged();
                }
            }
        }
    }
    emit participationChanged();
}

void GameInfoMediator::quickSort(int left, int right)
{
    int i = left, j = right;
    QDate pivot = QDate::fromString(participatedGames[(left + right) / 2].getDate(),"dd/MM/yyyy");

    /* partition */
    while (i <= j) {
        while (QDate::fromString(participatedGames[i].getDate(),"dd/MM/yyyy") < pivot) ++i;
        while (QDate::fromString(participatedGames[j].getDate(),"dd/MM/yyyy") > pivot) --j;

        if (i <= j) {
            persistence::Game temp = participatedGames[i];
            participatedGames[i] = participatedGames[j];
            participatedGames[j] = temp;
            ++i;
            --j;
        }
    }

    /* recursion */
    if (left < j) quickSort(left, j);
    if (i < right) quickSort(i, right);
}
} // cabinet



