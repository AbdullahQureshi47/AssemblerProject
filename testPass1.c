/*
 * This is a driver to test pass1 and the Label Table functions.  It
 * reads its input from a file if a filename has been passed as a
 * command-line argument, or from the standard input otherwise.  It
 * constructs a table of instruction labels and addresses from the
 * input, where a label's address is determined by the address of its
 * instruction.  Instructions are assumed to be 4 bytes long, with the
 * first instruction starting at address 0.  Labels that appear anywhere
 * but at the beginning of a line are ignored.
 * For example, the following two lines of code would result in a table
 * with one entry, indicating that label A_LABEL is at address 4.
 *              add $t1, $t1, $t1   # This instruction is at address 0
 *    A_LABEL:  slt $t0, $t1, $t2   # This instruction is at address 4
 *              bne $t0, $zero, A_LABEL  # This instr. is at address 8
 *
 * USAGE:
 *      name [ filename ] [ 0|1 ]
 * where "name" is the name of the executable, "filename" is an optional
 * file containing the input to read, and " 0" or "1" specifies that
 * debugging should be turned off or on, respectively, regardless of any
 * calls to debug_on, debug_off, or debug_restore in the program.  Both
 * arguments are optional; if both are present they may appear in either
 * order.  If no filename is provided, the program reads its input from
 * stdin.  If no debugging choice is provided, the program prints
 * debugging messages, or not, depending on indications in the code.
 *
 * INPUT:
 * This program expects the input to consist of lines of MIPS
 * instructions, each of which may (or may not) contain a label at the
 * beginning of the line.  The input should have one MIPS instruction on
 * each line.  Labels should appear as the first token in the line,
 * followed immediately by a colon.  Labels may also appear elsewhere
 * in an instruction, but those labels are ignored by this program.
 *
 * OUTPUT:
 * The program prints the contents of the label table it has
 * constructed.  For the example above, the output might look like:
 *      Label: A_LABEL   Address: 4
 * (The actual formatting depends on the implementation of the
 * printLabels function in LabelTable.c.)
 *
 * ERROR CONDITIONS:
 * It is an error for the input to contain multiple instructions with
 * the same label at the beginning of the line.
 *
 * Author: Alyce Brady and Abdullah Qureshi
 * Date: 2/18/99
 *
 * Modified by:  Alyce Brady, 6/10/2014
 *      Allow filename to be passed as a parameter.
 * Modified by:  Alyce Brady, 5/25/2015
 *      Support use of printErr and printDebug functions.
 *      Improve function documentation.
 */

 #include "assembler.h"

const int SAME = 0;		/* useful for making strcmp readable */
                                /* e.g., if (strcmp (str1, str2) == SAME) */

static FILE * process_arguments(int argc, char * argv[]);

int main (int argc, char * argv[])
{
    FILE * fptr;               /* file pointer */
    LabelTable table;
    const char * ERROR1 = "Error: Cannot open file %s.\n";

    /* Process command-line arguments (if any). */
    fptr = process_arguments(argc, argv);
    if ( fptr == NULL )
    {
        return 1;   /* Fatal error when processing arguments */
    }

    /* Can turn debugging on or off here (debug_on() or debug_off())
     * or on the command line (pass 1 for on; 0 for off).
     */
    debug_on();

    /* Call pass1 to generate the label table. */
    table = pass1 (fptr);
    rewind (fptr);

    pass2(fptr,table);
    //rewind(fptr);

    if ( debug_is_on() )
        printLabels (&table);

    (void) fclose(fptr);
    return 0;
}

static FILE * process_arguments(int argc, char * argv[])
{
    FILE * fptr;               /* file pointer */

    /* Implementation notes:
     * The arguments are both optional and may be provided in either
     * order, which makes the logic more complicated.  This function
     * processes the debugging choice first, if one was specified, then
     * "erases" it from the argument list so that when we come to process
     * the filename we can assume that it is the first and only argument
     * (if provided at all).  If two arguments are provided but neither
     * is a debugging choice, or if more than two arguments are provided,
     * then a usage error message is printed.
     * The valid combinations are:
     *   program               no arguments are provided
     *   program 0|1           process debugging choice and decrement
     *                         argc so it looks like there were no arguments
     *   program filename      no debugging choice; process filename
     *   program 0|1 filename  process debugging choice and shift
     *                         filename into first argument; now it looks
     *                         like there was just one argument, filename
     *   program filename 0|1  process debugging choice and decrement
     *                         argc; now it looks like there was just
     *                         one argument, filename
     */

    if ( argc > 1 )
    {
        if ( strcmp(argv[1], "0") == SAME )
        {
            debug_off();  override_debug_changes();
            /* Done processing; move filename down (if it's there). */
            argv[1] = argc > 2 ? argv[2] : argv[1];
            argc--;
        }
        else if ( strcmp(argv[1], "1") == SAME )
        {
            debug_on();  override_debug_changes();
            /* Done processing; move filename down (if it's there). */
            argv[1] = argc > 2 ? argv[2] : argv[1];
            argc--;
        }
        else if ( argc > 2 && strcmp(argv[2], "0") == SAME )
        {
            debug_off();  override_debug_changes();
            argc--;
        }
        else if ( argc > 2 && strcmp(argv[2], "1") == SAME )
        {
            debug_on();  override_debug_changes();
            argc--;
        }
    }


    if ( argc > 2 )
    {
        printError("Usage:  %s [filename] [0|1]\n", argv[0]);
        return 0;
    }

    /* Process the filename, if one was passed in. */
    if ( argc > 1 )
    {
        /* Open the file for reading */
        if ((fptr = fopen (argv[1], "r")) == NULL)
        {
            printError("Error: Cannot open file %s.\n", argv[1]);
            return NULL;
        }
    }
    else  /* No file passed in; use standard input. */
        fptr = stdin;

    return fptr;   /* Everything was OK! */
}
