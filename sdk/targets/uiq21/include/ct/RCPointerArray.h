// Copyright (c) Symbian Ltd 2001

#ifndef __RCPOINTERARRAY_H
#define __RCPOINTERARRAY_H

/**@ingroup array */
/**@{ */

/** A subclass of RArray for use with C class pointers that are owned
	by the array. Close() also deletes all the objects in the array
	(i.e. it's the same as ResetAndDestroy)
	@see RMPointerArray
 */
template<class T> class RCPointerArray : public RPointerArray<T>
	{
 public:
	/** Constructor */
	inline RCPointerArray();
	/** Closes the array and frees all resources (including deleting
		objects in the array */
	inline void Close();
	};

template <class T>
inline RCPointerArray<T>::RCPointerArray()
	{
	}

template <class T>
inline void RCPointerArray<T>::Close()
	{
	ResetAndDestroy();
	}
///@}
#endif
