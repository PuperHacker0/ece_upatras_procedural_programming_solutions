//up1100979
#include <stdio.h>
#include <string.h>

#define MAX_FILENAME_LENGTH 40
#define MAX_WORD_LENGTH 30
#define MAX_NUMBER_WORDS 27000 //Careful not to exceed 1MB stack limit

void empty_input_buffer(void);
void import_text(char text[MAX_NUMBER_WORDS][MAX_WORD_LENGTH], int* words_read, int*);
void read_dictionary(char dict[MAX_NUMBER_WORDS][MAX_WORD_LENGTH], int* words_read);
void save_text_to_file(char text[MAX_NUMBER_WORDS][MAX_WORD_LENGTH], int);
void error_correction(char text[MAX_NUMBER_WORDS][MAX_WORD_LENGTH]);
void compute_text_stats(char text[MAX_NUMBER_WORDS][MAX_WORD_LENGTH], int, int);
void compute_char_count(int*, char text[MAX_NUMBER_WORDS][MAX_WORD_LENGTH], int);
void compute_different_words(char text[MAX_NUMBER_WORDS][MAX_WORD_LENGTH], int word_count, int* different_word_count);

int main(void) {
	int choice, text_word_count = 0, dict_word_count = 0, text_whitespace_count = 0;
	//Actual number of words in the text, not the maximum of the container
	char text[MAX_NUMBER_WORDS][MAX_WORD_LENGTH];
	//dict[MAX_NUMBER_WORDS][MAX_WORD_LENGTH];

	while (1) {
		printf("Which text mode would you like?\n1. Import text from file\n");
		printf("2. Enter dictionary words from keyboard\n3. Text correction\n4. Save text\n");
		printf("5. Compute text statistics\n6. Exit application\n");

		(void)scanf("%d", &choice);
		printf("\n");

		switch (choice) {
		case 1: {
			text_whitespace_count = 0;
			import_text(text, &text_word_count, &text_whitespace_count);
			break;
		}
		case 2:
			//read_dictionary(dict, &dict_word_count);
			break;
		case 3:
			error_correction(text);
			break;
		case 4:
			save_text_to_file(text, text_word_count);
			break;
		case 5:
			compute_text_stats(text, text_word_count, text_whitespace_count);
			break;
		case 6: //Exit
			printf("Thank you for using this application!\n");
			return 0;
		default:
			printf("Invalid choice, please try again.\n");
			empty_input_buffer(); //To remove extra chars in the end that might be processed by the next scanf call
		}
		printf("\n");
	}

	return 0;
}

void import_text(char text[MAX_NUMBER_WORDS][MAX_WORD_LENGTH], int* words_read, int* whitespace_count) {
	char filename[MAX_FILENAME_LENGTH];
	printf("What is the name of the file to read from? (with extension)\n");
	(void)scanf(" %s", filename);

	FILE* f;
	if ((f = fopen(filename, "r")) == NULL) {
		printf("Failed to open the file, please try again later.\n");
		return;
	}

	char word[MAX_WORD_LENGTH];
	*words_read = 0; //To overwrite the previous input
	while (fscanf(f, "%30s", word) == 1) {
		strcpy(text[(*words_read)++], word);
	}

	//Count whitespaces
	fseek(f, 0, SEEK_SET); //Go to the start of the file
	char tmp;
	while ((tmp = fgetc(f)) != -1)
		if (tmp == ' ') ++(*whitespace_count);

	fclose(f);
}

void empty_input_buffer(void) {
	while (getchar() != '\n'); //No need for a block here ;)
}

void read_dictionary(char dict[MAX_NUMBER_WORDS][MAX_WORD_LENGTH], int* words_read) {
	/*printf("Please enter the words of the dictionary, one at a time.\n");

	char word[MAX_WORD_LENGTH];
	*words_read = 0;
	while (scanf("%s", word), strcmp(word, "*T*E*L*O*S*")) {
		strcpy(dict[(*words_read)++], word);
	}*/
}

void error_correction(char text[MAX_NUMBER_WORDS][MAX_WORD_LENGTH]) {

}

void save_text_to_file(char text[MAX_NUMBER_WORDS][MAX_WORD_LENGTH], int word_count) {
	char filename[] = "saved_text00.txt";
	printf("Text contents will be saved to %s.\n", filename);

	FILE* f;
	if ((f = fopen(filename, "w")) == NULL) {
		printf("Failed to write to the file, please try again later.\n");
		return;
	}

	for (int i = 0; i < word_count; ++i)
		fprintf(f, "%s\n", text[i]);

	fclose(f);
}

void compute_text_stats(char text[MAX_NUMBER_WORDS][MAX_WORD_LENGTH], int word_count, int whitespace_count) {
	//a
	int total_chars = 0;
	compute_char_count(&total_chars, text, word_count);

	printf("Total number of characters (excluding whitespaces): %d\n", total_chars);
	printf("Total number of characters (including whitespaces): %d\n", total_chars + whitespace_count);

	//b
	int different_word_count = word_count;
	compute_different_words(text, word_count, &different_word_count);
	printf("The text has %d different word(s) (case sensitive!)\n", different_word_count);

	//c
	int histogram[MAX_WORD_LENGTH] = { 0 }; //Store the number of words with y letters, for all allowed y
	for (int i = 0; i < word_count; ++i)
		++histogram[strlen(text[i]) - 1];

	printf("Word character number histogram:\n");
	for (int j = 1; j < MAX_WORD_LENGTH /*Exclude NULL terminator*/; ++j) {
		printf("Words of size %d: %d\n", j, histogram[j - 1]);
	}

	//d
}

void compute_char_count(int* total_chars, char text[MAX_NUMBER_WORDS][MAX_WORD_LENGTH], int word_count) {
	for (int i = 0, curr_word_length; i < word_count; ++i)
		*total_chars += (curr_word_length = (int)strlen(text[i]));
}

void compute_different_words(char text[MAX_NUMBER_WORDS][MAX_WORD_LENGTH], int word_count, int* different_word_count) {
	//Note that this will not exclude hyphens, fullstops, dashes, or any other punctuation points!!!
	char processed[MAX_NUMBER_WORDS]; //Bool array, processed or not
	//This is to avoid duplicate word excluding one another multiple times, we need to skip these
	memset(processed, 0, MAX_NUMBER_WORDS);

	for (int i = 0; i < word_count; ++i) {
		if (processed[i]) continue;
		int occurences = 0;
		for (int j = 0; j < word_count; ++j)
			if (!strcmp(text[i], text[j])) {//The words match
				++occurences;
				processed[j] = 1;
			}

		*different_word_count -= occurences - 1;
		//Remove duplicate matches from the word count
		processed[i] = 1;
	}
}