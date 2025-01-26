#include <algorithm>
#include <iostream>
#include <sstream>
#include <stack>
#include <string>
#include <vector>

using namespace std;

class Node {
 private:
  int nodeNumber;
  string type;
  string textWithin;
  bool inLoop = false;
  int pointCounter = 0;
  int parentLoop = 0;

 public:
  Node() {}
  Node(int nodeNum, string nodeType, string text)
      : nodeNumber(nodeNum), type(nodeType), textWithin(text) {}

  int getNodeNumber() const { return nodeNumber; }
  string getType() const { return type; }
  string getTextWithin() const { return textWithin; }
  int getParentLoop() { return parentLoop; }
  int checkCount() { return pointCounter; }

  void setNodeNumber(int number) { nodeNumber = number; }
  void setType(string settype) { type = settype; }
  void setTextWithin(string text) { textWithin = text; }
  void setIfLoop(bool in) { inLoop = in; }
  void setParentLoop(int n) { parentLoop = n; }
  void IncreaseCount() { pointCounter++; }
  void DecreaseCount() { pointCounter--; }

  bool isInLoop() const { return inLoop; }
};

void convertFlowChart(vector<Node> allNodes, vector<vector<int>> adjList) {
  stack<pair<int, bool>> flowStack;
  cout << "start" << endl;

  // Push the first node after START
  if (!adjList.empty() && !adjList[0].empty()) {
    flowStack.push({adjList[0][0], true});
  }

  while (!flowStack.empty()) {
    pair<int, bool> current = flowStack.top();
    flowStack.pop();
    bool isStart = current.second;
    Node n;

    if (current.first != -1) {
      n = allNodes[current.first];
    } else {
      Node newN(-1, "ELSE", "");
      n = newN;
    }

    if (n.getType() == "IF") {
      if (isStart) {
        cout << "if(" << n.getTextWithin() << ") {" << endl;
        flowStack.push({current.first, false});  // Push IF end

        vector<int> connected = adjList[current.first];
        if (connected.size() >= 2) {
          // Push false branch first, ELSE marker, then true branch
          flowStack.push({connected[1], true});  // False branch (e.g., node 3)
          flowStack.push({-1, true});            // ELSE marker
          flowStack.push({connected[0], true});  // True branch (e.g., node 2)
        }
      } else {
        cout << "}" << endl;  // Close IF block
      }
    } else if (n.getType() == "BLOCK") {
      if (isStart) {
        cout << n.getTextWithin() << ";" << endl;
        vector<int> connected = adjList[current.first];
        for (auto it = connected.rbegin(); it != connected.rend(); ++it) {
          flowStack.push({*it, true});
        }
      }
    } else if (n.getType() == "ELSE") {
      if (isStart) {
        cout << "} else {" << endl;
        flowStack.push({-1, false});  // Push ELSE end
      } else {
        cout << "}" << endl;  // Close ELSE block
      }
    }
  }
  cout << "end" << endl;
}
int main() {
  int numNodesInFlowChart;
  cin >> numNodesInFlowChart;
  cin.ignore();  // Clear the newline after reading numNodesInFlowChart

  vector<Node> allNodes(numNodesInFlowChart);
  string line;

  // Read START node (skips empty lines)
  while (getline(cin, line)) {
    if (line.empty()) continue;
    istringstream iss(line);
    string nodeNumber, nodeType;
    if (iss >> nodeNumber >> nodeType) {
      int index = stoi(nodeNumber);
      allNodes[index] = Node(index, nodeType, "");
      break;
    }
  }

  // Read middle nodes (IF/BLOCK)
  for (int i = 0; i < numNodesInFlowChart - 2; ++i) {
    while (getline(cin, line)) {
      if (line.empty()) continue;
      istringstream iss(line);
      string nodeNumber, nodeType, nodeText;
      if (iss >> nodeNumber >> nodeType >> nodeText) {
        int index = stoi(nodeNumber);
        allNodes[index] = Node(index, nodeType, nodeText);
        break;
      }
    }
  }

  // Read END node (skips empty lines)
  while (getline(cin, line)) {
    if (line.empty()) continue;
    istringstream iss(line);
    string nodeNumber, nodeType;
    if (iss >> nodeNumber >> nodeType) {
      int index = stoi(nodeNumber);
      allNodes[index] = Node(index, nodeType, "");
      break;
    }
  }

  // Read adjacency list
  vector<vector<int>> adjList(numNodesInFlowChart);
  while (getline(cin, line)) {
    if (line.empty()) continue;
    istringstream iss(line);
    vector<int> newVector;
    int u;
    iss >> u;
    int num;
    while (iss >> num) {
      newVector.push_back(num);
    }
    if (u >= 0 && u < numNodesInFlowChart) {
      adjList[u] = newVector;
    }
  }

  convertFlowChart(allNodes, adjList);
  return 0;
}