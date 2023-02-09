#include "curses.hpp"

// Output ----------------------------------------------------- ||
#ifdef ARDUINO_NANO_BUILD
	void clear(){
		Serial.print(STRL("\033[2J"));
	}
	
	void refresh(){
		// Does nothing, since output isn't buffered on Arduino Nano
	}
	
	void move(int y,int x){
		Serial.print(STRL("\033["));
		Serial.print(y + 1);
		Serial.write(';');
		Serial.print(x + 1);
		Serial.write('H');
	}
	
	void addch(char c){
		Serial.write(c);
	}
	
	void printw(const __FlashStringHelper* str){
		Serial.print(str);
	}
	
#endif

// Input ------------------------------------------------------ ||
int current_delay = -1;

#ifdef ARDUINO_NANO_BUILD
	int getch(){
		// Replicate ncurses' timeout() functionality with Arduino libraries
		
		if(current_delay > 0){
			// > 0: Wait for current_delay milliseconds
			//      Note that, unlike ncurses, this delay is guaranteed in its entirety (it cannot be cut
			//      short by the user pressing keys before the delay is over.)
			delay(current_delay);
			
			// Clear the serial buffer, only saving the last input
			// Note that Serial.available() is only called once and captured in a variable - this is to
			// handle (perhaps unlikely) edge cases where while(Serial.available() > 0) never exits
			int available_chars = Serial.available();
			int return_char = -1;
			
			for(int i = 0;i < available_chars;++i){
				return_char = Serial.read();
			}
			
			// Done!
			return return_char;
			
		}else if(current_delay < 0){
			// < 0: Blocking read
			while(Serial.available() < 1){
				// Block until input is available
			}
			
			return Serial.read();
		}else{
			// = 0: Return immediately
			return Serial.read();
		}
	}
#endif

void set_timeout(int delay){
	if(current_delay == delay){
		return;
	}
	
	#ifdef ARDUINO_NANO_BUILD
		// Nothing
	#else
		timeout(delay);
	#endif
	
	current_delay = delay;
}