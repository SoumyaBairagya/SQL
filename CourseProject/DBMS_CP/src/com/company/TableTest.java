/** Tests basics functionality including:
 * The Table class
 */
package com.company;

import org.junit.Test;

import static org.junit.Assert.*;

public class TableTest {

    /**
     * test readTable() Test loading a db file and reading it.
     */
    @Test
    public void testReadTable() {
        Table.readTable("students").print();
    }

    /**
     * test writeTable() Test writing into a db file and reading it.
     */
    @Test
    public void testWriteTable() {
        Table testTable = Table.readTable("students");
        testTable.writeTable("blank");
    }

    public static void main(String[] args) {
        System.exit(ucb.junit.textui.runClasses(TableTest.class));
    }

}
