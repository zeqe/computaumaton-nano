#ifndef QUEUE_READ_INCLUDED
	#include "unsigned.h"
	#include "symbol.h"
	
	enum queue_read_mode{
		QUEUE_READ_IDEMPOTENT,
		QUEUE_READ_ADD,
		QUEUE_READ_REMOVE
	};
	
	// ------------------------------------------------------------ ||
	
	#define TRIGGER_DISABLED 0
	#define PREFIX_DISABLED '\0'
	
	struct queue_read_io_config{
		// _update() config -------------------||
		bool triggers_chain; // determines whether '\t' re-opens a new read after closing the
		                     // current one
		
		int trigger_add;     // input that triggers an addition read
		int trigger_remove;  // input that triggers a removal read
		
		// TRIGGER_DISABLED for either trigger will disable the respective functionality
		
		// _draw() config ---------------------||
		char prefix_add;     // character displayed in front of queue contents when adding
		char prefix_remove;  // character displayed in front of queue contents when removing
		
		// PREFIX_DISABLED for either prefix will cause only queue contents to be drawn in the
		// respective mode, no prefix
		
		bool bracket;        // enclose queue contents with {}
		bool paranthesize;   // enclose queue contents with () - if bracket is true, with {()}
	};
	
	#define QUEUE_READ_IO_CONFIG_INIT(TC,TA,TR,PA,PR,B,P) {(TC),(TA),(TR),(PA),(PR),(B),(P)}
	
	// ------------------------------------------------------------ ||
	
	struct set;
	
	struct queue_read{
		// Configuration
		struct set *superset;
		struct queue_read *subqueue;
		
		const struct queue_read_io_config * const io_conf;
		
		// Execution state
		enum queue_read_mode mode;
		symb value;
	};
	
	#define QUEUE_READ_INIT(SUPERSET,SUBQUEUE,IO_CONF) {(SUPERSET),(SUBQUEUE),(IO_CONF),QUEUE_READ_IDEMPOTENT,SYMBOL_COUNT}
	
	struct set *queue_read_superset(struct queue_read *read);
	
	void queue_read_init(struct queue_read *read,enum queue_read_mode mode);
	void queue_read_enq (struct queue_read *read,symb val);
	void queue_read_deq (struct queue_read *read);
	
	bool                 queue_read_complete(struct queue_read *read);
	enum queue_read_mode queue_read_mode    (struct queue_read *read);
	symb                 queue_read_value   (struct queue_read *read);
	
	// ------------------------------------------------------------ ||
	// read->io_conf cannot be NULL for these methods
	
	void queue_read_update(struct queue_read *read,int in,bool is_switching,void (*on_submit)(enum queue_read_mode));
	void queue_read_draw(struct queue_read *read);
	
	#define QUEUE_READ_INCLUDED
#endif