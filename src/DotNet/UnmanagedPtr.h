// Copyright (c) 2009, Object Computing, Inc.
// All rights reserved.
// See the file license.txt for licensing information.
#pragma once

/// Non ref counted smart pointer.
template<typename T>
ref class UnmanagedPtr
{
public:
  UnmanagedPtr():ptr_(0), size_(0){}

  UnmanagedPtr(T* ptr):ptr_(ptr), size_(sizeof(*ptr_))
  {
    //System::GC::AddMemoryPressure(size_);
  }

  T& GetRef()
  {
    return *ptr_;
  }

  T* operator->()
  {
    return ptr_;
  }

  !UnmanagedPtr() { Release(); }
  ~UnmanagedPtr() { Release(); }

  void Release()
  {
    if(ptr_ != 0)
    {
      delete ptr_;
      //System::GC::RemoveMemoryPressure(size_);
      ptr_ = 0;
      size_ = 0;
    }
  }

private:
  T* ptr_;
  long long size_;

};


template <typename T>
ref class BoostPtrHolder
{
public:
  typedef typename T::element_type* TPointer;
  typedef typename T::element_type TValue;
  typedef BoostPtrHolder<T> TMyType;

  BoostPtrHolder(): ptr_(new T), size_(0) {}
  BoostPtrHolder(const T& rhs):ptr_(new T(rhs)), size_(sizeof(*ptr_))
  {
    //System::GC::AddMemoryPressure(size_);
  }


  ~BoostPtrHolder()
  {
    Release();
  }

  !BoostPtrHolder()
  {
    Release();
  }

  T& GetBoostPtr()
  {
    return *ptr_;
  }

  T& operator=(T& rhs)
  {
    (*ptr_) = rhs;
  }

  TValue& GetRef()
  {
    return *((*ptr_).operator->());
  }

  TPointer operator->()
  {
    return (*ptr_).operator->();
  }

  operator T()
  {
    return *ptr_;
  }


  void Release()
  {
    if(ptr_ != 0)
    {
      delete ptr_;
      //System::GC::RemoveMemoryPressure(size_);
      ptr_ = 0;
      size_ = 0;
    }
  }

private:
  T* ptr_;
  long long size_;
};
