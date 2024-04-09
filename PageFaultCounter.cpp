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

bool numInVector(std::vector<char> vector, char num) {
    for (int idx = 0; idx < vector.size(); idx++) {
        if (vector[idx] == num) {
            return true;
        }
    }
    return false;
}

int vectorFind(std::vector<char> vector, char target) {
    for (int idx = 0; idx < vector.size(); idx++) {
        if (vector[idx] == target) {
            return idx;
        }
    }
    return -1;
}

void printVector(std::vector<char> vector, char lead, char end) {
    std::cout << lead;
    for (int idx = 0; idx < vector.size(); idx++) {
        std::cout << vector[idx];

        if (idx != vector.size() - 1) {
            std::cout << ", ";
        }
    }
    std::cout << end;
}

void printVector(std::vector<std::string> vector, char lead, char end) {
    std::cout << lead;
    for (int idx = 0; idx < vector.size(); idx++) {
        std::cout << vector[idx];

        if (idx != vector.size() - 1) {
            std::cout << ", ";
        }
    }
    std::cout << end;
}

char const* charConvert(int num) {
    std::string t = std::to_string(num);
    char const* n_char = t.c_str();
    
    return n_char;
}

int LRUCount(std::string ref_string, int num_frames) {
    std::vector<char> numbers = numbersInRefString(ref_string);
    std::vector<char> page_table;
    std::vector<std::string> frame_list;
    std::vector<char> used_order;
    int frame = 1;
    int fault_count = 0;

    for (int idx = 0; idx < numbers.size(); idx++) {
        if (!numInVector(page_table, numbers[idx])) {
            fault_count++;
            if (page_table.size() >= num_frames) {
                char LRU = used_order.front();
                used_order.erase(used_order.begin());
                used_order.push_back(numbers[idx]);

                if (numbers[idx] == LRU) {
                    LRU = used_order.front();
                }

                int page_idx = vectorFind(page_table, LRU);

                frame = stoi(frame_list[page_idx]);

                page_table.erase(page_table.begin() + page_idx);
                frame_list.erase(frame_list.begin() + page_idx);
            }
            page_table.push_back(numbers[idx]);
            frame_list.push_back(std::to_string(frame));
            used_order.push_back(numbers[idx]);
            frame++;

            std::cout << "Step " << idx + 1 << " - Page table: ";
            printVector(page_table, '{', '}');
            std::cout << ", Frames: ";
            printVector(frame_list, '[', ']');
            std::cout << ", Faults: " << fault_count << std::endl;

        }
        else {
            std::cout << "Step " << idx + 1 << " - Page table: ";
            printVector(page_table, '{', '}');
            std::cout << ", Frames: ";
            printVector(frame_list, '[', ']');
            std::cout << ", Faults: " << fault_count << std::endl;
        }
    }
    
    return fault_count;
    
}

int OPTCount(std::string ref_string, int num_frames) {
    return -1;
}

int FIFOCount(std::string ref_string, int num_frames) {
    return -1;
}

int main()
{
    std::string ref_string = "7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2, 3";
    
    LRUCount(ref_string, 4);

    return 0;
}
