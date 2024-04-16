#include <iostream>
#include <string>
#include <vector>

//helper function to find the numbers in the ref string
std::vector<std::string> numbersInRefString(std::string ref_string) {
    //variables to store the numbers, and work
    std::vector<std::string> num_list;
    std::string number;
    int idx = 0;

    //loops until the end of the string
    while (ref_string[idx] != '\0') {
        //checks if the character is not a space or comma
        if (ref_string[idx] != ',' && ref_string[idx] != ' ') {
            number.push_back(ref_string[idx]);
        }
        else {
            //checks the temp string is not empty, then adds it to the list of numbers
            if (number != "") {
                num_list.push_back(number);
            }
            number.clear();
        }
        idx++;
    }
    //adds the last number in the list to the return
    num_list.push_back(number);
    return num_list;
}

//helper function to check for a number in a vector
bool numInVector(std::vector<std::string> vector, std::string num) {
    //loops through the vector and checks if the string is present then returns true
    for (int idx = 0; idx < vector.size(); idx++) {
        if (vector[idx] == num) {
            return true;
        }
    }
    return false;
}

//helper function to find the index of a specific number in a vector
int vectorFind(std::vector<std::string> vector, std::string target) {
    //loops through the vector and returns the index if the target is found
    for (int idx = 0; idx < vector.size(); idx++) {
        if (vector[idx] == target) {
            return idx;
        }
    }
    return -1;
}

//helper function to print the contents of a vector in a good format
void printVector(std::vector<std::string> vector, char lead, char end) {
    //prints the leading character
    std::cout << lead;
    //loops through the vector and prints each element separated by a comma and a space
    for (int idx = 0; idx < vector.size(); idx++) {
        std::cout << vector[idx];

        if (idx != vector.size() - 1) {
            std::cout << ", ";
        }
    }
    //prints the ending character
    std::cout << end;
}

//function for Least Recently Used replacement algorithm
void LRUCount(std::string ref_string, int num_frames) {
    //variables for the input, page table, and frame list as well as an order and frame track for replacement
    std::vector<std::string> numbers = numbersInRefString(ref_string);
    std::vector<std::string> page_table;
    std::vector<std::string> frame_list;
    std::vector<std::string> used_order;
    int frame = 1;
    int fault_count = 0;

    //loops through the input numbers
    for (int idx = 0; idx < numbers.size(); idx++) {
        if (!numInVector(page_table, numbers[idx])) {
            //increases the fault count if the current page number is not already allocated
            fault_count++;

            //performs the replacement algorithm if all frames are allocated otherwise allocates a new frame
            if (page_table.size() >= num_frames) {
                //each time an input is called we add it to the used order list, so closer to the front of the list is the oldest page used. With this we can delete the first element
                std::string LRU = used_order.front();
                used_order.erase(used_order.begin());
                used_order.push_back(numbers[idx]);

                //finds the index of the LRU page
                int page_idx = vectorFind(page_table, LRU);

                //gets the frame associated with the page index
                frame = stoi(frame_list[page_idx]);

                //removes the LRU page and frame so that the new page can be added with the LRU frame
                page_table.erase(page_table.begin() + page_idx);
                frame_list.erase(frame_list.begin() + page_idx);
            }

            //adds the page and frame to their respective lists and increments the frame, so that if it is less than the max and does not do the replacement that it will be a new frame
            page_table.push_back(numbers[idx]);
            frame_list.push_back(std::to_string(frame));
            used_order.push_back(numbers[idx]);
            frame++;
        }
        else {
            //updates the used order if there is a page hit
            int loc = vectorFind(used_order, numbers[idx]);
            used_order.erase(used_order.begin() + loc);
            used_order.push_back(numbers[idx]);
        }
        //formats the output to the way the homework specified
        std::cout << "Step " << idx + 1 << " - Page table: ";
        printVector(page_table, '{', '}');
        std::cout << ", Frames: ";
        printVector(frame_list, '[', ']');
        std::cout << ", Faults: " << fault_count << std::endl;
    }   
}

//function for Optimal replacement algorithm
void OPTCount(std::string ref_string, int num_frames) {
    std::vector<std::string> numbers = numbersInRefString(ref_string);
    std::vector<std::string> page_table;
    std::vector<std::string> frame_list;
    int frame = 1;
    int fault_count = 0;

    for (int idx = 0; idx < numbers.size(); idx++) {
        if (!numInVector(page_table, numbers[idx])) {
            fault_count++;
            if (page_table.size() >= num_frames && idx != numbers.size() - 1) {
                std::string replace = page_table[0];
                std::vector<int> counts = { 0, 0, 0, 0 };
                for (int index = idx + 1; index < numbers.size(); index++) {
                    if (numInVector(page_table, numbers[index])) {
                        counts[vectorFind(page_table, numbers[index])]++;
                    }
                    int min = counts[0];
                    for (int j = 0; j < counts.size(); j++) {
                        if (counts[j] < min) {
                            replace = page_table[j];
                            min = counts[j];
                        }
                    }
                }
                
                int page_idx = vectorFind(page_table, replace);

                frame = stoi(frame_list[page_idx]);

                page_table.erase(page_table.begin() + page_idx);
                frame_list.erase(frame_list.begin() + page_idx);

                
              
            }
            else if (page_table.size() >= num_frames){
                page_table.erase(page_table.begin());
                frame = stoi(frame_list[0]);
                frame_list.erase(frame_list.begin());
            }

            page_table.push_back(numbers[idx]);
            frame_list.push_back(std::to_string(frame));
            frame++;    
        }
        //formats the output to the way the homework specified
        std::cout << "Step " << idx + 1 << " - Page table: ";
        printVector(page_table, '{', '}');
        std::cout << ", Frames: ";
        printVector(frame_list, '[', ']');
        std::cout << ", Faults: " << fault_count << std::endl;
    }
}

//function for First In First Out replacement algorithm
void FIFOCount(std::string ref_string, int num_frames) {
    //variables for the input, page table, and frame list as well as the frame
    std::vector<std::string> numbers = numbersInRefString(ref_string);
    std::vector<std::string> page_table;
    std::vector<std::string> frame_list;
    int frame = 1;
    int fault_count = 0;

    //loops through the input
    for (int idx = 0; idx < numbers.size(); idx++) {
        if (!numInVector(page_table, numbers[idx])) {
            //increases the fault count if the given input is not in the page table yet
            fault_count++;

            //if all the frames are allocated, begins the replacement algorithm
            if (page_table.size() >= num_frames) {
                page_table.erase(page_table.begin()); //erases the first element in the page table
                frame = stoi(frame_list[0]); //sets the frame to the erased elements frame
                frame_list.erase(frame_list.begin()); //removes the fram to prepare it being replaced
            }
            //adds the frame and page to the respective lists
            page_table.push_back(numbers[idx]);
            frame_list.push_back(std::to_string(frame));
            frame++;
        }
        //formats the output
        std::cout << "Step " << idx + 1 << " - Page table: ";
        printVector(page_table, '{', '}');
        std::cout << ", Frames: ";
        printVector(frame_list, '[', ']');
        std::cout << ", Faults: " << fault_count << std::endl;
        
    }
}

int main()
{
    std::string ref_string = "";
    int num_frames = 0;

    std::cout << "Enter the reference string: ";
    std::getline(std::cin, ref_string);

    std::cout << "Enter the number of frames: ";
    std::cin >> num_frames;

    if (std::cin.fail()) {
        std::cout << "An invalid input was given for number of frames.";
        return -1;
    }
    
    OPTCount(ref_string, num_frames);

    return 0;
}
