#include <LimpExtra/peri_stdout.h>



void LPStdout_emuStamp(void *obj){
	LPStdout *peri = obj;
	
	switch(peri->peri.state){
		case 0:{
			if(LPeri_interrupt(&peri->peri)){
				peri->peri.state = 1; // Exits the initial state
			}
		}
		break;
		
		case 0x22:{
			if(peri->peri.acu[0]){
				if(peri->peri.acu[2]){
					fputc(peri->peri.acu[1], peri->file);
					peri->peri.acu[2] = 0;
				}
			}
			else{
				fflush(peri->file); // Flushes the output stream
				peri->peri.state = 1; // Restores to initial state
			}
			LPeri_out(&peri->peri, 1); // Signalizes the character has been received
		}
		break;
		
		case 0x26:{
			// In a Stamp, the device can send 16 characters at time
			for(Int i=0; i<16 && peri->peri.acu[1]; i++){
				Uint32 chr = peri->peri.bus->read8(peri->peri.bus, peri->peri.acu[0]);
				fputc(chr, peri->file);
				peri->peri.acu[0]++;
				peri->peri.acu[1]--;
			}
			
			// Verify stream has ended
			if(!peri->peri.acu[1]){
				fflush(peri->file);
				LPeri_out(&peri->peri, 1); // Signalizes the stream has been sended
				peri->peri.state = 1; // Restores to initial state
			}
		}
		break;
	}
}


void LPStdout_send(LPeri *peri, Uint32 data){
	switch(peri->state){
		case 1:{ // The Lobby state
			switch(data){
				case 0x10:{ // Info
					LPeri_out(peri, 1);
				}
				break;
				case 0x11:{ // Brand
					LPeri_out(peri, 0);
				}
				break;
				case 0x12:{ // Branch
					LPeri_out(peri, 0);
				}
				break;
				case 0x13:{ // Version
					LPeri_out(peri, 0);
				}
				break;
				
				case 0x21:{ // Sends a stream of u8 chars
					/*
						[0] := Size of Character stream to send
						[1] := Character sended
						[2] := Flag for any character send
					*/
					peri->state = 0x21;
				}
				break;
				case 0x24:{ // Sends a pointer to memory and size of writing
					/*
						[0] := Pointer of stream
						[1] := Size of stream
					*/
					peri->state = 0x24;
				}
				break;
			}
		}
		break;
		
		case 0x21:{ // Retrieves the size of stream
			// Setup the stream size and signal for receiving
			peri->acu[0] = data;
			peri->acu[2] = 0;
			peri->state = 0x22;
		}
		break;
		case 0x22:{ // Sending each character of stream
			if(peri->acu[0]&&!peri->acu[2]){
				// Saves character, signalizes for character receive and consumes the stream size
				peri->acu[1] = data;
				peri->acu[2] = 1;
				peri->acu[0]--;
			}
		}
		break;
		
		case 0x24:{ // Receiving the pointer to stream
			peri->acu[0] = data;
			peri->state = 0x25;
		}
		break;
		case 0x25:{ // Receiving the size of stream
			peri->acu[1] = data;
			peri->state = 0x26;
		}
		break;
	}
}


void LPStdout_init(LPStdout *peri, LBus *bus, FILE *file){
	memset(peri, 0, sizeof(LPStdout));
	LPeri_init(&peri->peri, bus);
	peri->peri.api_data = peri;
	peri->file = file;
	
	/* Setup Methods */
	peri->peri.emu.emuStamp = LPStdout_emuStamp;
	peri->peri.send = LPStdout_send;
}

