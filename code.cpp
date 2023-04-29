#include <algorithm>
#include<bits/stdc++.h>
#include <ctime>
#include <fstream>
#include <unordered_set>

using namespace std;


set<pair<int, int>> list_position_can_move {
  {7, 0},  {7, 1},  {7, 2}, {7, 3}, {7, 4}, {7, 5},
  {6, 0},  {0, 0},  {6, 2}, {6, 3}, {6, 4}, {6, 5},
  {5, 0},  {0, 0},  {5, 2}, {5, 3}, {5, 4}, {5, 5},
  {4, 0},  {0, 0},  {4, 2}, {4, 3}, {4, 4}, {4, 5},
  {3, 0},  {0, 0},  {3, 2}, {3, 3}, {3, 4}, {3, 5},
  {2, 0},  {0, 0},  {2, 2}, {2, 3}, {2, 4}, {2, 5},
  {1, 0},  {0, 0},  {0, 0}, {0, 0}, {0, 0}, {0, 0},
  {0, 0},  {0, 1},  {0, 2}, {0, 3}, {0, 4}, {0, 5}
};


std::pair<int, int> move_bfs(std::pair<int, int> monster, std::pair<int, int> player ) {

  auto [monster_x, monster_y] = monster;
  auto [player_x, player_y] = player;


  const std::vector<std::pair<int, int>> moves {{0, 1}, {1, 0}, {-1, 0}, {0, -1}};

  std::map<std::pair<int, int>, std::pair<int, int>> father;

  std::pair<int, int> current_position_of_moster(monster_x,monster_y);

  std::queue<std::pair<int, int>> q;
  q.push(current_position_of_moster);

  std::set<std::pair<int, int>> visited;
  visited.insert(current_position_of_moster);

  while (not q.empty()) {

      auto v = q.front();
      q.pop();

      for (auto m : moves) {
          std::pair<int, int> u;
          u.first = m.first + v.first;
          u.second = m.second + v.second;

          if (!visited.count(u) && list_position_can_move.count(u)) {
              father[u] = v;
              q.push(u);
              visited.insert(u);
          }
      }
  }

  std::pair<int, int> next_position = std::make_pair(player_x, player_y);

  while (father[next_position] != current_position_of_moster) {
      next_position = father[next_position];
  }

  cout << "a próxima posição do mostro é: " << endl;
  cout << next_position.first << " " << next_position.second << endl;

  return next_position;
}

int main(){
  pair<int, int> monster, player;

  auto &[monster_x, monster_y] = monster;
  cin >> monster_x >> monster_y;

  auto &[player_x, player_y] = player;
  cin >> player_x >> player_y;

  while (monster != player)
   monster  =  move_bfs(monster, player);


}
