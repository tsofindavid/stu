#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// NEMENIT, inak vas kod neprejde testom !!!
#include "data.h"

#define MAX_SLOTS 2

#define MIN_UNITS 1
#define MAX_UNITS 5

ITEM** items = NULL;
int item_pos = -1;
int item_atr = 0;

UNIT* army_1 = NULL;
int army_1_pos = -1;

UNIT* army_2 = NULL;
int army_2_pos = -1;

void formatLine(char line[MAX_LINE + 1], char result[MAX_LINE + 1]) {
    int resultSize = 0;
    int openQuote = 0;

    for (int i = 0; i < strnlen(line, MAX_LINE); i++) {
        if (line[i] == '"' && openQuote == 1) {
            openQuote = 0;
        }

        if (line[i] == '"' && openQuote == 0) {
            openQuote = 1;
        }

        if (isspace(line[i]) && openQuote == 0) {
            continue;
        }

        result[resultSize] = line[i];
        resultSize += 1;
    }

    result[resultSize] = '\0';
}

int parseKey(char* line, char* key) {
    int keySize = 0;
    int openQuote = 0;

    for (int i = 0; i < strnlen(line, MAX_LINE + 1); i++) {
        if (line[i] == '"' && openQuote == 0) {
            openQuote = 1;
            continue;
        }

        if (line[i] == '"' && openQuote == 1) {
            break;
        }

        if (openQuote == 1) {
            key[keySize] = line[i];
            key++;
        }
    }

    key[keySize] = '\0';
    return 0;
}

int parseSting(char* line, char* value) {
    int strSize = 0;
    int openQuote = 0;
    int afterColon = 0;

    for (int i = 0; i < strnlen(line, MAX_LINE + 1); i++) {
        if (line[i] == ':') {
            afterColon = 1;
            continue;
        }

        if (afterColon == 0) {
            continue;
        }

        if (line[i] == '"' && openQuote == 0) {
            openQuote = 1;
            continue;
        }

        if (line[i] == '"' && openQuote == 1) {
            break;
        }

        if (openQuote == 1) {
            value[strSize] = line[i];
            strSize++;
            continue;
        }
    }

    if (strSize == 0) {
        fprintf(stderr, "%s\n", ERR_MISSING_VALUE);

        return 1;
    }

    value[strSize] = '\0';
    return 0;
}
int parseInt(char* line, int* value) {
    char strValue[MAX_LINE + 1];
    int strSize = 0;
    int afterColon = 0;

    for (int i = 0; i < strnlen(line, MAX_LINE + 1); i++) {
        if (line[i] == ':') {
            afterColon = 1;
            continue;
        }

        if (afterColon == 0) {
            continue;
        }

        if (isdigit(line[i])) {
            strValue[strSize] = line[i];
            strSize++;
        }

        if (isalpha(line[i])) {
            fprintf(stderr, "%s\n", ERR_BAD_VALUE);
            return 1;
        }
    }

    if (strSize == 0) {
        fprintf(stderr, "%s\n", ERR_MISSING_VALUE);
        return 1;
    }

    strValue[strSize] = '\0';
    *value = atoi(strValue);
    return 0;
}

int readLine(char line[MAX_LINE + 1]) {
    char key[MAX_NAME + 1];
    char strValue[MAX_NAME + 1];
    int intValue;

    char formattedLine[MAX_LINE + 1];
    formatLine(line, formattedLine);

    if (parseKey(line, key) == 1) {
        return 1;
    }

    if (strcmp(key, "name") == 0) {
        if (parseSting(line, strValue) == 1) {
            return 1;
        }

        strncpy(items[item_pos]->name, strValue, MAX_NAME + 1);
        item_atr++;
    } else if (strcmp(key, "att") == 0) {
        if (parseInt(line, &intValue) == 1) {
            return 1;
        }
        items[item_pos]->att = intValue;
        item_atr++;
    } else if (strcmp(key, "def") == 0) {
        if (parseInt(line, &intValue) == 1) {
            return 1;
        }
        items[item_pos]->def = intValue;
        item_atr++;
    } else if (strcmp(key, "slots") == 0) {
        if (parseInt(line, &intValue) == 1) {
            return 1;
        }
        items[item_pos]->slots = intValue;
        item_atr++;
    } else if (strcmp(key, "range") == 0) {
        if (parseInt(line, &intValue) == 1) {
            return 1;
        }
        items[item_pos]->range = intValue;
        item_atr++;
    } else if (strcmp(key, "radius") == 0) {
        if (parseInt(line, &intValue) == 1) {
            return 1;
        }
        items[item_pos]->radius = intValue;
        item_atr++;
    }

    return 0;
}

int parseItems() {
    FILE* file = fopen(ITEMS_FILE, "r");
    if (!file) {
        fprintf(stderr, "%s\n", ERR_FILE);
        return 1;
    }

    char ch;
    char line[MAX_LINE + 1];
    int lineSize = 0;

    while ((ch = fgetc(file)) != EOF) {
        if (ch == '[' || ch == ']') {
            continue;
        }

        if (ch == '{') {
            items = realloc(items, (item_pos + 2) * sizeof(ITEM*));
            items[item_pos + 1] = calloc(1, sizeof(ITEM));
            item_pos++;
            item_atr = 0;

            continue;
        }

        if (ch == '}') {
            if (readLine(line) == 1) {
                return 1;
            }

            if (item_atr != 6) {
                fprintf(stderr, "%s\n", ERR_MISSING_ATTRIBUTE);
                return 1;
            }
            continue;
        }

        if (ch == '\n') {
            continue;
        }

        if (ch == ',') {
            line[lineSize] = '\0';
            lineSize += 1;
            if (readLine(line) == 1) {
                return 1;
            }
        } else {
            line[lineSize] = ch;
            lineSize += 1;
            continue;
        }

        memset(line, 0, sizeof(line));
        lineSize = 0;
    }

    fclose(file);
    return 0;
}

void printItems() {
    for (int i = 0; i < item_pos + 1; i++) {
        printf("Name: %s\nAttack: %d\nDefense: %d\nSlots: %d\nRange: %d\nRadius: %d\n\n",
               items[i]->name, items[i]->att, items[i]->def, items[i]->slots, items[i]->range,
               items[i]->radius);
    }
}

ITEM* findItem(char* name) {
    for (int i = 0; i < item_pos + 1; i++) {
        if (strncmp(items[i]->name, name, MAX_NAME + 1) == 0) {
            return items[i];
        }
    }

    return NULL;
}

int parsArmy(char* path, UNIT*** army, int* army_pos) {
    char line[MAX_LINE + 1];
    FILE* file = fopen(path, "r");
    if (!file) {
        fprintf(stderr, "%s\n", ERR_FILE);
        return 1;
    }

    fgets(line, sizeof(line), file);
    int units = atoi(line);

    if (units < MIN_UNITS || units > MAX_UNITS) {
        fprintf(stderr, "%s\n", ERR_UNIT_COUNT);
        return 1;
    }

    char unitName[MAX_NAME + 1];
    char item1[MAX_NAME + 1];
    char item2[MAX_NAME + 1];
    char item3[MAX_NAME + 1];

    for (int i = 0; i < units; i++) {
        fgets(line, sizeof(line), file);

        int scan = sscanf(line, "%s %s %s %s", unitName, item1, item2, item3);

        if (scan != 2 && scan != 3) {
            fprintf(stderr, "%s\n", ERR_ITEM_COUNT);
            return 1;
        }

        *army = realloc(*army, (*army_pos + 2) * sizeof(UNIT*));
        (*army_pos)++;

        (*army)[(*army_pos)] = calloc(1, sizeof(UNIT));
        (*army)[(*army_pos)]->item1 = NULL;
        (*army)[(*army_pos)]->item2 = NULL;

        (*army)[(*army_pos)]->hp = 100;
        strncpy((*army)[(*army_pos)]->name, unitName, MAX_NAME + 1);

        if (scan == 2 || scan == 3) {
            (*army)[(*army_pos)]->item1 = findItem(item1);

            if (!(*army)[(*army_pos)]->item1) {
                fprintf(stderr, "%s\n", ERR_WRONG_ITEM);
                return 1;
            }
        }

        if (scan == 3) {
            (*army)[(*army_pos)]->item2 = findItem(item2);

            if (!(*army)[(*army_pos)]->item2) {
                fprintf(stderr, "%s\n", ERR_WRONG_ITEM);
                return 1;
            }
        }

        int slots = 0;
        if ((*army)[(*army_pos)]->item1 != NULL && (*army)[(*army_pos)]->item2 != NULL) {
            slots = (*army)[(*army_pos)]->item1->slots + (*army)[(*army_pos)]->item2->slots;
        } else if ((*army)[(*army_pos)]->item1 != NULL) {
            slots = (*army)[(*army_pos)]->item1->slots;
        } else if ((*army)[(*army_pos)]->item2 != NULL) {
            slots = (*army)[(*army_pos)]->item2->slots;
        }

        if (slots > MAX_SLOTS) {
            fprintf(stderr, "%s\n", ERR_SLOTS);
            return 1;
        }
    }

    fclose(file);
    return 0;
}

void printArmy(int prefix, UNIT*** army, int* army_pos) {
    printf("Army %d\n", prefix);

    for (int i = 0; i < (*army_pos) + 1; i++) {
        printf("    Unit: %d\n", i);
        printf("    Name: %s\n", (*army)[i]->name);
        printf("    HP: %d\n", (*army)[i]->hp);

        if ((*army)[i]->item1 != NULL) {
            printf("    Item 1: %s,%d,%d,%d,%d,%d\n", (*army)[i]->item1->name,
                   (*army)[i]->item1->att, (*army)[i]->item1->def, (*army)[i]->item1->slots,
                   (*army)[i]->item1->range, (*army)[i]->item1->radius);
        }

        if ((*army)[i]->item2 != NULL) {
            printf("    Item 2: %s,%d,%d,%d,%d,%d\n", (*army)[i]->item2->name,
                   (*army)[i]->item2->att, (*army)[i]->item2->def, (*army)[i]->item2->slots,
                   (*army)[i]->item2->range, (*army)[i]->item2->radius);
        }

        printf("\n");
    }
}

int main(const int argc, char* argv[]) {
    if (argc == 1) {
        if (parseItems() == 1) {
            return 0;
        }

        printItems();
        return 0;
    }

    if (argc == 3) {
        parseItems();

        if (parsArmy(argv[1], &army_1, &army_1_pos) == 1) {
            return 0;
        }

        if (parsArmy(argv[2], &army_2, &army_2_pos) == 1) {
            return 0;
        }

        printArmy(1, &army_1, &army_1_pos);
        printArmy(2, &army_2, &army_2_pos);

        return 0;
    }

    fprintf(stderr, "%s\n", ERR_CMD);

    return 0;
}
