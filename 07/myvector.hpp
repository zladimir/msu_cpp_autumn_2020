#include <iostream>
#include <new>

template<class T>
class Allocator
{
public:
    Allocator() = default;
    T* allocate(size_t n)
    {
        return static_cast<T*>(operator new(n*sizeof(T)));
    }
    void deallocate(T* ptr, size_t n)
    {
        operator delete(ptr, n*sizeof(T));
    }
    template<class... Args>
    void construct(T* ptr, Args&&... args)
    {
        new(ptr) T(std::forward<Args>(args)...);
    }
    void destroy(T* ptr) noexcept
    {
        ptr->~T();
    }
    ~Allocator() = default;
};

template<class T>
class Iterator
{
    T* ptr_;
    bool reverse_;
public:
    explicit Iterator(T* ptr, bool reverse = false)
    {
        ptr_ = ptr;
        reverse_ = reverse;
    }
    Iterator& operator++()
    {
        if (reverse_) {
            --ptr_;
        } else {
            ++ptr_;
        }
        return *this;
    }
    Iterator& operator--()
    {
        if (reverse_) {
            ++ptr_;
        } else {
            --ptr_;
        }
        return *this;
    }
    Iterator operator+(size_t n)
    {
        if (reverse_) {
            return Iterator(ptr_ - n);
        } else {
            return Iterator(ptr_ + n);
        }
    }
    Iterator operator-(size_t n)
    {
        if (reverse_) {
            return Iterator(ptr_ + n);
        } else {
            return Iterator(ptr_ - n);
        }
    }
    bool operator==(const Iterator<T>& other) const
    {
        return ptr_ == other.ptr_;
    }
    bool operator!=(const Iterator<T>& other) const
    {
        return !(*this == other);
    }
    T& operator*() const
    {
        return *ptr_;
    }
};

template<class T, class allocator=Allocator<T>>
class vector
{
    T* ptr_;
    size_t size_;
    size_t capacity_;
    allocator alloc_;
public:
    explicit vector(size_t count=0)
    {
        ptr_ = alloc_.allocate(count);
        size_ = 0;
        capacity_ = count;
    }
    T& operator[](size_t i)
    {
        return ptr_[i];
    }
    const T& operator[](size_t i) const
    {
        return ptr_[i];
    }
    void push_back(const T& value){
        if (size_ == capacity_) {
            if (capacity_ == 0){
                reserve(1);
            } else {
                reserve(2*capacity_);
            }
        }
        alloc_.construct(ptr_ + size_, value);
        size_++;
    }
    void push_back(T&& value)
    {
        if (size_ == capacity_) {
            if (capacity_ == 0){
                reserve(1);
            } else {
                reserve(2*capacity_);
            }
        }
        alloc_.construct(ptr_ + size_, value);
        size_++;
    }
    void pop_back()
    {
        if (size_ > 0) {
            size_--;
            alloc_.destroy(ptr_ + size_);
        }
    }
    template<class... ArgsT>
    void emplace_back(ArgsT&&... args)
    {
        push_back(std::move(T(args...)));
    }
    Iterator<T> begin() noexcept
    {
        return Iterator<T>(ptr_);
    }
    Iterator<T> rbegin() noexcept
    {
        return Iterator<T>(ptr_ + size_ - 1, true);
    }
    Iterator<T> end() noexcept
    {
        return Iterator<T>(ptr_ + size_);
    }
    Iterator<T> rend() noexcept
    {
        return Iterator<T>(ptr_ - 1, true);
    }
    void reserve(size_t n){
        if (n > capacity_) {
            T* new_ptr = alloc_.allocate(n);
            for (size_t i = 0; i < size_; i++) {
                alloc_.construct(new_ptr + i, ptr_[i]);
                alloc_.destroy(ptr_ + i);
            }
            alloc_.deallocate(ptr_, size_);
            ptr_ = new_ptr;
            capacity_ = n;
        }
    }
    void resize(size_t n)
    {
        if (n < size_) {
            for (size_t i = n; i < size_; ++i) {
                alloc_.destroy(ptr_ + i);
            }
        }
        if (n > size_) {
            reserve(n);
            for (size_t i = size_; i < n; ++i) {
                alloc_.construct(ptr_ + i, T());
            }
        }
        size_ = n;
    }
    size_t capacity() const noexcept
    {
        return capacity_;
    }
    size_t size() const noexcept
    {
        return size_;
    }
    bool empty() const noexcept
    {
        return size_ == 0;
    }
    void clear() noexcept
    {
        for (size_t i = 0; i < size_; ++i) {
            alloc_.destroy(ptr_ + i);
        }
        size_ = 0;
    }
    ~vector()
    {
        for (size_t i = 0; i < size_; ++i) {
            alloc_.destroy(ptr_ + i);
        }
        alloc_.deallocate(ptr_, capacity_);
    }
};