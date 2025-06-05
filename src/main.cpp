// Copyright 2022 NNTU-CS
#include <iostream>
#include <chrono>
#include <random>
#include <fstream>
#include <algorithm>
#include <vector>

#include "tree.h"

void printVector(const std::vector<char>& vec) {
    for (char c : vec) {
        std::cout << c;
    }
    std::cout << std::endl;
}

void runExperiment() {
    std::ofstream dataFile("experiment_data.csv");
    dataFile << "n,getAllPerms,getPerm1,getPerm2\n";

    const int max_n = 10;
    const int samples = 100;

    for (int n = 1; n <= max_n; ++n) {
        std::vector<char> input;
        for (int i = 0; i < n; ++i) {
            input.push_back('a' + i);
        }

        PMTree tree(input);
        int total_perms = tree.getTotalPermutations();

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(1, total_perms);

        auto start = std::chrono::high_resolution_clock::now();
        auto all_perms = getAllPerms(tree);
        auto end = std::chrono::high_resolution_clock::now();
        double all_perms_time = std::chrono::duration<double>
        (end - start).count();

        double perm1_time = 0.0;
        double perm2_time = 0.0;

        for (int i = 0; i < samples; ++i) {
            int num = dis(gen);

            start = std::chrono::high_resolution_clock::now();
            auto perm1 = getPerm1(tree, num);
            end = std::chrono::high_resolution_clock::now();
            perm1_time += std::chrono::duration<double>(end - start).count();

            start = std::chrono::high_resolution_clock::now();
            auto perm2 = getPerm2(tree, num);
            end = std::chrono::high_resolution_clock::now();
            perm2_time += std::chrono::duration<double>(end - start).count();
        }

        perm1_time /= samples;
        perm2_time /= samples;
        dataFile << n << "," << all_perms_time << "," <<
        perm1_time << "," << perm2_time << "\n";
        std::cout << "n = " << n << " completed." << std::endl;
    }

    dataFile.close();
    std::cout << "Experiment data saved to experiment_data.csv" << std::endl;
}

int main() {
    std::vector<char> in = {'1', '2', '3'};
    PMTree tree(in);

    std::cout << "All permutations:" << std::endl;
    auto all_perms = getAllPerms(tree);
    for (const auto& perm : all_perms) {
        printVector(perm);
    }

    std::cout << "\nPermutation 1: ";
    printVector(getPerm1(tree, 1));

    std::cout << "Permutation 2: ";
    printVector(getPerm2(tree, 2));

    std::cout << "Permutation 6: ";
    printVector(getPerm2(tree, 6));
    runExperiment();

    return 0;
}
