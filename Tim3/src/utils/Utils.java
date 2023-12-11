package utils;

import java.util.ArrayList;
import java.util.List;

public class Utils {
    public static boolean isNumeric(String value){
        try {
            Long.parseLong(value);
            return true;
        } catch (NumberFormatException e) {
            return false;
        }
    }

    // greatest common divisor
    private static long calculateGcd(long a, long b) {
        while (b != 0) {
            long temp = b;
            b = a % b;
            a = temp;
        }
        return a;
    }

    // least common multiple
    private static long calculateLcm(long a, long b) {
        return (a * b) / calculateGcd(a, b);
    }

    // least common multiple of array
    public static long calculateLcmOfArray(long[] numbers) {
        if (numbers.length < 2) {
            throw new IllegalArgumentException("At least two numbers are required");
        }

        long lcm = calculateLcm(numbers[0], numbers[1]);

        for (int i = 2; i < numbers.length; i++) {
            lcm = calculateLcm(lcm, numbers[i]);
        }

        return lcm;
    }
    
    //https://stackoverflow.com/a/2942044/16302452
    public static <T> List<List<T>> transpose(List<List<T>> table) {
        List<List<T>> ret = new ArrayList<List<T>>();
        final int N = table.get(0).size();
        for (int i = 0; i < N; i++) {
            List<T> col = new ArrayList<T>();
            for (List<T> row : table) {
                col.add(row.get(i));
            }
            ret.add(col);
        }
        return ret;
    }

}
