import java.util.List;

import utils.InputFile;

public class D01 {
    static String wordToNumeric(String word){
        if (word.equals("one")) return "1";
        if (word.equals("two")) return "2";
        if (word.equals("six")) return "6";
        if (word.equals("four")) return "4";
        if (word.equals("five")) return "5";
        if (word.equals("nine")) return "9";
        if (word.equals("three")) return "3";
        if (word.equals("seven")) return "7";
        if (word.equals("eight")) return "8";
        return "";
    }
    static String checkStart(String str){
        String result = "";
        String sub;
        if (str.length() >= 3) {
            sub = str.substring(0, 3);
            result += wordToNumeric(sub);
        }
        if (str.length() >= 4){
            sub = str.substring(0, 4);
            result += wordToNumeric(sub);
        }
        if (str.length() >= 5){
            sub = str.substring(0, 5);
            result += wordToNumeric(sub);
        }
        return result;
    }
    public static void main(String[] args){
        List<String> raw = InputFile.readFile("./Tim3/src/input/01.txt");
        int sum = 0;
        for (String line : raw) {
            String numeric = "";
            for (int i = 0; i < line.length(); i++) {
                char chr = line.charAt(i);
                if (Character.isDigit(chr)) numeric += chr;
            }
            int number = Integer.parseInt("" + numeric.charAt(0) + numeric.charAt(numeric.length()-1)); //WTF JAVA WTF
            //System.out.println(numeric + " " + number);
            sum += number;
        }
        System.out.println("Part 1: " + sum);

        sum = 0;
        for (String line : raw) {
            String numeric = "";
            for (int i = 0; i < line.length(); i++) {
                char chr = line.charAt(i);
                if (Character.isDigit(chr)) numeric += chr;
                numeric += checkStart(line.substring(i));
            }
            int number = Integer.parseInt("" + numeric.charAt(0) + numeric.charAt(numeric.length()-1)); //WTF JAVA WTF
            sum += number;
        }
        System.out.println("Part 2: " + sum);
    }
}
