void reserve_patinet(u8 current_index_OfPateintList, patient* patient_list)
{
	u8 check_flag;
	
	printf("Enter the ID of the patient: ");
	scanf("%i",&(patient_list[current_index_OfPateintList].ID));
	
	check_flag = check_ID( (patient_list[current_index_OfPateintList].ID), patient_list);
	if(check_flag == 1){
		printf("This ID already exists");
	}
	else{
		printf("Ok, now enter the name of the patient: ");
		gets(patient_list[current_index_OfPateintList].name);
		fflush(stdin);
		printf("Enter the ID of the patient: ");
		scanf("%i",&(patient_list[current_index_OfPateintList].age));
		printf("Enter the ID of the patient: ");
		gets(patient_list[current_index_OfPateintList].gender);
		fflush(stdin);
		
		printf("The patient is added successfully.\n");
	}
	
	
}

	else if (option == 2 && check_flag == 0) 
	{
		printf("No pateient with this ID\n");
	}

		else if (option == 2 && check_flag == 1){
			printf("Correct ID. Now, you can edit patient info :\n___________\n");
		}
		
		
/*
// scanf in main before use this : 
u8 check_slot_available(u8 slot_chosen, ReservationSlot* slots_list )
{
	do {
		printf("Enter the slot nubmer you want :");
		scanf("%i", &slot_chosen);
		if(slot_chosen < 1 || slot_chosen > 5){
			printf("Error! Enter valid slot\n"); 
		}
	}while(slot_chosen < 1 || slot_chosen > 5);
	
	u8 slot_repeted = 0;  
	for(u8 slot = 0; slot < TOTAL_SLOTS_NUM; slot++){
		if (slot_chosen == slots_list [slot].slotOf_id){
			slot_repeted = 1; 
			break;
		}
	}
	return slot_repeted;
}
*/
