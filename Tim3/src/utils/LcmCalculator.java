package utils;

public class LcmCalculator {

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
}

