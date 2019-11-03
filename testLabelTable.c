 /*
 * Test Driver to test the functions to access and manipulate a label table.
 * It includes the following tests:
 *
 *         
 * Author:  Azra Ahmad 
 *        with assistance from: Younsukh Koh
 *
 * Creation Date:  Creation_Date
 *        modified: Modification_Date        reason
 *        modified: Modification_Date        reason
 * 
 */

#include "assembler.h"

const int SAME = 0;		/* useful for making strcmp readable */
                                /* e.g., if (strcmp (str1, str2) == SAME) */

static int process_debug_choice(int argc, char * argv[]);
static void testSearch(LabelTable * table, char * searchLabel);

int main(int argc, char * argv[])
{
    char * searchLabel;

   /* Create 2 tables, one static and one dynamic, for testing purposes */
    /* LabelEntry staticEntries[5];
    staticEntries[0].label = "Label1";
    staticEntries[0].address = 1000;
    LabelTable testTable1;      /* will be a table with static entries */
    /*LabelTable testTable2;      /* will be a table with dynamic entries */

    /* Initialize testTable1 with a static array of a given size. */
    /*testTable1.capacity = 5;
    testTable1.nbrLabels = 1;
    testTable1.entries = staticEntries;*/


    /* Can turn debugging on or off here (debug_on() or debug_off())
     * or on the command line (pass 1 for on; 0 for off).
     */
    process_debug_choice(argc, argv);


    LabelTable Table; //test table for test cases
    //print test cases
    printLabels(&Table);
    tableInit(&Table);
    printLabels(&Table);
    //addLabel cases
    addLabel(&Table, "Label1", 800);//add when empty
    addLabel(&Table, "Label2", 300);//
    addLabel(&Table, "Label3", 30000);// exceeds space limit
    addLabel(&Table, "Label4", 1000);//
    addLabel(&Table, "Label5", 8000);//exceeds space limit

    //Test cases for findLabel
    printLabels(&Table);
    testSearch(&Table, "Label2");
    testSearch(&Table, "Label3");
    testSearch(&Table, "Label4");
    testSearch(&Table, "Label17");
    testSearch(&Table, "Label15");
    testSearch(&Table, "Label19");

    /* Test printLabels and findLabel with static testTable1.
     * Use testSearch to test findLabel, for example:
     *      testSearch(&testTable, "Label1");
     * Examples of basic boundary testing:
     *     Set nbrLabels to 0 and test.
     *     Put four more entries in staticEntries, set nbrLabels to 5,
     *     and test.
     */






    /* Initialize testTable2 as a dynamic (changeable size) table. */
   // tableInit(&testTable2);

    /* Test printLabels and findLabel with dynamic testTable2. */




}

/*
 * The internal (static) process_debug_choice function parses the
 * command-line arguments for an optional choice (1 or 0) to turn all
 * debugging messages on or off.  The arguments passed to
 * process_debug_choice should be the same arguments that were passed to
 * the main function.  If the arguments were valid (no arguments passed,
 * or 0 or 1 passed as only argument), then this function returns 1; it
 * returns 0 if an invalid argument was passed in.
 *
 * A debugging choice argument of 0 or 1 indicates a choice to globally
 * turn debugging off or on, overriding any calls to debug_on,
 * debug_off, and debug_restore in the code.  0 means that no debugging
 * messages should be printed, 1 means that all debugging messages
 * should be printed.  If no debugging choice is specified, the
 * debug_print function will either print or not print messages
 * depending on the current debugging state set by the debug_on,
 * debug_off, and debug_restore functions.
 */
static int process_debug_choice(int argc, char * argv[])
{
    /* Process debugging choice and then decrement the argument count. */
    if ( argc > 1 )
    {
        if ( strcmp(argv[1], "0") == SAME )
        {
            debug_off();  override_debug_changes();
            argc--;
        }
        else if ( strcmp(argv[1], "1") == SAME )
        {
            debug_on();  override_debug_changes();
            argc--;
        }
    }

    /* The argument count should now be 1, either because there were no
     * arguments or because there was a 0 or 1 processed above, after
     * which we decremented the argument count (presumably from 2 to 1).
     */
    if ( argc > 1 )
    {
        printError("Usage:  %s [0|1]\n", argv[0]);
        return 0;
    }

    return 1;   /* Everything was OK! */
}

/*
 * testSearch tests the findLabel function, printing out the label being
 * searched for and either the address where it was found or, if it was
 * not found, an address of -1 and a message that the label was not in
 * the table.  
 *  @param  table        a pointer to the table through which to search
 *  @param  searchLabel  the label to search for
 */
static void testSearch(LabelTable * table, char * searchLabel)
{
    int address;

    printf("Looking for %s...\n", searchLabel);

    /* CODE MISSING !!! */
    address = -1;         /* bogus line, just to get it to compile */

    printf("\tthe address is %d.\n", address);
    if ( address == -1 )
        printf("\tThe label you're looking for does not exist.\n");
}