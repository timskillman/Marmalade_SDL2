#pragma once

//TODO TODO TODO!
//Should be equiv. to IwDebug.h

//#define IwTraceChannelOn(chan) (IwTraceChannelOn2(IW_TRACE_CHANNEL_##chan, #chan))
#define NULLSTR NULL

#define IwTrace2(chandef, chantxt, arg) \
        do { \
		} while (0) //should be this ...

            //if (IwTraceChannelOn2(chandef, chantxt)) \
            //{ \
            //    IwDebugTraceSetTraceChannel(chantxt); \
            //    IwDebugTraceLinePrintf arg; \
            //} \
        //} while (0)

#define IwTrace(chan, arg) IwTrace2(IW_TRACE_CHANNEL_##chan, #chan, arg)


#define IwAssertMsg(chan, expr, args) \
        do { \
        } while (0) //should be this ...
        //{ \
        //    IwAssertFullN(0, chan, expr, args, (NULLSTR)); \
        //} while (0)

#define IwAssert(chan, expr)    IwAssertMsg(chan, expr, (NULLSTR))
