/*
 *  Author : Bassant Ossama Milad Habib
 *  Group : 89
 *  Project name : Student Management System
 *  Project description:- The Student Management System is a C program designed
 *                      to manage student information efficiently. It allows the
 *                      user to perform various operations such as adding new
 *                      students, displaying all students, searching for
 *                      a student by ID,updating student details, calculating
 *                      the average GPA, and finding the student with the
 *                      highest GPA.
 *                      - This system utilizes fundamental programming concepts
 *                      including conditions,loops, strings, structures, and
 *                      pointers, besides the ability to use data structures
 *                      efficiently like the linked list.
 */

#include<stdio.h>
#include <stdlib.h>

struct student {
	int id;         //student id
	char name[50];  //student name
	int age;        //student age
	float gpa;      //student gpa
}data;

//structure to represent a node in a Linked List
struct node {
	struct student data;
	struct node *next;
};

struct node *head = NULL;

//prototypes of the functions that will be used in this code
void addStudent(const struct student *const ptr);
void displayStudents(void);
void searchStudentByID(int id);
void updateStudent(int id);
float calculateAverageGPA(void);
void searchHighestGPA(void);
void deleteStudent(int id);

/*============================================================================*/

/*
 * The main function :
 * serves as the entry point of the program.
 * It continuously displays the menu options to the user, takes the user's
 * choice as input, and calls the corresponding function based on the user's
 * selection.
 * The menu loop continues until the user decides to exit the program.
 */
int main(){

	setvbuf(stdout,NULL,_IONBF,0);
	setvbuf(stderr,NULL,_IONBF,0);

	struct student *p=&data;
	int op;
	int id;

	//using the [while(1)] to continuously display the menu options to the user
	while(1)
	{
		printf("1. Add Student \n2. Display Students \n"
				"3. Search Student by ID \n"
				"4. Update Student Information \n5. Delete Student \n"
				"6. Calculate Average GPA \n"
				"7. Find for Student with Highest GPA \n8. Exit \n");
		printf("Enter choice:");
		scanf("%d",&op);
		printf("------------------------------------------------------ \n");
		/*switch statement to switch between the 8 options that the user will
		 * choose from them */
		switch(op){
		case 1:
			printf ("Enter Student ID:");
			scanf("%d",&p->id);
			printf("Enter name: ");
			scanf(" %s",p->name);
			printf("Enter age: ");
			scanf(" %d",&p->age);
			printf("Enter GPA: ");
			scanf(" %f",&p->gpa);
			printf("------------------------------------------------------ \n");
			//Prompts the user for new student details and adds them to the system
			addStudent(p);
			break;
		case 2:
			displayStudents(); // Shows a list of all stored student records
			break;
		case 3:
			printf("Enter Student ID to search: ");
			scanf("%d",&id);
			//allows the user to find a specific student using their unique ID
			searchStudentByID(id);
			break;
		case 4:
			printf("Enter Student ID to update its information: ");
			scanf("%d",&id);
			/*
			 * Facilitates the updating of details for an existing student
			 * identified by their ID
			 */
			updateStudent(id);
			break;
		case 5:
			printf("Enter Student ID to delete its data:");
			scanf("%d",&id);
			deleteStudent(id); //Removes a student's record based on their ID
			break;
		case 6:
			// Computes and displays the average GPA of all students
			printf("Average GPA = %f\n",calculateAverageGPA());
			printf("---------------------------------------------------------- \n");
			break;
		case 7:
			//Identifies and displays the student with the highest GPA
			searchHighestGPA();
			break;
		case 8:
			//Terminates the program
			printf("Exiting... \n");
			return 0;
		default:
			printf("Invalid choice, Please try again\n");
		}
	}
	return 0;
}

/*============================================================================*/

/*
 * add student function:
 * collects new student details from the user and adds them to the student
 *  linked list.
 */
void addStudent(const struct student *const ptr)
{
	int flag=0;
	struct node *current = head;
	while (current !=NULL)
	{
		// checking if the student is already exists :
		if(current->data.id==ptr->id)
		{
			//  if ID exists: it prints an error message and returns
			printf("this ID is already reserved\n");
			printf("---------------------------------------------------------- \n");

			flag=1;
			return ;
		}
		current = current->next;
	}
	if(flag==1){
		return;
	}
	  //if ID does not exist: it attempts to allocate memory for a new node.
	else{
		flag=0;
		struct node *link = (struct node*) malloc(sizeof(struct node));

		 // If memory allocation fails, it prints an error message and returns.
		if (link == NULL) {
			printf("error \n");
			return;
		}
		/*
		 * If memory allocation is successful, it copies the student data to
		 * the new node and adds the node to the end of the linked list.
		 */
		else{
			link->data = *ptr;
			link->next = NULL;
			if(head==NULL)
			{
				head = link;
				return;
			}
			current = head;
			while(current->next != NULL)
			{
				current = current->next;
			}
			current->next = link;
		}
	//printf("new student takes place \n");
	//printf("---------------------------------------------------------- \n");
}
}

/*===========================================================================*/

/*
 * displayStudent function displays the details of all students currently in
 * the system.
 */
void displayStudents(void)
{
	struct node *ptr = head;

	// checking if the list is empty or not
	if (ptr==NULL)
	{
		/*
		 * if the list is empty:
		 * it prints a message indicating no students are present and return.
		 */
		printf("the list is empty\n");
		return;
	}
	/*
	 * if the list is not empty :
	 * it traverses the list and prints the details of each student
	 */
	while(ptr != NULL)
	{
		printf("[ id: %d, Name: %s, Age: %d, GPA: %f ]\n",
				ptr->data.id,ptr->data.name,ptr->data.age,ptr->data.gpa);
		ptr = ptr->next;
	}
	printf("---------------------------------------------------------- \n");
}

/*===========================================================================*/

/*
 * seacrhStudentByID function:
 * searches for a student by their ID and displays their details if found.
 */
void searchStudentByID(int id){
	struct node *current = NULL;

	// checking if the list is empty or not
	if(head==NULL)
	{
		printf("Linked List is empty\n");
		return;
	}
	current = head;
	while(current != NULL)
	{
		//checking if the student with that id is found or not
		if(current->data.id == id)
		{
			//If the student is found, the details of the student is printed
			printf("Student found:\n");
			printf("ID: %d, Name: %s, Age: %d, GPA: %f \n",current->data.id,
					current->data.name,current->data.age,current->data.gpa);
			printf("----------------------------------------------------------\n");
			return;
		}
		current = current->next;
	}
	/*
	 * If the student is not found, it prints a message indicating the student
	 * was not found.
	 */
	printf("Student with Id %d is not found.\n", id);
	printf("---------------------------------------------------------- \n");
}

/*===========================================================================*/

/*
 *  updateStudent function:
 *  updates the details of a student with the given ID.
 */
void updateStudent(int id) {
	struct node *current = NULL;

	// checking if the list is empty or not
	if(head == NULL)
	{
		printf("Linked List is empty\n");
		return;
	}
	current = head;
	while(current != NULL)
	{
		// checking if the student with that id is found or not
		if(current->data.id == id)
		{
			/*
			 *  If the student is found, then update the student's information
			 *  (student :name, age, gpa).
			 */
			printf("Enter new details for the Student with ID %d:\n",id);
			printf("Enter new Name:");
			scanf(" %s",current->data.name);
			//printf("\n");
			printf("Enter new Age:");
			scanf("%d",&current->data.age);
			//printf("\n");
			printf("Enter new GPA:");
			scanf("%f",&current->data.gpa);
			//printf("\n");
			printf("Student details updated successfully \n");
			printf("---------------------------------------------------------- \n");
			return;
		}
		current = current->next;
	}
	/*
	 * If the student is not found, it prints a message indicating the student
	 * was not found.
	 */
	printf("%d does not exist in the list\n", id);
	printf("---------------------------------------------------------- \n");
}

/*===========================================================================*/

/*
 *  calculateAverageGPA function:
 *  calculates and returns average GPA of all students which is of type float
 */
float calculateAverageGPA(void) {
	struct node *ptr = NULL;
	float sum = 0;
	float avg = 0;
	int num = 0;

	// checking if the list is empty or not
	if(head == NULL)
	{
		// If the list is empty, it returns 0.0
		printf("Linked List is empty\n");
		return 0.0;
	}
	/*
	 * If the list is not empty, it returns the average GPA(avg) by dividing the
	 * total sum of GPAs(sum) by the number of students(num)
	 */
	ptr=head;
	while (ptr != NULL)
	{
		sum+=ptr->data.gpa;  //the sum of the GPAs of all students
		ptr=ptr->next;
		num++;               //counting the number of students
	}
	avg=sum/num;
	return avg;     // returning average of GPAs(avg)
}

/*===========================================================================*/

/*
 *  searchHighestGPA function:
 *  finds and displays the student with the highest GPA
 */
void searchHighestGPA(void) {
	struct node *current = NULL;
	struct node *previous = NULL;

	// checking if the list is empty or not
	if(head == NULL)
	{
		/*
		 * If the list is empty, it prints a message indicating that there are
		 * no students.
		 */
		printf("Linked List is empty\n");
		return;
	}
	previous=head;
	current=head;
	while (current != NULL)
	{
		// keeping track of the student with the highest GPA encountered
		if(current->data.gpa >= previous->data.gpa)
		{
			previous=current;
		}
		current=current->next;
	}
	/*
	 * After finding the student with the highest GPA, the details of that
	 * student will be printed
	 */
	printf("Student with the highest GPA:\n");
	printf("[ ID: %d, Name: %s, Age: %d, GPA: %f ] \n",previous->data.id
			,previous->data.name,previous->data.age,previous->data.gpa);
	printf("---------------------------------------------------------- \n");

}

/*===========================================================================*/

/*
 *  deleteStudent function:
 *  deletes a student from the linked list by their ID
 */
void deleteStudent(int id) {
    struct node *current = NULL;
    struct node *previous = NULL;

	// checking if the list is empty or not
    if (head == NULL) {
        printf("Linked List is empty\n");
        printf("----------------------------------------------------------\n");
        return;
    }
    current = head;
	// searching for the student with the given ID if it is at the head
    if (current->data.id == id)
    {
        head = current->next;
        free(current);
        printf("Student with ID %d is deleted successfully\n", id);
        printf("----------------------------------------------------------\n");
        return;
    }
	/*
	 * searching for the student with the given ID starting from the position
	 * that after the head
	 */
    while (current != NULL)
    {
    	 /* If the student is found, the node is removed from the list and frees
          * the memory allocated for the node and a success message is printed
          */
        if (current->data.id == id)
        {
            previous->next = current->next;
            free(current);
            printf("Student with ID %d is deleted successfully\n", id);
            printf("----------------------------------------------------------\n");
            return;
        }
        previous = current;
        current = current->next;
    }

    /*  If the student is not found, a message saying the student
   	 *  was not found is printed
   	 */
    printf("Student with ID %d is not found\n", id);
    printf("----------------------------------------------------------\n");
}

