#include "GameInfoMediator.h"
#include "../persistence/DBHandler.h"
#include "../persistence/Participant.h"
#include "../persistence/Game.h"
#include "../persistence/User.h"

void Quicksort(QVector <persistence::Game>);

namespace cabinet {
GameInfoMediator::GameInfoMediator(QObject *parent)
    :QObject(parent)
{
    QObject::connect(this, SIGNAL(participationChanged()), SIGNAL(participatedInChanged()));
    QObject::connect(this, SIGNAL(participationChanged()), SIGNAL(lastPlayedChanged()));
    QObject::connect(this, SIGNAL(participationChanged()), SIGNAL(countMahjongChanged()));
}

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

void GameInfoMediator::setParticipation(QString login)
{
    participated = persistence::DBHandler::instance()->getParticipant(login);
    if (! participated.isEmpty()) {
        for (auto & i : participated){
            i.getGameId();
            for(auto & j : persistence::DBHandler::instance()->getGames()){
                if(j.getGameId() == i.getGameId())
                    participatedGames.push_back(j);
            }
        }
        Quicksort(participatedGames);
    }

    // получим кол-во сыгранных маджонгов
    int mcount = 0;
    for (const auto & i : participatedGames){
        if (i.getWinner() == persistence::DBHandler::instance()->selectUser(login).getLogin()){
            mcount++;
        }
    }
    emit participationChanged();
}

//void GameInfoMediator::setMahjong()
//{
//    //заполним вектор структур, чтобы получить позицию нашего игрока в играх, где он выиграл маджонг)
//    QVector <userPlace> u;
//    userPlace temp;
//    for (const auto & j : persistence::DBHandler::instance()->getParticipant(QString &login)){
//        temp.gameId -> j.getGameId();
//        for (auto & k : i.getUserId){
//            temp.Place -> k.getUserId(at(login));
//        }
//        u.push_back(temp);
//    }

//    // получит лучший/худщий маджонги и их даты игр.
//    for (auto & k : persistence::Dbhandler::instance()->getHands(participatedGamed(gameId))){
//        mworst, mbest = k.getScore();
//        date = k.getDate();
//        /* а теперь я так понимаю что надо пройтись по вектору структур, и поле place сделать индектаром поля score у вектора QVector<int> score, оесть 2 уикла 1 для вектора структур, второй для вектора очков*/
//        for (auto & l : u){
//            for (auto & n : persistence::Dbhandler::instance()->getHands(participatedGamed(gameId))){
//                if(n.getScore.at(u.place) > mbest) {
//                    mbest = n.getScore.at(u.place),
//                            mbestDate = n.getDate();
//                }
//                if(n.getScore.at(u.place) < mworst) {
//                    mworst = n.getScore.at(u.place),
//                            mworstDate = n.getDate();
//                }
//            }
//        }

//    }
//}//end setMahjong

} // cabinet

void Quicksort (QVector <persistence::Game> participatedGames)
{
    QString medianaValued = participatedGames[participatedGames.size()/2].getDate();
    int mediana = participatedGames.size()/2;
    int left = 0;
    int right = participatedGames.size()-1;
    int temp;
    while(true){
        if (participatedGames[left].getDate() < participatedGames[mediana].getDate())
        {left ++;}
        if(participatedGames[right].getDate() > participatedGames[mediana].getDate())
        {right--;}
        if (left == right) break;
        if (left < right){
            participatedGames[temp] = participatedGames[left];
            participatedGames[left] = participatedGames[right];
            participatedGames[right] = participatedGames[temp];
            if (left == mediana) {
                mediana = right;
            }
            if (right == mediana) {
                mediana = left;
            }
        }
    } // end while
} // end Quicksort



