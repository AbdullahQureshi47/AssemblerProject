/*
 * Label Table: functions to access and manipulate a label table
 *
 * This file provides the definitions of a set of functions for
 * creating, maintaining, and using a table of assembly language
 * instruction labels and the memory addresses associated with them.
 *
 * Author: Alyce Brady and Azra Ahmad with assistance from Younsukh Koh
 *
 * Creation Date:   2/16/99
 *   Modified:  12/20/2000   Updated postcondition information.
 *   Modified:  4/19/2013    Modernized call to fprintf for errors.
 *   Modified:  5/25/2015    Updated to use printError function.
 *
 * WARNING: These functions are incomplete!!!!!
*/

#include "assembler.h"

// internal global variables (global to this file only)
static const char * ERROR0 = "Error: no label table exists.\n";
static const char * ERROR1 = "Error: a duplicate label was found.\n";
static const char * ERROR2 = "Error: cannot allocate space in memory.\n";

// internal function (visible to this file only)
static int verifyTableExists(LabelTable * table);

void tableInit (LabelTable * table)
  /* Postcondition: table is initialized to indicate that there
   *       are no label entries in it.
   */
{
        /* verify that current table exists */
        if ( ! verifyTableExists (table) )
            return;           /* fatal error: table doesn't exist */

        table->nbrLabels=0;
        table->capacity=0;
        table->entries=NULL;
        if (table->nbrLabels == 0 && table->capacity == 0 && table->entries == NULL)
      printDebug("Table Successfully initialized. \n");
  else
      printDebug("Table initialization failed. \n");
}

void printLabels (LabelTable * table)
  /* Postcondition: all the labels in the table, with their
   *      associated addresses, have been printed to the standard
   *      output.
   */
{

        //labels for table numbers
        int t= table->nbrLabels;

        if ( table == NULL )
            (void) printf ("Label Table is a NULL pointer.\n");
        else if ( t == 0)
        {
            printf ("There are labels in the table:\n");
          }
        else
        {
            //variable i
            int i;
            //capacity of the table
            int c = table->capacity;
            printf("There are %d labels in the table with a capacity of %d. \n", t, c);

            LabelEntry * entries; //table entries
              //this if statements checks to make sure there is enough memory for
            //the entries
            if((entries = malloc(t * sizeof(LabelEntry))) ==NULL)
            {
              printError("%s", ERROR2);
              return;
            }

          entries = table->entries;
          //character for entry label
          char * l;
          //integer for entry address
          int a;
          for(i=0; i<t; i++)
            {
              l = entries[i].label;
              a = entries[i].address;
              printf("%d. Label Value: %s, Label Address: %d \n", i, l, a);

            }
       }
}

int findLabel (LabelTable * table, char * label)
  /* Returns the address associated with the label; -1 if label is
   *      not in the table or table doesn't exist
   */
{

  if(table == NULL)
  {
    printf("Table is a NULL pointer. \n");
    return -1;
  }
  else
  {
    LabelEntry * entries;
    entries = table->entries;

    int i;
    char * l;
    int index=table->nbrLabels;
    for(i = 0; i<index; i++)
    {
      l = entries[i].label;

      if (strcmp(label,l)==1)
      {
        //return address
        printf("%s", label);
        return entries[i].address;
      }
    }

    return -1; //if couldnt find the item

  }

}

int addLabel (LabelTable *table, char * label, int PC)
  /* Postcondition: if label was already in table, the table is
   *      unchanged; otherwise a new entry has been added to the
   *      table with the specified label name and instruction address
   *      (memory location) and the table has been resized if necessary.
   * Returns 1 if no fatal errors occurred; 0 if memory allocation error
   *      or table doesn't exist.
   */
{
        char * labelDuplicate;

        /* verify that current table exists */
        if ( ! verifyTableExists (table) )
            return 0;           /* fatal error: table doesn't exist */

        /* Was the label already in the table? */
        if ( findLabel(table, label) != -1)
        {
            /* This is an error (ERROR1), but not a fatal one.
             * Report error; don't add the label to the table again.
             */

    //(void) fprintf(stderr, ERROR1);
          printError("%s", ERROR1);
          return 1;
        }

        /* Create a dynamically allocated version of label that will persist. */
        /*   NOTE: on some machines you may need to make this _strdup !  */
        if ((labelDuplicate = strdup (label)) == NULL)
        {
            printError ("%s", ERROR2);
            return 0;           /* fatal error: couldn't allocate memory */
        }

        /* Resize the table if necessary. */
        if ( table->nbrLabels >= table->capacity )
        {
            /* CODE MISSING ! */
            /* Tip:  Choose a new size that will work even if current
             *       capacity is 0.
             */
          if(table->capacity != 0)
          {
            tableResize(table, (table -> capacity)*2); // Double the existing size
          }

          else if(table->capacity == 0)
          {
            tableResize(table, (table->capacity)+1); //Incrementing the size by 1
          }
        }



        /* Add the label */

      table->entries[table->nbrLabels].label = labelDuplicate;
      table->entries[table->nbrLabels].address = PC;
      table->nbrLabels++;

        return 1;               /* everything worked great! */
}

int tableResize (LabelTable * table, int newSize)
  /* Postcondition: table now has the capacity to hold newSize
   *      label entries.  If the new size is smaller than the
   *      old size, the table is truncated after the first
   *      newSize entries.
   * Returns 1 if everything went OK; 0 if memory allocation error
   *      or table doesn't exist.
   */
{
        char *       ptr;               /* points to any byte in memory */
        LabelEntry * newEntryList;
        int          smaller;

        /* verify that current table exists */
        if ( ! verifyTableExists (table) )
            return 0;           /* fatal error: table doesn't exist */

        /* create a new internal table of the specified size */
        if ((newEntryList = malloc (newSize * sizeof(LabelEntry))) == NULL)
        {
            printError ("%s", ERROR2);
            return 0;           /* fatal error: couldn't allocate memory */
        }

        if ( table->entries )           /* if there were entries */
        {
            /* move contents of internal table to new internal table */
            smaller = table->nbrLabels < newSize ? table->nbrLabels : newSize;
            (void) memcpy (newEntryList, table->entries,
                           smaller * sizeof(LabelEntry));

            /* free the space taken up by the old internal table */
            free (table->entries);
            table->nbrLabels = smaller;
        }

        table->entries = newEntryList;
        table->capacity = newSize;
        return 1;
}

static int verifyTableExists(LabelTable * table)
 /* Returns true (1) if table exists; prints an error and returns
  * false (0) otherwise.
  */
{
        /* verify that current table exists */
        if ( ! table )
        {
            printError ("%s", ERROR0);
            return 0;
        }

        return 1;
}
