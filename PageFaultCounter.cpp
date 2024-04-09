#include <iostream>
#include <string>
#include <vector>

std::vector<char> numbersInRefString(std::string ref_string) {
    std::vector<char> num_list;
    for (int idx = 0; idx < ref_string.size(); idx++) {
        if (ref_string[idx] != ',' && ref_string[idx] != ' ') {
            num_list.push_back(ref_string[idx]);
        }
    }
    return num_list;
}

int LRUCount(std::string ref_string, int num_frames) {
    std::vector<char> numbers = numbersInRefString(ref_string);
    std::vector<int> frame_list;
    std::vector<int> used_order;

    
    return -1;
    
}

int OPTCount(std::string ref_string, int num_frames) {
    return -1;
}

int FIFOCount(std::string ref_string, int num_frames) {
    return -1;
}

int main()
{
    std::string ref_string = "1, 2, 3, 4, 1, 2, 5, 1, 2, 3, 4, 5";
    std::vector<char> numbers = numbersInRefString(ref_string);

    for (int i = 0; i < numbers.size(); i++) {
        std::cout << numbers[i] << " ";
    }

    return 0;
}
