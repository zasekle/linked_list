//
// Created by jeremiah on 5/3/23.
//

#pragma once

#include <cstddef>
#include <memory>
#include <sstream>
#include <iostream>

template <typename T>
struct CustomList {

    [[nodiscard]] bool empty() const {
        return list_size == 0;
    }

    [[nodiscard]] size_t size() const {
        return list_size;
    }

    void clear() {
        Node* current_node = first_node;
        while (current_node) {
            Node* next_node = current_node->next;
            delete current_node;
            current_node = next_node;
        }

        list_size = 0;
        first_node = nullptr;
        last_node = nullptr;
    }

    void insert(T val, size_t pos) {
        int current_value = 0;
        Node* current_node = first_node;
        while(current_value != pos) {
            current_node = current_node->next;
            current_value++;
        }

        if (pos == 0) {
            first_node = new Node{
                    std::move(val)
            };
            if(empty()) {
                last_node = first_node;
            } else {
                first_node->next = current_node;
                current_node->prev = first_node;
            }
        } else if (pos == list_size) {
            current_node = last_node;
            last_node = new Node{
                    std::move(val)
            };
            last_node->prev = current_node;
            current_node->next = last_node;
        } else { //In middle of list.
            Node* new_node = new Node{
                    std::move(val)
            };
            new_node->next = current_node;
            new_node->prev = current_node->prev;

            new_node->prev->next = new_node;
            current_node->prev = new_node;
        }
        //Should come after, the value is used above.
        list_size++;
    }

    T erase(size_t pos) {
        std::unique_ptr<T> returned_value;
        if (pos == 0) {
            returned_value = std::move(first_node->value);
            if (list_size == 1) {
                delete first_node;
                first_node = nullptr;
                last_node = nullptr;
            } else {
                Node* current_node = first_node;
                first_node = current_node->next;
                first_node->prev = nullptr;
                delete current_node;
            }
        } else if (pos == list_size-1) {
            returned_value = std::move(last_node->value);
            Node* current_node = last_node;
            last_node = current_node->prev;
            last_node->next = nullptr;
            delete current_node;
        } else { //In middle of list.
            int current_value = 0;
            Node* current_node = first_node;
            while(current_value != pos) {
                current_node = current_node->next;
                current_value++;
            }
            returned_value = std::move(current_node->value);

            current_node->next->prev = current_node->prev;
            current_node->prev->next = current_node->next;

            delete current_node;
        }
        //Should come after, the value is used above.
        list_size--;
        return *returned_value;
    }

    void push_back(T val) {
        list_size++;
        if (!first_node) {
            first_node = new Node{
                std::move(val)
            };
            last_node = first_node;
        } else {
            Node* current_last_node = last_node;
            last_node = new Node{
                    std::move(val)
            };
            last_node->prev = current_last_node;
            current_last_node->next = last_node;
        }
    }

    T pop_back() {
        Node* current_last_node = last_node;
        last_node = nullptr;
        list_size--;

        if (current_last_node == first_node) {
            first_node = nullptr;
        } else {
            current_last_node->prev->next = nullptr;
            last_node = current_last_node->prev;
        }

        std::unique_ptr<T> current_value = std::move(current_last_node->value);
        current_last_node->value = nullptr;

        delete current_last_node;
        return *current_value;
    }

    void push_front(T val) {
        list_size++;
        if (!first_node) {
            first_node = new Node{
                    std::move(val)
            };
            last_node = first_node;
        } else {
            Node* current_first_node = first_node;
            first_node = new Node{
                    std::move(val)
            };
            first_node->next = current_first_node;
            current_first_node->prev = first_node;
        }
    }

    T pop_front() {
        Node* current_first_node = first_node;
        first_node = nullptr;
        list_size--;

        if (current_first_node == last_node) {
            last_node = nullptr;
        } else {
            current_first_node->next->prev = nullptr;
            first_node = current_first_node->next;
        }

        std::unique_ptr<T> current_value = std::move(current_first_node->value);
        current_first_node->value = nullptr;

        delete current_first_node;
        return *current_value;
    }

    void print() {
        Node* current_node = first_node;
        std::stringstream string_stream;
        while(current_node) {
            string_stream
                << *current_node->value << ' ';
            current_node = current_node->next;
        }
        std::cout << string_stream.str() << '\n';
    }

private:

    struct Node {
        Node() = delete;

        explicit Node(T&& _value) : value(std::make_unique<T>(_value)) {}

        std::unique_ptr<T> value = nullptr;
        Node* prev = nullptr;
        Node* next = nullptr;
    };

    Node* first_node = nullptr;
    Node* last_node = nullptr;

    size_t list_size = 0;
};

