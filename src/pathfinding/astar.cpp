//
// Created by 40203 on 22/03/2018.
//
/*
#include "astar.h"
#include <LevelSystem.h>
#include <queue>

using namespace std;
using namespace sf;

class Node {
private:
    Vector2i _pos;
    int _level;
    int _priority;

public:
    Node() = default;
    Node(const Vector2i& pos, int level, int priority)
            : _pos(pos), _level(level), _priority(priority) {}

    const Vector2i& getPos() const {return _pos;}

    int getLevel() const { return  _level;}

    int getPriority() const { return _priority;}

    unsigned int estimate(const Vector2i& dest) const {
      Vector2i delta = dest - _pos;
      return static_cast<unsigned int>(length(delta));
    }

    void updatePriority(const Vector2i& dest){
      //heuristic is just euclidian distance.
      //can be modified
      _priority = _level + estimate(dest) * 10;
    }

    void nextLevel() { _level += 10; }

    //used for priority ordering
    bool operator<(const Node& other) const {
      return _priority > other._priority;
    }
};

vector<Vector2i> pathFind(Vector2i start, Vector2i finish) {
  static std::array<sf::Vector2i, 4> directions = {
          Vector2i(1,0), Vector2i(0,1), Vector2i(-1,0), Vector2i(0,-1)
  };

  //this may not be the most efficient mechanism, but should not be a
  //problem unless your maps get very big.
  vector<vector<bool>> closed_nodes_map(ls::getWidth());
  vector<vector<int>> open_nodes_map(ls::getWidth());
  vector<vector<Vector2i>> direction_map(ls::getWidth());

  //queue of nodes to test, Priority ordered
  //we need two for when we redirect and copy the path.
  priority_queue<Node> queue[2];
  //index of current queue
  size_t queue_index = 0;

  // initialise the lookup maps. Initialally everything looks traverseable and
  //no route has been planned.
  for(size_t y = 0; y<ls::getHeight(); ++y){
    for(size_t x = 0; x<ls::getWidth(); ++x){
      closed_nodes_map[x].push_back(false);
      open_nodes_map[x].push_back(0);
      direction_map[x].emplace_back(Vector2i(0,0));
    }
  }

  //Add start node to the queue = we will check it first
  Node n0(start, 0, 0);
  //update the priority of the node
  n0.updatePriority(finish);
  //push onto the current queue of nodes to check
  queue[queue_index].push(n0);
  //And update the value in the open_nodes_map
  open_nodes_map[start.x][start.y] = n0.getPriority();

  //loop until quque is empty
  while(!queue[queue_index].empty()){
    auto tmp = queue[queue_index].top();
    n0 = Node(tmp.getPos(), tmp.getLevel(), tmp.getPriority());
    auto pos = n0.getPos();

    //remove node from open list
    queue[queue_index].pop();
    open_nodes_map[pos.x][pos.y] = 0;
    //mark on closed node list
    closed_nodes_map[pos.x][pos.y] = true;

    //check if reached goal
    if(pos == finish){
      vector<Vector2i> path;
      while (!(pos == start)){
        //get the direction
        auto dir = direction_map[pos.x][pos.y];
        //add the current pos to the path
        path.push_back(pos);
        pos += dir;
      }
      //path is inverted reverse it
      reverse(begin(path), end(path));
      //return path
      return path;
    }
    //not reached goal check all four directions
    for(auto& dir : directions){
      auto next = pos + dir;

      //check if next is valid
      if(!next.x < 0 || next.x > ls::getWidth() || next.y < 0 ||
              next.y > ls::getHeight() ||
              ls::getTile(Vector2ul(next.x, next.y)) == LevelSystem::groundTiles::types()) {
        //generate new node
        Node m0(next, n0.getLevel(), n0.getPriority());
        m0.nextLevel();
        m0.updatePriority(finish);

        //check if new node has no priority
        if(open_nodes_map[next.x][next.y] == 0){
          //update priority and add to the queue
          open_nodes_map[next.x][next.y] = m0.getPriority();
          queue[queue_index].push(m0);
          //put the opposite direction into the direction map
          //we work backwards
          direction_map[next.x][next.y] = dir * -1;
        }

        //if it has a priority, check if the property is better on the new
        //route
        else if(open_nodes_map[next.x][next.y] > m0.getPriority()){
          //update the priority info
          open_nodes_map[next.x][next.y] = m0.getPriority();
          //update the direction mpa with the inverse direction
          direction_map[next.x][next.y] = dir * -1;
          //now replace the node via via swapping across the lists and ignoring
          //the old one
          while(queue[queue_index].top().getPos() != next) {
            queue[1- queue_index].push(queue[queue_index].top());
            queue[queue_index].pop();
          }
          queue[queue_index].pop();
          if(queue[queue_index].size() > queue[1-queue_index].size())
            queue_index = 1 -queue_index;
          while(!queue[queue_index].empty()){
            queue[1- queue_index].push(queue[queue_index].top());
            queue[queue_index].pop();
          }
        }
      }
    }
  }
  return vector<Vector2i>();
<<<<<<< HEAD
}*/
=======
}

 */
>>>>>>> 3cd22644aa5c3fd379602a19841c6ab484c3569d
