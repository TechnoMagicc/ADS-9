// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TREE_H_
#define INCLUDE_TREE_H_

#include <vector>
#include <memory>

class PMTree {
 private:
    struct Node {
        char value;
        std::vector<std::shared_ptr<Node>> children;
        Node(char v) : value(v) {}
    };

    std::shared_ptr<Node> root;
    int total_permutations;
    std::vector<char> elements;

    void buildTree(std::shared_ptr<Node> parent, const std::vector<char>
        & remaining);
    void getAllPermsHelper(std::shared_ptr<Node> node, std::vector<char>
        & current, 
                         std::vector<std::vector<char>>& result) const;
    void getPerm1Helper(std::shared_ptr<Node> node, std::vector<char>& current,
                       int& counter, int target, 
                       std::vector<char>& result) const;
    void getPerm2Helper(std::shared_ptr<Node> node, std::vector<char>& current,
                       int& remaining, std::vector<char>& result) const;
    int factorial(int n) const;

 public:
    explicit PMTree(const std::vector<char>& input);
    std::vector<std::vector<char>> getAllPerms() const;
    std::vector<char> getPerm1(int num) const;
    std::vector<char> getPerm2(int num) const;
    int getTotalPermutations() const { return total_permutations; }
};

std::vector<std::vector<char>> getAllPerms(const PMTree& tree);
std::vector<char> getPerm1(const PMTree& tree, int num);
std::vector<char> getPerm2(const PMTree& tree, int num);

#endif // INCLUDE_TREE_H_