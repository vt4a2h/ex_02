#pragma once
#include <exception>
#include <algorithm>
#include <stdio.h>

#define CHECK_AND_RETURN(len, index) if (index >= len) throw BadIndex(); return m_Array[index];

namespace fixed_arrays {

    class BadIndex : public std::exception { const char* what() const throw() { return "bad array index"; } };

    /*! \brief Класс FixedArray представляет собой реализацию одномерного статического массива. */
    template <class Type, size_t arrayLength>
    class FixedArray
    {
    public:
        FixedArray() :  m_Array(new Type[arrayLength]), m_Size(arrayLength) {}
        FixedArray(std::initializer_list<Type> l);
        FixedArray(const FixedArray &src) { copy(src, *this); }
        virtual ~FixedArray() {delete []m_Array; }

        FixedArray& operator=(const FixedArray &rhs);
        Type& operator[](size_t index)             { CHECK_AND_RETURN(arrayLength, index) }
        const Type& operator[](size_t index) const { CHECK_AND_RETURN(arrayLength, index) }

        const Type& at(size_t index) const { CHECK_AND_RETURN(arrayLength, index) }
        size_t size() const { return m_Size; }
        bool empty()  const { return m_Size != 0 ? true : false; }

        Type* begin() { return m_Array;}
        const Type* begin() const { return m_Array;}

        Type* end() { return m_Array + m_Size;}
        const Type* end() const { return m_Array + m_Size;}

        FixedArray(FixedArray &&src) = delete;
        FixedArray& operator=(FixedArray &&rhs) = delete;
    private:
        void copy(const FixedArray &src, FixedArray &dst);

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
            delete []m_Array;
            copy(rhs, *this);

        return *this;
    }

    template <class Type, size_t arrayLength>
    void FixedArray<Type, arrayLength>::copy(const FixedArray &src, FixedArray &dst)
    {
        dst.m_Size = src.m_Size;

        m_Array = new Type[m_Size];
        std::copy(src.begin(), src.end(), begin());
    }


    /*! \brief Класс FixedArray2D представляет собой реализацию двумерного статического массива. */
    template<class Type, size_t N, size_t M>
    class FixedArray2D
    {
    public:
        FixedArray2D() : m_Array(new FixedArray<Type, N>[M]), m_Size(M) {}
        FixedArray2D(std::initializer_list<FixedArray<Type, N>> l);
        FixedArray2D(const FixedArray2D &src) { copy(src, *this); }
        virtual ~FixedArray2D() { delete []m_Array;}

        FixedArray2D& operator=(const FixedArray2D &rhs);
        FixedArray<Type, N>& operator[](size_t index)             { CHECK_AND_RETURN(M, index) }
        const FixedArray<Type, N>& operator[](size_t index) const { CHECK_AND_RETURN(M, index) }

        const FixedArray<Type, N>& at(size_t index) const { CHECK_AND_RETURN(M, index) }
        size_t rowCount() const { return m_Size; }
        size_t colCount() const { return N; }
        bool empty()  const { return m_Size != 0 ? true : false; }

        FixedArray<Type, N>* begin() { return m_Array;}
        const FixedArray<Type, N>* begin() const { return m_Array;}

        FixedArray<Type, N>* end() { return m_Array + m_Size;}
        const FixedArray<Type, N>* end() const { return m_Array + m_Size;}

        FixedArray2D(FixedArray2D &&src) = delete;
        FixedArray2D& operator=(FixedArray2D &&rhs) = delete;

    private:
        void copy(const FixedArray2D &src, FixedArray2D &dst);

        FixedArray<Type, N> *m_Array;
        size_t m_Size;
    };

    template<class Type, size_t N, size_t M>
    FixedArray2D<Type, N, M>::FixedArray2D(std::initializer_list<FixedArray<Type, N>> l)
        : m_Array(new FixedArray<Type, N>[M])
        , m_Size(M)
    {
        std::copy(l.begin(), l.end(), begin());
    }


    template<class Type, size_t N, size_t M>
    FixedArray2D<Type, N, M>& FixedArray2D<Type, N, M>::operator=(const FixedArray2D &rhs)
    {
        if (this != &rhs)
            delete []m_Array;
            copy(rhs, *this);

        return *this;
    }


    template<class Type, size_t N, size_t M>
    void FixedArray2D<Type, N, M>::copy(const FixedArray2D &src, FixedArray2D &dst)
    {
        dst.m_Size = src.m_Size;

        m_Array = new FixedArray<Type, N>[m_Size];
        std::copy(src.begin(), src.end(), begin());
    }

}
