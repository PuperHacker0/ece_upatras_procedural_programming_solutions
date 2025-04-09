//up1100979
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_FILENAME_LENGTH 40
#define MAX_WORD_LENGTH 30

//Utility structs and functions
typedef struct text_t {
    char** text;
    int word_count;
} Text;

Text init_Text(void);
void empty_input_buffer(void);

//Text functions
void import_text(Text*, int*);
void save_text_to_file(Text*);
void compute_text_stats(Text*, int);
void compute_char_count(int*, Text*);
void compute_different_words(Text*, int*);

//Dict functions
void error_correction(Text*, Text*);
int exists_in_dictionary(char* word, Text*);
void add_word_to_dict(char* word, Text*);

int main(void) {
	int choice, text_word_count = 0, dict_word_count = 0, text_whitespace_count = 0, dict_whitespace_count;
	Text txt = init_Text(), dict = init_Text();

	while (1) {
		printf("Which text mode would you like?\n1. Import text from file\n");
		printf("2. Import dictionary from file\n3. Text correction\n4. Save text\n");
		printf("5. Compute text statistics\n6. Exit application\n");

		(void)scanf("%d", &choice);
		printf("\n");

		switch (choice) {
		case 1: {
			text_whitespace_count = 0;
			import_text(&txt, &text_whitespace_count);
			break;
		}
		case 2:
            import_text(&dict, &dict_whitespace_count);
            //There should be a separate function for the counting whitespaces but this will suffice for now
			break;
		case 3:
			error_correction(&txt, &dict);
			break;
		case 4:
			save_text_to_file(&txt);
			break;
		case 5:
			compute_text_stats(&txt, text_whitespace_count);
			break;
		case 6: //Exit
			printf("Thank you for using this application!\n");
			return 0;
		default:
			printf("Invalid choice, please try again.\n");
			empty_input_buffer();
            //To remove extra chars in the end that might be processed by the next scanf call
		}
		printf("\n");
	}

	return 0;
}

Text init_Text() {
    Text t;
    t.text = NULL, t.word_count = 0;
    return t;
}

void empty_input_buffer(void) {
	while (getchar() != '\n');
}

void import_text(Text* txt_ptr, int* whitespace_count) {
    //New calls inside the program append new files to the end of the previously read ones
	char filename[MAX_FILENAME_LENGTH];
	printf("What is the name of the file to read from? (with extension)\n");
	(void)scanf(" %s", filename);

	FILE* f;
	if ((f = fopen(filename, "r")) == NULL) {
		printf("Failed to open the file, please try again later.\n");
		return;
	}

	//We can have the word[] on the stack and strcpy it every time
    //Or have it on the heap and malloc a new space every time, so we just save the old ptr in the text
    //This does consume more memory, because we keep allocating 30bytes no matter the size of the word
    //It would be more efficient to save it on the stack first and then after finding its strlen
    //to copy it to a variable size malloc call
	char* word;
    while (fscanf(f, " %29s", word = (char*)malloc(MAX_WORD_LENGTH * sizeof(char))) == 1) {
        ++(txt_ptr->word_count);
        txt_ptr->text = (char**)realloc(txt_ptr->text, txt_ptr->word_count * sizeof(char *));
        (txt_ptr->text)[txt_ptr->word_count - 1] = word;
        //The ptr to the beginning of the last word is the pointer of the malloc call we just made
    }
    free(word); //Don't forget to deallocate the last word which was malloc-ed but not used in fscanf

	//Count whitespaces
	fseek(f, 0, SEEK_SET); //Go to the start of the file
	char tmp;
	while ((tmp = fgetc(f)) != -1)
		if (tmp == ' ') ++(*whitespace_count);

	fclose(f);
}

void error_correction(Text* text_ptr, Text* dict_ptr) {
	if (dict_ptr->word_count == 0) {
		printf("The dictionary is empty. Skipping...\n");
		return;
	}

	for (int i = 0; i < text_ptr->word_count; ++i) {
		if (!exists_in_dictionary((text_ptr->text)[i], dict_ptr)) {
			printf("The word \"%s\" is not in the dictionary.\n", (text_ptr->text)[i]);
			printf("1. Replace it with another\n2. "
                "Add it to the dictionary\n3. Ignore this word\n4. Ignore all (abort text correction)\n");

			char flag;
			do {
				int choice;
				(void)scanf("%d", &choice);
				printf("\n");

				flag = 0; //Will keep running until a valid choice is given
				switch (choice) {
				case 1: {
					printf("Which word to replace with?\n");
					char new_word[MAX_WORD_LENGTH];

					(void)scanf("%s", new_word);
					printf("\n");

					if (!exists_in_dictionary(new_word, dict_ptr)) {
						printf("The new word itself does not exist in the dictionary. It will be added now.\n");
						add_word_to_dict(new_word, dict_ptr);
					}

					//Replace current word
					strcpy((text_ptr->text)[i], new_word);

					printf("Word replaced successfully.\n\n");
					break;
				}
				case 2:
					add_word_to_dict((text_ptr->text)[i], dict_ptr);
					break;
				case 3:
					continue; //With other words
				case 4: //Exit
					return;
				default:
					printf("Invalid choice, please try again.\n");
					flag = 1;
					empty_input_buffer();
                    //To remove extra chars in the end that might be processed by the next scanf call
				}
			} while (flag);
		}
		//Otherwise, the word is in the dict, so no problem there
	}

	printf("Spelling check complete.\n");
}

void add_word_to_dict(char* word, Text* dict_ptr) {
    ++(dict_ptr->word_count);
    //The word already exists on the heap. We just gotta make a separate copy of it in the heap for the dict
    dict_ptr->text = (char**)realloc(dict_ptr->text, sizeof(char*) * dict_ptr->word_count);
    //These should be a separate function but ok for now
    dict_ptr->text[dict_ptr->word_count - 1] = (char*)malloc(sizeof(char) * MAX_WORD_LENGTH);

	strcpy(dict_ptr->text[dict_ptr->word_count - 1], word);
	printf("Word added to the dictionary.\n");
}

int exists_in_dictionary(char* word, Text* dict_ptr) { //Non-zero if it exists, 0 otherwise
	for (int i = 0; i < dict_ptr->word_count; ++i)
		if (strcmp(word, (dict_ptr->text)[i]) == 0) //The word matches with this one in the dict
			return 1;
    
	return 0;
}

void save_text_to_file(Text* text_ptr) {
	char filename[] = "saved_text00.txt";
	printf("Text contents will be saved to %s.\n", filename);

	FILE* f;
	if ((f = fopen(filename, "w")) == NULL) {
		printf("Failed to write to the file, please try again later.\n");
		return;
	}

	for (int i = 0; i < text_ptr->word_count; ++i)
		fprintf(f, "%s\n", (text_ptr->text)[i]);
        //The ith element in the text pointer array, so the ith word

	fclose(f);
}

void compute_text_stats(Text* text_ptr, int whitespace_count) {
	//Whitespace count already calculated
	//From this application version onwards, stats are only printed in the file!
	char filename[] = "saved_stats00.txt";
	printf("Text stats will be saved to %s.\n", filename);

	FILE* f;
	if ((f = fopen(filename, "w")) == NULL) {
		printf("Failed to write to the stats file, please try again later.\n");
		return;
	}

	//a
	int total_chars = 0;
	compute_char_count(&total_chars, text_ptr);

	fprintf(f, "Total number of characters (excluding whitespaces and newlines): %d\n", total_chars);
	fprintf(f, "Total number of characters (including whitespaces,"
        "excluding newlines): %d\n", total_chars + whitespace_count);

	//b
	int different_word_count = text_ptr->word_count;
	compute_different_words(text_ptr, &different_word_count);
    //Pass by ptr in all these functions to not keep copying the struct around for no reason
	fprintf(f, "The text has %d different word(s) (case sensitive!)\n", different_word_count);

	//c
	int histogram[MAX_WORD_LENGTH] = { 0 };
    //Store the number of words with y letters, for all allowed y
	for (int i = 0; i < text_ptr->word_count; ++i)
		++histogram[strlen((text_ptr->text)[i]) - 1];

	fprintf(f, "Word character number histogram:\n");
	for (int j = 1; j < MAX_WORD_LENGTH /*Exclude NULL terminator*/; ++j)
		fprintf(f, "Words of size %d: %d\n", j, histogram[j - 1]);

	fclose(f);
	printf("Statistics saved successfully.\n");
}

void compute_char_count(int* total_chars, Text* text_ptr) {
	for (int i = 0, curr_word_length; i < text_ptr->word_count; ++i)
		*total_chars += (curr_word_length = (int)strlen((text_ptr->text)[i]));
}

void compute_different_words(Text* text_ptr, int* different_word_count) {
	//Note that this will include hyphens, fullstops, dashes, or any other punctuation points!!!
	char* processed = (char*)malloc(sizeof(char) * text_ptr->word_count);
    //Bool array, processed or not
	//This is to avoid duplicate words excluding one another multiple times, we need to skip these

	memset(processed, 0, text_ptr->word_count);

	for (int i = 0; i < text_ptr->word_count; ++i) {
		if (processed[i]) continue;
		int occurences = 0;
		for (int j = 0; j < text_ptr->word_count; ++j)
			if (!strcmp((text_ptr->text)[i], (text_ptr->text)[j])) { //The words match
				++occurences;
				processed[j] = 1;
			}

		*different_word_count -= occurences - 1;
		//Remove duplicate matches from the word count
		processed[i] = 1;
	}
}