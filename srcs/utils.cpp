#include "../includes/whole_includes.h"

int int_random(int range_min, int range_max)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(range_min, range_max);
    return dis(gen);
}

int roulette_wheel(int *prob, int prob_num)
{
    std::vector<int> prob_List;
    for(int i=0; i< prob_num; i++){
        prob_List.push_back(prob[i]);
    }

    std::random_device rd;
    std::mt19937 gen(rd());

    std::discrete_distribution<int> d{ prob_List.cbegin(), prob_List.cend() };

    return (d(gen));
}