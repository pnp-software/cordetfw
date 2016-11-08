/* 
 * A. Pasetti - P&P Software GmbH - Copyright 2010 - All Rights Reserved
 * 
 * OutStream Model
 *
 * The following aspects of the operation of an OutStream are modelled:
 * 1. Two OutManagers on different threads asking for commands to
 *    be sent out.
 * 2. A blocking middleware (MW) that can be either available or unavailable.
 * 3. The MW may change from NOT_AVAIL to AVAIL or viceversa at any time.
 * 4. The state of the MW is monitored by a dedicated process which 
 *    calls ConnectionAvailable on the OutStream when it finds that
 *    the MW connection is available (polling mechanism).
 * 5. The management of the sequence counter is not modelled.
 * 6. Operations on OutStream are called in mutual exclusion.
 * 7. No specific size of the Packet Queue (PQ) is modelled; the PQ can be
 *    empty, not full, or full.
 */

mtype = {AVAIL, NOT_AVAIL, BUFFERING, READY, SUCCESS, FAILURE};
mtype = {EMPTY, NOT_FULL, FULL};  /* State of Packet Queue in OutStream */
mtype = {CONNECTION_AVAILABLE, SEND}; /* Commands to OutStream */
mtype = {FREE, CMD_MNG, CNCT_MON};  /* Owner of the lock on the OutStream */
mtype mwState = NOT_AVAIL;  
mtype outStreamState = READY;
mtype outStreamPQ = EMPTY;
mtype outStreamLock = FREE;
bool sendReqSuccessful = false;

/* A call to this macro corresponds to sending a command to the OutStream
 * State Machine. 
 */
inline outStream(cmd) {
   if
   :: (outStreamState==BUFFERING) && (cmd==CONNECTION_AVAILABLE) ->
       do   
       :: (outStreamPQ!=EMPTY) ->
          atomic { 
            if
            :: mwState==AVAIL -> sendReqSuccessful = true;
            :: else -> sendReqSuccessful = false;
            fi; }
            if
            :: sendReqSuccessful -> outStreamPQ = EMPTY;
            :: sendReqSuccessful -> outStreamPQ = NOT_FULL;
            :: !sendReqSuccessful -> break;
            fi;
       :: (outStreamPQ==EMPTY) -> break;
       od;
       if
       :: (outStreamPQ==EMPTY) -> outStreamState = READY;
       :: (outStreamPQ!=EMPTY) -> outStreamState = BUFFERING;
       fi;
   :: (outStreamState==BUFFERING) && (cmd==SEND) ->
      if
      :: (outStreamPQ==FULL) -> skip;      /* Report Error */
      :: (outStreamPQ!=FULL) -> outStreamPQ = NOT_FULL;
      :: (outStreamPQ!=FULL) -> outStreamPQ = FULL;
      fi;
   :: (outStreamState==READY) && (cmd==SEND) ->
      assert(outStreamPQ==EMPTY);  /* Property P5 */
      atomic { 
         if
         :: mwState==AVAIL -> sendReqSuccessful = true;
         :: else -> sendReqSuccessful = false;
         fi; }
      if
      :: sendReqSuccessful -> skip;
      :: else -> outStreamPQ = NOT_FULL;
                 outStreamState = BUFFERING;
      fi;    
   :: else -> skip;
   fi;
} 

/* Processes representing the OutManagers which request that commands
 * be sent out. A send request is modelled as a call to operation Send
 * on the OutStream.
 * Each OutManager runs for some time and then terminates. This models
 * the fact that the OutManager stops sending out commands.
 */
active [2] proctype OutManager() {
  do
  :: atomic{ (outStreamLock==FREE) -> outStreamLock = CMD_MNG }; 
     outStream(SEND); 
     outStreamLock = FREE;
  :: true -> break;
  od;
}

/* Process representing the MW connection. 
 * The connection toggles between AVAIL and NOT_AVAIL.  
 */
active proctype mwConnection() {
  do
  :: mwState==AVAIL -> mwState=NOT_AVAIL;  
  :: mwState==NOT_AVAIL -> mwState=AVAIL;  
  od;
}

/* Process representing the thread which monitors the MW availability and 
 * which, when it finds the connection available, calls operation 
 * ConnectionAvailable on the OutStream.
 */
active proctype mwCnctMonitor() {
  do
  :: mwState==AVAIL -> 
     atomic{ (outStreamLock==FREE) -> outStreamLock = CNCT_MON }; 
     outStream(CONNECTION_AVAILABLE);
     outStreamLock = FREE;
  od;
}

/* Define variables used to formulate never claims */
#define r	(mwState==AVAIL)
#define q	(outStreamLock!=CMD_MNG)
#define s	(outStreamPQ==EMPTY)

/* The following formulas are used as (positive forms of) never claims */
	
/* P3: There is no backlog of unsent packets in the OutCmdStream. 
 * This property is satisfied if, when the OutCmdManagers permanently 
 * stop making requests for fresh packets to be sent and the connection 
 * remains available, then the packet queue eventually becomes emtpy. */
ltl P3 {((<> [] q)  && (<> [] r)) -> ( (<> [] s) )}

