//up1100979
#include <stdio.h>

#define MAX_FILENAME_LENGTH 20
#define MAX_WORD_LENGTH 20
#define MAX_NUMBER_WORDS 20000 //Careful not to exceed 1MB stack limit

void empty_input_buffer(void);
void read_text(char text[MAX_NUMBER_WORDS][MAX_WORD_LENGTH]);
void read_dictionary(char dict[MAX_NUMBER_WORDS][MAX_WORD_LENGTH]);
void save_text_to_file(char* filename, char text[MAX_NUMBER_WORDS][MAX_WORD_LENGTH]);
void error_correction(char text[MAX_NUMBER_WORDS][MAX_WORD_LENGTH]);
void compute_text_stats(char text[MAX_NUMBER_WORDS][MAX_WORD_LENGTH]);

int main(void) {
	int choice;
	char text[MAX_NUMBER_WORDS][MAX_WORD_LENGTH],
		dict[MAX_NUMBER_WORDS][MAX_WORD_LENGTH];

	while (1) {
		printf("Which text mode would you like?\n1. Enter text from keyboard or import from file\n");
		printf("2. Enter dictionary words from keyboard\n3. Text correction\n4. Save text\n");
		printf("5. Compute text statistics\n6. Exit application\n");

		(void)scanf("%d", &choice);

		switch (choice) {
		case 1: {
			read_text(text);
			break;
		}
		case 2:
			read_dictionary(dict);
			break;
		case 3:
			error_correction(text);
			break;
		case 4: {
			char filename[MAX_FILENAME_LENGTH];
			printf("What is the name of the file to save to?\nWarning: the file WILL be overwritten if it already exists\n");
			(void)scanf("%s", filename);

			save_text_to_file(filename, text);
			break;
		}
		case 5:
			compute_text_stats(text);
			break;
		case 6: //Exit
			printf("Thank you for using this application!\n");
			return 0;
		default:
			printf("Invalid choice, please try again\n");
			empty_input_buffer(); //To remove extra chars in the end that might be processed by the next scanf call
		}
	}

	return 0;
}

void read_text(char text[MAX_NUMBER_WORDS][MAX_WORD_LENGTH]) {

}

void empty_input_buffer(void) {
	while (getchar() != '\n'); //No need for a block here ;)
}

void read_dictionary(char dict[MAX_NUMBER_WORDS][MAX_WORD_LENGTH]) {

}

void error_correction(char text[MAX_NUMBER_WORDS][MAX_WORD_LENGTH]) {

}

void save_text_to_file(char* filename, char text[MAX_NUMBER_WORDS][MAX_WORD_LENGTH]) {

}

void compute_text_stats(char text[MAX_NUMBER_WORDS][MAX_WORD_LENGTH]) {

}