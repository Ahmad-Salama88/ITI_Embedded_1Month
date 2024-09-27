
#include <stdio.h>
#include <stdlib.h>
//#include <util/delay.h>

void clear_screen() {
	system("cls");
}

#include "Clinic.h"

// 30 = 5*6 todays_slota * workDays 
patient patient_list [30] = {
	{"Ahmad Salama", 30, "MALE", 326161 },
	{"Hisham Salama", 29, "MALE", 815815 },
};
ReservationSlot slots_list[5] = {
	{1,0,-1},
	{2,1,326161},
	{3,1,815815},
	{4,0,-1},
	{5,0,-1},
};					 

u8 current_index_OfPateintList = 2; // initial value (2 reserved slots >> 0,1, (2))
u8 *PTRcurrent_index_OfPateintList = &current_index_OfPateintList;

int main()
{	
	u8 mode_input;
	u8 flag_pass;
	u16 option_Admin, option_User; 
		
	while(1)
	{
		printf("\n\nEnter 1 to open ADMIN mode, 2 for USER mode:");
		scanf("%i",&mode_input);
		
									/** ADMIN MODE **/ 
		if(1 == mode_input )
		{
			
			flag_pass = check_password();
			if(flag_pass == 0){
				printf("No more trials!\n");
				// EXIT THE PROGRAMME		return 0; for main? 
			}
			else if(flag_pass == 1){
				printf("(1) Add a new patient.\n(2) Edit a patient record.\n(3) Reserve a slot with the doctor.\n(4) Cancel a reservation.\n\n"); 
				printf("Choose an optoin: ");
				scanf("%i",&option_Admin);
				switch(option_Admin){
					case 1: {	
						reserve_patient (patient_list, PTRcurrent_index_OfPateintList);	
						break;
						}
					case 2: {
						edit_patinet(patient_list, PTRcurrent_index_OfPateintList);	
						break; 
						}
					case 3: {
						disp_slots_available(slots_list);
						reserve_slot (slots_list, patient_list);
						break; 
						}
					case 4: {
						cancel_slot (slots_list, patient_list);
						break; 
						} 
					default : {
						printf("invalid option\n");
						// EXIT PROGRAMME ? 
						}
					
				}
			}
		}
		
									/** USER MODE **/ 
		else if(mode_input == 2)
		{
			printf("User Options:\n(1) View patient record.\n(2) View available slots.\n\nChoose an option: ");
			scanf("%i", &option_User);
			switch(option_User){
					case 1: {
						view_patient_record(patient_list, current_index_OfPateintList);
						break;
						}
					case 2: {
						view_todays_reservations(slots_list);
						break; 
						}
					default : {
						printf("invalid option\n");
						// EXIT PROGRAMME ? 
						}
				}
		}
		
		//_delay_ms(2000);
		//clear_screen();
	}	
	
	
	

	return 0; 
}