#include <cstdlib>
#include <fstream>
#include <iostream>
#include <memory>
#include <numeric>
#include <stdexcept>
#include <vector>

namespace {
struct Node {
  int nr_child_nodes = 0;
  int nr_metadata = 0;
  std::vector<std::unique_ptr<Node>> child_nodes;
  std::vector<int> metadata;
};

std::istream &operator>>(std::istream &fin, Node &node) {
  fin >> node.nr_child_nodes >> node.nr_metadata;
  if (!fin) throw std::runtime_error("problem readin instream");
  for (int ch_id = 0; ch_id < node.nr_child_nodes; ch_id++) {
    auto p_node = std::make_unique<Node>();
    if (fin >> *p_node)
      node.child_nodes.push_back(std::move(p_node));
    else
      throw std::runtime_error("problme reading instream");
  }
  for (int meta_id = 0; meta_id < node.nr_metadata; meta_id++) {
    int md;
    if (fin >> md)
      node.metadata.push_back(md);
    else
      throw std::runtime_error("problem reading instream");
  }
  return fin;
}

int sumMetadata(Node const& node){
  int sum = std::accumulate(node.metadata.begin(), node.metadata.end(), 0);
  for(auto const& child : node.child_nodes){
    sum += sumMetadata(*child);
  }
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
  std::cout << "The sum of meta data is " << sumMetadata(node) << '\n';
  return EXIT_SUCCESS;
}
