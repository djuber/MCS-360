/** @file isort.h
    @author Daniel Uber

    @brief parameterized insertion sort on a container type.


    Note, a time optimization exists using Library Sort
    (Gapped insertion sort) but it is not a space optimization.
    Library sort is O(nlogn) while Insertion sort is O(n^2).

    Pseudocode from http://en.wikipedia.org/wiki/Insertion_sort

*/


#ifndef _ISORT_H_
#define _ISORT_H_
/** generalized insertion sort

    Use templates.
    @tparam containertype should support index operations. i.e.

    I expect a vector or with container[index] valid. This could be a deque.

    @tparam contenttype is what's stored in containertype

    @tparam accessortype should be operable to yield a value.

    @tparam valuetype should be yielded by accessortype on contenttype
    and comparable by comparisontype

    @tparam comparisontype should give a (partial) ordering on
    objects of valuetype.

    @param v is a container of elements

*/
template
< typename containertype,
  typename contenttype,
  typename accessortype,
  typename valuetype,
  typename comparisontype>
  void isort(containertype& v)
{
  accessortype ac;
  comparisontype comp;
  int j=0, i=0;
  int s = v.size();
  valuetype key;
  contenttype tmp;
  if(!v.empty())
    for(j=1; j!=s; ++j)
      {
	tmp= v[j];
	key = ac( v[j]);
	i = j - 1;
	while( (i>=0) && comp(key, ac(v[i])))
	  {
	    v[i+1] = v[i];
	    i = i -1;
	  }
	v[i+1] = tmp;
      }
  return;
}
#endif
