// Copyright 2022 NNTU-CS
#include <stdexcept>
#include <algorithm>

#include "tree.h"

PMTree::PMTree(const std::vector<char>& input) : elements(input) {
    if (input.empty()) {
        root = nullptr;
        total_permutations = 0;
        return;
    }

    elements = input;
    std::sort(elements.begin(), elements.end());

    root = std::make_shared<Node>('\0');
    buildTree(root, elements);
    total_permutations = factorial(elements.size());
}

void PMTree::buildTree(std::shared_ptr<Node> parent,
    const std::vector<char>& remaining) {
    if (remaining.empty()) return;

    for (size_t i = 0; i < remaining.size(); ++i) {
        auto child = std::make_shared<Node>(remaining[i]);
        parent->children.push_back(child);

        std::vector<char> new_remaining;
        for (size_t j = 0; j < remaining.size(); ++j) {
            if (j != i) {
                new_remaining.push_back(remaining[j]);
            }
        }

        buildTree(child, new_remaining);
    }
}

std::vector<std::vector<char>> PMTree::getAllPerms() const {
    std::vector<std::vector<char>> result;
    if (!root) return result;

    std::vector<char> current;
    getAllPermsHelper(root, current, result);
    return result;
}

void PMTree::getAllPermsHelper(std::shared_ptr<Node> node,
    std::vector<char>& current,
                              std::vector<std::vector<char>>& result) const {
    if (node->value != '\0') {
        current.push_back(node->value);
    }

    if (node->children.empty()) {
        result.push_back(current);
    } else {
        for (const auto& child : node->children) {
            getAllPermsHelper(child, current, result);
        }
    }

    if (node->value != '\0') {
        current.pop_back();
    }
}

std::vector<char> PMTree::getPerm1(int num) const {
    std::vector<char> result;
    if (num < 1 || num > total_permutations) return result;

    int counter = 0;
    std::vector<char> current;
    getPerm1Helper(root, current, counter, num, result);
    return result;
}

void PMTree::getPerm1Helper(std::shared_ptr<Node> node,
    std::vector<char>& current,
                           int& counter, int target,
                           std::vector<char>& result) const {
    if (!result.empty()) return;
    
    if (node->value != '\0') {
        current.push_back(node->value);
    }

    if (node->children.empty()) {
        counter++;
        if (counter == target) {
            result = current;
        }
    } else {
        for (const auto& child : node->children) {
            getPerm1Helper(child, current, counter, target, result);
            if (!result.empty()) return;
        }
    }

    if (node->value != '\0') {
        current.pop_back();
    }
}

std::vector<char> PMTree::getPerm2(int num) const {
    std::vector<char> result;
    if (num < 1 || num > total_permutations) return result;

    int remaining = num - 1;
    std::vector<char> current;
    getPerm2Helper(root, current, remaining, result);
    return result;
}

void PMTree::getPerm2Helper(std::shared_ptr<Node> node,
    std::vector<char>& current,
                           int& remaining,
                           std::vector<char>& result) const {
    if (node->value != '\0') {
        current.push_back(node->value);
    }

    if (node->children.empty()) {
        if (remaining == 0) {
            result = current;
        }
        remaining--;
    } else {
        for (const auto& child : node->children) {
            if (remaining < 0) break;
            
            int subtree_size = factorial(node->children.size() - 1);
            if (remaining >= subtree_size) {
                remaining -= subtree_size;
                continue;
            }
            
            getPerm2Helper(child, current, remaining, result);
            break;
        }
    }

    if (node->value != '\0') {
        current.pop_back();
    }
}

int PMTree::factorial(int n) const {
    static const int fact[] = {1, 1, 2, 6, 24, 120, 720, 5040, 40320,
        362880, 3628800};
    if (n < 0) return 0;
    if (n <= 10) return fact[n];

    int result = 1;
    for (int i = 2; i <= n; ++i) {
        result *= i;
    }
    return result;
}

std::vector<std::vector<char>> getAllPerms(const PMTree& tree) {
    return tree.getAllPerms();
}

std::vector<char> getPerm1(const PMTree& tree, int num) {
    return tree.getPerm1(num);
}

std::vector<char> getPerm2(const PMTree& tree, int num) {
    return tree.getPerm2(num);
}
