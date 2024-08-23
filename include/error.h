/*
 *** Error definition
 */

#ifndef ERROR_H_
#define ERROR_H_

#define E_OK		(0)		// successful termination
#define E_SYS		(-5)	// system error
#define E_NOCOP		(-6)	// cannot use co-processor
#define E_NOSPT     (-9)    // not supported
#define E_RSFN      (-10)   // reserved function code
#define E_RSATR     (-11)   // attribute error
#define E_PAR       (-17)   // parameter error
#define E_ID        (-18)   // ID error
#define E_CTX       (-25)   // context error
#define E_MACV      (-26)   // memory access violation
#define E_OACV      (-27)   // object access violation
#define E_ILUSE     (-28)   // system call error
#define E_NOMEM     (-33)   // insufficient memory
#define E_LIMIT     (-34)   // upper limit error
#define E_OBJ       (-41)   // object state error
#define E_NOEXS     (-42)   // object error
#define E_QOVR      (-43)   // upper error
#define E_RLWAI     (-49)   // forced cancel from wait state
#define E_TMOUT     (-50)   // time out error
#define E_DLT       (-51)   // remove waiting object
#define E_DISWAI    (-52)   // cancel wait state by disable wait
#define E_IO        (-57)   // I/O error

#endif /* ERROR_H_ */
