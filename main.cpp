#include <iostream>
#include <algorithm>

struct Measurement {
    int frequency;
    int length;
};

struct Node {
    int year;
    Measurement* measurements;
    int count;
    int max;
    Node* left;
    Node* right;

    Node(int y) : year(y), count(0), max(100), left(nullptr), right(nullptr) {
        measurements = new Measurement[max];
    }

    ~Node() {
        delete[] measurements;
    }

    void add(int frequency, int length) {
        if (count == max) {
            resize();
        }
        measurements[count++] = {frequency, length};
    }

    void resize() {
        max *= 2;
        Measurement* new_measurements = new Measurement[max];
        for (int i = 0; i < count; ++i) {
            new_measurements[i] = measurements[i];
        }
        delete[] measurements;
        measurements = new_measurements;
    }

    void insert() {
        std::sort(measurements, measurements + count, [](const Measurement& a, const Measurement& b) {
            if (a.frequency == b.frequency)
                return a.length < b.length;
            return a.frequency < b.frequency;
        });
    }
};

void add_node(Node*& root, int year, int frequency, int length) {
    if (!root) {
        root = new Node(year);
        root->add(frequency, length);
    } else if (year < root->year) {
        add_node(root->left, year, frequency, length);
    } else if (year > root->year) {
        add_node(root->right, year, frequency, length);
    } else {
        root->add(frequency, length);
    }
}

void check_status(Node*& root, int year, int frequency, int length, bool& is_valid, bool& is_invalid) {
    if (frequency >= 20 && frequency <= 20000) {
        int speed = frequency * length;

        if (speed >= 31300 && speed <= 35000) {
            add_node(root, year, frequency, length);

            if (frequency >= 275 && frequency <= 325) {
                is_valid = true;
            } else {
                is_invalid = true;
            }
        }
    }
}

void tree_print(Node* root) {
    if (!root) return;

    tree_print(root->left);

    root->insert();

    std::cout << root->year << ": ";
    for (int i = 0; i < root->count; ++i) {
        std::cout << "(" << root->measurements[i].frequency << "," << root->measurements[i].length << ") ";
    }
    std::cout << std::endl;

    tree_print(root->right);
}

void clear_mem(Node* root) {
    if (!root) return;
    clear_mem(root->left);
    clear_mem(root->right);
    delete root;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    Node* node = nullptr;

    int n;
    bool is_valid = false;
    bool is_invalid = false;

    std::cin >> n;

    for (int i = 0; i < n; ++i) {
        int year, frequency, length;
        std::cin >> year >> frequency >> length;
        check_status(node, year, frequency, length, is_valid, is_invalid);
    }

    tree_print(node);

    if (is_valid && !is_invalid) {
        std::cout << "TAK" << std::endl;
    } else {
        std::cout << "NIE" << std::endl;
    }

    clear_mem(node);
    return 0;
}

// TIP See CLion help at <a
// href="https://www.jetbrains.com/help/clion/">jetbrains.com/help/clion/</a>.
//  Also, you can try interactive lessons for CLion by selecting
//  'Help | Learn IDE Features' from the main menu.