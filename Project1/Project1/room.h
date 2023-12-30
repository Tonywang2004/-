#pragma once
// Room.h
#include <vector>
#include "player.h"

class Room {
public:
    Room(int id) : id(id) {}

    
    int getId() const {
        return id;
    }
    
    // �������������Ƴ���ҡ���ȡ������Ϣ��
    // ��������������ɾ�������
    void AddPlayer(const std::shared_ptr<Player>& player) {
        if (players_.size() < 4) {
            players_.push_back(player);
        }
        
    }
    // ��ȡ�����е������Ŀ
    size_t GetPlayerCount() const {
        return players_.size();
    }
    //��ȡ���
    std::vector<std::string> GetAllPlayerNames() const {
        std::vector<std::string> names;
        for (const auto& player : players_) {
            names.push_back(player->getName());
        }
        return names;
    }
    // �ӷ����Ƴ����
    void RemovePlayer(const std::shared_ptr<Player>& player) {
        players_.erase(std::remove(players_.begin(), players_.end(), player), players_.end());
    }

    

private:
    int id;
    std::vector<std::shared_ptr<Player>> players_;
    std::unordered_map<int, std::shared_ptr<Room>> rooms_;
};
