package com.company;

import java.util.Arrays;
import java.util.List;

/**
 * A single row of a database.
 *
 * @author Tim Chan
 */
class Row {
    /**
     * A Row whose column values are DATA. The array DATA must not be altered
     * subsequently.
     */
    Row(String[] data) {
        _data = data;
    }

    /**
     * Return a Row formed from the current values of COLUMNS (in order).
     * COLUMNS must all have been resolved to non-empty TableIterators.
     */
    static Row make(List<Column> columns) {
        int columnSize = columns.size();
        String[] result = new String[columnSize];
        for (int i = 0; i < columnSize; i++) {
            result[i] = columns.get(i).value();
        }
        return new Row(result);
    }

    /**
     * A Row whose column values are extracted by COLUMNS from ROWS (see
     * {@link db61b.Column#Column}).
     */
    Row(List<Column> columns) {
        int columnSize = columns.size();
        String[] result = new String[columnSize];
        for (int i = 0; i < columnSize; i++) {
            result[i] = columns.get(i).value();
        }
        _data = result;
    }

    /** Return my number of columns. */
    int size() {
        return _data.length;
    }

    /** Return the value of my Kth column. Requires that 0 <= K < size(). */
    String get(int k) {
        return _data[k];
    }

    /**
     * Print Row (an array) into comma-ed String e.g.:.
     * 101,Knowles,Jason,F,2003,EECS
     *
     * @return String
     *
     */
    public String toCommaString() {
        String result = Arrays.toString(_data);
        if (_data.length == 0) {
            return "";
        }
        return result.replaceAll("^\\[|\\]$", "").replaceAll(", ", ",");
    }

    @Override
    /** Print method for Row, built upon toString */
    public String toString() {
        String result = Arrays.toString(_data);
        if (_data.length == 0) {
            return "";
        }
        return result.replaceAll("^\\[|\\]$", "").replaceAll(",", "");
    }

    @Override
    public boolean equals(Object obj) {
        try {
            return Arrays.equals(_data, ((Row) obj)._data);
        } catch (ClassCastException e) {
            return false;
        }
    }

    /*
     * NOTE: Whenever you override the .equals() method for a class, you should
     * also override hashCode so as to insure that if two objects are supposed
     * to be equal, they also return the same .hashCode() value (the converse
     * need not be true: unequal objects MAY also return the same .hashCode()).
     * The hash code is used by certain Java library classes to expedite
     * searches (see Chapter 7 of Data Structures (Into Java)).
     */

    @Override
    public int hashCode() {
        return Arrays.hashCode(_data);
    }

    /** Contents of this row. */
    private String[] _data;
}
