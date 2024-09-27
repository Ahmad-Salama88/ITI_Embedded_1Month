
#include <stdio.h>
#include "Clinic.h" 

extern u8 current_index_OfPateintList; 
extern u8* PTRcurrent_index_OfPateintList;


/*************************************************************************************************/
/***************************************** ADMIN MODE *************************************************/

u8 check_password(void)
{
	u16 input_pass; 
	u8 flag_check = 0;
	
	for(u8 time = 1; time <= 3; time++)
	{
		//printf("%i\n\n",time);
		printf("Enter the passwod :");
		scanf("%i",&input_pass);
	
		if(PASSWORD == input_pass){
			flag_check = 1; 
			break;
		}
		else if (time != 3){
			printf("Wrong, Enter it again. \n");
		}
		else{}
		//printf("%i\n\n",time);
	}
	
	return flag_check;	//if 0 >> return 0? (in main) to exit the prog. 
	
}

u8 check_ID (u32 ID_input, patient* patient_list)
{
	s8 check_flag = -1; // default : not repaeted 
	for(u8 patientN = 0; patientN < *PTRcurrent_index_OfPateintList ; patientN ++)
	{
		if(ID_input == patient_list[patientN].ID){
			check_flag = patientN; 
			break; 
		}
	}
	//printf("%i",check_flag);
	return check_flag; 
}

						/*
						 option 1 
								*/

void reserve_patient (patient* patient_list,u8* PTRcurrent_index_OfPateintList)
{
	s8 check_flag;
	
	printf("Enter the ID of the patient: ");
	scanf("%i",&(patient_list[*PTRcurrent_index_OfPateintList].ID));
	
	check_flag = check_ID( (patient_list[*PTRcurrent_index_OfPateintList].ID), patient_list);
	if(check_flag != -1)
	{
		//printf("%i",check_flag);
		printf("This ID already exists\n");
		patient_list[*PTRcurrent_index_OfPateintList].ID = 00000; // 0 again 
		// EXIT THE PROGRAMME 
	}
	
	else if (check_flag == -1){
		
		printf("Okay\n______\n");
		printf("Now enter the name of the patient: ");
		getchar();		// clean the buffer before fgets
		fgets(patient_list[*PTRcurrent_index_OfPateintList].name, NAME_SIZE, stdin);
		printf("Enter the age of the patient: ");
		scanf("%i",(patient_list[*PTRcurrent_index_OfPateintList].age));
		getchar();
		printf("Enter the gender of the patient: ");
		fgets(patient_list[*PTRcurrent_index_OfPateintList].name, GENDER_SIZE, stdin);
		
		(*PTRcurrent_index_OfPateintList)++;
		
		printf("Added successfully\n");
	}
	// EXIT THE PROGRAMME 
}


						/*
						 option 2 
								*/
void edit_patinet(patient* patient_list,u8* PTRcurrent_index_OfPateintList)
{
	u8 check_flag;
	u8 index_edit; 
	u32 ID_input;
	
	printf("Enter the ID of the patient: ");
	scanf("%i", &ID_input);
	
	check_flag = check_ID (ID_input, patient_list);
	if(check_flag == -1){
		printf("No patients with this ID.");
		//EXIT THE PROGRAMME
	}
	else {
		index_edit = check_flag; 
		
		printf("Okay\n______\n");
		printf("Now enter the new name of the patient: ");
		getchar();		// clean the buffer before fgets
		fgets(patient_list[*PTRcurrent_index_OfPateintList].name, NAME_SIZE, stdin);
		printf("Enter the new age of the patient: ");
		scanf("%i",(patient_list[*PTRcurrent_index_OfPateintList].age));
		getchar();
		printf("Enter the new gender of the patient: ");
		fgets(patient_list[*PTRcurrent_index_OfPateintList].name, GENDER_SIZE, stdin);
		
		printf("the patient is now edited\n");
		//EXIT THE PROGRAMME
	}
}

						/*
						 option 3 
								*/
								
void print_switch_appoint(u8 slotNum)
{
		switch (slotNum){
			case 0 : printf("1 -> 2:00 to 2:30 pm\n"); break; 
			case 1 : printf("2 -> 2:30 to 3:00 pm\n"); break; 
			case 2 : printf("3 -> 3:00 to 3:30 pm\n"); break;
			case 3 : printf("4 -> 4:00 to 4:30 pm\n"); break; 
			case 4 : printf("5 -> 4:30 to 5:00 pm\n"); break; 
		}
}

// the return "available" here >> to use before reserve_patinet (if avilable > go inside it)
u8 disp_slots_available (ReservationSlot* slots_list)
{
	u8 available = 0; // no available slots
	
	printf("Available slots : \n__________\n");
	for(u8 slotNum = 0; slotNum < TOTAL_SLOTS_NUM; slotNum++){
		if( 0 == slots_list[slotNum].is_reserved ){
			print_switch_appoint(slotNum);
			available = 1;	// change at lest one time 
		}
		else{}
	}
	if( 0 == available)
	{
		printf("No avilable slots.\n"); 
	}
	return available;	// to use in main before conserve any new patient 
}



//scan the ID in main and pass it 
//scan the chosen slot, first
void book_slot(u32 ID_input, ReservationSlot* slots_list, u8 slot_chosen)
{
	for(u8 slot = 0; slot<5; slot++){
		if(slots_list[slot].patient_id == ID_input){
			slots_list[slot].slotOf_id= slot_chosen; 
			break;
		}
	}
}

// scan the index_chosen in the main & check it using check_slot 
void reserve_slot (ReservationSlot* slots_list, patient* patient_list)
{
	u16 index_chosen;
	u32 ID_input;
	s8 check_flag;
	
	printf("Enter the ID of the patient: ");
	scanf("%i", &ID_input);
	
	check_flag = check_ID (ID_input, patient_list);
	
	if(check_flag == -1){
		printf("No patients with this ID.");
	}
	
	else 
	{
		printf("Enter the slot to reserve : ");
		scanf("%i",&index_chosen);
		
		while(index_chosen < 1 || index_chosen > 5){
			printf("Error! Enter valid slot\n"); 
		}
		
		if (slots_list[index_chosen-1].is_reserved == 0)
			{
				slots_list[index_chosen-1].is_reserved = 1;
				printf("The slot reserved successfully. \n");		
			}
		else if(slots_list[index_chosen-1].is_reserved == 1)
			{
				printf("The slot is already reserved. \n");
			}	
	
	//EXIT THE PROGRAMME
	}
	
	
}

						/*
						 option 4
								*/
								
s8 check_ID_slot(u32 ID_slot, ReservationSlot* slots_list)
{
	s8 check_flag = -1; // default : not repaeted 
	for(u8 patient_slotN = 0; patient_slotN < 5 ; patient_slotN ++)
	{
		if(ID_slot == slots_list[patient_slotN].patient_id){
			check_flag = patient_slotN; 
			break; 
		}
	}
	//printf("%i",check_flag);
	return check_flag; 
	
}
void cancel_slot (ReservationSlot* slots_list, patient* patient_list)
{
	u16 index_chosen;
	u32 ID_input;
	s8 check_flag;
	s8 index_cancel; 
	
	printf("Enter the ID of the patient: ");
	scanf("%i", &ID_input);
	
	check_flag = check_ID_slot (ID_input, slots_list);
	//printf("%i", check_flag);	//
	if(check_flag == -1){
		printf("No patients with this ID.");
	}
	
	else 
	{
		index_cancel = check_flag; 
		if (slots_list[index_cancel].is_reserved == 1)
			{
				slots_list[index_cancel].is_reserved = 0;
				slots_list[index_cancel].patient_id = -1;
				printf("The slot cancelled successfully. \n");		
			}
		else if(slots_list[index_cancel].is_reserved == 0)
			{
				printf("The slot is already available. \n");
			}	
	
	//EXIT THE PROGRAMME
	}
	
	
}

/*************************************************************************************************/
/***************************************** USER MODE *************************************************/
			

						/*
						 option 1
								*/
								
void view_patient_record(patient* patient_list, u8 total_patients) {
    u32 ID_input;
    u8 found = 0;

    printf("Enter the ID of the patient: ");
    scanf("%i", &ID_input);

    for(u8 i = 0; i < total_patients; i++) {
        if(patient_list[i].ID == ID_input) {
            printf("Patient ID: %i\n", patient_list[i].ID);
            printf("Name: %s\n", patient_list[i].name);
            printf("Age: %i\n", patient_list[i].age);
            printf("Gender: %s\n", patient_list[i].gender);
            found = 1;
            break;
        }
    }

    if(!found) {
        printf("No patient found with this ID.\n");
    }
}

						/*
						 option 2
								*/

void view_todays_reservations(ReservationSlot* slots_list) {
    printf("Today's Reservations:\n");

    for(u8 i = 0; i < TOTAL_SLOTS_NUM; i++) {
        if(slots_list[i].is_reserved) {
            printf("Slot %i: Patient ID %i\n", slots_list[i].slotOf_id, slots_list[i].patient_id);
        } else {
            printf("Slot %i: Available\n", slots_list[i].slotOf_id);
        }
    }
}

