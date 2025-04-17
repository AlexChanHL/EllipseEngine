#pragma once

#include <memory>


template<typename T>
class VectorSharedIteratorHeap
{
   public:
    VectorSharedIteratorHeap()
    : m_size{0},
      m_begin{nullptr},
      m_current{nullptr},
      m_end{nullptr}
    {
    m_begin = std::make_shared<Iterator>();
    m_current = m_begin;
    m_end = std::make_shared<Iterator>();
    m_end->m_elem = std::make_shared<T>();
    m_begin->m_next = m_end;
    m_end->m_prev = m_begin;
    }

    VectorSharedIteratorHeap(T elem)
    : m_size{0},
      m_begin{nullptr},
      m_current{nullptr},
      m_end{nullptr}
    {
    m_begin = std::make_shared<Iterator>();
    m_begin->m_elem = std::make_shared<T>(elem);
    m_size++;
    m_current = m_begin;
    m_end = std::make_shared<Iterator>();
    m_end->m_elem = std::make_shared<T>();
    m_begin->m_next = m_end;
    m_end->m_prev = m_begin;
    }

    VectorSharedIteratorHeap(unsigned long size)
    : m_size{size}
    {
    m_begin = std::make_shared<Iterator>();
    m_current = m_begin;

    for(unsigned long i=0;i<size - 1;i++)
    {
    m_current->m_next = std::make_shared<Iterator>();
    m_current->m_next->m_prev = m_current;
    m_current = m_current->m_next;

    }

    m_current->m_next = m_end;
    m_end = std::make_shared<Iterator>();
    m_end->m_prev = m_current;
    }

    ~VectorSharedIteratorHeap()
    {
    std::shared_ptr<Iterator> input = m_begin;
    while(input != m_end)
    {
    std::shared_ptr<Iterator> inputNext = input->m_next;
    input = inputNext;
    }


    }

    class Iterator
    {
       public:
        Iterator()
        : m_elem{nullptr},
          m_next{nullptr},
          m_prev{nullptr}
        {

        }

        void operator--(int32_t val)
        {
        m_next = m_prev->m_next;
        m_elem = m_prev->m_elem;
        m_prev = m_prev->m_prev;
        }

        void operator++(int32_t val)
        {
        m_prev = m_next->m_prev;
        m_elem = m_next->m_elem;
        m_next = m_next->m_next;
        }

        Iterator operator+(unsigned long val)
        {
        Iterator current = *(m_next->m_prev);

        for(unsigned long i=0;i<val;i++)
        {
        current = *(current.m_next);
        }

        return current;
        }
        Iterator operator-(unsigned long val)
        {
        // if(m_next == nullptr)
        // {
        // current = *(m_prev->m_next);
        // }
        // Iterator current = *(m_next->m_prev);
        Iterator current = *(m_prev->m_next);

        for(unsigned long i=0;i<val;i++)
        {
        current = *(current.m_prev);
        }

        return current;
        }

        bool operator==(Iterator input)
        {
        return m_elem == input.m_elem;
        }
        bool operator!=(Iterator input)
        {
        return m_elem != input.m_elem;
        }

        T& operator*()
        {
        return *m_elem;
        }
        T& operator->()
        {
        return *m_elem;
        }
        
       public:
        std::shared_ptr<T> m_elem;
        std::shared_ptr<Iterator> m_next;
        std::shared_ptr<Iterator> m_prev;

       private:
    };

    T& operator[](unsigned long idx)
    {
    Iterator iterator = begin();
    for(unsigned long i = 0;i < idx;i++)
    {
    iterator++;
    }

    return *iterator;
    }

    T& operator[](unsigned long idx) const
    {
    Iterator iterator = begin();
    for(unsigned long i = 0;i < idx;i++)
    {
    iterator++;
    }

    return *iterator; }

    void pushBack(T val)
    {
    if(m_begin->m_elem == nullptr)
    {
    m_current->m_elem = std::make_shared<T>(val);
    m_end->m_prev = m_current;
    m_current->m_next = m_end;
    m_size++;
    return;
    }

    m_current->m_next = std::make_shared<Iterator>();
    m_current->m_next->m_elem = std::make_shared<T>(val);
    m_current->m_next->m_prev = m_current;
    m_current = m_current->m_next;
    m_current->m_next = m_end;
    m_end->m_prev = m_current;
    m_size++;
    return;
    }

    // void insert(std::shared_ptr<Iterator> input)
    // {
    // std::shared_ptr<Iterator> first = m_begin;
    // while(first != m_end)
    // {
    // if(first == input)
    // {
    // std::shared_ptr<Iterator> newIter = std::make_shared<Iterator>();
    // newIter->m_next = first->m_next;
    // newIter = first->m_next->m_prev;
    // newIter->m_prev = first;
    // first->m_next = newIter;
    // break;
    // }
    //     
    // first = first->m_next;
    // }
    // }

    void erase(Iterator input)
    {
    if(input == *m_begin)
    {
    std::shared_ptr<Iterator> iteratorBegin = m_begin->m_next;
    m_begin->m_elem = nullptr;

    if(iteratorBegin != m_end)
    {
    m_begin = iteratorBegin;
    }

    m_size--;
    return;
    }

    std::shared_ptr<Iterator> first = m_begin;

    while(first != m_end)
    {
    if(*first == input)
    {
    first->m_prev->m_next = first->m_next;

    first->m_next->m_prev = first->m_prev;
    break;
    }
    first = first->m_next;
    }

    if(first->m_next == m_end)
    {
    m_current = first->m_prev;
    }
    m_size--;
    }

    // void popBack()
    // {
    // std::shared_ptr<Iterator> endPrevElem = m_end->m_prev->m_prev;
    // delete m_end->m_prev;
    // m_end->m_prev = endPrevElem;
    // m_end->m_prev->m_next = m_end;
    // }

    void reverse()
    {
    Iterator endIterator = end(); 
    std::shared_ptr<Iterator> beginIterator = m_begin; 
    std::shared_ptr<Iterator> iterator = m_end;
    VectorSharedIteratorHeap nums;
    
    while(iterator != m_begin)
    {
    nums.pushBack(**(endIterator.m_prev));
    endIterator--;
    iterator = iterator->m_prev;
    }

    iterator = m_end;
    unsigned long idx = 0;
    while(iterator != m_begin)
    {
    beginIterator->m_elem = nums[idx];
    beginIterator = beginIterator->m_next;
    idx++;
    iterator = iterator->m_prev;
    }

    }

    bool empty()
    {
    if(m_size == 0)
    {
    return true;
    }
    return false;
    }

    T back()
    {
    return **(m_end->m_prev);
    }

    unsigned long size()
    {
    return m_size;
    }

    unsigned long size() const
    {
    return m_size;
    }

    Iterator begin()
    {
    return *m_begin;
    }

    Iterator begin() const
    {
    return *m_begin;
    }

    Iterator end()
    {
    return *m_end;
    }

    Iterator end() const
    {
    return *m_end;
    }
    
   private:
    unsigned long m_size;
    std::shared_ptr<Iterator> m_begin;
    std::shared_ptr<Iterator> m_current;
    std::shared_ptr<Iterator> m_end;
};
