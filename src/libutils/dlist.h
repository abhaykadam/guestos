#ifndef __LIBUTILS_LIST_H
#define __LIBUTILS_LIST_H

#include <types.h>

/*
 * Simple doubly linked list implementation.
 *
 * Some of the internal functions ("__xxx") are useful when
 * manipulating whole lists rather than single entries, as
 * sometimes we already know the next/prev entries and we can
 * generate better code by using them directly rather than
 * using the generic single-entry routines.
 */

struct list_head {
	struct list_head *next, *prev;
};

#define LIST_HEAD_INIT(name) { &(name), &(name) }

#define LIST_HEAD(name) \
	struct list_head name = LIST_HEAD_INIT(name)

static inline void INIT_LIST_HEAD(struct list_head *list)
{
	list->next = list;
	list->prev = list;
}

/*
 * Insert a new entry between two known consecutive entries.
 *
 * This is only for internal list manipulation where we know
 * the prev/next entries already!
 */
static inline void __dlist_add(struct list_head *new,
			      struct list_head *prev,
			      struct list_head *next)
{
	next->prev = new;
	new->next = next;
	new->prev = prev;
	prev->next = new;
}

/**
 * dlist_add - add a new entry
 * @new: new entry to be added
 * @head: list head to add it after
 *
 * Insert a new entry after the specified head.
 * This is good for implementing stacks.
 */
static inline void dlist_add(struct list_head *new, struct list_head *head)
{
	__dlist_add(new, head, head->next);
}


/**
 * dlist_add_tail - add a new entry
 * @new: new entry to be added
 * @head: list head to add it before
 *
 * Insert a new entry before the specified head.
 * This is useful for implementing queues.
 */
static inline void dlist_add_tail(struct list_head *new, struct list_head *head)
{
	__dlist_add(new, head->prev, head);
}


/*
 * dlist_empty - tests whether list is empty
 * @head: the list to test
 */

static inline int dlist_empty(const struct list_head *head) {
	return head-> next == head;
}

/*
 * Delete a list entry by making the prev/next entries
 * point to each other.
 *
 * This is only for internal list manipulation where we know
 * the prev/next entries already!
 */
static inline void __dlist_del(struct list_head * prev, struct list_head * next) {
	next->prev = prev;
	prev->next = next;
}

/**
 * dlist_del - deletes entry from list.
 * @entry: the element to delete from the list.
 * Note: list_empty() on entry does not return true after this, the entry is
 * in an undefined state.
 */
static inline void __dlist_del_entry(struct list_head *entry) {
	__dlist_del(entry->prev, entry->next);
}

static inline void dlist_del(struct list_head *entry) {
	__dlist_del(entry->prev, entry->next);
}


/**
 * list_entry - get the struct for this entry
 * @ptr:        the &struct list_head pointer.
 * @type:       the type of the struct this is embedded in.
 * @member:     the name of the list_struct within the struct.
 */
#define dlist_entry(ptr, type, member) \
		container_of(ptr, type, member)

/**
 * dlist_for_each_entry  -       iterate over list of given type
 * @pos:        the type * to use as a loop cursor.
 * @head:       the head for your list.
 * @member:     the name of the list_struct within the struct.
 */
#define dlist_for_each_entry(pos, head, member)                          \
	for (pos = dlist_entry((head)->next, typeof(*pos), member);      \
		&pos->member != (head);    \
		pos = dlist_entry(pos->member.next, typeof(*pos), member))

#endif
