#pragma once
#include <iostream>
#include <vector>
#include <string>
// ������һ�� Player ��
class Player0
{
public:
    Player0(int id, std::string name) : id(id), name(std::move(name)) {}
    int getId() const { return id; }                    // ��ȡ���ID
    const std::string &getName() const { return name; } // ��ȡ�������

private:
    int id;
    std::string name;
};

// Room �ඨ��
class Room
{
private:
    int id;                       // �����ID
    std::vector<Player0> players; // �����е����

public:
    // ���캯��
    Room(int id) : id(id) {}

    bool addPlayer(const Player0 &player)
    {
        if (players.size() < 4)
        { // ���Ʒ���Ϊ4��
            players.push_back(player);
            return true;
        }
        return false;
    }
    const std::vector<Player0> &getPlayers() const
    {
        return players;
    }

    // ��ȡ����ID
    int getId() const
    {
        return id;
    }
};