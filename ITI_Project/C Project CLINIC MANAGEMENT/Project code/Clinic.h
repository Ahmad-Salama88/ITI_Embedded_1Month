
#ifndef _CLINIC_H
#define _CLINIC_H

#include "STD_TYPES.h"

#define TOTAL_SLOTS_NUM		5
#define PASSWORD 			1234

#define NAME_SIZE 		60
#define GENDER_SIZE 	10

typedef struct {
	u8 name[50];
	u8 age;	
	u8 gender[7];
	u32 ID;  // from 1 to 5
}patient;

typedef struct {
    u8 slotOf_id; 
    u8 is_reserved;  
    u32 patient_id;   
} ReservationSlot;





						/* ADMIN WINDOW */

u8 check_password(void);													
u8 check_ID (u32 ID_input, patient* patient_list);	

u8 check_slot_available(u8 slot_chosen, u8* slots_list );

	// patient_list is array (address to the first element in array of struct)
void reserve_patient (patient* patient_list,u8* PTRcurrent_index_OfPateintList); 			// optoin 1
void edit_patinet(patient* patient_list,u8* PTRcurrent_index_OfPateintList);    			// optoin 2

void print_switch_appoint(u8 slotNum);									//optoin 3 internally in disp_ 
u8 disp_slots_available (ReservationSlot* slots_list);					// option 3
void reserve_slot (ReservationSlot* slots_list, patient* patient_list);	// option 3

s8 check_ID_slot(u32 ID_slot, ReservationSlot* slots_list);				// option 4 intnerally in cancel_slot
void cancel_slot (ReservationSlot* slots_list, patient* patient_list);	// option 4




						/* USER MODE */ 
void view_patient_record(patient* patient_list, u8 total_patients); // OPTION 1
void view_todays_reservations(ReservationSlot* slots_list);			// OPTION 2









#endif