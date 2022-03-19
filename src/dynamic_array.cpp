#include "assignment/dynamic_array.hpp"

#include <algorithm>  // copy, fill
#include <stdexcept>  // invalid_argument (НЕЛЬЗЯ ИСПОЛЬЗОВАТЬ)

namespace assignment {

  DynamicArray::DynamicArray(int capacity) {

    // выбрасываем ошибку, если указана неположительная емкость массива
    if (capacity <= 0) {
      throw std::invalid_argument("capacity is not positive");
    }

    // Write your code here ...
    size_ = 0;
    capacity_ = capacity;
    data_ = new int[capacity_]{0};
  }

  DynamicArray::~DynamicArray() {
    // Write your code here ...
    capacity_ = 0;
    delete[] data_;
    data_ = nullptr;
    size_ = 0;
  }

  void DynamicArray::Add(int value) {
    // Write your code here ...
    if (size_ >= capacity_) {
      Resize(size_ + kCapacityGrowthCoefficient);
    }
    data_[size_] = value;
    size_++;
  }

  bool DynamicArray::Insert(int index, int value) {
    // Write your code here ...
    if (index < 0 || index > size_ ) {
      return false;
    } else if (size_ >= capacity_) {
      Resize(size_ + kCapacityGrowthCoefficient);
    }

    for (int i = size_; i > index; i--) {
      data_[i] = data_[i-1];
    }
    data_[index] = value;
    size_++;
    return true;
  }

  bool DynamicArray::Set(int index, int new_value) {
    // Write your code here ...
    if (index < 0 || index >= size_) {
      return false;
    }
    data_[index] = new_value;
    return true;
  }

  std::optional<int> DynamicArray::Remove(int index) {
    // Write your code here ...
    if (index >= 0 && index < size_) {
      int deletedInt = data_[index];
      for (int i = index; i < size_; i++) {
        data_[i] = data_[i+1];
      }
      size_--;
      return deletedInt;
    }
    return std::nullopt;
  }

  void DynamicArray::Clear() {
    // Write your code here ...
    delete[] data_;
    data_ = new int[kInitCapacity]{};
    size_ = 0;

  }

  std::optional<int> DynamicArray::Get(int index) const {
    // Write your code here ...
    if (index >= 0 && index < size_) {
      return data_[index];
    }
    return std::nullopt;
  }

  std::optional<int> DynamicArray::IndexOf(int value) const {
    // Write your code here ...
    for (int i = 0; i < size_; i++) {
      if (data_[i] == value) {
        return i;
      }
    }
    return std::nullopt;
  }

  bool DynamicArray::Contains(int value) const {
    return (this->IndexOf(value) == std::nullopt) ? false : true;
  }

  bool DynamicArray::IsEmpty() const {
    return size_ == 0;
  }

  int DynamicArray::size() const {
    return size_;
  }

  int DynamicArray::capacity() const {
    return capacity_;
  }

  bool DynamicArray::Resize(int new_capacity) {
    // Write your code here ...
    if (new_capacity <= capacity_) {
      return false;
    }
    int* newData = new int[new_capacity];
    for (int i = 0; i < size_; i++) {
      newData[i] = data_[i];
    }
    for (int i = size_; i < new_capacity; i++) {
      newData[i] = 0;
    }

    delete[] data_;
    data_ = newData;
    newData = nullptr;
    capacity_ = new_capacity;
    return true;
  }

  // ДЛЯ ТЕСТИРОВАНИЯ
  DynamicArray::DynamicArray(const std::vector<int>& values, int capacity) {

    size_ = static_cast<int>(values.size());
    capacity_ = capacity;

    data_ = new int[capacity]{};

    std::copy(values.data(), values.data() + size_, data_);
  }

  std::vector<int> DynamicArray::toVector(std::optional<int> size) const {

    if (capacity_ == 0 || data_ == nullptr) {
      return {};
    }

    if (size.has_value()) {
      return {data_, data_ + size.value()};
    }

    return {data_, data_ + capacity_};
  }

}  // namespace assignment