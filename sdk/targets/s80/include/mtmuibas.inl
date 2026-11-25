// MTMUIBAS.INL
//
// Copyright (C) Symbian Ltd 1998
//

///////////////////////////////////
// CBaseMtmUi - MTMUi base API   //
///////////////////////////////////

inline TUid CBaseMtmUi::Type() const
/** Gets the Type UID of the message type associated with the User Interface MTM.

@return UID of the message type associated with the MTM */
	{ return iBaseMtm.Type(); }

inline CBaseMtm& CBaseMtmUi::BaseMtm() const
/** Gets a reference to the Client-side MTM that requested this object.

@return Client-side MTM that requested this object */
	{ return iBaseMtm; }

