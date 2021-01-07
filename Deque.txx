#include <iostream>
#include <cstddef>

#include "Deque.hpp"

template<typename T>
Deque<T>::Deque()
{
  deque = new T[64+1];
  N = 64;
  F = 0;
  B = 0;  
} // end default constructor

template<typename T>
Deque<T>::Deque(const Deque& rhs )
{
  N = rhs.N;
  F = rhs.F;
  B = rhs.B;

  deque = new T[N+1];
  std::copy(rhs.deque, rhs.deque+rhs.N+1, deque);
}

template<typename T>
Deque<T>& Deque<T>::operator=(Deque rhs)
{
  swap(*this,rhs);

  return *this;
}

template<typename T>
Deque<T>::~Deque()
{
  delete [] deque;
}

template<typename T>
bool Deque<T>::isEmpty() const noexcept
{
  return (F == B);
}

template<typename T>
void Deque<T>::pushFront(const T & item)
{
  //index for next item we add to deque from the front
  size_t Fn;
  if(F == 0)
    Fn = N;
  else
    Fn = F-1;

  if(Fn == B) //grow if we're full
    {
      grow();
      //grow updates F and B so we push again with new F & B
      pushFront(item);
    }
  else //add item at next location
    {
      F = Fn;
      deque[(F+1)%(N+1)] = item;
    }
}

template<typename T>
void Deque<T>::popFront()
{
  if(isEmpty())
    throw std::runtime_error("Popping empty deque from the front");
  else
    F = (F+1)%(N+1);
}

template<typename T>
T Deque<T>::front() const
{
  if(isEmpty())
    throw std::runtime_error("Looking at the front of an empty deque");
  else
    return deque[(F+1)%(N+1)];
}

template<typename T>
void Deque<T>::pushBack(const T & item)
{
  //index for next item we add to deque from the back
  size_t Bn = (B+1)%(N+1);
  
  if(Bn == F) //grow if we're full
    {
      grow();
      //grow updates F and B so we push again with new F & B
      pushBack(item);
    }
  else
    {
      //add item at next location
      B = Bn;
      deque[B] = item;
    }
}

template<typename T>
void Deque<T>::popBack()
{
  if(isEmpty())
    throw std::runtime_error("Popping empty deque from the back");
  else if (B == 0) //since B is size_t so we have to manually wrap it when it's already at index 0
    B = N;
  else
    B--;
}

template<typename T>
T Deque<T>::back() const
{
    if(isEmpty())
      throw std::runtime_error("Looking at the back of an empty deque");
    else
      return deque[B];
}

template<typename T>
void Deque<T>::swap(Deque<T>& x, Deque<T>& y)
{
  std::swap(x.deque, y.deque);
  std::swap(x.N, y.N);
  std::swap(x.F, y.F);
  std::swap(x.B, y.B);  

  return;
}

template<typename T>
void Deque<T>::grow()
{
  //strategy: copy deque to new array so that front of deque is at index 0 and back of deque is at index N
  T * odeque = deque;
  
  deque = new T[2*N+1];

  //NOTE: the simplest (but less efficient) way to copy new old deque to new deque is via getting front from odeque and pushing back to new deque
  //copy over elements from old deque to new with front at index 0 and back at index N 
  int j = 1; //where elements from odeque will be placed in expanded deque
  
  for(int i = (F+1)%(N+1); i != B; i = (i+1)%(N+1)) //start from first element in deque and copy until we reach back index 
    {
      deque[j] = odeque[i];
      j++;
    }

  //copy over last element from old deque (since we stopeed at back index before copying)
  deque[j] = odeque[B];
  
  //reset front and back of deque
  F = 0;
  B = N;
  
  //get rid of old deque
  delete [] odeque;

  // update capacity
  N = 2*N;
  
  return;
}


template <typename U>
std::ostream& operator<<(std::ostream& os, const Deque<U>& d)
{
  for(size_t i = (d.F+1)%(d.N+1); i != d.B; i = (i+1)%(d.N+1))
    os << d.deque[i] << " ";

  return os;
}
