#include "assignment/linked_list.hpp"

namespace assignment {

  LinkedList::~LinkedList() {

    // эквивалентно очистке списка
    LinkedList::Clear();
  }

  void LinkedList::Add(int value) {
    // Write your code here ...
    Node* node = new Node(value, nullptr);
    if (size_ == 0) {
      front_ = node;
      back_ = node;
    } else {
      back_->next = node;
      back_ = node;
    }
    size_++;
  }

  bool LinkedList::Insert(int index, int value) {
    // Write your code here ...
    if (index < 0 || index > size_) {
      return false;
    }

    Node* newNode = new Node(value, nullptr);
    if (size_ == 0 || index == size_) {
      Add(value);
    } else {
      if (index == 0) {
        newNode->next = front_;
        front_ = newNode;
        size_++;
      } else {

        int i = 0;
        Node* node = front_;
        while (node != nullptr) {
          if (i == index - 1) {
            newNode->next = node->next;
            node->next = newNode;
            break;
          }
          i++;
          node = node->next;
        }
        size_++;
      }
    }
    return true;
  }

  bool LinkedList::Set(int index, int new_value) {
    if (index < 0 || index >= size_) {
      return false;
    }

    int i = 0;
    for (Node* node = front_; node != nullptr; node = node->next) {
      if (i == index) {
        node->value = new_value;
        return true;
      }
      i++;
    }
    return false;
  }

  std::optional<int> LinkedList::Remove(int index) {
    // Write your code here ...
    if (index < 0 || index >= size_) {
      return std::nullopt;
    }

    Node* forDeleteNode = nullptr;
    int value;

    if (index == 0) {
      forDeleteNode = front_;
      front_ = front_->next;
      value = forDeleteNode->value;
    } else {

      int i = 0;
      for (Node* node = front_; node != nullptr; node = node->next) {
        if (i == index - 1) {
          forDeleteNode = node->next;
          node->next = forDeleteNode->next;
          value = forDeleteNode->value;
          break;
        }
        i++;
      }
    }
    delete forDeleteNode;
    size_--;
    return value;
  }

  void LinkedList::Clear() {
    // Write your code here ...
    if (size_ > 0) {
      Node* node = front_;
      Node* forDeleteNode = nullptr;
      while(node != nullptr) {
        forDeleteNode = node;
        node = node->next;
        delete forDeleteNode;
      }
    }
    size_ = 0;
    front_ = nullptr;
    back_ = nullptr;
  }

  std::optional<int> LinkedList::Get(int index) const {
    // Write your code here ...
    if (index < 0 || index >= size_) {
      return std::nullopt;
    }
    Node* listNode = front_;
    for (int i = 1; i <= index; i++) {
      listNode = listNode->next;
    }
    return listNode->value;
  }

  std::optional<int> LinkedList::IndexOf(int value) const {
    // Write your code here ...
    Node* listNode = front_;
    for (int i = 0; i < size_; i++) {
      if (listNode->value == value) {
        return i;
      }
      listNode = listNode->next;
    }
    return std::nullopt;
  }

  bool LinkedList::Contains(int value) const {
    if (this->IndexOf(value) != std::nullopt) {
      return true;
    }
    return false;
  }

  bool LinkedList::IsEmpty() const {
    return size_ == 0;
  }

  int LinkedList::size() const {
    return size_;
  }

  std::optional<int> LinkedList::front() const {
    // Write your code here ...
    if (front_ != nullptr) {
      return front_->value;
    }
    return std::nullopt;
  }

  std::optional<int> LinkedList::back() const {
    // Write your code here ...
    if (back_ != nullptr) {
      return back_->value;
    }
    return std::nullopt;
  }

  Node* LinkedList::FindNode(int index) const {
    // Write your code here ...
    if (index < 0 || index >= size_) {
      return nullptr;
    }
    Node* listNode = front_;
    for (int i = 0; i < index; ++i) {
      listNode = listNode->next;
    }
    return listNode;
  }

  // ДЛЯ ТЕСТИРОВАНИЯ
  LinkedList::LinkedList(const std::vector<int>& values) {

    if (values.empty()) {
      return;
    }

    auto* curr_node = new Node(values.front());
    front_ = curr_node;

    for (int index = 1; index < values.size() - 1; ++index) {
      curr_node->next = new Node(values[index]);
      curr_node = curr_node->next;
    }

    if (values.size() == 1) {
      back_ = front_;
    } else {
      curr_node->next = new Node(values.back());
      back_ = curr_node->next;
    }

    size_ = static_cast<int>(values.size());
  }

  std::vector<int> LinkedList::toVector() const {

    if (front_ == nullptr || size_ == 0) {
      return {};
    }

    std::vector<int> array;
    array.reserve(size_);

    for (auto* node = front_; node != nullptr; node = node->next) {
      array.push_back(node->value);
    }

    return array;
  }

}  // namespace assignment