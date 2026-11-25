// Copyright (c) Symbian Ltd 2001

#ifndef __RMPOINTERARRAY_H__
#define __RMPOINTERARRAY_H__

/**@ingroup array */
/**@{ */

/** A subclass of RPointerArray for use with M class pointers which
	have a release method and are owned by the array. When the array is
	closed, the objects will be released.
	@see RCPointerArray
*/
template<class T> class RMPointerArray : public RPointerArray<T>
	{
 public:
	/** Constructor */
	inline RMPointerArray();
	/** Free all resources, calling Release() on the contents of the array */
	inline void Close();
	};

template <class T>
inline RMPointerArray<T>::RMPointerArray()
	{
	}

template <class T>
inline void RMPointerArray<T>::Close()
	{
	TInt count = Count();
	for (TInt ii = 0; ii < count; ii++)
		(*this)[ii]->Release();
	Reset();
	}
///@}
#endif
