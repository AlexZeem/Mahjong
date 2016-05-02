#include <QFile>
#include <QDebug>

#include "Game.h"
#include "Hand.h"
#include "User.h"
#include "Participant.h"
#include "DBImpl.h"
#include "DBHandler.h"

namespace persistence {

const QString rootDataPath         = "persistence.dat";

DBHandler::DBHandler()
    : impl(new impl_t())
{ load();

    impl->games.clear();
    Game g1(1,"02/05/2016","Player 2", QVector<int>(4,678));
    impl->games[g1.getGameId()] = g1;

    impl->hands.clear();
    Hand h1(1, 1, 'E', 2, QVector<unsigned int>(4,6), QVector<int>(4,45), "none");
    impl->hands[h1.getHandId()] = h1;

    impl->limits.clear();
    impl->limits << "Green dragon";

    impl->users.clear();
    User u1(false,"q", "q", "Player", "First", "000 123 45 67", "some@email.com", 3.14);
    impl->users[u1.getLogin()] = u1;

    impl->participants.clear();
    Participant p1(1, 1, QVector<QString>(4,"q"));
    impl->participants[p1.getGameId()] = p1;
}

DBHandler::~DBHandler()
{ save(); }

DBHandler* DBHandler::instance()
{
    static DBHandler*  ptr = 0;
    if (!ptr)
        ptr = new DBHandler();

    return ptr;
}

void DBHandler::load(const QString& path)
{
    QFile file(path + rootDataPath);
    file.open(QFile::ReadOnly);
    QDataStream inputStream(&file);
    QString temp;
    inputStream >> impl->gamesDataPath >> temp;
    qDebug() << impl->gamesDataPath << temp.toInt();
    impl->loadGamesData(path, temp.toInt());
    inputStream >> impl->handsDataPath >> temp;
    qDebug() << impl->handsDataPath << temp.toInt();
    impl->loadHandsData(path, temp.toInt());
    inputStream >> impl->limitsDataPath >> temp;
    qDebug() << impl->limitsDataPath << temp.toInt();
    impl->loadLimitsData(path, temp.toInt());
    inputStream >> impl->usersDataPath >> temp;
    qDebug() << impl->usersDataPath << temp.toInt();
    impl->loadUsersData(path, temp.toInt());
    inputStream >> impl->participantsDataPath >> temp;
    qDebug() << impl->participantsDataPath << temp.toInt();
    impl->loadParticipantsData(path, temp.toInt());
    file.close();
}

void DBHandler::save(const QString& path)
{
    QFile file(path + rootDataPath);
    file.open(QFile::WriteOnly);
    QDataStream outStream(&file);

    qDebug() << "Games items:" << impl->games.size();
    outStream << QString("games.dat") << QString::number(impl->games.size());
    impl->saveGamesData(path);

    qDebug() << "Hans items: " << impl->hands.size();
    outStream << QString("hands.dat") << QString::number(impl->hands.size());
    impl->saveHandsData(path);

    qDebug() << "Limits items: " << impl->limits.size();
    outStream << QString("limits.dat") << QString::number(impl->limits.size());
    impl->saveLimitsData(path);

    qDebug() << "Participants items: " << impl->participants.size();
    outStream << QString("participants.dat") << QString::number(impl->participants.size());
    impl->saveUsersData(path);

    qDebug() << "Users items: " << impl->users.size();
    outStream << QString("users.dat") << QString::number(impl->users.size());
    impl->saveParticipantsData(path);

    file.flush();
    file.close();
}

} //persistence
