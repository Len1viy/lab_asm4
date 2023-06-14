#include "item.h"


Item* create_item(unsigned int value) {
    Item *item = calloc(1, sizeof(Item));
    item->info = value;
    return item;
}

void delete_item(Item* item) {
    free(item);
}
