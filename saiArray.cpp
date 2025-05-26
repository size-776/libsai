#include "afx.h"
#include "saiArray.h"

//#include "last_header.h"

#define ARRAYCLASS CsaiIntArray
#define ARRAYITEM int
#include "saiArray.cc"
#undef ARRAYCLASS
#undef ARRAYITEM

//#define ARRAYCLASS CsaiStrArray
//#define ARRAYITEM CString
//#include "saiArray.cc"
//#undef ARRAYCLASS
//#undef ARRAYITEM

#define ARRAYCLASS CsaiDoubleArray
#define ARRAYITEM double
#include "saiArray.cc"
#undef ARRAYCLASS
#undef ARRAYITEM

#define ARRAYCLASS CsaiBoolArray
#define ARRAYITEM bool
#include "saiArray.cc"
#undef ARRAYCLASS
#undef ARRAYITEM

#define ARRAYCLASS CsaiVoidPtrArray
#define ARRAYITEM void*
#include "saiArray.cc"
#undef ARRAYCLASS
#undef ARRAYITEM

//#define ARRAYCLASS CsaiStringList
//#define ARRAYITEM CString
//#include "saiArray.cc"
//#undef ARRAYCLASS
//#undef ARRAYITEM
