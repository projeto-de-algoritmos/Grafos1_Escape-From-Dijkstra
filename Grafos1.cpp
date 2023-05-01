#include <algorithm>
#include<bits/stdc++.h>
#include <ctime>
#include <fstream>
#include <unordered_set>

using namespace std;

// Mapa estático com possíveis posições (x, y)
// Sendo que o par{0, 0}, diferente da origem{0, 0}, é considerado uma PAREDE no mapa!
set<pair<int, int>> list_position_can_move {
  {0, 7},  {1, 7},  {2, 7}, {3, 7}, {4, 7}, {5, 7},
  {0, 6},  {0, 0},  {2, 6}, {3, 6}, {4, 6}, {5, 6},
  {0, 5},  {0, 0},  {2, 5}, {3, 5}, {4, 5}, {5, 5},
  {0, 4},  {0, 0},  {2, 4}, {3, 4}, {4, 4}, {5, 4},
  {0, 3},  {0, 0},  {2, 3}, {3, 3}, {4, 3}, {5, 3},
  {0, 2},  {0, 0},  {2, 2}, {3, 2}, {4, 2}, {5, 2},
  {0, 1},  {0, 0},  {0, 0}, {0, 0}, {0, 0}, {0, 0},
  {0, 0},  {1, 0},  {2, 0}, {3, 0}, {4, 0}, {5, 0}
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

  cout << "A próxima posição do mostro é: ";
  cout << next_position.first << " " << next_position.second << endl;

  return next_position;
}

int main(){
  pair<int, int> monster, player;
  auto map_width = 0, max_map_width = 8;

  cout << "--------- Escape From Dijkstra ---------" << endl << endl; 
  cout << "O mapa do jogo:" << endl; 
  for (auto position : list_position_can_move){
    if (map_width != max_map_width){
      cout << "{" << position.first << ", " << position.second << "} ";
    } else {
      cout << endl;
      map_width = 0;
    }
    map_width++;
  }
  cout << endl << endl;

  auto &[monster_x, monster_y] = monster;
  cout << "Digite a posição (x,y) do monstro (ex.: 0 0): "; 
  cin >> monster_x >> monster_y;

  auto &[player_x, player_y] = player;
  cout << "Digite a posição (x,y) do jogador (ex.: 7 5): ";
  cin >> player_x >> player_y;

  cout << endl;
  while (monster != player)
   monster  =  move_bfs(monster, player);

}
