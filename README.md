# MIDI_TO_TRIGGER_SYNC
Arduino-based MIDI to trigger and Sync24 Generator

Taken from my Roland CR-5000 MIDI to trigger and sync interface.
Rev 03. 04-14 Travis Thatcher - recompas@gmail.com

This version is used for interfacing with Rolands CR-5000 which uses 
negative going triggers. For regular V+ trigger circuits reverse all 
HIGH / LOW logic in the code.

Note pins A0 and A1 are also set to digital output mode in order to 
pass on DIN SYNC to another device
