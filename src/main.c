#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <getopt.h>
#include "../include/move_utils.h"
#include "../include/file_utils.h"
#include "../include/linked_list.h"
#include "../include/globals.h"
#include <semaphore.h>
#include <string.h>
#define BUFFER_SIZE 4096

pthread_mutex_t resource_semaphore;


typedef struct {
    const char *source;
    const char *destination;
    int is_file;
} thread_args_t;


void *thread_function(void *arg) {
    thread_args_t *args = (thread_args_t *)arg;

    pthread_mutex_lock(&resource_semaphore);

    if (args->is_file) {
        if (mvMoveFileToDir(args->source, args->destination) == 0) {
        }
    } else {
        if (mvMoveDirToDir(args->source, args->destination) == 0) {
        }
    }
    pthread_mutex_unlock(&resource_semaphore);
    free(args);
    return NULL;
}

void process_stdin_to_linked_list(Node **head) {
    char buffer[BUFFER_SIZE];
    while (fgets(buffer, sizeof(buffer), stdin)) {
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0';
        }
        append_node(head, buffer);
    }
}

void parse_flags(int argc, char *argv[], int *non_flag_index) {
    int opt;
    while ((opt = getopt_long(argc, argv, "finvhb", long_options, NULL)) != -1) {
        switch (opt) {
            case 'f':
                option_force = 1;
            break;
            case 'i':
                option_interactive = 1;
            break;
            case 'n':
                option_no_clobber = 1;
            break;
            case 'v':
                option_verbose = 1;
            break;
            case 'b':
                option_backup = 1;
            break;
            case 'h':
                option_help = 1;
            break;
            case '?':
                default:
                    fprintf(stderr, "mv: illegal option\n");
            print_help();
            exit(1);
        }
    }

    *non_flag_index = optind;
}



int main(int argc, char *argv[]) {
    pthread_mutex_init(&resource_semaphore, NULL);

    int non_flag_index = -1;
    parse_flags(argc, argv, &non_flag_index);


    if (argc == 2 && option_help) {
        print_help();
        return 0;
    }


    if (argc == 2) {
        const char *destination = argv[1];
        Node *head = NULL;

        process_stdin_to_linked_list(&head);

        if (head == NULL) {
            fprintf(stderr, "No files provided via stdin.\n");
            return 1;
        }

        Node *current = head;
        pthread_t threads[BUFFER_SIZE];
        int thread_count = 0;

        while (current != NULL) {
            thread_args_t *args = malloc(sizeof(thread_args_t));
            if (!args) {
                fprintf(stderr, "Memory allocation failed.\n");
                free_list(head);
                return 1;
            }

            args->source = current->file_path;
            args->destination = destination;
            args->is_file = !is_file(current->file_path);

            if (pthread_create(&threads[thread_count], NULL, thread_function, (void *)args) != 0) {
                fprintf(stderr, "Error creating thread.\n");
                free(args);
                free_list(head);
                return 1;
            }

            current = current->next;
            thread_count++;
        }


        for (int i = 0; i < thread_count; i++) {
            pthread_join(threads[i], NULL);
        }

        free_list(head);
        pthread_mutex_destroy(&resource_semaphore);
        return 0;
    }



    if (argc < 3) {
        print_help();
        return 1;
    }


    if (non_flag_index == -1 || argc - non_flag_index < 2) {
        fprintf(stderr, "Error: Missing source or destination arguments.\n");
        return 1;
    }

    const char *source = argv[non_flag_index];
    const char *destination = argv[argc - 1];


    if (argc - non_flag_index > 2) {
        const char *destination = argv[argc - 1];
        Node *head = NULL;

        for (int i = non_flag_index; i < argc - 1; i++) {
            append_node(&head, argv[i]);
        }

        pthread_t threads[argc - non_flag_index - 1];
        int thread_count = 0;

        Node *current = head;
        while (current != NULL) {
            thread_args_t *args = malloc(sizeof(thread_args_t));
            if (!args) {
                fprintf(stderr, "Memory allocation failed.\n");
                free_list(head);
                return 1;
            }

            args->source = current->file_path;
            args->destination = destination;
            args->is_file = !is_file(current->file_path);

            if (pthread_create(&threads[thread_count], NULL, thread_function, (void *)args) != 0) {
                fprintf(stderr, "Error creating thread.\n");
                free(args);
                free_list(head);
                return 1;
            }

            current = current->next;
            thread_count++;
        }

        for (int i = 0; i < thread_count; i++) {
            pthread_join(threads[i], NULL);
        }

        free_list(head);
        return 0;
    } else {

        int source_is_file = !is_file(source);
        int destination_is_file = !is_file(destination);

        if (source_is_file && destination_is_file) {
            if (mvRenameFile(source, destination) == 0) {
            }

        }
        else if (!source_is_file && !destination_is_file) {
            if (file_exists(destination)) {
                if (mvMoveDirToDir(source, destination) == 0) {
                }

            } else {
                if (mvRenameDir(source, destination) == 0) {
                }
            }

        }
        else if (source_is_file && !destination_is_file) {
            if (mvMoveFileToDir(source, destination) == 0) {
            } }

        pthread_mutex_destroy(&resource_semaphore);
        return 0;
    }
}
