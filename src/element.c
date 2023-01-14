#include "element.h"

const struct chain_type ELEMENT_TYPE = {
	// Update
	.contains = &element_contains,
	
	.on_or_remove = &element_remove,
	
	.on_set = &element_set,
	
	.on_clear = &element_clear,
	
	// Draw
	.paranthesize = false,
	.bracket = false,
	
	.wrap_size = 20,
	
	.size = &element_size,
	
	.draw_vertical_get = &element_get
};

// ------------------------------------------------------------ ||

uint element_size(const void *e){
	return *((const element *)e) != SYMBOL_COUNT;
}

bool element_contains(const void *e,symb val){
	if(val >= SYMBOL_COUNT){
		return 0;
	}
	
	return *((const element *)e) == val;
}

void element_set(void *e,symb val){
	if(val >= SYMBOL_COUNT){
		return;
	}
	
	*((element *)e) = val;
}

void element_remove(void *e,symb val){
	if(val >= SYMBOL_COUNT){
		return;
	}
	
	if(*((element *)e) == val){
		element_clear(e);
	}
}

void element_clear(void *e){
	*((element *)e) = SYMBOL_COUNT;
}

symb element_get(const void *e,uint i){
	if(i > element_size(e)){
		return SYMBOL_COUNT;
	}
	
	return *((const element *)e);
}