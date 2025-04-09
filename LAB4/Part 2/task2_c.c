//up1100979
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_FILENAME_LENGTH 40
#define MAX_WORD_LENGTH 30

/*SIMIOSI:
I SCANF APO MONI TIS XORIZEI TIS LEXEIS STO WHITESPACE
ARA IKANOPOIEITAI I SYNTHIKI TIS ISSPACE(),
DEN XREIAZETAI PERAITERO ELEGXOS*/

//Node-related structs and utility functions
typedef struct node {
	char* str;
	struct node* next;
} Node;
typedef Node* LinkedList;
typedef Node* LinkedNodePtr;

LinkedNodePtr create_node(void);
void empty_input_buffer(void);

//Text-related functions
void import_text(LinkedList, int* words_read, int*);
void save_text_to_file(LinkedList, int);
void compute_text_stats(LinkedList, int, int);
void compute_char_count(int*, LinkedList, int);
void compute_different_words(LinkedList, int word_count, int* different_word_count);

//Dict-related functions
int exists_in_dictionary(char* word, LinkedList dict, int);
void add_word_to_dict(char* word, LinkedList dict, int* index);
void error_correction(LinkedList text, int, LinkedList dict, int*);

int main(void) {
	int choice, text_word_count = 0, dict_word_count = 0, text_whitespace_count = 0, dict_whitespace_count = 0;
	LinkedList text = create_node(), dict = create_node();

	while (1) {
		printf("Which text mode would you like?\n1. Import text from file\n");
		printf("2. Import dictionary from file\n3. Text correction\n4. Save text\n");
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
			import_text(dict, &dict_word_count, &dict_whitespace_count);
			break;
		case 3:
			error_correction(text, text_word_count, dict, &dict_word_count);
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

LinkedNodePtr create_node() {
	LinkedNodePtr ptr = (LinkedNodePtr)malloc(sizeof(Node));
	ptr->next = NULL, ptr->str = NULL;
	return ptr;
}

void import_text(LinkedList head, int* words_read, int* whitespace_count) {
	char filename[MAX_FILENAME_LENGTH];
	printf("What is the name of the file to read from? (with extension)\n");
	(void)scanf(" %s", filename);

	FILE* f;
	if ((f = fopen(filename, "r")) == NULL) {
		printf("Failed to open the file, please try again later.\n");
		return;
	}
	else if (head == NULL) {
		printf("Head not initialized!\n");
		return;
	}

	char* word;
    while (fscanf(f, " %29s", word = (char*)malloc(MAX_WORD_LENGTH * sizeof(char))) == 1) {
        ++(*words_read);
        head->str = word;
		head->next = create_node(); //There will be one extra final node (ok for now, should be done with if cases to fix this)
		head = head->next;
    }
    free(word); //Don't forget to deallocate the last word which was malloc-ed but not used in fscanf

	//Count whitespaces
	fseek(f, 0, SEEK_SET); //Go to the start of the file
	char tmp;
	while ((tmp = fgetc(f)) != -1)
		if (tmp == ' ') ++(*whitespace_count);

	fclose(f);
}

void empty_input_buffer(void) {
	while (getchar() != '\n');
}

void error_correction(LinkedList text_list, int text_word_count, LinkedList dict_list, int* dict_word_count) {
	if (dict_word_count == 0) {
		printf("The dictionary is empty. Skipping...\n");
		return;
	}

	for (int i = 0; i < text_word_count; ++i) {
		if (!exists_in_dictionary(text_list->str, dict_list, *dict_word_count)) {
			printf("The word \"%s\" is not in the dictionary.\n", text_list->str);
			printf("1. Replace it with another\n2. Add it to the dictionary\n3. Ignore this word\n4. Ignore all (abort text correction)\n");

			char flag;
			do {
				int choice;
				(void)scanf("%d", &choice);
				printf("\n");

				flag = 0; //Will keep running until a valid choice is given
				switch (choice) {
				case 1: {
					printf("Which word to replace with?\n");
					char* new_word = (char*)malloc(MAX_WORD_LENGTH * sizeof(char));

					(void)scanf(" %s", new_word);
					printf("\n");

					if (!exists_in_dictionary(new_word, dict_list, *dict_word_count)) {
						printf("The new word does not exist in the dictionary itself. It will be added now.\n");
						add_word_to_dict(new_word, dict_list, dict_word_count);
					}

					//Replace current word
					free(text_list->str); //Free the old word
					text_list->str = new_word; //Only need to copy a pointer, the word is already there on the heap

					printf("Word replaced successfully.\n\n");
					break;
				}
				case 2:
					add_word_to_dict(text_list->str, dict_list, dict_word_count);
					break;
				case 3:
					continue; //With other words
				case 4: //Exit
					return;
				default:
					printf("Invalid choice, please try again.\n");
					flag = 1;
					empty_input_buffer(); //To remove extra chars in the end that might be processed by the next scanf call
				}
			} while (flag);
		}
		//Otherwise, the word is in the dict, so no problem there
		text_list = text_list->next;
	}

	printf("Spelling check complete.\n");
}

void add_word_to_dict(char* word, LinkedList dict, int* index) {
	//Go to the end of the dict
	for (int i = 0; i < *index; ++i) //Go to the final dummy empty node
		dict = dict->next;
	
	dict->str = word;
	++(*index); //Increase word count
	dict->next = create_node(); //Make the next dummy node

	printf("Word added to the dictionary.\n");
}

int exists_in_dictionary(char* word, LinkedList dict, int dict_word_count) { //Non-zero if it exists, 0 otherwise
	for (int i = 0; i < dict_word_count; ++i) {
		if (strcmp(word, dict->str) == 0) //The word matches with this one in the dict
			return 1;
		dict = dict->next;
	}

	return 0;
}

void save_text_to_file(LinkedList text, int word_count) { //We do not care if this is  or not, because it is a local copy
	char filename[] = "saved_text00.txt";
	printf("Text contents will be saved to %s.\n", filename);

	FILE* f;
	if ((f = fopen(filename, "w")) == NULL) {
		printf("Failed to write to the file, please try again later.\n");
		return;
	}

	for (int i = 0; i < word_count; ++i) {
		fprintf(f, "%s\n", text->str);
		text = text->next;
	}

	fclose(f);
}

void compute_text_stats(LinkedList text, int word_count, int whitespace_count) {
	//Whitespace count already calculated
	//From this application version onwards, stats are only printed in the file!
	char filename[] = "saved_stats00.txt";
	printf("Stats will be saved to %s.\n", filename);

	FILE* f;
	if ((f = fopen(filename, "w")) == NULL) {
		printf("Failed to write to the stats file, please try again later.\n");
		return;
	}

	//a
	int total_chars = 0;
	compute_char_count(&total_chars, text, word_count);

	fprintf(f, "Total number of characters (excluding whitespaces and newlines): %d\n", total_chars);
	fprintf(f, "Total number of characters (including whitespaces, excluding newlines): %d\n", total_chars + whitespace_count);

	//b
	int different_word_count = word_count;
	compute_different_words(text, word_count, &different_word_count);
	fprintf(f, "The text has %d different word(s) (case sensitive!)\n", different_word_count);

	//c
	int histogram[MAX_WORD_LENGTH] = { 0 }; //Store the number of words with y letters, for all allowed y
	for (int i = 0; i < word_count; ++i) {
		++histogram[strlen(text->str) - 1];
		text = text->next;
	}

	fprintf(f, "Word character number histogram:\n");
	for (int j = 1; j < MAX_WORD_LENGTH /*Exclude NULL terminator*/; ++j)
		fprintf(f, "Words of size %d: %d\n", j, histogram[j - 1]);

	fclose(f);

	printf("Statistics saved successfully.\n");
}

void compute_char_count(int* total_chars, LinkedList text, int word_count) {
	for (int i = 0, curr_word_length; i < word_count; ++i) { //Could be done with a while or a for loop with txt=txt->next as the iteration
	//but this is a simpler way to keep track of how many words to read, there might be "" words, who knows!
	//Plus the last node is a dummy so checking if next=null won't work
	//This can be solved easily and written more concisely but for now it's ok
		*total_chars += (curr_word_length = (int)strlen(text->str));
		text = text->next;
	}
}

void compute_different_words(LinkedList text, int word_count, int* different_word_count) {
	//Note that this will not exclude hyphens, fullstops, dashes, or any other punctuation points!!!
	char* processed = (char*)malloc(sizeof(char) * word_count); //Bool array, processed or not
	//This is to avoid duplicate word excluding one another multiple times, we need to skip these
	memset(processed, 0, word_count);
	LinkedNodePtr head = text, search_match;

	for (int i = 0; i < word_count; ++i, text = text->next) {
		if (processed[i]) continue;

		int occurences = 0;
		search_match = head;
		for (int j = 0; j < word_count; ++j) {
			if (!strcmp(text->str, search_match->str)) { //The words match
				++occurences;
				processed[j] = 1;
			}
			search_match = search_match->next;
		}

		*different_word_count -= occurences - 1;
		//Remove duplicate matches from the word count
	}
}