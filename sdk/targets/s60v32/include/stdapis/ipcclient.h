/*
* ==============================================================================
*  Name        : ipcclient.h
*  Part of     : ipc server
*  Description : ipc server - client interface DLL
*
Copyright (c) Symbian Software Ltd 2007. All rights reserved.

Redistribution and use in source and binary forms, with or without 
modification, are permitted provided that the following conditions are met:
 * Redistributions of source code must retain the above copyright notice, this 
   list of conditions and the following disclaimer. 
 * Redistributions in binary form must reproduce the above copyright notice, 
   this list of conditions and the following disclaimer in the documentation 
   and/or other materials provided with the distribution. 
 * Neither the name of the <ORGANIZATION> nor the names of its contributors 
   may be used to endorse or promote products derived from this software 
   without specific prior written permission. 
   
THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE 
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL 
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR 
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER 
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
* ==============================================================================
*/

#ifndef __RIPC_SESSION__
#define __RIPC_SESSION__

#include<e32std.h> //RSessionBase
#include<e32def.h> //Varargs
#include<sys/types.h>
#include<sys/sem.h>

struct msqid_ds;
struct shmid_ds;

class TChunk
	{
public:
TChunk(): iRef(0){}
TChunk(TInt aShmID): iShmID(aShmID), iRef(0){}
TInt iShmID;
RChunk iChunk;
TInt iRef;
	};


//-----------------------------------------------------------------------
//Class name: RIpcSession
//Description: It represents the session to Ipc Server. 
//-----------------------------------------------------------------------

class RIpcSession : public RSessionBase
	{
	public:
		RIpcSession():iIsConnected(EFalse)
			{iLock.CreateLocal();}
				
		//msgqueue functions
		int msgctl(int msqid, int cmd, struct msqid_ds *buf, int &aerrno);
		int msgget(key_t key, int msgflg, int& aerrno);
		ssize_t msgrcv(int msqid, void *msgp, size_t msgsz, long msgtyp, int msgflg, int& aerrno);
		int msgsnd(int msqid, const void *msgp, size_t msgsz, int msgflg, int& aerrno);
		
		//msgqueue functions
		int shmctl(int shmid, int cmd, struct shmid_ds *buf, int &aerrno);
		int shmget(key_t key, size_t size, int shmflg, int& aerrno);
		void *shmat(int shmid, const void *shmaddr, int shmflg, int& aerrno);
		int shmdt(const void *shmaddr, int& aerrno);
	
		//semqueue functions
		int semget(key_t key, int nsems, int semflags, int& aerrno);
		int semctl(int semid, int semnum, int cmd, union semun *arg, int& aerrno);
		int semop(int semid, struct sembuf *sops, size_t nsops, int& aerrno);
		
		RFastLock iLock;
	private:
		TInt AddToList(const TInt& aKey, const TInt& aErr, const TThreadId& aThreadId, TAny*& aRetPtr);
		TInt OnDemandConnection();
		void Lock()
			{
			iLock.Wait();
			}
		void UnLock()
			{
			iLock.Signal();
			}
	private:

	TInt Connect();
	TInt iIsConnected;
	//todo put a lock around this list
	RArray<TChunk> iChunkList;
	};	
	
//__RIPC_SESSION__
#endif


