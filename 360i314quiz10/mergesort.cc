/** @file mergesort.cc
    @author Daniel Uber
    @brief Use mergesort on an array of ints
    and a vector of pointers to structs

    version 2 : correctly build a template function
    by using std::array, requires c++0x (g++ works)

    version 3 : move templated functions into class mergesort
    mergesort function is operator()
    this could be the constructor?
*/

#include <iostream>
#include <vector>
#include <array>
#include <string>
#include <cstddef>

template<typename container, typename accessor, typename comparator>
class mergesort {
  void merge(container &a, size_t start, size_t mid, size_t stop){
    accessor get;
    comparator comp;
    container t;
    size_t left = start;
    size_t right = mid + 1;
    size_t temp = 0;
    t = a; // just make a copy, we'll clobber it in the wrong spot
    while(left <= mid && right <= stop)
      // stable sort, right only if less than left
      if(comp(get(a[right]), get(a[left])))
	t[temp++] = a[right++];
      else
	t[temp++] = a[left++];
    while(left <= mid)
      t[temp++] = a[left++];
    while(right <= stop)
      t[temp++] = a[right++];
    while(temp != 0)
      a[--right] = t[--temp];
  return;
  }

  void ms(container &a, size_t start, size_t stop){
    if(start == stop) return;
    size_t mid = start + (stop - start)/2;
    ms(a, start, mid);
    ms(a, mid+1, stop);
    merge(a, start, mid, stop);
    return;
  }

public:
  void operator() (container &a, size_t size){
    ms(a,0,size-1);
  }
};

// accessor
struct identity{
  int operator() (int a){
    return a;
  }
};

// comparator
struct ltint{
  bool operator() (int a, int b){
    return (a < b);
  }
};


struct Student {
  std::string name;
  std::string id;
  float final;
  Student(std::string name, std::string id, float final){
    this->name = name;
    this->id = id;
    this->final = final;
  }
};

typedef std::vector<Student *> sv;

// accessor
struct id{
  std::string operator() (Student * t)
  {return t->id;}
};

// comparator
struct ltstr{
  /** string comparison for ordering */
  bool operator() (std::string s1, std::string s2){
    return (s1.compare(s2) < 0);
 }
};


int main(){

  const size_t SIZE = 9;
  std::array<int,SIZE> a ={ {13, 2, 1, 0, 3, 4, 5, 6, 1}};
  mergesort<std::array<int, SIZE>, identity, ltint> ms1;
  mergesort<sv, id, ltstr> ms2;
  // check array sort
  ms1(a,SIZE);
  for(int i = 0; i < 9; i++)
     std::cout<<a[i]<<" ";
  std::cout<<'\n';

  sv students;
  students.push_back(new Student("John", "105", 22.2));
  students.push_back(new Student("Jerry", "110", 22.3));
  students.push_back(new Student("Sally", "104", 26.3));

  // check vector sort
  ms2(students, 3);
  for(size_t i = 0; i < students.size(); i++)
    std::cout<<students[i]->name<<" "<<students[i]->id<<'\n';
  return 0;
}

