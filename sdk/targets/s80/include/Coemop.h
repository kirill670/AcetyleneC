// COEMOP.H
//

#if !defined(__COEMOP_H__)
#define __COEMOP_H__

#include <e32std.h>

/** 
 * declares an object type, <code>ETypeId</code>, for a class, in order to 
 * allow the object provider mechanism to locate and provide objects from the 
 * class. See also <code>MObjectProvider</code>
 *
 * @lib [what]
 * @publishedAll
 * @released
 */
#define DECLARE_TYPE_ID(id) enum { ETypeId = id };

//
// Used to wrap object type IDs in a standardised manner. Object type IDs must be asserted 
// in an ETypeId member data property by any types of object which 
// are capable of being retrieved by the MObjectProvider interface
//
/** 
 * The <code>TTypeUid</code> class specifies part of the object provider 
 * mechanism. The class encapsulates the UID that identifies the type of 
 * object that an object provider is to get. The class is also used to 
 * encapsulate a pointer to the object that the object provider has found. An 
 * object that is intended to be capable of being retrieved by the object 
 * provider mechanism must include the enum <code>{ETypeId = 0xabcdefgh};</code>
 * in its class definition, where <code>0xabcdefgh</code> is the UID value. 
 * The macro <code>DECLARE_TYPE_ID</code> can be used to do this. An instance 
 * of this class is passed to the <code>MObjectProvider::MopSupplyObject()</code>
 * method implemented by an object provider. A <code>TTypeUid::Ptr</code> is 
 * also returned by this method. See <code>MObjectProvider</code>.
 *
 * @lib [what]
 * @publishedAll
 * @released
 */
class TTypeUid : public TUid

    {
public:
   /** 
    * The <code>Ptr</code> class encapsulates a pointer to an object fetched 
    * by an object provider. The class has no public constructor. 
    * <code>TTypeUid::MakePtr()</code> or <code>TTypeUid::Null()</code> must 
    * be used to construct instances of this class. 
    *
    * @lib [what]
    */
    class Ptr

        {
        friend class TTypeUid;
    private:
        explicit inline Ptr(TAny* aPtr)
            : iPtr(aPtr)
            {}
    public:
       /** 
        * Retrieves the pointer to an object, which is encapsulated by the 
        * <code>Ptr</code>. 
        *
        * @return a pointer to an object
        * @remarks
        * @see
        */
        inline TAny* Pointer() const
            {return iPtr;}
    private:
        TAny* iPtr;
        };
public:
   /** 
    * The object constructor that takes a UID value.
    *
    * @param aUid The UID value that defines the type of object that an object 
    *             provider is to get
    * @remarks
    * @see
    */
    inline TTypeUid(TInt aUid)
        { iUid = aUid; }

   /** 
    * Constructs a <code>Ptr</code> class, which encapsulates a <code>NULL</code>
    * pointer.
    *
    * @return the constructed <code>Ptr</code> object
    * @remarks
    * @see
    */
    inline static Ptr Null()

        { return Ptr(NULL); }

   /** 
    * Constructs a <code>Ptr</code>, which encapsulates the specified object 
    * pointer.
    *
    * @param aT A pointer to the object, which is to be encapsulated
    * @return the constructed <code>Ptr</code> object 
    * @remarks
    * @see
    */
    template <class T> inline Ptr MakePtr(T* aT) const
        { __ASSERT_DEBUG(iUid == T::ETypeId,User::Invariant()); return Ptr(aT); }
    };


/** 
 * The <code>MObjectProvider</code> class specifies an interface that allows 
 * an object to be part of a network of object providers. The object provider 
 * mechanism can be used to find and access objects of a given type, where the 
 * type is defined by a <code>TTypeUid</code> object. Object providers may be 
 * arranged in a hierarchy, that is, an object provider may have a parent-child 
 * relationship with other another object provider. An object provider must 
 * provide an implementation for the <code>MopSupplyObject()</code> method 
 * and can choose to provide an implementation for the <code>MopNext()</code> 
 * method. Typically, it will also have functionality to define who its parent 
 * is. <code>CCoeControl</code> is an example of a class that implements this 
 * interface. Top level controls must have the view or AppUI set as their 
 * object provider. This is done by calling <code>CCoeControl::SetMopParent()</code>
 * on the view or the AppUI. The view or AppUI does this by calling the top 
 * level control's <code>CCoeControl::SetMopParent()</code> method.
 *
 * @lib [what]
 * @publishedAll 
 * @released 
 */
class MObjectProvider

    {
public:
    template<class T>
    T* MopGetObject(T*& aPtr) 
    /** Gets an object of the type defined by the template parameter.
    
    The object may be supplied directly by this object provider, or by other object 
    providers higher up the hierarchy.
    
    @param aPtr A reference to a pointer to an object of a type that is to be 
    retrieved.
    @return A pointer to an object of the type required, or NULL if none can be 
    found. */
        { return (aPtr=static_cast<T*>(MopGetById(T::ETypeId))); }

private: // must be overridden
    /** Gets an object whose type is encapsulated by the specified TTypeUid object.

    @param aId Encapsulates the Uid that identifies the type of object required.
    @return Encapsulates the pointer to the object provided. 
    Note that the encapsulated pointer may be NULL.

    @publishedAll 
    @released */
    virtual TTypeUid::Ptr MopSupplyObject(TTypeUid aId) = 0;

private: // may be overridden to continue chain of responsibility
    /**
    @publishedAll 
    @released */
    IMPORT_C virtual MObjectProvider* MopNext();

private: 
    IMPORT_C TAny* MopGetById(TTypeUid aId);
    };

#endif
