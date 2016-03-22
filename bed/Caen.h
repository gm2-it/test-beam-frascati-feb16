

#ifndef G__CAEN_H
#define G__CAEN_H

struct caen_5742 {
	ULong64_t system_clock;
	ULong64_t device_clock[18];
	UShort_t trace[18][1024];
};
//
struct caen_5730 {
	ULong64_t event_index;
	ULong64_t system_clock;
	UShort_t trace[8][500];
};

#endif
  
