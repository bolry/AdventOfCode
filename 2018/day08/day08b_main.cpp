#include <cstdlib>
#include <fstream>
#include <iostream>
#include <memory>
#include <numeric>
#include <stdexcept>
#include <vector>

namespace {
struct Node {
  std::vector<Node> child_nodes;
  std::vector<int> metadata;
};

std::istream &operator>>(std::istream &fin, Node &node) {
  int nr_child_nodes;
  int nr_metadata;
  fin >> nr_child_nodes >> nr_metadata;
  if (!fin) throw std::runtime_error("problem readin instream");

  node.child_nodes.resize(nr_child_nodes);
  for (auto &ch_node : node.child_nodes)
    if (!(fin >> ch_node))
      throw std::runtime_error("problme reading instream");

  node.metadata.resize(nr_metadata);
  for (int &md : node.metadata)
    if (!(fin >> md))
      throw std::runtime_error("problem reading instream");

  return fin;
}

int sumDataVersionB(Node const &node) {
  if (node.child_nodes.size() == 0) return std::accumulate(node.metadata.begin(), node.metadata.end(), 0);
  int sum = 0;
  for (int const index : node.metadata)
    if (0 < index && index <= node.child_nodes.size())
      sum += sumDataVersionB(node.child_nodes[index - 1]);
  return sum;
}

}  // close anonymous namespace

int main(int argc, char *argv[]) {
  std::cout.exceptions(std::cout.badbit | std::cout.eofbit | std::cout.failbit);
  if (argc < 2)
    throw std::runtime_error("Need one filename as input");
  std::ifstream in_file(argv[1]);
  if (!in_file)
    throw std::runtime_error("Problem opening file " + std::string(argv[1]));
  Node node;
  in_file >> node;
  std::cout << "The result for second part should be " << sumDataVersionB(node) << '\n';
  return EXIT_SUCCESS;
}
