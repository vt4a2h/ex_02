#pragma once
#include <exception>
#include <algorithm>
#include <stdio.h>

#define CHECK_AND_RETURN if (index >= arrayLength) throw BadIndex(); return m_Array[index];

namespace fixed_arrays {

    class BadIndex : public std::exception { const char* what() const throw() { return "bad array index"; } };

    /*! \brief Класс FixedArray представляет собой реализацию одномерного статического массива. */
    template <class Type, size_t arrayLength>
    class FixedArray
    {
    public:
        FixedArray() :  m_Array(new Type[arrayLength]), m_Size(arrayLength) {}
        FixedArray(FixedArray &&src) { move(src, this); }
        FixedArray(std::initializer_list<Type> l);
        FixedArray(const FixedArray &src) { copy(src, this); }
        virtual ~FixedArray() { delete []m_Array; }

        FixedArray& operator=(FixedArray &&rhs);
        FixedArray& operator=(const FixedArray &rhs);
        Type& operator[](size_t index)             { CHECK_AND_RETURN }
        const Type& operator[](size_t index) const { CHECK_AND_RETURN }

        const Type& at(size_t index) const { CHECK_AND_RETURN }
        size_t size() const { return m_Size; }
        bool empty()  const { return m_Size != 0 ? true : false; }

        Type* begin() { return m_Array;}
        const Type* begin() const { return m_Array;}

        Type* end() { return m_Array + m_Size;}
        const Type* end() const { return m_Array + m_Size;}

    private:
        void copy(const FixedArray &src, FixedArray &dst);
        void move(FixedArray &&src, FixedArray &dst);

        Type *m_Array;
        size_t m_Size;
    };

    template <class Type, size_t arrayLength>
    FixedArray<Type, arrayLength>::FixedArray(std::initializer_list<Type> l)
        : m_Array(new Type[arrayLength])
        , m_Size(arrayLength)
    {
        std::copy(l.begin(), l.end(), begin());
    }

    template <class Type, size_t arrayLength>
    FixedArray<Type, arrayLength>& FixedArray<Type, arrayLength>::operator=(const FixedArray &rhs)
    {
        if (this != &rhs)
            copy(rhs, *this);

        return *this;
    }

    template <class Type, size_t arrayLength>
    FixedArray<Type, arrayLength>& FixedArray<Type, arrayLength>::operator=(FixedArray &&rhs)
    {
        if (this != &rhs)
            move(rhs, *this);

        return this;
    }

    template <class Type, size_t arrayLength>
    void FixedArray<Type, arrayLength>::copy(const FixedArray &src, FixedArray &dst)
    {
        dst.m_Size = src.m_Size;

        delete []dst.m_Array;
        m_Array = new Type[m_Size];
        std::copy(src.begin(), src.end(), begin());
    }

    template <class Type, size_t arrayLength>
    void FixedArray<Type, arrayLength>::move(FixedArray &&src, FixedArray &dst)
    {
        delete []dst.m_Array;

        dst.m_Array = src.begin();
        src.m_Array = nullptr;

        dst.m_Size = src.size();
        src.m_Size = 0;
    }
}
